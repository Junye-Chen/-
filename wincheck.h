
#ifndef _wincheck
#define _wincheck
class wincheck
{
public:
	wincheck() {};
	//判断胜出的四个方向
	void win1(int a, int b, int c[15][15]);
	void win2(int a, int b, int c[15][15]);
	void win3(int a, int b, int c[15][15]);
	void win4(int a, int b, int c[15][15]);
	int win() const;
	void getnote(int n);
	void printinf() const;
	~wincheck() {};
	
private:
	int note, cooX, cooY;
	int count1, count2, count3, count4;
	int WIN1, WIN2, WIN3, WIN4;
	int board[15][15];
};
#endif // !_wincheck
#pragma once

