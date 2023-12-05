#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue>
#include <functional> // std::greater
#include <stack>
#include"Astar.h"

using std::vector;
using std::cin;
using std::cout;
using std::endl;

using Pair = std::pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //二次元配列上のグラフ
using PqP = std::priority_queue<Pair, vector<Pair>, std::greater<Pair>>; //昇順で要素を入れておく.昇順って小さい順って意味だからな

const int dy[4] = { 0,0,1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
const int dx[4] = { 1,-1,0,0 };

//入力
void Input(int _h, int _w, Graph& _v, Graph& _dist, vector<vector<Pair>>& _rest);

//初期化
void Initialize(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest);

//ダイクストラ法の基本実装
void Dijkstra(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest);

//最短経路を座標で獲得
void shortest_path(int h, int w, Graph& v, Graph& dist, vector<vector<Pair>>& rest, std::queue<Pair>& ans);

//ダイクストラ法経路探索をする関数（まとめただけ）
void DijkstraP();


int main(void) {


    return 0;
}

void Input(int h, int w, Graph &v, Graph &dist, vector<vector<Pair>> &rest)
{
	for (int i = 0; i < h; i++) {
		v.emplace_back(w);//w分の行を先にh列分だけ確保しておく
		dist.emplace_back(w);
		rest.emplace_back(w);
	}

	for (int i = 0; i < h; i++) {
		for (int f = 0; f < w; f++) {
			int n = 0;
			cin >> n;
			v.at(i).at(f) = n;
			rest[i][f] = Pair(i, f); //restにxy座標を入れる
		}
	}
}

void Initialize(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest)
{
	const int Inf = 9999999;//まだ探索していない

	que.emplace(0, 0);//スタート地点から探索を始める（paizaは左上からだったため０、０）
	dist.assign(h, vector<long long>(w, Inf));//初期化
	dist.at(0).at(0) = v.at(0).at(0); //スタート地点のコストを入れる
	rest.at(0).at(0) = Pair(0, 0); //スタート地点の座標は0のため
}


void Dijkstra(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest)
{
	while (!que.empty())
	{
		Pair now = que.top();//今いる場所を確保
		que.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.first;//今いる場所 NowY
			int nx = now.second;
			int sy = ny + dy[i];//今から探索する場所 SecondY
			int sx = nx + dx[i];
			if (sy < 0 || sy >= h || sx < 0 || sx >= w) {// 画面外なら
				continue;
			}
			if (dist.at(sy).at(sx) <= dist.at(ny).at(nx) + v.at(sy).at(sx)) { //これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋vのコスト分で今現在わかっている最短距離）でないなら。
				continue;													  //今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
			}
			que.emplace(sy, sx);
			rest.at(sy).at(sx) = Pair(ny, nx); //最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う
			dist.at(sy).at(sx) = dist.at(ny).at(nx) + v.at(sy).at(sx);//最短距離の更新
		}
	}
}

void shortest_path(int h, int w, Graph& v, Graph& dist, vector<vector<Pair>>& rest, std::queue<Pair>& ans)
{
	//ゴール地点
	int i = h - 1;
	int f = w - 1;

	cout << dist.at(i).at(f) << endl;//パイザは右下がゴールのためゴールの位置までの最短コストを表示

	ans.emplace(i, f);//ゴール地点だけあらかじめ入れとく

	while (true) {

		for (int n = 0; n < 4; n++) {
			int y = i;
			int x = f;
			y += dy[n]; //上下探索
			x += dx[n];
			if (y < 0 || y >= h || x < 0 || x >= w) {// 画面外なら
				continue;
			}
			if (rest.at(i).at(f) != Pair(y, x)) {//上下探索する時の座標とrestに入ってるその場所に行く前に居た座標と照らし合わせてその値が同じならansに入れる
				continue;
			}
			ans.emplace(rest.at(i).at(f)); //通ってきた座標を入れる
			i = y;  //次はその前にいた座標の上下左右を探索するため更新
			f = x;  //restの値を入れようとするとiとfで探索するため値が同時に更新されてしまい曲がり角でおかしくなってしまう
		}

		if (i == 0 && f == 0) {//初期位置に戻ったら
			break;
		}
	}

}

void DijkstraP()
{
	Graph v;    //マップの情報を入れる
	Graph dist; //マップの位置に連動してその頂点までどのぐらいの数で行けるか追加する
	vector<vector<Pair>> rest; //経路復元に使用するため、この中には一個前にいたxy座標を入れておく

	//縦幅と横幅の入力
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

	Input(h, w, v, dist, rest);

	//queを使って今までの最短距離順に並べて小さいほうから探索することで余分な処理を減らす。大きいのやった後に小さいのとかやったら当然意味ないし
	PqP que; //探索済みの場所を記憶しておく。一度行った場所だけを座標で横並びで覚えておけばいい

	Initialize(h, w, que, v, dist, rest);

	Dijkstra(h, w, que, v, dist, rest);

	std::queue<Pair> ans; //ゴールから座標を入れてってゴール側から取り出せるように

	shortest_path(h, w, v, dist, rest, ans);

	while (!ans.empty()) {
		cout << ans.front().first << " " << ans.front().second << endl;
		ans.pop();
	}
}
