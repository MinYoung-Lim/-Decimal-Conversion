#include <stdio.h>
#include <memory.h>

int* Binary(int num) {  // 2진수 변환 함수

	static int result[32] = { 0 };  // 양수일때 리턴해줄 배열 초기화
	static int T[32] = { 0 };  // 음수일때 리턴해줄 배열 초기화
	int O[32] = { 0 };  // 1의보수 저장할 배열 초기화
	int sw = 0;  //스위치 변수
	int i;

	if (num < 0) {  // 음수일때 스위치변수 1로변경, 절댓값저장
		sw = 1;
		num = -1 * num;
	}

	for (i = 0; num > 0; i++) {
		result[i] = num % 2;  // 2로나눈 나머지 저장
		num = num / 2;  // 새로운 몫 저장
	}

	if (sw == 1) {   //음수일때 2진수 처리

		int N = i;
		int C = 1;
		result[31] = 1;

		for (int i = 30; i >= 0; i--) {  // 1의 보수 
			O[i] = 1 - result[i];
		}

		for (int i = 0; i < 31; i++) {  // 2의 보수 
			result[i] = 1;
			if (O[i] == C)
				result[i] = 0;
			C = O[i] * C;
		}

		memcpy(T, result, sizeof(result)); // 다음 함수를 호출할 때 지장이없도록 T에 result 복사

		for (int i = 0; i < 32; i++)  // result 초기화
			result[i] = 0;
		return T;  // 2의 보수를 담고있는 T 반환
	}
	else {
		result[31] = 0;  // result 초기화
		return result;  // 양수인 정수의 result 반환
	}	
}

int* Octal(int num) {  // 8진수 변환 함수

	int M = 11;
	int cnt;
	int j = 0;
	int* result;
	static int T[11] = { 0 };  // 양수일때 반환할 배열
	static int Ans[11] = { 0 };  // (음수일 때) 3개씩 끊은 값 저장할 배열

	if (num > 0) {  // num이 양수일 때

		for (int i = 0; num > 0; i++) { 
			T[i] = num % 8;  // 8로 나눈 나머지 저장
			num = num / 8;  // 새로운 몫 저장
		}

		return T;  // 양수일 때의 8진수 반환

	}
	else {  // 음수일 때
		result = Binary(num);  // 2의 보수를 적용한 2진수 배열 저장

		for (cnt = 0; cnt < M; cnt++) {  

			Ans[cnt] += result[j];  // 첫번째 자리는 2^0 곱하기
			if (j != 32)
				Ans[cnt] += result[j + 1] * 2;  // 2^1 하여 더하기
			if (j != 32)
				Ans[cnt] += result[j + 2] * 2 * 2;  // 2^2 해서 더하기
			j = j + 3;  // 3비트 진행하였으므로 다음 비트는 +3
		}


		return Ans;

	}
}

char* Hexa(int num) {  // 16진수 변환 함수

	char H[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };  // 16진수에서 나타날 수 있는 문자를 문자형으로 저장하고 있는 배열 변수
	static char T[8] = {'0','0','0' ,'0' ,'0' ,'0' ,'0' ,'0' };
	int* result;
	static int Ans[8] = { 0 };  // 4비트씩 끊어서 저장할 배열
	int j = 0;
	int cnt;
	int i = 0;
	int M, N;

	if (num > 0) {
		do {
			M = num / 16;  // num을 16으로 나눈 몫 저장
			N = num % 16;  // num을 16으로 나눈 나머지 저장
			T[i] = H[N];  // 나머지를 result배열에 저장
			i++;
			num = M;  // 몫 M을 새로운 num으로 설정
		} while (M >= 16);  // 16이상일때만 실행

		T[i] = H[M];

		return T;

	}
	else {
		result = Binary(num);  // 2의 보수를 적용한 16진수 배열 저장
		for (cnt = 0; cnt < 8; cnt++) {
			Ans[cnt] += result[j];  // 2^0
			if (j != 32)
				Ans[cnt] += result[j + 1] * 2;  // 2^1 곱해서 더하기
			if (j != 32)
				Ans[cnt] += result[j + 2] * 2 * 2;  // 2^2 곱해서 더하기
			if (j != 32)
				Ans[cnt] += result[j + 3] * 2 * 2*2;  // 2^3 곱해서 더하기

			T[cnt] = H[Ans[cnt]];  // 해당하는 값 H배열에서 출력

			j = j + 4;  // 4비트씩 진행하였으므로 +4

		}

		return T;  // 음수의 16진수 저장한 배열 반환
	}
	

}

int main() {
	
	int num;  //입력받을 10진수
	int *result_2;
	int *result_8;
	char *result_16;
	int j;

	printf("변환할 10진수를 입력하세요 : ");
	scanf("%d", &num);

	result_2 = Binary(num);  // 2진수 함수 저장

	printf("2진수 : ");

	for (j = 31; j>=0; j--) {  //역순으로 출력
		printf("%d", result_2[j]);
	}

	printf("\n");

	result_8 = Octal(num);  // 8진수 함수 저장

	printf("8진수 : ");

	for (j = 10; j >= 0; j--) {  //역순으로 출력
		printf("%d", result_8[j]);
	}

	printf("\n");

	result_16 = Hexa(num);  // 16진수 함수 저장

	printf("16진수 : ");

	for (j = 7; j >= 0; j--) {  //역순으로 출력
		printf("%c", result_16[j]);
	}

	printf("\n");

	return 0;
}

