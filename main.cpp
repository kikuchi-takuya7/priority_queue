#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

const int INF = 9999999;//まだ探索していない
const int DONE = 1;//探索済み

int dy[4] = { 0,0,1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
int dx[4] = { 1,-1,0,0 };

struct Edge
{
	// 行き止まりかどうか
	int to;
	// コスト
	int cost;
};

int main(void) {

	// { distance, from }
	using Pair = std::pair<long long, long long>;
	using PP = std::pair<long long, Pair>;
	using Graph = vector<vector<long long>>;

	Graph v;    //マップの情報を入れる
	Graph dist; //マップの位置に連動してその頂点までどのぐらいの数で行けるか追加する
	vector<vector<PP>> rest; //経路復元に使用するため、この中にはコストと一個前にいたxy座標を入れておく
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

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
			//dist.at(i).at(f) = n;
		}
	}
	//queを使って今までの最短距離じゅんに並べて小さいほうから探索することで余分な処理を減らすのかも。大きいのやった後に小さいのとかやったら当然意味ないし
	std::priority_queue<Pair, vector<Pair>, std::greater<Pair>> que; //探索済みの場所を記憶しておく。二次元配列じゃなくてPair型なのはわざわざ行き止まりの所を記録する必要はないため、一度行った場所だけを座標で横並びで覚えておけばいい
	que.emplace(0, 0);//スタート地点から探索を始める（paizaは左上からだったため０、０）
	dist.assign(h, vector<long long>(w, INF));//初期化
	dist.at(0).at(0) = v.at(0).at(0); //スタート地点のコストを入れる
	rest.at(0).at(0) = PP(-1, Pair(-1, -1));


	while (!que.empty())
	{
		Pair now = que.top();//今いる場所を確保
		que.pop();

		//if (now.first == h - 1 && now.second == w - 1) { //ゴールなら
		//	cout << dist.at(now.first).at(now.second);
		//	break;
		//}

	
		for (int i = 0; i < 4; i++) {
			int ny = now.first;//今いる場所
			int nx = now.second;
			int sy = ny + dy[i];//この処理を上と一緒にやっちゃうと配列の要素の外に行ってしまうため別々これから探索する場所
			int sx = nx + dx[i];
			if (sy < 0 || sy >= h || sx < 0 || sx >= w) {// 画面外なら
				continue;
			}
			//if (v.at(ny).at(nx) == 1) {// 行き止まりなら
			//	continue;
			//}
			//if (dist.at(ny).at(nx) != INF) { //探索済みなら
			//	continue;
			//}
			if (dist.at(sy).at(sx) <= dist.at(ny).at(nx) + v.at(sy).at(sx)) { //これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋vのコスト分で今現在わかっている最短距離）でないなら。
                                                                                             //今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
				continue;
			}
			que.emplace(sy, sx);
			rest.at(sy).at(sx) = PP(dist[ny][nx], std::make_pair(ny, nx)); //最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う
			dist.at(sy).at(sx) = dist.at(ny).at(nx) + v.at(sy).at(sx);//最短距離の更新
		}
	}

	cout << dist.at(h - 1).at(w - 1);//パイザは右下がゴールのためゴールの位置をごり押しで表示しちゃった

	

	while (true)
	{

		//最初にこの処理を上下左右探索して元居た場所がわかったらその位置にフラグを立てるみたいな
		for (int i = 0; i < h; i++) {
			for (int f = 0; f < w; f++) {
				for (int n = 0; n < 4; n++) {
					if (rest[h - i - 1][w - f - 1] == PP(dist[h - i - 1 + dy[n]][w - f - 1 + dx[n]], rest[h - i - 1][w - f - 1].second));
				}
			}
		}
		
		cout << "--" << endl;
		for (int i = 0; i < h; i++) {
			for (int f = 0; f < w; f++) {
				
				
				cout << v.at(i).at(f);

				
			}
		}
	}

    return 0;
}