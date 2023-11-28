#pragma once
#include <vector>
#include <utility> // std::pair
#include <queue>
#include <functional> // std::greater

const int dy[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
const int dx[4] = { 1,-1,0,0 };

using std::vector;

using std::pair;
using Pair = pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //�񎟌��z���̃O���t
using PqP = std::priority_queue<Pair, vector<Pair>, std::greater<Pair>>; //�����ŗv�f�����Ă���

class Astar
{
public:

	Astar();

	void Input();
	
	void Initialize();

	void Astar_Basic();

	void Path_Search();

	void Heuristic(int _x, int _y);


private:

	int h_, w_; //�c���Ɖ���
	pair<int, int> start_;
	pair<int, int> goal_;

	Graph map_;    //�}�b�v�̃R�X�g������B
	Graph dist_; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̐��ōs���邩�ǉ�����
	vector<vector<Pair>> rest_; //�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���


};

