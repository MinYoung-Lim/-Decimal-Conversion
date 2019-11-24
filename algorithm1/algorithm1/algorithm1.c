#include <stdio.h>
#include <memory.h>

int* Binary(int num) {  // 2���� ��ȯ �Լ�

	static int result[32] = { 0 };  // ����϶� �������� �迭 �ʱ�ȭ
	static int T[32] = { 0 };  // �����϶� �������� �迭 �ʱ�ȭ
	int O[32] = { 0 };  // 1�Ǻ��� ������ �迭 �ʱ�ȭ
	int sw = 0;  //����ġ ����
	int i;

	if (num < 0) {  // �����϶� ����ġ���� 1�κ���, ��������
		sw = 1;
		num = -1 * num;
	}

	for (i = 0; num > 0; i++) {
		result[i] = num % 2;  // 2�γ��� ������ ����
		num = num / 2;  // ���ο� �� ����
	}

	if (sw == 1) {   //�����϶� 2���� ó��

		int N = i;
		int C = 1;
		result[31] = 1;

		for (int i = 30; i >= 0; i--) {  // 1�� ���� 
			O[i] = 1 - result[i];
		}

		for (int i = 0; i < 31; i++) {  // 2�� ���� 
			result[i] = 1;
			if (O[i] == C)
				result[i] = 0;
			C = O[i] * C;
		}

		memcpy(T, result, sizeof(result)); // ���� �Լ��� ȣ���� �� �����̾����� T�� result ����

		for (int i = 0; i < 32; i++)  // result �ʱ�ȭ
			result[i] = 0;
		return T;  // 2�� ������ ����ִ� T ��ȯ
	}
	else {
		result[31] = 0;  // result �ʱ�ȭ
		return result;  // ����� ������ result ��ȯ
	}	
}

int* Octal(int num) {  // 8���� ��ȯ �Լ�

	int M = 11;
	int cnt;
	int j = 0;
	int* result;
	static int T[11] = { 0 };  // ����϶� ��ȯ�� �迭
	static int Ans[11] = { 0 };  // (������ ��) 3���� ���� �� ������ �迭

	if (num > 0) {  // num�� ����� ��

		for (int i = 0; num > 0; i++) { 
			T[i] = num % 8;  // 8�� ���� ������ ����
			num = num / 8;  // ���ο� �� ����
		}

		return T;  // ����� ���� 8���� ��ȯ

	}
	else {  // ������ ��
		result = Binary(num);  // 2�� ������ ������ 2���� �迭 ����

		for (cnt = 0; cnt < M; cnt++) {  

			Ans[cnt] += result[j];  // ù��° �ڸ��� 2^0 ���ϱ�
			if (j != 32)
				Ans[cnt] += result[j + 1] * 2;  // 2^1 �Ͽ� ���ϱ�
			if (j != 32)
				Ans[cnt] += result[j + 2] * 2 * 2;  // 2^2 �ؼ� ���ϱ�
			j = j + 3;  // 3��Ʈ �����Ͽ����Ƿ� ���� ��Ʈ�� +3
		}


		return Ans;

	}
}

char* Hexa(int num) {  // 16���� ��ȯ �Լ�

	char H[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };  // 16�������� ��Ÿ�� �� �ִ� ���ڸ� ���������� �����ϰ� �ִ� �迭 ����
	static char T[8] = {'0','0','0' ,'0' ,'0' ,'0' ,'0' ,'0' };
	int* result;
	static int Ans[8] = { 0 };  // 4��Ʈ�� ��� ������ �迭
	int j = 0;
	int cnt;
	int i = 0;
	int M, N;

	if (num > 0) {
		do {
			M = num / 16;  // num�� 16���� ���� �� ����
			N = num % 16;  // num�� 16���� ���� ������ ����
			T[i] = H[N];  // �������� result�迭�� ����
			i++;
			num = M;  // �� M�� ���ο� num���� ����
		} while (M >= 16);  // 16�̻��϶��� ����

		T[i] = H[M];

		return T;

	}
	else {
		result = Binary(num);  // 2�� ������ ������ 16���� �迭 ����
		for (cnt = 0; cnt < 8; cnt++) {
			Ans[cnt] += result[j];  // 2^0
			if (j != 32)
				Ans[cnt] += result[j + 1] * 2;  // 2^1 ���ؼ� ���ϱ�
			if (j != 32)
				Ans[cnt] += result[j + 2] * 2 * 2;  // 2^2 ���ؼ� ���ϱ�
			if (j != 32)
				Ans[cnt] += result[j + 3] * 2 * 2*2;  // 2^3 ���ؼ� ���ϱ�

			T[cnt] = H[Ans[cnt]];  // �ش��ϴ� �� H�迭���� ���

			j = j + 4;  // 4��Ʈ�� �����Ͽ����Ƿ� +4

		}

		return T;  // ������ 16���� ������ �迭 ��ȯ
	}
	

}

int main() {
	
	int num;  //�Է¹��� 10����
	int *result_2;
	int *result_8;
	char *result_16;
	int j;

	printf("��ȯ�� 10������ �Է��ϼ��� : ");
	scanf("%d", &num);

	result_2 = Binary(num);  // 2���� �Լ� ����

	printf("2���� : ");

	for (j = 31; j>=0; j--) {  //�������� ���
		printf("%d", result_2[j]);
	}

	printf("\n");

	result_8 = Octal(num);  // 8���� �Լ� ����

	printf("8���� : ");

	for (j = 10; j >= 0; j--) {  //�������� ���
		printf("%d", result_8[j]);
	}

	printf("\n");

	result_16 = Hexa(num);  // 16���� �Լ� ����

	printf("16���� : ");

	for (j = 7; j >= 0; j--) {  //�������� ���
		printf("%c", result_16[j]);
	}

	printf("\n");

	return 0;
}

