#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
#include <conio.h>

void clear();
void gotoxy(int x, int y);
void intro();
void game_system_select();
void game_system_drop();
void game_system_remove();
void game_system_UI();
int game_system_gameover();

int start;//start_time
int end;//end_time
int board[21][10];
int num1 = 0;
int num2 = 0;
int score = 0;	
bool isBlockdropped = FALSE;
bool isLeftempty = TRUE;
bool isRightempty = TRUE;
bool isDownempty = TRUE;

int main() {
	srand((unsigned)time(NULL));
	intro();
	//board[20][x]���� 0����
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 0;
		}
	}
	//board[20][x] -1����
	for (int i = 0; i < 10; i++) {
		board[20][i] = -1;

	}
	//����
	while (1) {
		//board�� ��� ����
		game_system_select();
		while (1) {

			clear();
			//���ӿ��� ����
			if (game_system_gameover() == 1) {
				break;
			}
			
			//��� �������̽�
			for (int i = 0; i < 21; i++) {
				for (int j = 0; j < 10; j++) {
					//�ƹ��͵� ������ 0
					if (board[i][j] == 0) {
						printf("O  ");
					}
					//�������� ��� #
					else if (board[i][j] == 1) {
						printf("#  ");
					}
					//��ġ�� ��� @
					else if (board[i][j] == 2) {
						printf("@  ");
					}
					
				}
				printf("\n\n");

			}
			
			//��Ÿ UI
			game_system_UI();
			//���
			game_system_drop();
			//��� ����Ǿ����� �������� ���ư�
			if (isBlockdropped == TRUE) {
				isBlockdropped = FALSE;
				game_system_remove();
				break;
			}
			
		}
		if (game_system_gameover() == 1) {
			break;
		}

	}
	clear();
	printf("���ӿ��� \n����:%d", score);
}
//�α� �ʱ�ȭ
void clear() {
	system("cls");
}
//�α� �̵�
void gotoxy(int x, int y) {
	x--;
	y--;
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void intro() {
	printf("������������ ���⹰ ��Ʈ����\n");
	printf("û���� 2�г� ���ؼ�\n");
	printf("press any key to start");
	int a;
	a = _getch();
}
//���� ��� ����
void game_system_select() {
	srand((unsigned)time(NULL));
	num1 = rand() % 7;
	//Z
	if (num1 == 0) {
		board[0][3] = 1;
		board[0][4] = 1;
		board[1][4] = 1;
		board[1][5] = 1;
		num2 = 1;
	}
	//S
	else if (num1 == 1) {
		board[0][5] = 1;
		board[0][6] = 1;
		board[1][5] = 1;
		board[1][4] = 1;
		num2 = 1;
	}
	//I
	else if (num1 == 2) {
		board[0][3] = 1;
		board[0][4] = 1;
		board[0][5] = 1;
		board[0][6] = 1;
		num2 = 1;
	}
	//O
	else if (num1 == 3) {
		board[0][4] = 1;
		board[0][5] = 1;
		board[1][4] = 1;
		board[1][5] = 1;
		num2 = 1;
	}
	//J
	else if (num1 == 4) {
		board[0][6] = 1;
		board[1][4] = 1;
		board[1][5] = 1;
		board[1][6] = 1;
		num2 = 1;
	}
	//L
	else if (num1 == 5) {
		board[0][4] = 1;
		board[1][4] = 1;
		board[1][5] = 1;
		board[1][6] = 1;
		num2 = 1;
	}
	//T
	else if (num1 == 6) {
		board[0][5] = 1;
		board[1][4] = 1;
		board[1][5] = 1;
		board[1][6] = 1;
		num2 = 1;
	}
}
//��� �ϰ�
void game_system_drop() {
	//���۽ð�
	start = clock();
	char move = NULL;
	while (1) {
		move = 'q';
		//�������� Ȯ��
		end = clock();
		if (end - start == 1000) {
			break;
		}
		//Ű���� �Է� ������ ������ ����
		else if (_kbhit()) {
			move = _getch();
			printf("%c", move);
		}
		//���� �̵�
		if (move == '4') {
			isLeftempty = TRUE;
			for (int i = 19; i > -1; i--) {
				for (int j = 9; j > -1; j--) {
					//board�� 1�Ͻ�

					if (board[i][j] == 1) {
						//�� 0�̸� �϶�
						if (board[i][j - 1] == 2 || j == 0) {
							isLeftempty = FALSE;
						}
						//���� 2�� �� ��� �϶�/

					}
				}
			}
			if (isLeftempty == TRUE) {
				for (int i = 19; i > -1; i--) {
					for (int j = 0; j < 10; j++) {
						//board�� 1�Ͻ�

						if (board[i][j] == 1) {
							//���� 0�̸� �϶�
							board[i][j - 1] = 1;
							board[i][j] = 0;
						}
					}
				}
			}

			

		}

		//������ �̵�
		else if (move == '6') {
			isRightempty = TRUE;
			for (int i = 19; i > -1; i--) {
				for (int j = 9; j > -1; j--) {
					//board�� 1�Ͻ�

					if (board[i][j] == 1) {
						//�� 0�̸� �϶�
						if (board[i][j + 1] == 2 || j == 9) {
							isRightempty = FALSE;
						}
						//���� 2�� �� ��� �϶�/

					}
				}
			}
			if (isRightempty == TRUE) {
				for (int i = 19; i > -1; i--) {
					for (int j = 9; j > -1; j--) {
						//board�� 1�Ͻ�

						if (board[i][j] == 1) {
							//���� 0�̸� �϶�
							board[i][j + 1] = 1;
							board[i][j] = 0;
						}
					}
				}
			}

		}
		//�϶�
		else if (move == '2') {
			break;
		}
		//���� ȸ��
		else if (move == 'a') {

			//0 0
			//  0 0 
			if (num1 == 0) {
				int a[2];
				int b[2];
				int c[2];
				int d[2];
				if (num2 == 1) {
					for (int x = 0; x < 4; x++) {
						for (int i = 0; i < 20; i++) {
							for (int j = 0; j < 10; j++) {
								if (board[i][j] == 1) {
									if (x == 0) {
										a[0] = i;
										a[1] = j;
										board[i][j] = 0;
									}
									else if (x == 1) {
										b[0] = i;
										b[1] = j;
										board[i][j] = 0;
									}
									else if (x == 2) {
										c[0] = i;
										c[1] = j;
										board[i][j] = 0;
									}
									else if (x == 3) {
										d[0] = i;
										d[1] = j;
										board[i][j] = 0;
									}
								}
							}
						}
					}
					if (board[a[0] - 1][a[1]] == 0 && board[b[0] - 1][b[1]] == 0 && board[b[0] - 1][b[1] + 1] == 0 && board[b[0]][b[1] + 1]) {
						board[b[0] - 1][b[1] + 1] = 1;
						board[b[0]][b[1]] = 1;
						board[c[0]][c[1]] = 1;
						board[b[0]][b[1] + 1] = 1;
						num2 = 2;
					}



				}

				else if (num2 == 2) {
					for (int x = 0; x < 4; x++) {
						for (int i = 0; i < 20; i++) {
							for (int j = 0; j < 10; j++) {
								if (board[i][j] == 1) {
									if (x == 0) {
										a[0] = i;
										a[1] = j;
										board[i][j] = 0;
									}
									else if (x == 1) {
										b[0] = i;
										b[1] = j;
										board[i][j] = 0;
									}
									else if (x == 2) {
										c[0] = i;
										c[1] = j;
										board[i][j] = 0;
									}
									else if (x == 3) {
										d[0] = i;
										d[1] = j;
										board[i][j] = 0;
									}
								}
							}
						}
					}
					if (b[1] != 0) {
						board[b[0]][b[1] - 1] = 1;
						board[b[0]][b[1]] = 1;
						board[d[0]][d[1]] = 1;
						board[d[0]][d[1] + 1] = 1;
						num2 = 1;
					}
					else if (b[0] == 0) {
						board[b[0]][b[1]] = 1;
						board[c[0]][c[1]] = 1;
						board[c[0] - 1][c[1]] = 1;
						board[d[0]][d[1] + 2] = 1;
						num2 = 1;
					}
				}

			}

			//  0 0 
			//0 0   
			else if (num1 == 1) {
				int a[2];
				int b[2];
				int c[2];
				int d[2];
				if (num2 == 1) {
					for (int x = 0; x < 4; x++) {
						for (int i = 0; i < 20; i++) {
							for (int j = 0; j < 10; j++) {
								if (board[i][j] == 1) {
									if (x == 0) {
										a[0] = i;
										a[1] = j;
										board[i][j] = 0;
									}
									else if (x == 1) {
										b[0] = i;
										b[1] = j;
										board[i][j] = 0;
									}
									else if (x == 2) {
										c[0] = i;
										c[1] = j;
										board[i][j] = 0;
									}
									else if (x == 3) {
										d[0] = i;
										d[1] = j;
										board[i][j] = 0;
									}
								}
							}
						}
					}
					if (board[a[0] - 1][a[1]] == 0) {
						board[a[0] - 1][a[1]] = 1;
						board[b[0]][b[1]] = 1;
						board[a[0]][a[1]] = 1;
						board[d[0]][d[1] + 1] = 1;
						num2 = 2;
					}



				}

				else if (num2 == 2) {
					for (int x = 0; x < 4; x++) {
						for (int i = 0; i < 20; i++) {
							for (int j = 0; j < 10; j++) {
								if (board[i][j] == 1) {
									if (x == 0) {
										a[0] = i;
										a[1] = j;
										board[i][j] = 0;
									}
									else if (x == 1) {
										b[0] = i;
										b[1] = j;
										board[i][j] = 0;
									}
									else if (x == 2) {
										c[0] = i;
										c[1] = j;
										board[i][j] = 0;
									}
									else if (x == 3) {
										d[0] = i;
										d[1] = j;
										board[i][j] = 0;
									}
								}
							}
						}
					}
					if (b[1] != 0) {
						board[b[0]][d[1] - 1] = 1;
						board[b[0]][b[1]] = 1;
						board[c[0]][c[1]] = 1;
						board[d[0]][d[1] - 2] = 1;
						num2 = 1;
					}
					else if (b[0] == 0) {
						board[d[0]][d[1]] = 1;
						board[c[0]][c[1]] = 1;
						board[b[0] - 1][b[1]] = 1;
						board[c[0]][c[1] + 1] = 1;
						num2 = 1;
					}
				}
			}

			// 0 0 0 0 

			else if (num1 == 2) {
				int a[2];
				int b[2];
				int c[2];
				int d[2];
				for (int x = 0; x < 4; x++) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 10; j++) {
							if (board[i][j] == 1) {
								if (x == 0) {
									a[0] = i;
									a[1] = j;
									board[i][j] = 0;
								}
								else if (x == 1) {
									b[0] = i;
									b[1] = j;
									board[i][j] = 0;
								}
								else if (x == 2) {
									c[0] = i;
									c[1] = j;
									board[i][j] = 0;
								}
								else if (x == 3) {
									d[0] = i;
									d[1] = j;
									board[i][j] = 0;
								}
							}
						}
					}
				}
				if (num2 == 1) {
					board[c[0]][c[1] - 3] = 1;
					board[c[0]][c[1] - 2] = 1;
					board[c[0]][c[1] - 1] = 1;
					board[c[0]][c[1]] = 1;
					num2 = 2;
				}
				else if (num2 == 2) {
					if (a[1] = 0) {
						board[b[0]][b[1]] = 1;
						board[b[0]][b[1] + 1] = 1;
						board[b[0]][b[1] + 2] = 1;
						board[b[0]][b[1] + 3] = 1;
						num2 = 1;
					}
					else if (d[1] = 9) {
						board[b[0]][b[1]] = 1;
						board[b[0]][b[1] - 1] = 1;
						board[b[0]][b[1] - 2] = 1;
						board[b[0]][b[1] - 3] = 1;
						num2 = 1;
					}
					else if (d[1] = 8) {
						board[b[0]][b[1]] = 1;
						board[b[0]][b[1] + 1] = 1;
						board[b[0]][b[1] - 1] = 1;
						board[b[0]][b[1] - 2] = 1;
						num2 = 1;
					}
					else if (b[1] = 1) {
						board[b[0]][b[1]] = 1;
						board[b[0]][b[1] + 1] = 1;
						board[b[0]][b[1] - 1] = 1;
						board[b[0]][b[1] + 2] = 1;
						num2 = 1;
					}
					else {
						board[b[0]][b[1]] = 1;
						board[b[0]][b[1] + 1] = 1;
						board[b[0]][b[1] - 1] = 1;
						board[b[0]][b[1] - 2] = 1;
						num2 = 1;
					}
				}
			}


			// 0 0
			// 0 0
			else if (num1 == 3) {
				//nope
			}
			//     0 
			// 0 0 0
			else if (num1 == 4) {
				int a[2];
				int b[2];
				int c[2];
				int d[2];
				for (int x = 0; x < 4; x++) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 10; j++) {
							if (board[i][j] == 1) {
								if (x == 0) {
									a[0] = i;
									a[1] = j;
									board[i][j] = 0;
								}
								else if (x == 1) {
									b[0] = i;
									b[1] = j;
									board[i][j] = 0;
								}
								else if (x == 2) {
									c[0] = i;
									c[1] = j;
									board[i][j] = 0;
								}
								else if (x == 3) {
									d[0] = i;
									d[1] = j;
									board[i][j] = 0;
								}
							}
						}
					}
				}
				if (num2 = 1) {
					board[a[0]][a[1]] = 1;
					board[d[0]][d[1]] = 1;
					board[a[0] - 1][a[1]] = 1;
					board[a[0] - 1][a[1] - 1] = 1;
					num2 = 2;
				}
				else if (num2 = 2) {
					board[a[0]][a[1]] = 1;
					board[b[0]][b[1]] = 1;
					board[b[0]][b[1] + 1] = 1;
					board[a[0] + 1][a[1]] = 1;
					num2 = 3;
				}
				else if (num2 = 3) {
					board[a[0]][a[1]] = 1;
					board[d[0]][d[1]] = 1;
					board[b[0] - 1][a[1]] = 1;
					board[a[0] - 1][a[1]] = 1;
					num2 = 4;
				}
				else if (num2 = 4) {
					board[d[0]][d[1]] = 1;
					board[c[0]][c[1]] = 1;
					board[b[0]][b[1] + 1] = 1;
					board[c[0]][c[1] - 1] = 1;
					num2 = 1;
				}

			}

			// 0
			// 0 0 0
			else if (num1 == 5) {
				int a[2];
				int b[2];
				int c[2];
				int d[2];
				for (int x = 0; x < 4; x++) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 10; j++) {
							if (board[i][j] == 1) {
								if (x == 0) {
									a[0] = i;
									a[1] = j;
									board[i][j] = 0;
								}
								else if (x == 1) {
									b[0] = i;
									b[1] = j;
									board[i][j] = 0;
								}
								else if (x == 2) {
									c[0] = i;
									c[1] = j;
									board[i][j] = 0;
								}
								else if (x == 3) {
									d[0] = i;
									d[1] = j;
									board[i][j] = 0;
								}
							}
						}
					}
				}
				if (num2 = 1) {
					board[a[0]][a[1]] = 1;
					board[b[0]][b[1]] = 1;
					board[a[0] - 1][a[1]] = 1;
					board[b[0]][b[1] - 1] = 1;
					num2 = 2;
				}
				else if (num2 = 2) {
					board[a[0]][a[1]] = 1;
					board[b[0]][b[1]] = 1;
					board[a[0]][a[1] - 1] = 1;
					board[a[0]][a[1] - 2] = 1;
					num2 = 3;
				}
				else if (num2 = 3) {
					board[a[0]][a[1]] = 1;
					board[b[0]][b[1]] = 1;
					board[a[0] + 1][a[1]] = 1;
					board[a[0] + 2][a[1]] = 1;
					num2 = 4;
				}
				else if (num2 = 4) {
					board[a[0]][a[1]] = 1;
					board[c[0]][c[1]] = 1;
					board[c[0]][c[1] + 1] = 1;
					board[c[0]][c[1] + 2] = 1;
					num2 = 1;
				}
			}
			//  0
			//0 0 0
			else if (num1 == 6) {
				int a[2];
				int b[2];
				int c[2];
				int d[2];
				for (int x = 0; x < 4; x++) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 10; j++) {
							if (board[i][j] == 1) {
								if (x == 0) {
									a[0] = i;
									a[1] = j;
									board[i][j] = 0;
								}
								else if (x == 1) {
									b[0] = i;
									b[1] = j;
									board[i][j] = 0;
								}
								else if (x == 2) {
									c[0] = i;
									c[1] = j;
									board[i][j] = 0;
								}
								else if (x == 3) {
									d[0] = i;
									d[1] = j;
									board[i][j] = 0;
								}
							}
						}
					}
				}
				if (num2 = 1) {
					board[a[0]][a[1]] = 1;
					board[c[0]][c[1]] = 1;
					board[d[0]][d[1]] = 1;
					board[c[0] - 1][c[1]] = 1;
					num2 = 2;
				}
				else if (num2 = 2) {
					board[b[0]][b[1]] = 1;
					board[c[0]][c[1]] = 1;
					board[d[0]][d[1]] = 1;
					board[b[0]][b[1] - 1] = 1;
					num2 = 3;
				}
				else if (num2 = 3) {
					board[a[0]][a[1]] = 1;
					board[b[0]][b[1]] = 1;
					board[d[0]][d[1]] = 1;
					board[b[0] + 1][b[1]] = 1;
					num2 = 4;
				}
				else if (num2 = 4) {
					board[a[0]][a[1]] = 1;
					board[c[0]][c[1]] = 1;
					board[b[0]][b[1]] = 1;
					board[c[0]][c[1] + 1] = 1;
					num2 = 1;
				}
			}

		}

	}
	//����ϰ��ý���
	isDownempty = TRUE;
	for (int i = 19; i > -1; i--) {
		for (int j = 9; j > -1; j--) {
			//board�� 1�Ͻ�
				
			if (board[i][j] == 1) {
				//���� 0�̸� �϶�
				if (board[i + 1][j] == 2 || board[i + 1][j] == -1) {
					isDownempty = FALSE;
				}
				//���� 2�� �� ��� �϶�/
					
			}
		}
	}
	if (isDownempty == TRUE) {
		for (int i = 19; i > -1; i--) {
			for (int j = 0; j < 10; j++) {
				//board�� 1�Ͻ�

				if (board[i][j] == 1) {
					//���� 0�̸� �϶�
					board[i + 1][j] = 1;
					board[i][j] = 0;
				}
			}
		}
	}
	else {
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 10; y++) {
				if (board[x][y] == 1) {
					board[x][y] = 2;
				}
			}
		}
		isBlockdropped = TRUE;
	}
	
	
}
				//���� ����
