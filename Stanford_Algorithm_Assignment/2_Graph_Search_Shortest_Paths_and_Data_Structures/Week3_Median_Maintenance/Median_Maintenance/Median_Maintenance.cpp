// Median_Maintenance.cpp : O(NlogN) using MaxHeap and MinHeap
// Goal: calcualte sum of median(following insertion) and divide by 10000

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream in("Median.txt", ifstream::in);
	if (!in.is_open()) {
		cerr << "Error: Median.txt file not found!" << endl;
		return -1;
	}

	// std::less - http://www.cplusplus.com/reference/functional/less/
	priority_queue<int, vector<int>, less<int>> maxHeap;
	// std::greater - http://www.cplusplus.com/reference/functional/greater/
	priority_queue<int, vector<int>, greater<int>> minHeap;

	int ret = 0;
	while (!in.eof()) {
		int val; in >> val;
		// �Һ��� 1: �ִ� ���� ũ��� �ּ� ���� ũ��� ���ų�, �ϳ� �� ũ��
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(val);
		else
			minHeap.push(val);
		// �Һ��� 2: �ִ� ���� �ִ� ���Ҵ� �ּ� ���� �ּ� ���Һ��� �۰ų� ����
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int lhs = maxHeap.top(), rhs = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(rhs);
			minHeap.push(lhs);
		}
		ret = (ret + maxHeap.top()) % 10000;
	}
	// Exact Output : 1213
	cout << ret;

	return 0;
}