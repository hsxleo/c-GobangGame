#include <stdio.h>
#include <stdlib.h>

#define N 20
int chess[N+1][N+1] = { 0 };  //棋盘的数组
int arr1[N + 1][N + 1] = { 0 }; //黑棋上一步的状态
int arr2[N + 1][N + 1] = { 0 }; //白棋上一步的状态


//打印棋盘
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
				printf (" ●");
			}
			else if (chess[i][j] == 2) {
				printf (" ○");
			}
		}
		printf ("\n");
	}
}

//记录上一步
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

//返回到上一步
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


//输出结束
void inputOver (int state) {
	if (state == 1) {
		printf ("游戏结束，白方获胜");
	}
	else if (state == 2) {
		printf ("游戏结束，黑方获胜");
	}
	while (1) {
		;
	}
}

//判断游戏是否结束
void judgeWin (int x, int y, int state) {
	int count = 0;
	int i,j;
	for (i = x - 4; i <= x + 4; i++) {  //垂直方向
		if (i < 0 || i > N) continue;
		if (chess[i][y] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
	count = 0;
	for (i = y - 4; i <= y + 4; i++) {  //水平方向
		if (i < 0 || i > N) continue;
		if (chess[x][i] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
	count = 0;
	for (i = x - 4, j = y - 4; i <= x + 4; i++, j++) {   //正对角线
		if (i < 0 || i > N || j < 0 || j > N) continue;
		if (chess[i][j] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
	count = 0;
	for (i = x - 4, j = y + 4; i <= x + 4; i++, j--) {   //反对角线
		if (i < 0 || i > N || j < 0 || j > N) continue;
		if (chess[i][j] != state) count = 0;
		else {
			count++;
			if (count == 5) inputOver (state);
		}
	}
}

//人人
void PPGame() {
	int state = 1;  //谁下棋  1白棋 2黑棋
	system ("cls");
	printChess ();
	while (1) {
		if (state == 1) {
			printf ("白方下棋,请输入你要下的(x,y)坐标(-1,-1)悔棋:");
		}
		else if (state == 2) {
			printf ("黑方下棋,请输入你要下的(x,y)坐标(-1,-1)悔棋:");
		}
		int x, y;
		scanf ("%d%d", &x, &y);
		if (x == -1 && y == -1) {  //悔棋
			system ("cls");
			chessToArr (state);
			printChess ();
		}
		else if (x > N || y > N || x < 1 || y < 1) {
			printf ("输入有误，请重新输入:");
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
			printf ("输入有误\n");
		}
	}
}


/*
白棋为玩家  黑棋为电脑

白棋下一子电脑会对白棋周围的8个方向进行判断，找到一种最优先要解决的，然后在比如有四个连续的，我们就要在这段连续棋子的一端或另一端用黑棋堵住，
如果四个连续的8个方向都没有，就继续往下找，找3个的，找2个依次类推。
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
		for (int i = x - n; i <= x; i++) {  //水平方向
			if (i < 1) break;  //出界判断
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //连续个数满足   在两头进行堵塞
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
		for (int i = x; i <= x + n; i++) {  //水平方向
			if (i > N) break;
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //连续个数满足   在两头进行堵塞
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
		for (int i = y - n; i <= y; i++) {  //垂直方向
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
		for (int i = y; i <= y + n; i++) {  //垂直方向
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
		for (int i = y; i <= y + n; i++) {  //垂直方向
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
		for (int i = y - n; i <= y; i++) {  //垂直方向
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
		for (int i = x; i <= x + n; i++) {  //水平方向
			if (i > N) break;
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //连续个数满足   在两头进行堵塞
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
		for (int i = x - n; i <= x; i++) {  //水平方向
			if (i < 1) break;  //出界判断
			if (chess[i][y] != state) break;
			else {
				count++;
				if (count == m) {  //连续个数满足   在两头进行堵塞
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
	for (int i = x - n, j = y - n; i <= x; i++, j++) {   //主对角线
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
	for (int i = x, j = y; i <= x + n; i++, j++) {   //主对角线
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
	for (int i = x - n, j = y + n; i <= x; i++, j--) {   //副对角线
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
	for (int i = x, j = y; i <= x + n; i++, j--) {   //副对角线
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

//人机
void PCGame () {
	int state = 1;  //谁下棋  1玩家 2电脑
	printChess ();
	int x = 0, y = 0;
	while (1) {
		if (state == 1) {
			printf ("玩家(白方)下棋,请输入你要下的(x,y)坐标(-1,-1)悔棋:");
			scanf ("%d%d", &x, &y);
			if (x == -1 && y == -1) {  //悔棋
				chessToArr (state);
				system ("cls");
				printChess ();
			}
			else if (x > N || y > N || x < 1 || y < 1) {
				printf ("输入有误\n");
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
			for (t = 4; t >= 0; t--) {  //循环判断  寻找最急的一种  4、3、2、1、0
				if (PCPlay (x, y, t)) {
					break;
				}
			}
			state = state % 2 + 1;
		}
	}
}


int main () {
	printf ("*************五子棋*************\n\n");
	printf ("\t1.人人对战\n");
	printf ("\t2.人机对战\n");
	printf ("\t3.退出游戏\n");
	printf ("\n******************************\n");
	printf ("请选择:");
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
			printf ("输入有误请重新输入:");
		}
	}
	return 0;
}



