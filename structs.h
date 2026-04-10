// File: structs.h
// Dùng để định nghĩa cấu trúc dữ liệu chung

// Include Guard: Tránh lỗi định nghĩa lại thư viện khi include nhiều lần
#ifndef STRUCTS_H
#define STRUCTS_H

// Sử dụng #define cho các độ dài chuỗi cố định
#define MAX_DATE_LEN 15
#define MAX_CAT_LEN 50

// 1. Cấu trúc lưu trữ thông tin của MỘT giao dịch
typedef struct Transaction {
    int id;                       // Mã giao dịch (Tự động tăng)
    char date[MAX_DATE_LEN];      // Ngày tháng (Định dạng: DD/MM/YYYY)
    char category[MAX_CAT_LEN];   // Danh mục (VD: Luong, An_uong, Tien_nha...)
    long long amount;             // Số tiền
    int type;                     // Loại giao dịch: 1 là Thu, 0 là Chi
} Transaction;

// 2. Cấu trúc Node cho Danh sách liên kết đơn (Yêu cầu Chương 3)
typedef struct Node {
    Transaction data;             // Dữ liệu của Node
    struct Node* next;            // Con trỏ trỏ đến Node tiếp theo (Cấu trúc tự trỏ)
} Node;

// Định nghĩa alias cho con trỏ để code gọn hơn (Tùy chọn)
typedef struct Node* NodePtr;

#endif // Kết thúc Include Guard