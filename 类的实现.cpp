#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include"chessboard.h"
#include"gamerunning.h"
#include"player.h"
#include"wincheck.h"
#include"AI.h"

using namespace std;

Chessboard::Chessboard(int x, int y):cooX(x),cooY(y) {

}

void Chessboard::initgamesurface() {
	memset(chessboard, 0, sizeof(chessboard));
}

void Chessboard::draw_chessboard() const {
	system("cls");//��ս���
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (i == cooX && j == cooY) {
				cout << "�w ";
			}
			else if (i == 0 && j == 0 && chessboard[0][0] != 1 && chessboard[0][0] != 2) {
				cout << "�� ";
			}
			else if (i == 0 && j == 14 && chessboard[0][14] != 1 && chessboard[0][14] != 2) {
				cout << "��";
			}
			else if (i == 14 && j == 0 && chessboard[14][0] != 1 && chessboard[14][0] != 2) {
				cout << "�� ";
			}
			else if (i == 14 && j == 14 && chessboard[14][14] != 1 && chessboard[14][14] != 2) {
				cout << "��";
			}
			else if (i == 0 && chessboard[0][j] != 1 && chessboard[0][j] != 2) {
				cout << "�� ";
			}
			else if (i == 14 && chessboard[14][j] != 1 && chessboard[14][j] != 2) {
				cout << "�� ";
			}
			else if (j == 0 && chessboard[i][0] != 1 && chessboard[i][0] != 2) {
				cout << "�� ";
			}
			else if (j == 14 && chessboard[i][14] != 1 && chessboard[i][14] != 2) {
				cout << "��";
			}
			else if (chessboard[i][j] == 1) {
				cout << "��";
			}
			else if (chessboard[i][j] == 2) {
				cout << "��";
			}
			else {
				cout << "�� ";
			}
		}
		cout << endl;
	}
}

void Chessboard::save_record(int n) {
	record.push_back(cooX + 1);
	record.push_back(cooY + 1);
	lastplayer = n;
}

void Chessboard::load_record() {
	//���ش洢���������鵽��ǰ���飬����ֵnowplayer=lastplayer;
	ifstream infile("����.txt", ios::in);
	if (!infile)
	{
		cerr << "�����޷���..." << endl;
		abort();
	}
	char line[20];
	infile.getline(line, 20);
	infile.getline(line, 20);		//��ȡ�����Ϣ
	lastplayer = static_cast<int>(line[0]) - '0';
	infile.getline(line, 20);
	//��ȡ��������
	for (int i = 0; i < 15; i++)
	{
		infile.getline(line, 20);
		for (int j = 0; j < 15; j++)
		{
			chessboard[i][j] = static_cast<int>(line[j]) - '0';
		}
	}
	infile.close();
}

void Chessboard::store_record() {
	//���α�����ң����̺�����
	ofstream outfile("����.txt", ios::out);
	if (!outfile)
	{
		cerr << "�����޷���..." << endl;
		abort();
	}
	outfile << "��һ������ǣ�\n" << 3 - lastplayer << endl;
	outfile << "�Ծֵ�����Ϊ��\n";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			outfile << chessboard[i][j];
		}
		outfile << endl;
	}
	outfile << "�Ծֵ�����Ϊ��\n";
	for (unsigned int i = 0; i < record.size(); i = i + 2)
		outfile << "(" << record[i] << "," << record[i + 1] << ")" << '\n';
	//outfile << '\n';
	outfile.close();
}

void Chessboard::print_record() const{
	ifstream infile("����.txt", ios::in);
	if (!infile)
	{
		cerr << "�����޷���..." << endl;
		abort();
	}
	char line[20];
	for (int i = 0; i < 19; i++)
	{
		infile.getline(line, 20);
	}
	while (!infile.eof()) {
		infile.getline(line, 20);
		cout << line << endl;
	}
	infile.close();
}

