#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater

using std::vector;
using std::cin;
using std::cout;
using std::endl;

const int INF = 2100100100;

enum {
	REFT,
	RIGHT,
	UP,
	DOWN

};

struct Edge
{
	// 行先
	int to;
	// コスト
	int cost;
};

int main(void) {

	using Graph = vector<vector<Edge>>;

	// { distance, from }
	using Pair = std::pair<int, int>;

	Graph v;
	vector<vector<int>> dist;
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

	for (int i = 0; i < h; i++) {
		v.emplace_back(w);
		dist.emplace_back(w);
	}



	for (int i = 0; i < h; i++) {
		for (int f = 0; f < w; f++) {
			cin >> v.at(i).at(f).to;
		}
	}


	std::queue<Pair> que;
	que.emplace(0, 0);
	dist.front() = { 0,0 };
	dist.assign(h, vector<int>(w, INF));

	int y[4] = { 0,0,1,-1 };
	int x[4] = { 1,-1,0,0 };

	while (!que.empty())
	{
		Pair now = que.front();
		que.pop();



	}

    return 0;
}