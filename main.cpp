#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater
#include <stack>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

const int INF = 9999999;//�܂��T�����Ă��Ȃ�
const int DONE = 1;//�T���ς�

const int dy[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
const int dx[4] = { 1,-1,0,0 };

int main(void) {

	// { distance, from }
	using Pair = std::pair<long long, long long>;
	//using PP = std::pair<long long, Pair>;
	using Graph = vector<vector<long long>>;

	Graph v;    //�}�b�v�̏�������
	Graph dist; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̐��ōs���邩�ǉ�����
	vector<vector<Pair>> rest; //�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���

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
			rest[i][f] = Pair(i, f); //rest��xy���W������
		}
	}

	//que���g���č��܂ł̍ŒZ�������ɕ��ׂď������ق�����T�����邱�Ƃŗ]���ȏ��������炷�̂����B�傫���̂������ɏ������̂Ƃ�������瓖�R�Ӗ��Ȃ���
	std::priority_queue<Pair, vector<Pair>, std::greater<Pair>> que; //�T���ς݂̏ꏊ���L�����Ă����B��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���
	que.emplace(0, 0);//�X�^�[�g�n�_����T�����n�߂�ipaiza�͍��ォ�炾�������߂O�A�O�j
	dist.assign(h, vector<long long>(w, INF));//������
	dist.at(0).at(0) = v.at(0).at(0); //�X�^�[�g�n�_�̃R�X�g������
	rest.at(0).at(0) = Pair(0, 0); //�X�^�[�g�n�_�̍��W��0�̂���


	while (!que.empty())
	{
		Pair now = que.top();//������ꏊ���m��
		que.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.first;//������ꏊ
			int nx = now.second;
			int sy = ny + dy[i];
			int sx = nx + dx[i];//������T������ꏊ
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
				continue;													  //������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
			}
			que.emplace(sy, sx);
			rest.at(sy).at(sx) = Pair(ny, nx); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			dist.at(sy).at(sx) = dist.at(ny).at(nx) + v.at(sy).at(sx);//�ŒZ�����̍X�V
		}
	}

	//�S�[���n�_
	int i = h - 1;
	int f = w - 1;

	cout << dist.at(i).at(f) << endl;//�p�C�U�͉E�����S�[���̂��߃S�[���̈ʒu�܂ł̍ŒZ�R�X�g��\��

	//std::priority_queue<Pair> ans; //�p�C�U�̓S�[������X�^�[�g�n�_�Ɍ������Ă邽�ߑ傫�����ɕ��ёւ���
	std::stack<Pair> ans; //���ꂽ���ԂɎ��o���悤

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
			if (rest.at(i).at(f) != Pair(y,x)) {//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l�������Ȃ�ans�ɓ����
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
	
	while (!ans.empty()) {

		cout << ans.top().first << " " << ans.top().second << endl;
		ans.pop();
	}
	
	
	/*while (!ans.empty()) { 
		cout << "--" << endl;
		for (int i = 0; i < h; i++) {
			for (int f = 0; f < w; f++) {


				if (!ans.empty() && ans.top() == Pair(i, f)) {
					cout << "*";
					ans.pop();
				}
				else {
					cout << " ";
				}
				
				

				cout << v.at(i).at(f);


			}
			cout << endl;
		}
	}*/


    return 0;
}