void Gamerunning::rungame() {

	int sign = 0;
	cooX = cooY = 15 / 2;//�������
	nowplayer = p1.getmark();

	cout << "�Ƿ�Ҫ�������ף� Y / N " << endl;
	char key = _getch();
	if (key == 'Y' || key == 'y') {
		load_record();
		nowplayer = lastplayer;
		cout << "���׼������...";
	}

	while (true)
	{
		draw_chessboard();
		int a = _getch();
		switch (a)
		{
		case 87://up W
		case 119:
			cooX--;
			if (cooX < 0) { cooX = 0; }
			break;
		case 115://down S
		case 83:
			cooX++;
			if (cooX > 14) { cooX = 14; }
			break;
		case 65://left A
		case 97:
			cooY--;
			if (cooY < 0) { cooY = 0; }
			break;
		case 68://right D
		case 100:
			cooY++;
			if (cooY > 14) { cooY = 14; }
			break;
		case 82://regret R
		case 114:
			regret();
			swap();
			break;
		case 80:	//pause p
		case 112:
			sign = 1;
			goto pause;
		case 32://move   space
			storetemp();//���´�ʱ��������
			if (move() == 1) {
				chessboard[cooX][cooY] = nowplayer;
				save_record(nowplayer);			//��������
				//�ж�ʤ��
				c1.getnote(nowplayer);
				c1.win1(cooX, cooY, chessboard);
				c1.win2(cooX, cooY, chessboard); 
				c1.win3(cooX, cooY, chessboard);
				c1.win4(cooX, cooY, chessboard);
				if (c1.win()) {
					goto out;
				}
				else
				{
					swap();		//����
				}
			}
			break;
		}
		
	}
out:c1.printinf();
	
pause: 
	 cout << "Ҫ����˴ζԾ��� Y / N " << endl;//ֱ���˳����Ǳ�������
	 char k = _getch();
	 if (k == 'Y' || k == 'y') {
		 store_record();
		 cout << "�ѱ���Ծ�" << endl;
		 cout << "�鿴�Ծ�����...��" << endl;
		 k = _getch();
		 if (k == 'Y' || k == 'y') {
			 cout << "�Ծ��������£�" << endl;
			 print_record();
		 }
	 }
}

void Gamerunning::rungame(int s) {		//AI���ֵ�����

	int sign = 0;
	cooX = cooY = 15 / 2;//�������

	cout << "�Ƿ�Ҫ�������ף� Y / N " << endl;
	char key = _getch();
	if (key == 'Y' || key == 'y') {
		load_record();
		nowplayer = lastplayer;
		cout << "���׼������...";
	}
	//�ж�����
	if (s==1)
	{
		chessboard[cooX][cooY] = 1;
		nowplayer = p1.getmark();
	}
	else {
		nowplayer = p1.getmark();
	}

	while (true)
	{
		draw_chessboard();
		int a = _getch();
		switch (a)
		{
		case 87://up W
		case 119:
			cooX--;
			if (cooX < 0) { cooX = 0; }
			break;
		case 115://down S
		case 83:
			cooX++;
			if (cooX > 14) { cooX = 14; }
			break;
		case 65://left A
		case 97:
			cooY--;
			if (cooY < 0) { cooY = 0; }
			break;
		case 68://right D
		case 100:
			cooY++;
			if (cooY > 14) { cooY = 14; }
			break;
		case 82://regret R
		case 114:
			regret();
			swap();
			break;
		case 80:	//pause p
		case 112:
			sign = 1;
			goto pause;
		case 32://move   space
			storetemp();//���´�ʱ��������
			if (move() == 1) {
				chessboard[cooX][cooY] = nowplayer;

				save_record(nowplayer);			//��������
				//�ж�ʤ��
				c1.getnote(nowplayer);

				c1.win1(cooX, cooY, chessboard);
				c1.win2(cooX, cooY, chessboard);
				c1.win3(cooX, cooY, chessboard);
				c1.win4(cooX, cooY, chessboard);
				if (c1.win()) {
					goto out;
				}
				else
				{
					nowplayer = 3 - nowplayer;		//����
					//AI����
					
					Ai.find(cooX, cooY, chessboard);
					
					cooX = Ai.getx();
					cooY = Ai.gety();
					chessboard[cooX][cooY] = nowplayer;
					
					save_record(nowplayer);			//��������
				
					c1.getnote(nowplayer);//��ȡ������Ϣ
					//�ж�ʤ��
					c1.win1(cooX, cooY, chessboard);
					c1.win2(cooX, cooY, chessboard);
					c1.win3(cooX, cooY, chessboard);
					c1.win4(cooX, cooY, chessboard);
					if (c1.win()) {
						goto out;
					}
					nowplayer = 3 - nowplayer;
				}
			}
			break;
		}

	}
out:c1.printinf();

pause:
	cout << "Ҫ����˴ζԾ��� Y / N " << endl;//ֱ���˳����Ǳ�������
	char k = _getch();
	if (k == 'Y' || k == 'y') {
		store_record();
		cout << "�ѱ���Ծ�" << endl;
		cout << "�鿴�Ծ�����...��" << endl;
		k = _getch();
		if (k == 'Y' || k == 'y') {
			cout << "�Ծ��������£�" << endl;
			print_record();
		}
	}
}

int Gamerunning::move() const{
	if (chessboard[cooX][cooY] == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void Gamerunning::swap() {
	nowplayer == p1.getmark() ? nowplayer = p2.getmark() : nowplayer = p1.getmark();
}

void Gamerunning::regret() { 
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			chessboard[i][j] = temp[i][j];
		}
	}
}

