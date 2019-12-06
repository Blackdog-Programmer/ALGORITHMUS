// Karatsuba_algorithm.cpp : O(n^log3)
// https://en.wikipedia.org/wiki/Karatsuba_algorithm
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void normalize(vector<int>& num);
vector<int> multiply(const vector<int> &a, const vector<int> &b);
// a+= b * (10^k)�� �����Ѵ�
void addTo(vector<int> &a, const vector<int> &b, size_t k);
// a-= b�� �����Ѵ� a >= b�� �����Ѵ�
void subFrom(vector<int>& a, const vector<int>& b);
vector<int> Karatsuba(const vector<int> &a, const vector<int> &b);


#include <iostream>

int main()
{
   vector<int> lhs{ 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2 };
   reverse(lhs.begin(), lhs.end());
   vector<int> rhs{ 2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,3,6,0,2,8,7,4,7,1,3,5,2,6,6,2,4,9,7,7,5,7,2,4,7,0,9,3,6,9,9,9,5,9,5,7,4,9,6,6,9,6,7,6,2,7 };
   reverse(rhs.begin(), rhs.end());

   vector<int> ret = Karatsuba(lhs, rhs);
   reverse(ret.begin(), ret.end());
   for (vector<int>::iterator i = ret.begin(); i < ret.end(); ++i)
      cout << *i;
   cout << endl;
}

vector<int> Karatsuba(const vector<int> &a, const vector<int> &b) {
   size_t an = a.size(), bn = b.size();
   // a�� b���� ª�� ��� ���� �ٲ۴�
   if (an < bn) return Karatsuba(b, a);
   // ���� ���: a�� b�� ��� �ִ� ���
   if (an == 0 || bn == 0) return vector<int>();
   // ���� ���: a ����� ���� ª�� ��� O(n^2) �������� ����Ѵ�
   if (an <= 50) return multiply(a, b);

   size_t half = an / 2;
   // a�� b�� �ؿ��� half�ڸ��� �������� �и��Ѵ�
   vector<int> a0(a.begin(), a.begin() + half);
   vector<int> a1(a.begin() + half, a.end());
   vector<int> b0(b.begin(), b.begin() + min<size_t>(b.size(), half));
   vector<int> b1(b.begin() + min<size_t>(b.size(), half), b.end());

   // z2 = a1 * b1
   vector<int> z2 = Karatsuba(a1, b1);
   // z0 = a0 * 0b
   vector<int> z0 = Karatsuba(a0, b0);
   // a0 = a0 + a1
   // b0 = b0 + b1
   addTo(a0, a1, 0); addTo(b0, b1, 0);
   // z1 = (a0 * b0) - z0 - z2
   vector<int> z1 = Karatsuba(a0, b0);
   subFrom(z1, z0);
   subFrom(z1, z2);
   // ret = z0 + z1 * 10^half + z2 * 10^(half * 2)
   vector<int> ret;
   addTo(ret, z0, 0);
   addTo(ret, z1, half);
   addTo(ret, z2, half + half);

   return ret;
}

void addTo(vector<int>& a, const vector<int>& b, size_t k) {
   a.resize(max((a.size() + 1), (b.size() + k)));

   for (register int i = 0; i < b.size(); ++i)
      a[i + k] += b[i];
   normalize(a);
}
void subFrom(vector<int>& a, const vector<int>& b) {
   for (register int i = 0; i < b.size(); ++i) 
      a[i] -= b[i];
   normalize(a);
}

void normalize(vector<int>& num) {
   num.push_back(0);

   for (register size_t i = 0; i + 1 < num.size(); ++i) {
      if (num[i] < 0) {
         int borrow = (abs(num[i]) + 9) / 10;
         num[i + 1] -= borrow;
         num[i] += borrow * 10;
      }
      else {
         num[i + 1] += num[i] / 10;
         num[i] %= 10;
      }
   }
   while (num.size() > 1 && num.back() == 0) num.pop_back();
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
   vector<int> c(a.size() + b.size() + 1, 0);
   for (register size_t i = 0; i < a.size(); ++i)
      for (register size_t j = 0; j < b.size(); ++j)
         c[i + j] += a[i] * b[j];
   normalize(c);
   return c;
}