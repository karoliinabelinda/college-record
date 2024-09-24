#include<iostream>
using namespace std;

int main()
{
 int A, i,e;
 cout << "請輸入e:";
 cin >> e;
 cout << "請輸入A:";
 cin >>A;
 i = 0;
 A = A * e;
 while (i <= 0)
 {
  if (A % 7 == 1 || A == 1)
  {
   cout << "010" << endl;
   break;
  }
  if (A % 7 == 2 || A == 2)
  {
   cout << "100" << endl;
   break;
  }
  if (A % 7 == 3 || A == 3 )
  {
   cout << "011" << endl;
   break;
  }
  if(A % 7 == 4 || A == 4)
  {
   cout << "110" << endl;
   break;
  }
  if (A % 7 == 5 || A == 5)
  {
   cout << "111" << endl;
   break;
  }
  if (A % 7 == 6 || A == 6)
  {
   cout << "101" << endl;
   break;
  }
  if (A % 7 == 0 || A == 7)
  {
   cout << "001" << endl;
   break;
  }
  if ( A == 0)
  {
   cout << "000" << endl;
   break;
  }
 }
 return 0;
}