void Gamerunning::storetemp() {
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			temp[i][j] = chessboard[i][j];
		}
	}
}

void wincheck::getnote(int n) {
	note = n;
}
void wincheck::printinf() const {
	if (note == 1)
	{
		cout << "����ʤ!" << endl;
	}
	else {
		cout << "����ʤ!" << endl;
	}
}

int wincheck::win() const {
	if (WIN1 == 1 || WIN2 == 1 || WIN3 == 1 || WIN4 == 1)
	{
		return 1;
	}
	else {
		return 0;
	}
}
void wincheck::win1(int a, int b, int c[15][15]) {
	int x = a;
	int y = b;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = c[i][j];
		}
	}

	count1 = 1;
	while (board[--x][y] == note)       //chessbosrd����wincheck��ĳ�Ա������ʹ����Ԫ����
	{
		count1++;
	}
	x = a;		//��λ
	while (board[++x][y] == note)
	{
		count1++;

	}//������
	if (count1 >= 5) {
		WIN1 = 1;
	}
}
void wincheck::win2(int a, int b, int c[15][15]) {
	int x = a;
	int y = b;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = c[i][j];
		}
	}

	count2 = 1;
	while (board[x][--y] == note)
	{
		count2++;
	}y = b;
	while (board[x][++y] == note)
	{
		count2++;
	}//������
	if (count2 >= 5) {
		WIN2 = 1;
	}
}
void wincheck::win3(int a, int b, int c[15][15]) {
	int x = a;
	int y = b;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = c[i][j];
		}
	}

	count3 = 1;
	while (board[--x][--y] == note)
	{
		count3++;
	}
	x = a;
	y = b;
	while (board[++x][++y] == note)
	{
		count3++;
	}
	if (count3 >= 5) {
		WIN3 = 1;
	}
}
void wincheck::win4(int a, int b, int c[15][15]) {
	int x = a;
	int y = b;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = c[i][j];
		}
	}

	count4 = 1;
	while (board[++x][--y] == note)
	{
		count4++;
	}
	x = a;
	y = b;
	while (board[--x][++y] == note)
	{
		count4++;
	}//б���
	if (count4 >= 5) {
		WIN4 = 1;
	}
}


//���������������������
void AI::find(int x, int y, int a[15][15]) {
	int temp[15][15];
	memset(temp, 0, sizeof(temp));
	//��
	for (int i = x - 5; i < x; i++)
	{
		if (i < 0) continue;
		temp[i][y] = evaluate(i, y, a);
	}
	//��
	for (int i = x + 1; i < x+6; i++)
	{
		if (i > 14) continue;
		temp[i][y] = evaluate(i, y, a);
	}
	//��
	for (int i = y - 5; i < y; i++)
	{
		if (i < 0) continue;
		temp[x][i] = evaluate(x, i, a);
	}
	//��
	for (int i = y + 1; i < y+6; i++)
	{
		if (i > 14) continue;
		temp[x][i] = evaluate(x, i, a);
	}
	//����
	for (int i = x - 5, j = y-5; i < x && j < y; i++, j++)
	{
		if (i < 0 || j<0) continue;
		temp[i][j] = evaluate(i, j, a);
	}
	//����
	for (int i = x - 1, j = y + 1; i > x-6 && j < y+6; i--, j++)
	{
		if (i < 0 || j > 14) continue;
		temp[i][j] = evaluate(i, j, a);
	}
	//����
	for (int i = x + 5, j = y - 5; i > x && j < y; i--, j++)
	{
		if (i >14 || j < 0) continue;
		temp[i][j] = evaluate(i, j, a);
	}
	//����
	for (int i = x + 1, j = y + 1; i < x+6 && j < y+6; i++, j++)
	{
		if (i >14 || j >14) continue;
		temp[i][j] = evaluate(i, j, a);
	}

	//�������̵��е����ֵ
	int max = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (temp[i][j]!=0 && temp[i][j]>max && a[i][j]==0)
			{
				max = temp[i][j];
				xmax = i;
				ymax = j;
			}
		}
	}

}

