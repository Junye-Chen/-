#include"player.h"

#ifndef AI_
#define AI_

class AI:public Player
{
public:
	AI() {};
	AI(AI &p) { mark = p.mark; };
	void find(int x, int y, int a[15][15]);
	int evaluate(int x, int y,int c[15][15]);
	int getmark() const { return mark; };
	void setmark(int x) { mark = x; };
	int getx() const { return xmax; };
	int gety() const { return ymax; };
	~AI() {};

private:
	int mark;
	int xmax, ymax;
	const int scoretable[10] = { 10,35,800,150000,8000000,20,500,100000,4000000,0 }; //局势评分表
};

#endif // !AI

