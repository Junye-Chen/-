#include<vector>
using namespace std;
#ifndef _chessboard_
#define _chessboard_

class Chessboard
{
public:
	Chessboard() {};
	Chessboard(int cooX, int cooY);
	void initgamesurface();
	void draw_chessboard() const;
	void save_record(int n);
	void load_record();
	void store_record();
	void print_record() const;
	~Chessboard() {};

	int cooX, cooY;
	int chessboard[15][15];
	int lastplayer;
	vector<int>record;
private:
	
};

#endif // !chessboard