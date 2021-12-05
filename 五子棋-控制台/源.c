#include <stdio.h>
#include <stdlib.h>

#define N 20
int chess[N+1][N+1] = { 0 };  //���̵�����
int arr1[N + 1][N + 1] = { 0 }; //������һ����״̬
int arr2[N + 1][N + 1] = { 0 }; //������һ����״̬


//��ӡ����
void printChess () {
	int i, j;
	printf ("   ");
	for (int i = 1; i <= N; i++) {
		printf ("%3d", i);
	}
	printf ("\n");
	for (i = 1; i <= N; i++) {
		printf ("%3d", i);
		for (j = 1; j <= N; j++) {
			if (chess[i][j] == 0) {
				printf ("  +");
			}
			else if (chess[i][j] == 1) {
				printf (" ��");
			}
			else if (chess[i][j] == 2) {
				printf (" ��");
			}
		}
		printf ("\n");
	}
}

//��¼��һ��
void arrToChess (int state) {
	int i,j;
	if (state == 1) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				arr1[i][j] = chess[i][j];
			}
		}
	}
	else if (state == 2) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				arr2[i][j] = chess[i][j];
			}
		}
	}
}

//���ص���һ��
void chessToArr (int state) {
	int i, j;
	if (state == 1) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				chess[i][j] = arr1[i][j];
			}
		}
	}
	else if (state == 2) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				chess[i][j] = arr2[i][j];
			}
		}
	}
}


//�������
void inputOver (int state) {
	if (state == 1) {
		printf ("��Ϸ�������׷���ʤ");
	}
	else if (state == 2) {
		printf ("��Ϸ�������ڷ���ʤ");
	}
	while (1) {
		;
	}
}

