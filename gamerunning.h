#include<vector>
#include"chessboard.h"
#include"player.h"
#include"wincheck.h"
#include"AI.h"

#ifndef gamerunning_
#define gamerunning_

class Gamerunning :public Chessboard
{
public:
	Gamerunning(Player &a, Player &b, wincheck &c) :p1(a), p2(b), c1(c) {};//��֧��Ĭ�Ϲ���
	Gamerunning(Player &a, AI &b, wincheck &c) :p1(a), Ai(b), c1(c) {};
	void rungame();
	void rungame(int s);
	int move() const;
	void swap();
	void storetemp();
	void regret();
	~Gamerunning() {};

private:
	Player p1, p2;
	AI Ai;
	wincheck c1;
	int nowplayer;
	int temp[15][15];//��¼����֮ǰ������
};

#endif // !gamerunning_
#pragma once
