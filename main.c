#include <stdio.h>
#include <stdlib.h>
#include "structs.h" 

// Khai báo sẵn các chức năng của hàm
void addTransaction();
void displayTransactions();
void searchTransaction();
void deleteTransaction();
void showStatistics();
void loadFromFile();
void saveToFile();

void showMenu() {
    printf("\n========================================\n");
    printf("      QUAN LY THU CHI CA NHAN\n");
    printf("========================================\n");
    printf("1. Them giao dich moi\n");
    printf("2. Hien thi danh sach giao dich\n");
    printf("3. Tim kiem giao dich\n");
    printf("4. Xoa giao dich\n");
    printf("5. Thong ke tong hop\n");
    printf("6. Luu va Thoat\n");
    printf("========================================\n");
    printf("Chon chuc nang (1-6): ");
}

int main() {
    int choice;


    do {
        showMenu();
        // Kiểm tra xem người dùng có nhập đúng là một số hay không
        if (scanf("%d", &choice) != 1) {
            printf("\n[!] Loi: Vui long nhap so nguyen!\n");
            while(getchar() != '\n'); // Xóa bộ nhớ đệm tránh lặp vô hạn
            continue;
        }

        switch(choice) {
            case 1:
                printf("\n>>> Chuc nang 'Them giao dich' dang duoc phat trien...\n");
                // addTransaction();
                break;
            case 2:
                printf("\n>>> Chuc nang 'Xem danh sach' dang duoc phat trien...\n");
                // displayTransactions();
                break;
            case 3:
                printf("\n>>> Chuc nang 'Tim kiem' dang duoc phat trien...\n");
                // searchTransaction();
                break;
            case 4:
                printf("\n>>> Chuc nang 'Xoa' dang duoc phat trien...\n");
                // deleteTransaction();
                break;
            case 5:
                printf("\n>>> Chuc nang 'Thong ke' dang duoc phat trien...\n");
                // showStatistics();
                break;
            case 6:
                printf("\n>>> Dang luu du lieu... Tam biet!\n");
                // saveToFile();
                break;
            default:
                printf("\n[!] Lua chon khong hop le! Vui long chon tu 1 den 6.\n");
        }
    } while(choice != 6);

    return 0;
}