#include <stdio.h>

int main() {
    double distance;
    int is_surge;
    double base_fare = 0.0;
    double final_fare = 0.0;
    double surcharge_amount = 0.0;

    printf("=== HỆ THỐNG TÍNH CƯỚC GRABRIDE ===\n");
    printf("Nhap khoang cach di chuyen (km): ");
    if (scanf("%lf", &distance) != 1) {
        printf("Loi: Du lieu nhap vao khong hop le!\n");
        return 1;
    }

    if (distance <= 0) {
        printf("Loi: Khoang cach di chuyen phai lon hon 0 km. Tu choi xu ly!\n");
        return 1;
    }

    printf(
        "Nhap trang thai phu phi (1: Troi mua hoac gio cao điểm, 0: Binh'
      ' thuong): "
    );
    if (scanf("%d", &is_surge) != 1) {
        printf("Loi: Trang thai phu phi khong hop le!\n");
        return 1;
    }

    if (distance <= 2.0) {
        base_fare = 12000.0;
    } else {
        base_fare = 12000.0 + (distance - 2.0) * 4500.0;
    }

    final_fare = base_fare;

    if (is_surge == 1) {
        final_fare = base_fare * 1.2;
        surcharge_amount = final_fare - base_fare;
    }

    printf("\n--- CHI TIET HOA ĐƠN CHUYẾN ĐI ---\n");
    printf("Khoang cach di chuyen: %.2f km\n", distance);
    printf("Cuoc co ban: %.0f VNĐ\n", base_fare);
    if (is_surge == 1) {
        printf("Phu phi (1.2x): %.0f VNĐ\n", surcharge_amount);
    } else {
        printf("Phu phi: 0 VNĐ\n");
    }
    printf("Tong chi phi thanh toan: %.0f VNĐ\n", final_fare);
    printf("-----------------------------------\n");

    return 0;
}
