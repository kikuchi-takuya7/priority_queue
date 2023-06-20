#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater

using std::vector;
using std::cin;
using std::cout;
using std::endl;

const int INF = 0;//�܂��T�����Ă��Ȃ�
const int DONE = 1;//�T���ς�

enum {
	REFT,
	RIGHT,
	UP,
	DOWN

};

struct Edge
{
	// �s���~�܂肩�ǂ���
	int to;
	// �T���ς݂��ǂ���
	int dist;
};

int main(void) {

	// { distance, from }
	using Pair = std::pair<int, int>;

	using Graph = vector<vector<int>>;

	Graph v; //�}�b�v�̏�������
	Graph dist; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̐��ōs���邩�ǉ�����
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

	for (int i = 0; i < h; i++) {
		v.emplace_back(w);//w���̍s����h�񕪂����m�ۂ��Ă���
		dist.emplace_back(w);
	}

	for (int i = 0; i < h; i++) {
		for (int f = 0; f < w; f++) {
			cin >> v.at(i).at(f);
		}
	}

	std::queue<Pair> que; //�T���ς݂̏ꏊ���L�����Ă����B�񎟌��z�񂶂�Ȃ���Pair�^�Ȃ̂͂킴�킴�s���~�܂�̏����L�^����K�v�͂Ȃ����߁A��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���
	que.emplace(0, 0);//�X�^�[�g�n�_����T�����n�߂�ipaiza�͍��ォ�炾�������߂O�A�O�j
	dist.assign(h, vector<int>(w, INF));//������
	dist.at(0).at(0) = 1; //�ŏ��͊��ɒT���ς݂̂��߂P
	//dist.front() = { 0,0 };
	
	while (!que.empty())
	{
		Pair now = que.front();//������ꏊ���m��
		que.pop();

		if (now.first == h - 1 && now.second == w - 1) { //�S�[���Ȃ�
			cout << dist.at(now.first).at(now.second);
			break;
		}

		int dy[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
		int dx[4] = { 1,-1,0,0 };
		for (int i = 0; i < 4; i++) {
			int ny = now.first;//���ꂩ��T������ꏊ
			int nx = now.second;
			ny += dy[i];//���̏�������ƈꏏ�ɂ�����Ⴄ�Ɣz��̗v�f�̊O�ɍs���Ă��܂����ߕʁX
			nx += dx[i];
			if (ny < 0 || ny >= h || nx < 0 || nx >= w) {// ��ʊO�Ȃ�
				continue;
			}
			if (v.at(ny).at(nx) == 1) {// �s���~�܂�Ȃ�
				continue;
			}
			if (dist.at(ny).at(nx) != INF) { //�T���ς݂Ȃ�
				continue;
			}
			que.emplace(ny, nx);
			dist.at(ny).at(nx) = dist.at(now.first).at(now.second) + DONE;
		}
	}

	

    return 0;
}