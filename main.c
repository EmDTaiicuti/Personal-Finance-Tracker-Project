#include <stdio.h>
#include <stdlib.h>
#include <string.h> // thêm thư viện xử lý chuỗi
#include "structs.h" 

// khai báo sẵn các chức năng của hàm 
void addTransaction(Node** head); // đã sửa lỗi thiếu tham số
void displayTransactions(Node* head); // thêm tham số
void searchTransaction(Node* head); // thêm tham số truyền vào
void deleteTransaction(Node** head); // thêm tham số con trỏ bậc 2
void showStatistics(Node** head);// 
void loadFromFile(Node** head); // thêm tham số
void saveToFile(Node* head); // thêm tham số
void freeMemory(Node** head); // khai báo thêm hàm dọn rác
// ==========================================
// MODULE: DANH SACH LIEN KET & XU LY DU LIEU
// ==========================================

// hàm cấp phát bộ nhớ động tạo nọt mới
Node* createNode(Transaction t) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("[!] Loi: Khong the cap phat bo nho!\n");
        return NULL;
    }
    // đổ dữ liệu vào node và cho con trỏ trỏ vào null
    newNode->data = t;
    newNode->next = NULL;
    return newNode;
}

// hàm thêm giao dịch do người dùng nhập vào Danh sách (Thêm vào cuối - Insert at Tail)
void addTransaction(Node** head) {
    Transaction t;
    printf("\n--- NHAP THONG TIN GIAO DICH MOI ---\n");
    
    // nhập liệu cơ bản (tutu chưa code xong hihi )
    printf("Nhap Ma ID (so nguyen): "); 
    scanf("%d", &t.id);
    
    printf("Nhap Ngay (DD/MM/YYYY): "); 
    scanf("%s", t.date);
    
    printf("Nhap Danh muc (VD: An_uong, Luong): "); 
    scanf("%s", t.category);
    
    printf("Nhap So tien (VNĐ): "); 
    scanf("%lld", &t.amount);
    
    printf("Loai giao dich (1 la Thu, 0 la Chi): "); 
    scanf("%d", &t.type);

    // gọi máy tạo node
    Node* newNode = createNode(t);

    // thuật toán gắn node vào danh sách liên kết
    if (*head == NULL) {
        // nếu danh sách đang trống, Node mới chính là Head
        *head = newNode;
    } else {
        // nếu danh sách đã có người, chạy từ đầu đến cuối hàng để xếp hàng
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; // gắn vào đuôi
    }
    
    printf("\n=> Tinh tong... Da them giao dich [%s] thanh cong!\n", t.category);
}

// hàm đọc dữ liệu từ file khi khởi động
void loadFromFile(Node** head) {
    // mở file ở chế độ đọc ("r" - read)
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("\n[*] He thong: Khong tim thay file 'data.txt'. Se tao file moi khi ban luu.\n");
        return; // thoát hàm nếu file không tồn tại
    }

    Transaction t;
    int count = 0; // biến đếm xem đã tải được bao nhiêu dòng

    // đọc liên tục cho đến khi hết file (EOF)
    while (fscanf(file, "%d %s %s %lld %d", &t.id, t.date, t.category, &t.amount, &t.type) == 5) {
        // dùng lại máy tạo node
        Node* newNode = createNode(t);
        
        // thuật toán gắn node vào danh sách liên kết
        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    fclose(file); // mở file xong nhớ phải đóng lại
    if (count > 0) {
        printf("\n[*] He thong: Da tai thanh cong %d giao dich tu file!\n", count);
    }
}
// hàm ghi dữ liệu từ danh sách liên kết ra file (ghi đè dữ liệu cũ)
void saveToFile(Node* head) {
    // mở file ở chế độ "w" (write): xóa sạch dữ liệu cũ và ghi mới lại từ đầu
    FILE* file = fopen("data.txt", "w"); 
    if (file == NULL) {
        printf("\n[!] Loi: Khong the mo file de luu du lieu!\n");
        return;
    }

    Node* current = head;
    int count = 0;
    
    // duyệt qua từng node và dùng fprintf để in vào file
    while (current != NULL) {
        fprintf(file, "%d %s %s %lld %d\n", 
                current->data.id, 
                current->data.date, 
                current->data.category, 
                current->data.amount, 
                current->data.type);
        current = current->next;
        count++;
    }

    fclose(file); // ghi xong thì phải đóng cửa lại
    printf("\n[*] He thong: Da luu an toan %d giao dich vao file 'data.txt'.\n", count);
}

