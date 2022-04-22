#ifndef player_
#define player_
class Player
{
public:
	Player(){};   
	Player(Player &p) { mark = p.mark; };
	int getmark() const { return mark; };
	void setmark(int x) { mark = x; };
	~Player() {};

private:
	int mark;
};

#endif // !player_
#pragma once
