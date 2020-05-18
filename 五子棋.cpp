#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>


using namespace std;

//ȫ�ֱ���
int chessboard[15][15];
int cooX, cooY;
int Player;
//��������
void draw_chessboard();
void run_game();
int move();
//�ж�ʤ�����ĸ�����
int win1();
int win2();
int win3();
int win4();

int main()
{
	//������Ϸ����
	SetConsoleTitle(L"������");
	system("color E0");//��ɫ
	system("mode con cols=40 lines=20");//size

	
	//��Ϸ��ʼ
	while (true)
	{
		run_game();
		
	if (Player == 1)
		{
			cout << "����ʤ!" << endl;
		}
		else {
			cout << "����ʤ!" << endl;
		}
		cout << "�Ƿ�����һ�֣� Y/N " << endl;
		char d;
		cin >> d;
		if (d == 'Y' || d == 'y')
			continue;
		else
			break;
	}
	return 0;
}

void draw_chessboard() {
	system("cls");//��ս���
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 15; j++){
			if(i==cooX&&j==cooY){
				cout << "�w ";
			}else if (i == 0 && j == 0) {
				cout << "�� ";
			}else if(i==0&&j==14){
				cout << "��";
			}else if (i == 14 && j == 0) {
				cout << "�� ";
			}else if (i == 14 && j == 14) {
				cout << "��";
			}else if (i == 0) {
				cout << "�� ";
			}else if (i == 14) {
				cout << "�� ";
			}else if (j == 0) {
				cout << "�� ";
			}else if (j == 14) {
				cout << "��";
			}else if (chessboard[i][j] == 1) {
				cout << "��";
			}else if (chessboard[i][j] == 2) {
				cout << "��";
			}else {
				cout << "�� ";
			}
		}
		cout << endl;
	}
}

void run_game() {
	//��ʼ��
	static int count = 0;
	memset(chessboard, 0, sizeof(chessboard));
	cooX = cooY = 15 / 2;
	Player = 1;                 //���� 1 ������ 2
	
	while (true)
	{
		draw_chessboard();
		int a = getch();
		switch (a)
		{
		case 87://up
		case 119:
			cooX--;
			if (cooX < 0) { cooX = 0; }
			break;
		case 115://down
		case 83:
			cooX++;
			if (cooX > 14) { cooX = 14; }
			break;
		case 65://left
		case 97:
			cooY--;
			if (cooY < 0) { cooY = 0; }
			break;
		case 68://right
		case 100:
			cooY++;
			if (cooY > 14) { cooY = 14; }
			break;
		case 32://move
			if (move() == 1) {
				chessboard[cooX][cooY] = Player;
				if (win1()==1|| win2() == 1 || win3() == 1 || win4() == 1) {
					goto out;
				}
				else {
					Player == 1 ? Player = 2 : Player = 1;
					count++;
				}
			}
			break;
		}
	}
out: cout << "�غ���=" << count+1 << endl;
}

int move() {
	if (chessboard[cooX][cooY] == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int win1() {
	int count1 = 1;
	int x = cooX;
	int y = cooY;
	while (chessboard[--x][y] == Player)
	{
		count1++;
	}
	x = cooX;
	while (chessboard[++x][y] == Player)
	{
		count1++;

	}//������
	if (count1 == 5) {
		return 1;
	}
	else {
		return 0;
	}
}

int win2() {
	int count2 = 1;
	int x, y;
	x = cooX;
	y = cooY;
	while (chessboard[x][--y] == Player)
	{
		count2++;
	}y = cooY;
	while (chessboard[x][++y] == Player)
	{
		count2++;
	}//������
	if (count2 == 5) {
		return 1;
	}
	else {
		return 0;
	}
}
int win3() {
	int count3 = 1;
	int x, y;
	x = cooX;
	y = cooY;
	while (chessboard[--x][--y] == Player)
	{
		count3++;
	}
	x = cooX;
	y = cooY;
	while (chessboard[++x][++y] == Player)
	{
		count3++;
	}
	if (count3== 5) {
		return 1;
	}
	else {
		return 0;
	}
}
int win4() {
	int count4 = 1;
	int x, y;
	x = cooX;
	y = cooY;
	while (chessboard[++x][--y] == Player)
	{
		count4++;
	}
	x = cooX;
	y = cooY;
	while (chessboard[--x][++y] == Player)
	{
		count4++;
	}//б���
	if (count4 == 5) {
		return 1;
	}
	else {
		return 0;
	}
}