// hàm giải phóng bộ nhớ động để tránh rò rỉ bộ nhớ (memory leak) - yêu cầu chương 2
void freeMemory(Node** head) {
    Node* current = *head;
    Node* nextNode;
    
    while (current != NULL) {
        nextNode = current->next; // giữ lại địa chỉ node tiếp theo trước khi xóa
        free(current);            // tiêu hủy (trả ram) node hiện tại
        current = nextNode;       // tiến lên node tiếp theo
    }
    
    *head = NULL; // reset danh sách về trống cho an toàn
    printf("[*] He thong: Da don dep RAM thanh cong (Free Memory).\n");
}
// hàm hiển thị danh sách giao dịch dưới dạng bảng
void displayTransactions(Node* head) {
    // kiểm tra xem danh sách có trống không
    if (head == NULL) {
        printf("\n[!] Danh sach giao dich hien dang trong! Vui long them moi.\n");
        return; // thoát hàm luôn
    }

    // in thanh tiêu đề của bảng
    printf("\n===========================================================================\n");
    printf("| %-5s | %-12s | %-20s | %-15s | %-6s |\n", "ID", "Ngay", "Danh muc", "So tien (VND)", "Loai");
    printf("===========================================================================\n");

    // bắt đầu duyệt từ đầu danh sách (head)
    Node* current = head;
    while (current != NULL) {
        // chuyển đổi type từ số (1, 0) sang chuỗi (Thu, Chi)
        char typeStr[10];
        if (current->data.type == 1) {
            strcpy(typeStr, "Thu");
        } else {
            strcpy(typeStr, "Chi");
        }

        // in thông tin của node hiện tại
        printf("| %-5d | %-12s | %-20s | %15lld | %-6s |\n", 
               current->data.id, 
               current->data.date, 
               current->data.category, 
               current->data.amount, 
               typeStr);
        
        // nhảy sang node tiếp theo
        current = current->next;
    }
    printf("===========================================================================\n");
}
// hàm tìm kiếm giao dịch theo danh mục (tìm gần đúng bằng strstr)
void searchTransaction(Node* head) {
    // kiểm tra danh sách rỗng
    if (head == NULL) {
        printf("\n[!] Danh sach trong, khong co gi de tim!\n");
        return;
    }

    char keyword[50];
    printf("\n--- TIM KIEM GIAO DICH ---\n");
    printf("Nhap tu khoa danh muc (VD: An, Luong...): ");
    scanf("%s", keyword);

    // in thanh tiêu đề bảng kết quả
    printf("\n>>> KET QUA TIM KIEM CHO '%s':\n", keyword);
    printf("===========================================================================\n");
    printf("| %-5s | %-12s | %-20s | %-15s | %-6s |\n", "ID", "Ngay", "Danh muc", "So tien (VND)", "Loai");
    printf("===========================================================================\n");

    Node* current = head;
    int foundCount = 0; // biến đếm số kết quả tìm được

    // duyệt từ đầu đến cuối danh sách
    while (current != NULL) {
        // hàm strstr sẽ kiểm tra xem 'keyword' có nằm trong 'category' không
        if (strstr(current->data.category, keyword) != NULL) {
            char typeStr[10];
            if (current->data.type == 1) strcpy(typeStr, "Thu");
            else strcpy(typeStr, "Chi");

            // in ra giao dịch khớp với từ khóa
            printf("| %-5d | %-12s | %-20s | %15lld | %-6s |\n", 
                   current->data.id, 
                   current->data.date, 
                   current->data.category, 
                   current->data.amount, 
                   typeStr);
            foundCount++;
        }
        current = current->next; // đi tới node tiếp theo
    }
    printf("===========================================================================\n");

    // thông báo nếu không tìm thấy gì
    if (foundCount == 0) {
        printf("[!] Khong tim thay giao dich nao khop voi tu khoa '%s'.\n", keyword);
    } else {
        printf("=> Tim thay %d giao dich.\n", foundCount);
    }
}
// hàm xóa giao dịch theo mã ID
void deleteTransaction(Node** head) {
    // kiểm tra danh sách rỗng
    if (*head == NULL) {
        printf("\n[!] Danh sach trong, khong co gi de xoa!\n");
        return;
    }

    int deleteId;
    printf("\n--- XOA GIAO DICH ---\n");
    printf("Nhap Ma ID cua giao dich can xoa: ");
    if (scanf("%d", &deleteId) != 1) {
        printf("[!] Loi: ID phai la so nguyen!\n");
        while(getchar() != '\n'); // dọn dẹp bộ nhớ đệm nếu nhập sai
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    // trường hợp 1: node cần xóa nằm ngay đầu danh sách (chính là head)
    if (current != NULL && current->data.id == deleteId) {
        *head = current->next; // dời head sang node thứ 2
        free(current);         // trả ram của node cũ
        printf("=> Da xoa thanh cong giao dich co ID: %d\n", deleteId);
        return;
    }

    // trường hợp 2: tìm node cần xóa ở đoạn giữa hoặc cuối danh sách
    while (current != NULL && current->data.id != deleteId) {
        prev = current;          // prev đi sau lưu dấu vết
        current = current->next; // current đi trước dò tìm
    }

    // nếu duyệt đến cuối (null) mà vẫn không tìm thấy ID
    if (current == NULL) {
        printf("[!] Khong tim thay giao dich voi ID: %d\n", deleteId);
        return;
    }

    // thuật toán xóa: ngắt kết nối node hiện tại, nối node trước với node sau
    prev->next = current->next;
    free(current); // tiêu hủy node cần xóa
    printf("=> Da xoa thanh cong giao dich co ID: %d\n", deleteId);
}
// hàm đệ quy tính tổng tiền theo loại (1: Thu, 0: Chi) - yêu cầu chương 2
long long calculateTotalRecursive(Node* head, int type) {
    // điều kiện dừng của đệ quy: nếu danh sách hết thì trả về 0
    if (head == NULL) return 0;

    long long currentAmount = 0;
    if (head->data.type == type) {
        currentAmount = head->data.amount;
    }

    // gọi đệ quy: tổng = tiền hiện tại + tổng của phần còn lại
    return currentAmount + calculateTotalRecursive(head->next, type);
}

// hàm hiển thị báo cáo tài chính tổng hợp
void showStatistics(Node* head) {
    if (head == NULL) {
        printf("\n[!] Danh sach trong, khong co du lieu de thong ke!\n");
        return;
    }

    // gọi hàm đệ quy để tính toán
    long long totalIncome = calculateTotalRecursive(head, 1); // Tổng Thu
    long long totalExpense = calculateTotalRecursive(head, 0); // Tổng Chi
    long long balance = totalIncome - totalExpense;           // Số dư

    printf("\n========================================\n");
    printf("        BAO CAO TAI CHINH TONG HOP\n");
    printf("========================================\n");
    printf(" 1. Tong thu nhap:  %15lld VND\n", totalIncome);
    printf(" 2. Tong chi tieu:  %15lld VND\n", totalExpense);
    printf("----------------------------------------\n");
    printf(" => SO DU HIEN TAI: %15lld VND\n", balance);
    
    if (balance < 0) {
        printf(" [!] Canh bao: Ban dang chi tieu vuot muc thu nhap!\n");
    } else {
        printf(" [*] Trang thai: Tai chinh on dinh.\n");
    }
    printf("========================================\n");
}
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
    
    // khai báo con trỏ head quản lý Danh sách liên kết (Khởi tạo là NULL)
    Node* head = NULL; 

    // gọi hàm tải dữ liệu khi vừa mở app
    loadFromFile(&head);

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("\n[!] Loi: Vui long nhap so nguyen!\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch(choice) {
            case 1:
                addTransaction(&head); // gọi hàm Thêm và truyền địa chỉ của head(10/4)
                break;
            //các case khác giữ nguyên như cũ nha mấy bé(10/4)
            case 2:
                displayTransactions(head); // gọi hàm hiển thị
                break;
            case 3:
                searchTransaction(head); // gọi hàm tìm kiếm
                break;
         case 4:
                deleteTransaction(&head); // gọi hàm xóa (truyền địa chỉ)
                break;
        case 5:
                showStatistics(head); // gọi hàm thống kê
                break;
            case 6:
                printf("\n>>> Dang luu du lieu va don dep he thong... Tam biet!\n");
                saveToFile(head);      // gọi hàm lưu file
                freeMemory(&head);     // gọi hàm dọn rác ram
                break;
            default:
                printf("\n[!] Lua chon khong hop le! Vui long chon tu 1 den 6.\n");
        }
    } while(choice != 6);

    return 0;
}
