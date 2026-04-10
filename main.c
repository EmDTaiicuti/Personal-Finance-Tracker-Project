#include <stdio.h>
#include <stdlib.h>
#include <string.h> // thêm thư viện xử lý chuỗi(10/4)
#include "structs.h" 

// khai báo sẵn các chức năng của hàm 
void addTransaction(Node** head); // đã sửa lỗi thiếu tham số
void displayTransactions(Node* head); // thêm tham số
void searchTransaction();
void deleteTransaction();
void showStatistics();
void loadFromFile(Node** head); // thêm tham số
void saveToFile();

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
