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

	//�ǂ�99�ł������
	cout << "�}�b�v�̃R�X�g����͂��ĂˁB99�Ȃ��" << endl;
	for (int i = 0; i < h_; i++) {
		for (int f = 0; f < w_; f++) {
			int n = 0;
			cin >> n;
			map_.at(i).at(f) = n;
			rest_[i][f] = Pair(i, f); //rest��xy���W������
		}
	}
}

void Astar::Initialize()
{
}

void Astar::Astar_Basic()
{
}

void Astar::Path_Search()
{
}

void Astar::Heuristic(int _x, int _y)
{
}
