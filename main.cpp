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

const int INF = 9999999;//�܂��T�����Ă��Ȃ�
const int DONE = 1;//�T���ς�

int dy[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
int dx[4] = { 1,-1,0,0 };

struct Edge
{
	// �s���~�܂肩�ǂ���
	int to;
	// �R�X�g
	int cost;
};

int main(void) {

	// { distance, from }
	using Pair = std::pair<long long, long long>;
	using PP = std::pair<long long, Pair>;
	using Graph = vector<vector<long long>>;

	Graph v;    //�}�b�v�̏�������
	Graph dist; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̐��ōs���邩�ǉ�����
	vector<vector<PP>> rest; //�o�H�����Ɏg�p���邽�߁A���̒��ɂ̓R�X�g�ƈ�O�ɂ���xy���W�����Ă���
	int w = 0, h = 0;
	cin >> h;
	cin >> w;

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
			//dist.at(i).at(f) = n;
		}
	}
	//que���g���č��܂ł̍ŒZ���������ɕ��ׂď������ق�����T�����邱�Ƃŗ]���ȏ��������炷�̂����B�傫���̂������ɏ������̂Ƃ�������瓖�R�Ӗ��Ȃ���
	std::priority_queue<Pair, vector<Pair>, std::greater<Pair>> que; //�T���ς݂̏ꏊ���L�����Ă����B�񎟌��z�񂶂�Ȃ���Pair�^�Ȃ̂͂킴�킴�s���~�܂�̏����L�^����K�v�͂Ȃ����߁A��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���
	que.emplace(0, 0);//�X�^�[�g�n�_����T�����n�߂�ipaiza�͍��ォ�炾�������߂O�A�O�j
	dist.assign(h, vector<long long>(w, INF));//������
	dist.at(0).at(0) = v.at(0).at(0); //�X�^�[�g�n�_�̃R�X�g������
	rest.at(0).at(0) = PP(-1, Pair(-1, -1));


	while (!que.empty())
	{
		Pair now = que.top();//������ꏊ���m��
		que.pop();

		//if (now.first == h - 1 && now.second == w - 1) { //�S�[���Ȃ�
		//	cout << dist.at(now.first).at(now.second);
		//	break;
		//}

	
		for (int i = 0; i < 4; i++) {
			int ny = now.first;//������ꏊ
			int nx = now.second;
			int sy = ny + dy[i];//���̏�������ƈꏏ�ɂ�����Ⴄ�Ɣz��̗v�f�̊O�ɍs���Ă��܂����ߕʁX���ꂩ��T������ꏊ
			int sx = nx + dx[i];
			if (sy < 0 || sy >= h || sx < 0 || sx >= w) {// ��ʊO�Ȃ�
				continue;
			}
			//if (v.at(ny).at(nx) == 1) {// �s���~�܂�Ȃ�
			//	continue;
			//}
			//if (dist.at(ny).at(nx) != INF) { //�T���ς݂Ȃ�
			//	continue;
			//}
			if (dist.at(sy).at(sx) <= dist.at(ny).at(nx) + v.at(sy).at(sx)) { //���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{v�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
                                                                                             //������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
				continue;
			}
			que.emplace(sy, sx);
			rest.at(sy).at(sx) = PP(dist[ny][nx], std::make_pair(ny, nx)); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			dist.at(sy).at(sx) = dist.at(ny).at(nx) + v.at(sy).at(sx);//�ŒZ�����̍X�V
		}
	}

	cout << dist.at(h - 1).at(w - 1);//�p�C�U�͉E�����S�[���̂��߃S�[���̈ʒu�����艟���ŕ\�����������

	

	while (true)
	{

		//�ŏ��ɂ��̏������㉺���E�T�����Č������ꏊ���킩�����炻�̈ʒu�Ƀt���O�𗧂Ă�݂�����
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