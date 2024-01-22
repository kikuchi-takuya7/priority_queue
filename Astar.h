#pragma once
#include <vector>
#include <utility> // std::pair
#include <queue>
#include <stack>
#include <functional> // std::greater

const int moveY[8] = { 0, 0, 1,-1, 1 ,1,-1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
const int moveX[8] = { 1,-1, 0, 0, 1,-1 ,1,-1 };

//const int moveY[4] = { 0,0,1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
//const int moveX[4] = { 1,-1,0,0 };

using std::vector;
using std::pair;
using Pair = pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //二次元配列上のグラフ
using PP = pair<long long, pair<int, int>>;//firstにコスト。secondにそのコストの位置と同じ座標を入れる
using PqPP = std::priority_queue<PP, vector<PP>, std::greater<PP>>; //昇順で要素を入れておく.昇順って小さい順って意味だからな
//new メモ　最近の研究によりpriorty内のペア型はfirstの値だけ判定して並び替えられることが判明いたしました。なので覚えておいてね

//いろんなとこがyとx逆だから気を付けて

/// <summary>
/// ヒューリスティック分distに値足してるせいでコストの結果がヒューリスティック分増えちゃってるけど気にしないで。結果としては変わらないし効率的になってるからﾀﾌﾞﾝ
/// </summary>
class Astar
{
public:

	Astar();

	void CreateAstar();

private:

	//input　エラー処理めんどいからまだ
	void Input();
	
	void Initialize();

	void Astar_Basic();

	void Path_Search();

	int Heuristic(int _x, int _y);


private:

	int h_, w_; //縦幅と横幅
	pair<int, int> start_;
	pair<int, int> goal_;

	Graph map_;    //マップのコストを入れる。
	Graph dist_; //マップの位置に連動してその頂点までどのぐらいの歩数で行けるか追加する
	vector<vector<Pair>> rest_; //経路復元に使用するため、この中には一個前にいたxy座標を入れておく



	PqPP que_; //探索済みの場所を記憶しておく。一度行った場所だけを座標で横並びで覚えておけばいい
	//newメモ ヒューリスティックで探した合計が一番近いやつってこれでいいんじゃね
	//その位置までのヒューリスティックとコストを合わせたりなんなりするところ

	std::stack <Pair> ans_;

	//どのぐらい試行回数重ねたのかの確認
	int total_;
};

