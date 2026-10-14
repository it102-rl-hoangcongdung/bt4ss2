# BÁO CÁO BÀI TẬP 04: THIẾT KẾ KIẾN TRÚC DYNAMIC PRICING ENGINE CHO GRABRIDE

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Activity Diagram)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt4.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu]) --> Input[Nhập khoảng cách km và trạng thái phụ phí]
  Input --> CheckValid{Khoảng cách > 0?}
  CheckValid -- Không hợp lệ <= 0 --> Error[Thông báo lỗi khoảng cách không hợp lệ] --> EndFail([Kết thúc: Từ chối xử lý])
  CheckValid -- Hợp lệ > 0 --> CheckDist{Khoảng cách <= 2 km?}
  CheckDist -- Đúng <= 2 km --> BaseFare[Cước cơ bản = 12.000 VNĐ]
  CheckDist -- Lớn hơn 2 km --> CalcKm[Cước cơ bản = 12.000 + (km - 2) * 4.500]
  BaseFare --> CheckSurge{Trời mưa hoặc giờ cao điểm?}
  CalcKm --> CheckSurge
  CheckSurge -- Có: Phụ phí 1.2x --> ApplySurge[Tổng cước = Cước cơ bản * 1.2]
  CheckSurge -- Không: Không phụ phí --> KeepFare[Tổng cước = Cước cơ bản]
  ApplySurge --> Output[In chi tiết hóa đơn: Cước cơ bản, Phụ phí, Tổng tiền]
  KeepFare --> Output
  Output --> EndSuccess([Kết thúc: Hoàn tất chuyến đi])
```

---

## 1. Mục tiêu và Phân tích Nghiệp vụ

Bài tập này yêu cầu xây dựng một phân hệ tính cước tự động (Trip Fare Module) cho nền tảng GrabRide nhằm giải quyết bài toán minh bạch chi phí cho cả hành khách và tài xế.

Hệ thống cần tiếp nhận hai thông số đầu vào chính gồm khoảng cách di chuyển thực tế tính bằng km (kiểu dữ liệu double) và trạng thái phụ phí gồm trời mưa hoặc giờ cao điểm (kiểu dữ liệu int dùng làm cờ hiệu).

- Giá mở cửa cố định: 12.000 VNĐ áp dụng cho 2 km đầu tiên.
- Cước phí bổ sung: 4.500 VNĐ cho mỗi km tiếp theo từ km thứ 3 trở đi.
- Hệ số phụ phí: Nhân hệ số 1.2x (tăng 20%) khi có điều kiện thời tiết xấu hoặc giờ cao điểm.
- Kiểm tra toàn vẹn dữ liệu: Từ chối xử lý ngay lập tức nếu khoảng cách nhập vào nhỏ hơn hoặc bằng 0 km.

## 2. Phân tích Luồng Dữ liệu và Xử lý Lỗi Logic (Data Flow)

Luồng dữ liệu trong mô-đun được thiết kế đi tuần tự từ khâu tiếp nhận thông tin, kiểm tra tính hợp lệ đến bước phân rẽ nhánh tính toán cước cơ bản và áp dụng hệ số nhân phụ phí.

Việc tách bạch rõ ràng giữa tầng kiểm tra dữ liệu đầu vào và tầng tính toán giúp mã nguồn tường minh, dễ bảo trì và hạn chế tối đa sai sót logic tài chính.

- Kiểm tra điều kiện biên: Khoảng cách <= 0 được bắt lại ngay từ đầu để tránh lỗi chia cho không hoặc tính cước âm.
- Phân rẽ nhánh khoảng cách: Sử dụng cấu trúc rẽ nhánh if / else để phân tách rõ khoảng cách trong phạm vi 2 km đầu và khoảng cách vượt quá 2 km.
- Xử lý phụ phí minh bạch: Tách riêng bước tính cước cơ bản và bước nhân hệ số phụ phí 1.2x giúp in hóa đơn chi tiết từng thành phần tiền cước.

## 3. Bảng đặc tả chi tiết quy trình tính cước

Bảng dưới đây mô tả chi tiết từng bước thực thi của thuật toán trong chương trình C:

| Bước | Thành phần thực hiện | Hành động xử lý | Điều kiện và Kết quả |
| --- | --- | --- | --- |
| 1 | Hệ thống | Nhập liệu khoảng cách km và cờ phụ phí | Đọc giá trị từ bàn phím bằng hàm scanf |
| 2 | Kiểm tra dữ liệu | Kiểm tra điều kiện khoảng cách > 0 | Nếu <= 0: Thông báo lỗi và dừng chương trình |
| 3 | Kiểm tra khoảng cách | So sánh khoảng cách với mốc 2 km | Nếu <= 2: Gán cước cơ bản = 12.000 VNĐ |
| 4 | Tính cước km tiếp theo | Thực hiện phép tính cho quãng đường > 2 km | Cước = 12.000 + (km - 2) * 4.500 |
| 5 | Kiểm tra phụ phí | Kiểm tra cờ trạng thái mưa hoặc giờ cao điểm | Nếu đúng: Nhân tổng cước với hệ số 1.2 |
| 6 | Xuất hóa đơn | In chi tiết cước cơ bản, phụ phí và tổng tiền | Hiển thị rõ ràng ra giao diện dòng lệnh |

## 4. Đánh giá thiết kế và Hướng dẫn kiểm thử mã nguồn

Chương trình C được viết tuân thủ chuẩn ANSI C / C11, chỉ sử dụng các thư viện chuẩn tiêu chuẩn (<stdio.h>) và cấu trúc rẽ nhánh if / else theo đúng giới hạn yêu cầu của đề bài.

Mã nguồn đã được đẩy lên GitHub Organization tại repository 'it102-rl-hoangcongdung' với cấu trúc thư mục chuẩn xác trong thư mục 'grab_ride_fare_module'.

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt4.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt4.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `main.c`: Mã nguồn chương trình.
