#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater

using std::vector;
using std::cin;
using std::cout;
using std::endl;

const int INF = 799797979;//まだ探索していない
const int DONE = 1;//探索済み

struct Edge
{
	// 行き止まりかどうか
	int to;
	// コスト
	int cost;
};

int main(void) {

	// { distance, from }
	using Pair = std::pair<int, int>;

	using Graph = vector<vector<int>>;

	Graph v;    //マップの情報を入れる
	Graph dist; //マップの位置に連動してその頂点までどのぐらいの数で行けるか追加する
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

	for (int i = 0; i < h; i++) {
		v.emplace_back(w);//w分の行を先にh列分だけ確保しておく
		dist.emplace_back(w);
	}

	for (int i = 0; i < h; i++) {
		for (int f = 0; f < w; f++) {
			cin >> v.at(i).at(f);
		}
	}

	std::priority_queue<Pair, vector<Pair>, std::greater<Pair>> que; //探索済みの場所を記憶しておく。二次元配列じゃなくてPair型なのはわざわざ行き止まりの所を記録する必要はないため、一度行った場所だけを座標で横並びで覚えておけばいい
	que.emplace(0, 0);//スタート地点から探索を始める（paizaは左上からだったため０、０）
	dist.assign(h, vector<int>(w, INF));//初期化
	dist.at(0).at(0) = 0; //最初は既に探索済みのため
	//dist.front() = { 0,0 };
	
	while (!que.empty())
	{
		Pair now = que.top();//今いる場所を確保
		que.pop();

		if (now.first == h - 1 && now.second == w - 1) { //ゴールなら
			cout << dist.at(now.first).at(now.second);
			break;
		}

		int dy[4] = { 0,0,1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
		int dx[4] = { 1,-1,0,0 };
		for (int i = 0; i < 4; i++) {
			int ny = now.first;//今いる場所
			int nx = now.second;
			ny += dy[i];//この処理を上と一緒にやっちゃうと配列の要素の外に行ってしまうため別々これから探索する場所
			nx += dx[i];
			if (ny < 0 || ny >= h || nx < 0 || nx >= w) {// 画面外なら
				continue;
			}
			//if (v.at(ny).at(nx) == 1) {// 行き止まりなら
			//	continue;
			//}
			if (dist.at(ny).at(nx) != INF) { //探索済みなら
				continue;
			}
			que.emplace(ny, nx);
			dist.at(ny).at(nx) = dist.at(now.first).at(now.second) + v.at(ny).at(nx);


		}
	}

	

    return 0;
}