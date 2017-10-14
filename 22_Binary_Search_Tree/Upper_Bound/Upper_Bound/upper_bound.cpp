// http://koistudy.net/?mid=prob_page&NO=1887
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int n, k, d[1010];

// key ������ ó������ ū ���� ��ġ�� ��ȯ 
int upper_bound(int key);

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			scanf("%d", &d[i]);

		scanf("%d", &k);

		printf("%d\n", upper_bound(k));
	}
	return 0;
}

int upper_bound(int key) {
	int ret = n + 1;
	int first = 1, last = n;
	int mid;
	while (first <= last) {
		mid = (first + last) / 2;
		if (d[mid] > key) {
			ret = mid;
			last = mid - 1;
		}
		else first = mid + 1;
	}
	return ret;
}