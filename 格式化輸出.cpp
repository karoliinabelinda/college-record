#include<iostream>
using namespace std;

// ��ƥΨӿ�X�S�w�榡�����
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
    int number1[5] = {1, 2, 3, 4, 5}; // ��l�ư}�C
    int i = 0, j = 0;

    // �~�h�j��
    while (j < 5)
    {
        // ���h�j��
        while (i < 5)
        {
            // ��X A
            cout << "A: " << number1[i] + 858993461 + i;
            print_format(i);

            // ��X e
            cout << " e: " << number1[j] + 858993461 + j;
            print_format(j);

            // ��X B
            cout << " B: " << number1[j] + 858993461 + j;
            print_format(j);

            cout << "    "; // ���j

            i++; // �W�[ i
        }
        cout << endl; // �C�@���X���ᴫ��
        j++;          // �W�[ j
        i = 0;        // ���m i �� 0
    }

    return 0;
}