//�ж���Ϸ�Ƿ����
void judgeWin (int x, int y, int state) {
	int count = 0;
	int i,j;
	for (i = x - 4; i <= x + 4; i++) {  //��ֱ����
		if (i < 0 || i > N) continue;
		if (chess[i][y] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
	count = 0;
	for (i = y - 4; i <= y + 4; i++) {  //ˮƽ����
		if (i < 0 || i > N) continue;
		if (chess[x][i] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
	count = 0;
	for (i = x - 4, j = y - 4; i <= x + 4; i++, j++) {   //���Խ���
		if (i < 0 || i > N || j < 0 || j > N) continue;
		if (chess[i][j] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
	count = 0;
	for (i = x - 4, j = y + 4; i <= x + 4; i++, j--) {   //���Խ���
		if (i < 0 || i > N || j < 0 || j > N) continue;
		if (chess[i][j] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
}

//����
void PPGame() {
	int state = 1;  //˭����  1���� 2����
	system ("cls");
	printChess ();
	while (1) {
		if (state == 1) {
			printf ("�׷�����,��������Ҫ�µ�(x,y)����(-1,-1)����:");
		}
		else if (state == 2) {
			printf ("�ڷ�����,��������Ҫ�µ�(x,y)����(-1,-1)����:");
		}
		int x, y;
		scanf ("%d%d", &x, &y);
		if (x == -1 && y == -1) {  //����
			system ("cls");
			chessToArr (state);
			printChess ();
		}
		else if (x > N || y > N || x < 1 || y < 1) {
			printf ("������������������:");
		}
		else if (chess[x][y] == 0) {
			arrToChess (state);
			chess[x][y] = state;
			system ("cls");
			printChess ();
			judgeWin (x, y, state);
			state = state % 2 + 1;
		}
		else {
			printf ("��������\n");
		}
	}
}


/*
����Ϊ���  ����Ϊ����

������һ�ӵ��Ի�԰�����Χ��8����������жϣ��ҵ�һ��������Ҫ����ģ�Ȼ���ڱ������ĸ������ģ����Ǿ�Ҫ������������ӵ�һ�˻���һ���ú����ס��
����ĸ�������8������û�У��ͼ��������ң���3���ģ���2���������ơ�
*/

int PCPlay (int x, int y, int n) {
	int state = 1;
	int m = n + 1;
	int count;
	srand ((unsigned int )(time(NULL)));
	int t = rand () % 2;

	switch (t) 	{
	case 0:
		count = 0;
		for (int i = x - n; i <= x; i++) {  //ˮƽ����
			if (i < 1) break;  //�����ж�
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //������������   ����ͷ���ж���
					if (i <= N - 1)
						if (chess[i + 1][y] == 0) {
							chess[i + 1][y] = 2;
							printChess ();
							judgeWin (i + 1, y, 2);
							return 1;
						}
					if (i >= m)
						if (chess[i - m][y] == 0) {
							chess[i - m][y] = 2;
							printChess ();
							judgeWin (i - m, y, 2);
							return 1;
						}
				}
			}
		}
		count = 0;
		for (int i = x; i <= x + n; i++) {  //ˮƽ����
			if (i > N) break;
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //������������   ����ͷ���ж���
					if (i <= N - 1)
						if (chess[i + 1][y] == 0) {
							chess[i + 1][y] = 2;
							printChess ();
							judgeWin (i + 1, y, 2);
							return 1;
						}
					if (i >= m)
						if (chess[i - m][y] == 0) {
							chess[i - m][y] = 2;
							printChess ();
							judgeWin (i - m, y, 2);
							return 1;
						}
				}
			}
		}
		count = 0;
		for (int i = y - n; i <= y; i++) {  //��ֱ����
			if (i < 1) break;
			if (chess[x][i] != state) break;
			else {
				count++;
				if (count == m) {
					if (i <= N - 1)
						if (chess[x][i + 1] == 0) {
							chess[x][i + 1] = 2;
							printChess ();
							judgeWin (x, i + 1, 2);
							return 1;
						}
					if (i >= m)
						if (chess[x][i - m] == 0) {
							chess[x][i - m] = 2;
							printChess ();
							judgeWin (x, i - m, 2);
							return 1;
						}
				}
			}
		}
		count = 0;
		for (int i = y; i <= y + n; i++) {  //��ֱ����
			if (i > N) break;
			if (chess[x][i] != state) break;
			else {
				count++;
				if (count == m) {
					if (i <= N - 1)
						if (chess[x][i + 1] == 0) {
							chess[x][i + 1] = 2;
							judgeWin (x, i + 1, 2);
							printChess ();
							return 1;
						}
					if (i >= m)
						if (chess[x][i - m] == 0) {
							chess[x][i - m] = 2;
							printChess ();
							judgeWin (x, i - m, 2);
							return 1;
						}
				}
			}
		}
		break;
	case 1:
		count = 0;
		for (int i = y; i <= y + n; i++) {  //��ֱ����
			if (i > N) break;
			if (chess[x][i] != state) break;
			else {
				count++;
				if (count == m) {
					if (i <= N - 1)
						if (chess[x][i + 1] == 0) {
							chess[x][i + 1] = 2;
							judgeWin (x, i + 1, 2);
							printChess ();
							return 1;
						}
					if (i >= m)
						if (chess[x][i - m] == 0) {
							chess[x][i - m] = 2;
							printChess ();
							judgeWin (x, i - m, 2);
							return 1;
						}
				}
			}
		}
		count = 0;
		for (int i = y - n; i <= y; i++) {  //��ֱ����
			if (i < 1) break;
			if (chess[x][i] != state) break;
			else {
				count++;
				if (count == m) {
					if (i <= N - 1)
						if (chess[x][i + 1] == 0) {
							chess[x][i + 1] = 2;
							printChess ();
							judgeWin (x, i + 1, 2);
							return 1;
						}
					if (i >= m)
						if (chess[x][i - m] == 0) {
							chess[x][i - m] = 2;
							printChess ();
							judgeWin (x, i - m, 2);
							return 1;
						}
				}
			}
		}
		count = 0;
		for (int i = x; i <= x + n; i++) {  //ˮƽ����
			if (i > N) break;
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //������������   ����ͷ���ж���
					if (i <= N - 1)
						if (chess[i + 1][y] == 0) {
							chess[i + 1][y] = 2;
							printChess ();
							judgeWin (i + 1, y, 2);
							return 1;
						}
					if (i >= m)
						if (chess[i - m][y] == 0) {
							chess[i - m][y] = 2;
							printChess ();
							judgeWin (i - m, y, 2);
							return 1;
						}
				}
			}
		}
		count = 0;
		for (int i = x - n; i <= x; i++) {  //ˮƽ����
			if (i < 1) break;  //�����ж�
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //������������   ����ͷ���ж���
					if (i <= N - 1)
						if (chess[i + 1][y] == 0) {
							chess[i + 1][y] = 2;
							printChess ();
							judgeWin (i + 1, y, 2);
							return 1;
						}
					if (i >= m)
						if (chess[i - m][y] == 0) {
							chess[i - m][y] = 2;
							printChess ();
							judgeWin (i - m, y, 2);
							return 1;
						}
				}
			}
		}
		break;
	}
	

	count = 0;
	for (int i = x - n, j = y - n; i <= x; i++, j++) {   //���Խ���
		if (i < 1 || j < 1) break;;
		if (chess[i][j] != state) break;
		else {
			count++;
			if (count == m) {
				if (i <= N - 1 && j <= N - 1)
					if (chess[i + 1][j + 1] == 0) {
						chess[i + 1][j + 1] = 2;
						printChess ();
						judgeWin (i + 1, j + 1, 2);
						return 1;
					}
				if (i >= m && j >= m)
					if (chess[i - m][j - m] == 0) {
						chess[i - m][j - m] = 2;
						printChess ();
						judgeWin (i -m, j -m, 2);
						return 1;
					}

			}
		}
	}
	count = 0;
	for (int i = x, j = y; i <= x + n; i++, j++) {   //���Խ���
		if (i > N || j > N) break;
		if (chess[i][j] != state) break;
		else {
			count++;
			if (count == m) {
				if (i <= N - 1 && j <= N - 1)
					if (chess[i + 1][j + 1] == 0) {
						chess[i + 1][j + 1] = 2;
						printChess ();
						judgeWin (i + 1, j + 1, 2);
						return 1;
					}
				if (i >= m && j >= m)
					if (chess[i - m][j - m] == 0) {
						chess[i - m][j - m] = 2;
						printChess ();
						judgeWin (i - m, j - m, 2);
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = x - n, j = y + n; i <= x; i++, j--) {   //���Խ���
		if (i < 1 || j < 1) break;
		if (chess[i][j] != state) break;
		else {
			count++;
			if (count == m) {
				if (i <= N - 1 && j >= 1)
					if (chess[i + 1][j - 1] == 0) {
						chess[i + 1][j - 1] = 2;
						printChess ();
						judgeWin (i + 1, j - 1, 2);
						return 1;
					}
				if (i >= m && j <= N - m)
					if (chess[i - m][j + m] == 0) {
						chess[i - m][j + m] = 2;
						printChess ();
						judgeWin (i - m, j + m, 2);
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = x, j = y; i <= x + n; i++, j--) {   //���Խ���
		if (i > N || j > N) break;
		if (chess[i][j] != state) break;
		else {
			count++;
			if (count == m) {
				if (i <= N - 1 && j >= 1)
					if (chess[i + 1][j - 1] == 0) {
						chess[i + 1][j - 1] = 2;
						printChess ();
						judgeWin (i + 1, j - 1, 2);
						return 1;
					}
				if (i >= m && j <= N - m)
					if (chess[i - m][j + m] == 0) {
						chess[i - m][j + m] = 2;
						printChess ();
						judgeWin (i - m, j + m, 2);
						return 1;
					}
			}
		}
	}
	return 0;
}

//�˻�
void PCGame () {
	int state = 1;  //˭����  1��� 2����
	printChess ();
	int x = 0, y = 0;
	while (1) {
		if (state == 1) {
			printf ("���(�׷�)����,��������Ҫ�µ�(x,y)����(-1,-1)����:");
			scanf ("%d%d", &x, &y);
			if (x == -1 && y == -1) {  //����
				chessToArr (state);
				system ("cls");
				printChess ();
			}
			else if (x > N || y > N || x < 1 || y < 1) {
				printf ("��������\n");
			}
			else if (chess[x][y] == 0) {
				arrToChess (state);
				chess[x][y] = state;
				system ("cls");
				printChess ();
				judgeWin (x, y, state);
				state = state % 2 + 1;
			}
		}
		else if (state == 2) {
			int t;
			system ("cls");
			for (t = 4; t >= 0; t--) {  //ѭ���ж�  Ѱ�����һ��  4��3��2��1��0
				if (PCPlay (x, y, t)) {
					break;
				}
			}
			state = state % 2 + 1;
		}
	}
}


int main () {
	printf ("*************������*************\n\n");
	printf ("\t1.���˶�ս\n");
	printf ("\t2.�˻���ս\n");
	printf ("\t3.�˳���Ϸ\n");
	printf ("\n******************************\n");
	printf ("��ѡ��:");
	int option;
	while (1) {
		scanf ("%d", &option);
		if (option == 1) {
			PPGame ();
		}
		else if (option == 2) {
			PCGame ();
		}
		else if (option == 3) {
			exit (1);
		}
		else {
			printf ("������������������:");
		}
	}
	return 0;
}