int AI::evaluate(int x, int y, int c[15][15]) {
	int bnum=0, wnum=0,sum=0;
	//����
	for (int i = x - 4; i < x + 1; i++)
	{
		for (int n = i; n < i + 5; n++) {
			if (n < 0 || n>14) continue;//����Խ����
			//����
			if (c[n][y] == 1) {
				bnum++;
			}
			else if (c[n][y] == 2) {
				wnum++;
			}
		}
		if (bnum != 0 && wnum != 0) {
			sum += scoretable[9];
		}
		else if(bnum == 0 && wnum == 0){
			sum += scoretable[0];
		}
		else if (bnum == 1 && wnum == 0) {
			sum += scoretable[1];
		}
		else if (bnum == 2 && wnum == 0) {
			sum += scoretable[2];
		}
		else if (bnum == 3 && wnum == 0) {
			sum += scoretable[3];
		}
		else if (bnum == 4 && wnum == 0) {
			sum += scoretable[4];
		}
		else if (bnum == 0 && wnum == 1) {
			sum += scoretable[5];
		}
		else if (bnum == 0 && wnum == 2) {
			sum += scoretable[6];
		}
		else if (bnum == 0 && wnum == 3) {
			sum += scoretable[7];
		}
		else if (bnum == 0 && wnum == 4) {
			sum += scoretable[8];
		}
	}
	//����
	bnum = 0, wnum = 0;
	for (int i = y - 4; i < y + 1; i++)
	{
		for (int n = i; n < i + 5; n++) {
			if (n < 0 || n>14) continue;
			//����
			if (c[x][n] == 1) {
				bnum++;
			}
			else if (c[x][n] == 2) {
				wnum++;
			}
		}
		if (bnum != 0 && wnum != 0) {
			sum += scoretable[9];
		}
		else if (bnum == 0 && wnum == 0) {
			sum += scoretable[0];
		}
		else if (bnum == 1 && wnum == 0) {
			sum += scoretable[1];
		}
		else if (bnum == 2 && wnum == 0) {
			sum += scoretable[2];
		}
		else if (bnum == 3 && wnum == 0) {
			sum += scoretable[3];
		}
		else if (bnum == 4 && wnum == 0) {
			sum += scoretable[4];
		}
		else if (bnum == 0 && wnum == 1) {
			sum += scoretable[5];
		}
		else if (bnum == 0 && wnum == 2) {
			sum += scoretable[6];
		}
		else if (bnum == 0 && wnum == 3) {
			sum += scoretable[7];
		}
		else if (bnum == 0 && wnum == 4) {
			sum += scoretable[8];
		}
	}
	//��б
	bnum = 0, wnum = 0;
	for (int i = x - 4,j=y-4; i < x + 1 && j<y+1 ; i++,j++)
	{
		for (int m = i, n=j; m < i + 5 && n<j+5; m++,n++) {
			if (n < 0 || m<0 || n>14 || m>14) continue;
			//����
			if (c[m][n] == 1) {
				bnum++;
			}
			else if (c[m][n] == 2) {
				wnum++;
			}
		}
		if (bnum != 0 && wnum != 0) {
			sum += scoretable[9];
		}
		else if (bnum == 0 && wnum == 0) {
			sum += scoretable[0];
		}
		else if (bnum == 1 && wnum == 0) {
			sum += scoretable[1];
		}
		else if (bnum == 2 && wnum == 0) {
			sum += scoretable[2];
		}
		else if (bnum == 3 && wnum == 0) {
			sum += scoretable[3];
		}
		else if (bnum == 4 && wnum == 0) {
			sum += scoretable[4];
		}
		else if (bnum == 0 && wnum == 1) {
			sum += scoretable[5];
		}
		else if (bnum == 0 && wnum == 2) {
			sum += scoretable[6];
		}
		else if (bnum == 0 && wnum == 3) {
			sum += scoretable[7];
		}
		else if (bnum == 0 && wnum == 4) {
			sum += scoretable[8];
		}
	}
	//��б
	bnum = 0, wnum = 0;
	for (int i = x + 4, j = y - 4; i > x - 1 && j < y + 1; i--, j++)
	{
		for (int m = i, n = j; m > i - 5 && n < j + 5; m--, n++) {
			if (n < 0 || m<0 || m > 14 || n>14) continue;
			//����
			if (c[m][n] == 1) {
				bnum++;
			}
			else if (c[m][n] == 2) {
				wnum++;
			}
		}
		if (bnum != 0 && wnum != 0) {
			sum += scoretable[9];
		}
		else if (bnum == 0 && wnum == 0) {
			sum += scoretable[0];
		}
		else if (bnum == 1 && wnum == 0) {
			sum += scoretable[1];
		}
		else if (bnum == 2 && wnum == 0) {
			sum += scoretable[2];
		}
		else if (bnum == 3 && wnum == 0) {
			sum += scoretable[3];
		}
		else if (bnum == 4 && wnum == 0) {
			sum += scoretable[4];
		}
		else if (bnum == 0 && wnum == 1) {
			sum += scoretable[5];
		}
		else if (bnum == 0 && wnum == 2) {
			sum += scoretable[6];
		}
		else if (bnum == 0 && wnum == 3) {
			sum += scoretable[7];
		}
		else if (bnum == 0 && wnum == 4) {
			sum += scoretable[8];
		}
	}
	return sum;
}

