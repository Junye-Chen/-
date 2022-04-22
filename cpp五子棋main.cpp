#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<vector>

#include"chessboard.h"
#include"gamerunning.h"
#include"player.h"
#include"wincheck.h"
#include"AI.h"

using namespace std;

void setgamesurface();
void help();			//提示文档

int main()
{
	setgamesurface();
	//创建对象
	wincheck judge;
	Player player1, player2;
	AI ai;

	int n = 0;
	while (true)
	{
		if (n == 0) help();
		cout << "1、人机对战 or 2、人人对战？" << endl;
		char mode;
		cin >> mode;
		cout << "请选择棋子颜色 B / W ？" << endl;
		char chesscolor;
		
		if (mode == '1') {
			cin >> chesscolor;
			switch (chesscolor)
			{
			case 66:// B
			case 98:
				player1.setmark(1);
				ai.setmark(2);
				break;
			case 87:// W
			case 119:
				player1.setmark(2);
				ai.setmark(1);
				break;
			}
			//定义新游戏
			Gamerunning newgame1(player1, ai, judge);
			newgame1.initgamesurface();		//清空数组
			newgame1.rungame(ai.getmark());//游戏进行
		}
		
		else {
			cin >> chesscolor;
			switch (chesscolor)
			{
			case 66:// B
			case 98:
				player1.setmark(1);
				player2.setmark(2);
				break;
			case 87:// W
			case 119:
				player1.setmark(2);
				player2.setmark(1);
				break;
			}
			//定义新游戏
			Gamerunning newgame(player1, player2, judge);
			newgame.initgamesurface();		//清空数组
			newgame.rungame();//游戏进行
			
		}
		
		
		

		
		cout << "再来一局？ Y / N " << endl;
		char d;
		cin >> d;
		if (d == 'Y' || d == 'y') {
			n = 1;
			continue;
		} else {
			cout << "游戏结束！" << endl;
			break;
		}
	}
	return 0;
}

//设置游戏界面
void setgamesurface() {
	//设置游戏界面
	SetConsoleTitle(L"五子棋");
	system("color E0");//颜色
	system("mode con cols=40 lines=25");//size
};
void help() {
	cout << "/*************HELP*************/\n";
	cout << "a：向左\nd：向右\nw：向上\ns：向下\n";
	cout << "space：下子"<<endl;
	cout << "r：悔棋" << endl;
	cout << "p：中途退出当前游戏" << endl;
	cout << "........................." << endl;
}

