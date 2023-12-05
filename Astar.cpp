#include<iostream>
#include "Astar.h"

using std::cin;
using std::cout;
using std::endl;

Astar::Astar()
{
}

void Astar::Input()
{
	cout << "�c�Ɖ������" << endl;
	cin >> h_;
	cin >> w_;

	

	for (int i = 0; i < h_; i++) {
		map_.emplace_back(w_);//w���̍s����h�񕪂����m�ۂ��Ă���
		dist_.emplace_back(w_);
		rest_.emplace_back(w_);
	}

	//�ǂ�99�ł������?�Y�ݒ�
	cout << "�}�b�v�̃R�X�g����͂��ĂˁB99�Ȃ��(��)" << endl;
	for (int i = 0; i < h_; i++) {
		for (int f = 0; f < w_; f++) {
			int n = 0;
			cin >> n;
			map_.at(i).at(f) = n;
			rest_[i][f] = Pair(i, f); //rest��xy���W������
		}
	}

	cout << "�X�^�[�g�n�_�����" << endl;
	int x, y;
	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;

	start_ = std::make_pair(x, y);//�X�^�[�g�n�_����T�����n�߂�
	rest_.at(0).at(0) = Pair(x, y); //�X�^�[�g�n�_�̍��W
	que_.emplace(x, y);//�X�^�[�g�n�_����T�����n�߂�

	cout << "�S�[������" << endl;
	int goalX, goalY;
	cout << "X = "; cin >> goalX;
	cout << "Y = "; cin >> goalY;

	goal_ = std::make_pair(goalX, goalY);

	dist_.at(x).at(y) = map_.at(x).at(y); //�X�^�[�g�n�_�̃R�X�g������
}

void Astar::Initialize()
{
	h_ = 0;
	w_ = 0;

	const int Inf = 9999999;//�܂��T�����Ă��Ȃ�

	start_ = std::make_pair(0, 0);//�X�^�[�g�n�_����T�����n�߂�
	goal_ = std::make_pair(0, 0);
	dist_.assign(h_, vector<long long>(w_, Inf));//������

}

void Astar::Astar_Basic()
{
	while (!que_.empty())
	{
		Pair now = que_.top();//������ꏊ���m��
		que_.pop();

		for (int i = 0; i < 8; i++) {
			int ny = now.first;//������ꏊ NowY
			int nx = now.second;
			int sy = ny + moveY[i];//������T������ꏊ SecondY
			int sx = nx + moveX[i];
			if (sy < 0 || sy >= h_ || sx < 0 || sx >= w_) {// ��ʊO�Ȃ�
				continue;
			}
			if (dist_.at(sy).at(sx) <= dist_.at(ny).at(nx) + map_.at(sy).at(sx)) { //���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{v�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
				continue;													  //������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
			}
			que_.emplace(sy, sx);
			rest_.at(sy).at(sx) = Pair(ny, nx); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			dist_.at(sy).at(sx) = dist_.at(ny).at(nx) + map_.at(sy).at(sx);//�ŒZ�����̍X�V
		}
	}
}

void Astar::Path_Search()
{
}

int Astar::Heuristic(int _x, int _y)
{
	int x = _x - goal_.first;
	int y = _y - goal_.second;

	return abs(x + y);
}
