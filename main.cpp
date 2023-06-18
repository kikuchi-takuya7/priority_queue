#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater

using std::vector;
using std::cin;
using std::cout;
using std::endl;

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
	using Pair = std::pair<long long, int>;

	Graph v;

	int w = 0, h = 0;
	cin >> h;
	cin >> w;

	for (int i = 0; i < h; i++) {
		v.emplace_back(w);
	}



	for (int i = 0; i < h; i++) {
		for (int f = 0; f < w; f++) {
			cin >> v.at(i).at(f).to;
		}
	}

	int count = 1;
	int x = 0, y = 0;
	int xt = 0, yt = 0;
	while (true)
	{
		if (x < w) x++;
		if (v.at(x).at(y).to == 0) {
			count++;
		}
		else {
			x--;
		}

		if (y < h) y++;
		if (v.at(xt).at(y).to == 0) {
			count++;
		}
		else {
			y--;
		}

	}

    return 0;
}