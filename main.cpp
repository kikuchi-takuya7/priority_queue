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
using Graph = vector<vector<long long>>; //�񎟌��z���̃O���t
using PqP = std::priority_queue<Pair, vector<Pair>, std::greater<Pair>>; //�����ŗv�f�����Ă���.�������ď����������ĈӖ��������

const int dy[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
const int dx[4] = { 1,-1,0,0 };

//����
void Input(int _h, int _w, Graph& _v, Graph& _dist, vector<vector<Pair>>& _rest);

//������
void Initialize(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest);

//�_�C�N�X�g���@�̊�{����
void Dijkstra(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest);

//�ŒZ�o�H�����W�Ŋl��
void shortest_path(int h, int w, Graph& v, Graph& dist, vector<vector<Pair>>& rest, std::queue<Pair>& ans);

//�_�C�N�X�g���@�o�H�T��������֐��i�܂Ƃ߂������j
void DijkstraP();


int main(void) {


    return 0;
}

void Input(int h, int w, Graph &v, Graph &dist, vector<vector<Pair>> &rest)
{
	for (int i = 0; i < h; i++) {
		v.emplace_back(w);//w���̍s����h�񕪂����m�ۂ��Ă���
		dist.emplace_back(w);
		rest.emplace_back(w);
	}

	for (int i = 0; i < h; i++) {
		for (int f = 0; f < w; f++) {
			int n = 0;
			cin >> n;
			v.at(i).at(f) = n;
			rest[i][f] = Pair(i, f); //rest��xy���W������
		}
	}
}

void Initialize(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest)
{
	const int Inf = 9999999;//�܂��T�����Ă��Ȃ�

	que.emplace(0, 0);//�X�^�[�g�n�_����T�����n�߂�ipaiza�͍��ォ�炾�������߂O�A�O�j
	dist.assign(h, vector<long long>(w, Inf));//������
	dist.at(0).at(0) = v.at(0).at(0); //�X�^�[�g�n�_�̃R�X�g������
	rest.at(0).at(0) = Pair(0, 0); //�X�^�[�g�n�_�̍��W��0�̂���
}


void Dijkstra(int h, int w, PqP& que, Graph& v, Graph& dist, vector<vector<Pair>>& rest)
{
	while (!que.empty())
	{
		Pair now = que.top();//������ꏊ���m��
		que.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.first;//������ꏊ NowY
			int nx = now.second;
			int sy = ny + dy[i];//������T������ꏊ SecondY
			int sx = nx + dx[i];
			if (sy < 0 || sy >= h || sx < 0 || sx >= w) {// ��ʊO�Ȃ�
				continue;
			}
			if (dist.at(sy).at(sx) <= dist.at(ny).at(nx) + v.at(sy).at(sx)) { //���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{v�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
				continue;													  //������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
			}
			que.emplace(sy, sx);
			rest.at(sy).at(sx) = Pair(ny, nx); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			dist.at(sy).at(sx) = dist.at(ny).at(nx) + v.at(sy).at(sx);//�ŒZ�����̍X�V
		}
	}
}

void shortest_path(int h, int w, Graph& v, Graph& dist, vector<vector<Pair>>& rest, std::queue<Pair>& ans)
{
	//�S�[���n�_
	int i = h - 1;
	int f = w - 1;

	cout << dist.at(i).at(f) << endl;//�p�C�U�͉E�����S�[���̂��߃S�[���̈ʒu�܂ł̍ŒZ�R�X�g��\��

	ans.emplace(i, f);//�S�[���n�_�������炩���ߓ���Ƃ�

	while (true) {

		for (int n = 0; n < 4; n++) {
			int y = i;
			int x = f;
			y += dy[n]; //�㉺�T��
			x += dx[n];
			if (y < 0 || y >= h || x < 0 || x >= w) {// ��ʊO�Ȃ�
				continue;
			}
			if (rest.at(i).at(f) != Pair(y, x)) {//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l�������Ȃ�ans�ɓ����
				continue;
			}
			ans.emplace(rest.at(i).at(f)); //�ʂ��Ă������W������
			i = y;  //���͂��̑O�ɂ������W�̏㉺���E��T�����邽�ߍX�V
			f = x;  //rest�̒l�����悤�Ƃ����i��f�ŒT�����邽�ߒl�������ɍX�V����Ă��܂��Ȃ���p�ł��������Ȃ��Ă��܂�
		}

		if (i == 0 && f == 0) {//�����ʒu�ɖ߂�����
			break;
		}
	}

}

void DijkstraP()
{
	Graph v;    //�}�b�v�̏�������
	Graph dist; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̐��ōs���邩�ǉ�����
	vector<vector<Pair>> rest; //�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���

	//�c���Ɖ����̓���
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

	Input(h, w, v, dist, rest);

	//que���g���č��܂ł̍ŒZ�������ɕ��ׂď������ق�����T�����邱�Ƃŗ]���ȏ��������炷�B�傫���̂������ɏ������̂Ƃ�������瓖�R�Ӗ��Ȃ���
	PqP que; //�T���ς݂̏ꏊ���L�����Ă����B��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���

	Initialize(h, w, que, v, dist, rest);

	Dijkstra(h, w, que, v, dist, rest);

	std::queue<Pair> ans; //�S�[��������W�����Ă��ăS�[����������o����悤��

	shortest_path(h, w, v, dist, rest, ans);

	while (!ans.empty()) {
		cout << ans.front().first << " " << ans.front().second << endl;
		ans.pop();
	}
}
