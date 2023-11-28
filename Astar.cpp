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

	//壁は99でいいよね
	cout << "マップのコストを入力してね。99なら壁" << endl;
	for (int i = 0; i < h_; i++) {
		for (int f = 0; f < w_; f++) {
			int n = 0;
			cin >> n;
			map_.at(i).at(f) = n;
			rest_[i][f] = Pair(i, f); //restにxy座標を入れる
		}
	}
}

void Astar::Initialize()
{
}

void Astar::Astar_Basic()
{
}

void Astar::Path_Search()
{
}

void Astar::Heuristic(int _x, int _y)
{
}
