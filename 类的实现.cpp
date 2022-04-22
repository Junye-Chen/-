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
	system("cls");//清空界面
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (i == cooX && j == cooY) {
				cout << "╳ ";
			}
			else if (i == 0 && j == 0 && chessboard[0][0] != 1 && chessboard[0][0] != 2) {
				cout << "┏ ";
			}
			else if (i == 0 && j == 14 && chessboard[0][14] != 1 && chessboard[0][14] != 2) {
				cout << "┓";
			}
			else if (i == 14 && j == 0 && chessboard[14][0] != 1 && chessboard[14][0] != 2) {
				cout << "┗ ";
			}
			else if (i == 14 && j == 14 && chessboard[14][14] != 1 && chessboard[14][14] != 2) {
				cout << "┛";
			}
			else if (i == 0 && chessboard[0][j] != 1 && chessboard[0][j] != 2) {
				cout << "┳ ";
			}
			else if (i == 14 && chessboard[14][j] != 1 && chessboard[14][j] != 2) {
				cout << "┻ ";
			}
			else if (j == 0 && chessboard[i][0] != 1 && chessboard[i][0] != 2) {
				cout << "┣ ";
			}
			else if (j == 14 && chessboard[i][14] != 1 && chessboard[i][14] != 2) {
				cout << "┫";
			}
			else if (chessboard[i][j] == 1) {
				cout << "●";
			}
			else if (chessboard[i][j] == 2) {
				cout << "○";
			}
			else {
				cout << "┼ ";
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
	//加载存储的棋盘数组到当前数组，并赋值nowplayer=lastplayer;
	ifstream infile("棋谱.txt", ios::in);
	if (!infile)
	{
		cerr << "棋谱无法打开..." << endl;
		abort();
	}
	char line[20];
	infile.getline(line, 20);
	infile.getline(line, 20);		//读取玩家信息
	lastplayer = static_cast<int>(line[0]) - '0';
	infile.getline(line, 20);
	//读取棋盘数组
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
	//依次保存玩家，棋盘和棋谱
	ofstream outfile("棋谱.txt", ios::out);
	if (!outfile)
	{
		cerr << "棋谱无法打开..." << endl;
		abort();
	}
	outfile << "下一个玩家是：\n" << 3 - lastplayer << endl;
	outfile << "对局的棋盘为：\n";
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			outfile << chessboard[i][j];
		}
		outfile << endl;
	}
	outfile << "对局的棋谱为：\n";
	for (unsigned int i = 0; i < record.size(); i = i + 2)
		outfile << "(" << record[i] << "," << record[i + 1] << ")" << '\n';
	//outfile << '\n';
	outfile.close();
}

void Chessboard::print_record() const{
	ifstream infile("棋谱.txt", ios::in);
	if (!infile)
	{
		cerr << "棋谱无法打开..." << endl;
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
	cooX = cooY = 15 / 2;//坐标居中
	nowplayer = p1.getmark();

	cout << "是否要加载棋谱？ Y / N " << endl;
	char key = _getch();
	if (key == 'Y' || key == 'y') {
		load_record();
		nowplayer = lastplayer;
		cout << "棋谱加载完成...";
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
			storetemp();//记下此时棋盘数组
			if (move() == 1) {
				chessboard[cooX][cooY] = nowplayer;
				save_record(nowplayer);			//记下棋谱
				//判断胜负
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
					swap();		//换手
				}
			}
			break;
		}
		
	}
out:c1.printinf();
	
pause: 
	 cout << "要保存此次对局吗？ Y / N " << endl;//直接退出还是保存棋谱
	 char k = _getch();
	 if (k == 'Y' || k == 'y') {
		 store_record();
		 cout << "已保存对局" << endl;
		 cout << "查看对局详情...？" << endl;
		 k = _getch();
		 if (k == 'Y' || k == 'y') {
			 cout << "对局棋谱如下：" << endl;
			 print_record();
		 }
	 }
}

