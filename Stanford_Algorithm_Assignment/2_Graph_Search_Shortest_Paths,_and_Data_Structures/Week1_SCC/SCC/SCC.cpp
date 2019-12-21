// SCC.cpp : tarjanSCC - O(V + E)
// https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
// Configuration: stack memory size = 32MB, because size of large graph
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int vertexSize = 875714;
const int maxSccSize = 5;

vector<vector<int>> edge(vertexSize);
// �� ������ �����ʴ� ��ȣ, �����ʹ� ��ȣ�� 0���� �����ϸ�,
// ���� ������ ������Ʈ�� ���� �������� �����ʴ� ��ȣ�� ����.
vector<int> sccID;
// �� ���� �߰� ����
vector<int> discovered;
// ������ ��ȣ�� ��� ����
stack<int> stk;
int sccCounter, vertextCounter;
// here�� ��Ʈ�� �ϴ� ����Ʈ������ ������ �����̳� ���� ������
// ���� �� �� �ִ� ���� �� �ּ� �߰� ������ ��ȯ�Ѵ�.
// (�̹� SCC�� ���� �������� ����� ���������� �����Ѵ�)
int scc(int here);
// tarjan SCC �˰���
void tarjanSCC();

int main(int argc, char *argv[])
{
   ifstream in("SCC.txt", ifstream::in);
   if (!in.is_open()) {
      cerr << "Error: SCC.txt not found!" << endl;
      return -1;
   }
   while (!in.eof()) {
      int from, to; in >> from >> to;
      edge[from - 1].push_back(to - 1);
   }
   
   tarjanSCC();

   vector<int> sccSize(vertexSize, 0);
   sort(sccID.begin(), sccID.end());
   int i = 0;
   while (i < sccID.size()) {
      int count = 0; int id = sccID[i];
      while (i < sccID.size() && sccID[i] == id) {
         ++count; ++i;
      }
      sccSize[id] = count;
   }

   sort(sccSize.begin(), sccSize.end());
   reverse(sccSize.begin(), sccSize.end());
   for (int i = 0; i < maxSccSize; ++i) {
      cout << sccSize[i] << " ";
   }
   return 0;
}

int scc(int here) {
   int ret = discovered[here] = vertextCounter++;
   // ���ÿ� here�� �ִ´�. here�� �ļյ��� ��� ���ÿ��� here �Ŀ� ����.
   stk.push(here);
   for (int i = 0; i < edge[here].size(); ++i) {
      int there = edge[here][i];
      // (here, there)�� Ʈ�� ������ ���
      if (discovered[there] == -1)
         ret = min(ret, scc(there));
      // there�� �����ؾ� �ϴ� ���� ������ �ƴ϶��
      else if (sccID[there] == -1)
         ret = min(ret, discovered[there]);
   }
   // here���� �θ�� �ö󰡴� ������ ����� ���� Ȯ���Ѵ�.
   if (ret == discovered[here]) {
      // here�� ��Ʈ�� �ϴ� ����Ʈ���� ���� �ִ� �������� ���� �ϳ��� ������Ʈ�� ���´�.
      while (true) {
         int t = stk.top();
         stk.pop();
         sccID[t] = sccCounter;
         if (t == here) break;
      }
      ++sccCounter;
   }
   return ret;
}

void tarjanSCC() {
   // �迭 �ʱ�ȭ
   sccID = discovered = vector<int>(edge.size(), -1);
   // ī���� �ʱ�ȭ
   sccCounter = vertextCounter = 0;
   // ��� ������ ���� scc() ȣ��
   for (int i = 0; i < edge.size(); ++i) 
      if (discovered[i] == -1) scc(i);
   return;
}