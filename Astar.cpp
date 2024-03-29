#include<iostream>
#include "Astar.h"

using std::cin;
using std::cout;
using std::endl;

Astar::Astar()
{
}

void Astar::CreateAstar()
{

	Initialize();
	Input();
	Astar_Basic();
	Path_Search();

	cout << "Y" << " " << "X" << endl;
	while (!ans_.empty()) {
		cout << ans_.top().first << " " << ans_.top().second << endl;
		ans_.pop();
	}
	cout << total_ << endl;

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

	//壁は-1でいいよね?
	cout << "マップのコストを入力してね。-1なら壁(仮)" << endl;
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
	x -= 1;
	y -= 1;

	if (map_.at(y).at(x) == -1) {
		cout << "まちがえてますよ" << endl;
		return;
	}

	start_ = std::make_pair(y, x);//スタート地点から探索を始める
	rest_.at(y).at(x) = Pair(y, x); //スタート地点の座標
	que_.emplace(0, Pair(y, x));//スタート地点から探索を始める

	cout << "ゴール入力" << endl;
	int goalX, goalY;
	cout << "X = "; cin >> goalX;
	cout << "Y = "; cin >> goalY;
	goalX -= 1;
	goalY -= 1;

	if (map_.at(goalY).at(goalX) == -1) {
		cout << "まちがえてますよ" << endl;
		return;
	}

	goal_ = std::make_pair(goalY, goalX);

	const int Inf = 9999999;//まだ探索していない
	dist_.assign(h_, vector<long long>(w_, Inf));//初期化

	dist_.at(y).at(x) = map_.at(y).at(x); //スタート地点のコストを入れる

	

}

void Astar::Initialize()
{
	h_ = -1;
	w_ = -1;

	total_ = 0;

	start_ = std::make_pair(-1, -1);//スタート地点から探索を始める
	goal_ = std::make_pair(-1, -1);
	

}

void Astar::Astar_Basic()
{
	while (!que_.empty())
	{
		PP now = que_.top();//今いる場所を確保
		que_.pop();

		for (int i = 0; i < 8; i++) {

			total_++;

			int ny = now.second.first;//今いる場所 NowY
			int nx = now.second.second;
			int sy = ny + moveY[i];//今から探索する場所 SecondY
			int sx = nx + moveX[i];
			
			// 画面外なら
			if (sy < 0 || sy >= h_ || sx < 0 || sx >= w_) {
				continue;
			}

			//壁なら
			if (map_.at(sy).at(sx) == -1) {
				continue;
			}

			//これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋vのコスト分で今現在わかっている最短距離）でないなら。
			if (dist_.at(sy).at(sx) <= dist_.at(ny).at(nx) + map_.at(sy).at(sx) + Heuristic(sy, sx)) {
				continue; //今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
			}
			
			rest_.at(sy).at(sx) = Pair(ny, nx); //最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う

			//コストにヒューリスティック分を足すことによって、もしそこまでの道が一番コストが低くても遠ざかってってる場合ヒューリスティック分でコスト増えるから結果コストが大きくなってより制度が高まる
			dist_.at(sy).at(sx) = dist_.at(ny).at(nx) + map_.at(sy).at(sx) + Heuristic(sy, sx);//ヒューリスティック分も込みで最短距離の更新

			if (sy == goal_.first && sx == goal_.second)
				break;

			que_.emplace( PP(dist_.at(sy).at(sx), Pair(sy, sx)));//コストと共に次の探索候補を入れておく
		}
	}
}

void Astar::Path_Search()
{
	//ゴール地点
	int i = goal_.first;
	int f = goal_.second;

	cout << dist_.at(i).at(f) << endl;//パイザは右下がゴールのためゴールの位置までの最短コストを表示

	ans_.emplace(i, f);//ゴール地点だけあらかじめ入れとく

	while (true) {

		for (int n = 0; n < 8; n++) {
			int y = i;
			int x = f;
			y += moveY[n]; //上下探索
			x += moveX[n];
			if (y < 0 || y >= h_ || x < 0 || x >= w_) {// 画面外なら
				continue;
			}
			if (rest_.at(i).at(f) != Pair(y, x)) {//上下探索する時の座標とrestに入ってるその場所に行く前に居た座標と照らし合わせてその値が同じならansに入れる
				continue;
			}
			ans_.emplace(rest_.at(i).at(f)); //通ってきた座標を入れる
			i = y;  //次はその前にいた座標の上下左右を探索するため更新
			f = x;  //restの値を入れようとするとiとfで探索するため値が同時に更新されてしまい曲がり角でおかしくなってしまう
		}

		if (i == start_.first && f == start_.second) {//初期位置に戻ったら
			break;
		}
	}
}

int Astar::Heuristic(int _x, int _y)
{
	int x = abs(_x - goal_.second);
	int y = abs(_y - goal_.first);

	return std::max(x,y);
}