void Gamerunning::rungame(int s) {		//AI部分的运行

	int sign = 0;
	cooX = cooY = 15 / 2;//坐标居中

	cout << "是否要加载棋谱？ Y / N " << endl;
	char key = _getch();
	if (key == 'Y' || key == 'y') {
		load_record();
		nowplayer = lastplayer;
		cout << "棋谱加载完成...";
	}
	//判断先手
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
			storetemp();//记下此时棋盘数组
			if (move() == 1) {
				chessboard[cooX][cooY] = nowplayer;

				save_record(nowplayer);			//记下棋谱
				//判断胜负
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
					nowplayer = 3 - nowplayer;		//换手
					//AI下子
					
					Ai.find(cooX, cooY, chessboard);
					
					cooX = Ai.getx();
					cooY = Ai.gety();
					chessboard[cooX][cooY] = nowplayer;
					
					save_record(nowplayer);			//记下棋谱
				
					c1.getnote(nowplayer);//获取棋手信息
					//判断胜负
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
	cout << "要保存此次对局吗？ Y / N " << endl;//直接退出还是保存棋谱
	char k = _getch();
	if (k == 'Y' || k == 'y') {
		store_record();
		cout << "已保存对局" << endl;
		cout << "查看对局详情...？" << endl;
		k = _getch();
		if (k == 'Y' || k == 'y') {
			cout << "对局棋谱如下：" << endl;
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
		cout << "黑棋胜!" << endl;
	}
	else {
		cout << "白棋胜!" << endl;
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
	while (board[--x][y] == note)       //chessbosrd不是wincheck类的成员，考虑使用友元函数
	{
		count1++;
	}
	x = a;		//复位
	while (board[++x][y] == note)
	{
		count1++;

	}//竖向检查
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
	}//横向检查
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
	}//斜检查
	if (count4 >= 5) {
		WIN4 = 1;
	}
}


//问题出在以下两个函数中
void AI::find(int x, int y, int a[15][15]) {
	int temp[15][15];
	memset(temp, 0, sizeof(temp));
	//上
	for (int i = x - 5; i < x; i++)
	{
		if (i < 0) continue;
		temp[i][y] = evaluate(i, y, a);
	}
	//下
	for (int i = x + 1; i < x+6; i++)
	{
		if (i > 14) continue;
		temp[i][y] = evaluate(i, y, a);
	}
	//左
	for (int i = y - 5; i < y; i++)
	{
		if (i < 0) continue;
		temp[x][i] = evaluate(x, i, a);
	}
	//右
	for (int i = y + 1; i < y+6; i++)
	{
		if (i > 14) continue;
		temp[x][i] = evaluate(x, i, a);
	}
	//左上
	for (int i = x - 5, j = y-5; i < x && j < y; i++, j++)
	{
		if (i < 0 || j<0) continue;
		temp[i][j] = evaluate(i, j, a);
	}
	//右上
	for (int i = x - 1, j = y + 1; i > x-6 && j < y+6; i--, j++)
	{
		if (i < 0 || j > 14) continue;
		temp[i][j] = evaluate(i, j, a);
	}
	//左下
	for (int i = x + 5, j = y - 5; i > x && j < y; i--, j++)
	{
		if (i >14 || j < 0) continue;
		temp[i][j] = evaluate(i, j, a);
	}
	//右下
	for (int i = x + 1, j = y + 1; i < x+6 && j < y+6; i++, j++)
	{
		if (i >14 || j >14) continue;
		temp[i][j] = evaluate(i, j, a);
	}

	//搜索棋盘点中的最大值
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
	//竖向
	for (int i = x - 4; i < x + 1; i++)
	{
		for (int n = i; n < i + 5; n++) {
			if (n < 0 || n>14) continue;//数组越界检查
			//计数
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
	//横向
	bnum = 0, wnum = 0;
	for (int i = y - 4; i < y + 1; i++)
	{
		for (int n = i; n < i + 5; n++) {
			if (n < 0 || n>14) continue;
			//计数
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
	//左斜
	bnum = 0, wnum = 0;
	for (int i = x - 4,j=y-4; i < x + 1 && j<y+1 ; i++,j++)
	{
		for (int m = i, n=j; m < i + 5 && n<j+5; m++,n++) {
			if (n < 0 || m<0 || n>14 || m>14) continue;
			//计数
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
	//右斜
	bnum = 0, wnum = 0;
	for (int i = x + 4, j = y - 4; i > x - 1 && j < y + 1; i--, j++)
	{
		for (int m = i, n = j; m > i - 5 && n < j + 5; m--, n++) {
			if (n < 0 || m<0 || m > 14 || n>14) continue;
			//计数
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

