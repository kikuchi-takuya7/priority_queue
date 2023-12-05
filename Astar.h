#pragma once
#include <vector>
#include <utility> // std::pair
#include <queue>
#include <functional> // std::greater

//const int moveY[8] = { 0, 0, 1,-1, 1 ,1,-1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
//const int moveX[8] = { 1,-1, 0, 0, 1,-1 ,1,-1 };

const int moveY[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
const int moveX[4] = { 1,-1,0,0 };

using std::vector;
using std::pair;
using Pair = pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //�񎟌��z���̃O���t
using PqP = std::priority_queue<Pair, vector<Pair>, std::greater<Pair>>; //�����ŗv�f�����Ă���.�������ď����������ĈӖ��������
using PqI = std::priority_queue<int, vector<int>, std::greater<int>>;

class Astar
{
public:

	Astar();

	//input�@�G���[�����߂�ǂ�����܂�
	void Input();
	
	void Initialize();

	void Astar_Basic();

	void Path_Search();

	int Heuristic(int _x, int _y);


private:

	int h_, w_; //�c���Ɖ���
	pair<int, int> start_;
	pair<int, int> goal_;

	Graph map_;    //�}�b�v�̃R�X�g������B
	Graph dist_; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̕����ōs���邩�ǉ�����
	vector<vector<Pair>> rest_; //�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���

	//que���g���č��܂ł̍ŒZ�������ɕ��ׂď������ق�����T�����邱�Ƃŗ]���ȏ��������炷�B�傫���̂������ɏ������̂Ƃ�������瓖�R�Ӗ��Ȃ���
	PqP que_; //�T���ς݂̏ꏊ���L�����Ă����B��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���
	//new���� �q���[���X�e�B�b�N�ŒT�������v����ԋ߂�����Ă���ŋ��߂�ꂻ�������
	
	PqI costQue_;//����Ə��que���A������悤�ɂ��āA���̈ʒu�܂ł̃q���[���X�e�B�b�N�ƃR�X�g�����킹����Ȃ�Ȃ肷��Ƃ���

};

