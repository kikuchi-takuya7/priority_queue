#include<iostream>
#include "Astar.h"

using std::cin;
using std::cout;
using std::endl;

Astar::Astar()
{
}

void Astar::Input()
{
	cout << "縦と横を入力" << endl;
	cin >> h_;
	cin >> w_;

	

	for (int i = 0; i < h_; i++) {
		map_.emplace_back(w_);//w分の行を先にh列分だけ確保しておく
		dist_.emplace_back(w_);
		rest_.emplace_back(w_);
	}

	//壁は99でいいよね?悩み中
	cout << "マップのコストを入力してね。99なら壁(仮)" << endl;
	for (int i = 0; i < h_; i++) {
		for (int f = 0; f < w_; f++) {
			int n = 0;
			cin >> n;
			map_.at(i).at(f) = n;
			rest_[i][f] = Pair(i, f); //restにxy座標を入れる
		}
	}

	cout << "スタート地点を入力" << endl;
	int x, y;
	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;

	start_ = std::make_pair(x, y);//スタート地点から探索を始める
	rest_.at(0).at(0) = Pair(x, y); //スタート地点の座標
	que_.emplace(x, y);//スタート地点から探索を始める

	cout << "ゴール入力" << endl;
	int goalX, goalY;
	cout << "X = "; cin >> goalX;
	cout << "Y = "; cin >> goalY;

	goal_ = std::make_pair(goalX, goalY);

	dist_.at(x).at(y) = map_.at(x).at(y); //スタート地点のコストを入れる
}

void Astar::Initialize()
{
	h_ = 0;
	w_ = 0;

	const int Inf = 9999999;//まだ探索していない

	start_ = std::make_pair(0, 0);//スタート地点から探索を始める
	goal_ = std::make_pair(0, 0);
	dist_.assign(h_, vector<long long>(w_, Inf));//初期化

}

void Astar::Astar_Basic()
{
	while (!que_.empty())
	{
		Pair now = que_.top();//今いる場所を確保
		que_.pop();

		for (int i = 0; i < 8; i++) {
			int ny = now.first;//今いる場所 NowY
			int nx = now.second;
			int sy = ny + moveY[i];//今から探索する場所 SecondY
			int sx = nx + moveX[i];
			if (sy < 0 || sy >= h_ || sx < 0 || sx >= w_) {// 画面外なら
				continue;
			}
			if (dist_.at(sy).at(sx) <= dist_.at(ny).at(nx) + map_.at(sy).at(sx)) { //これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋vのコスト分で今現在わかっている最短距離）でないなら。
				continue;													  //今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
			}
			que_.emplace(sy, sx);
			rest_.at(sy).at(sx) = Pair(ny, nx); //最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う
			dist_.at(sy).at(sx) = dist_.at(ny).at(nx) + map_.at(sy).at(sx);//最短距離の更新
		}
	}
}

void Astar::Path_Search()
{
}

int Astar::Heuristic(int _x, int _y)
{
	int x = _x - goal_.first;
	int y = _y - goal_.second;

	return abs(x + y);
}
