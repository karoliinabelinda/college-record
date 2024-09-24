#include<iostream>
using namespace std;

// 函數用來輸出特定格式的資料
void print_format(int i) {
    switch (i) {
        case 0: cout << ", 010, 1"; break;
        case 1: cout << ", 100, 1"; break;
        case 2: cout << ", 011, 2"; break;
        case 3: cout << ", 110, 2"; break;
        case 4: cout << ", 111, 3"; break;
        case 5: cout << ", 101, 2"; break;
    }
}

int main()
{
    int number1[5] = {1, 2, 3, 4, 5}; // 初始化陣列
    int i = 0, j = 0;

    // 外層迴圈
    while (j < 5)
    {
        // 內層迴圈
        while (i < 5)
        {
            // 輸出 A
            cout << "A: " << number1[i] + 858993461 + i;
            print_format(i);

            // 輸出 e
            cout << " e: " << number1[j] + 858993461 + j;
            print_format(j);

            // 輸出 B
            cout << " B: " << number1[j] + 858993461 + j;
            print_format(j);

            cout << "    "; // 間隔

            i++; // 增加 i
        }
        cout << endl; // 每一行輸出完後換行
        j++;          // 增加 j
        i = 0;        // 重置 i 為 0
    }

    return 0;
}