void game_system_remove() {

	bool isLinefull[20];
	
	for (int i = 0; i < 20; i++){
		isLinefull[i] = FALSE;

	}
	for (int i = 0; i < 20; i++) {
		int blocknum = 0;
		//���� �ϼ� ���� Ȯ��
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == 2) {
				blocknum++;
			}
		}
		if (blocknum == 10) {
			isLinefull[i] = TRUE;
		}
		//���ٻ���
		

	}
	for (int i = 19; i > -1; i--) {
		if (isLinefull[i] == TRUE) {
			for (int j = 0; j < 10; j++) {
				board[i][j] = 0;

			}
			score = score + 100;
			for (int x = i - 1; x > -1; x--) {
				for (int y = 0; y < 10; y++) {
					if (board[x][y] == 2) {
						board[x][y] = 0;
						board[x + 1][y] = 2;
					}
				}
			}
			for (int x = i + 1; x < 20; x++) {
				if (isLinefull[x] == TRUE) {
					isLinefull[x - 1] = TRUE;
					isLinefull[x] = FALSE;
				}
			}
		
		}
		
	}
	
}
void game_system_UI() {
	
	gotoxy(33, 10);
	printf("����:%d", score);
	gotoxy(33, 1);
	printf("<<�� ���� ����� ��ġ�Ǹ� ���ӿ���");
}
int game_system_gameover() {
	int num = 0;
	for (int i = 0; i <10; i++) {
		if (board[0][i] == 2) {
			num = 1;
		}

	}
	if (num == 0) {
		return 0;
	}
	else {
		return 1;
	}

}