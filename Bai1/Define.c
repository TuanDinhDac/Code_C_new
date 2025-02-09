#include <stdio.h>

// 1. Định nghĩa kiểu dữ liệu cơ bản
typedef int I8;
typedef float F8;
typedef double F16;
typedef char C8;
typedef unsigned int UI8;
typedef long I16;

// 2. Định nghĩa kiểu enum
typedef enum {
    FALSE,  // 0
    TRUE    // 1
} Boolean;

// 3. Định nghĩa người dân
typedef struct {
    C8 name[50];
    I8 age;
    C8 address;
} Person;

// 4. Ví dụ union
union {
    I8 i;
    F8 f;
    C8 str[20];
}UnionExample;

int main()
{
    printf("hello");

}
