#pragma once
#include <vector>
#include <utility> // std::pair
#include <queue>
#include <functional> // std::greater

const int dy[4] = { 0,0,1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
const int dx[4] = { 1,-1,0,0 };

using std::vector;

using std::pair;
using Pair = pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //二次元配列上のグラフ
using PqP = std::priority_queue<Pair, vector<Pair>, std::greater<Pair>>; //昇順で要素を入れておく

class Astar
{
public:

	Astar();

	void Input();
	
	void Initialize();

	void Astar_Basic();

	void Path_Search();

	void Heuristic(int _x, int _y);


private:

	int h_, w_; //縦幅と横幅
	pair<int, int> start_;
	pair<int, int> goal_;

	Graph map_;    //マップのコストを入れる。
	Graph dist_; //マップの位置に連動してその頂点までどのぐらいの数で行けるか追加する
	vector<vector<Pair>> rest_; //経路復元に使用するため、この中には一個前にいたxy座標を入れておく


};

