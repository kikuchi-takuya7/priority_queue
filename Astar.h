#pragma once
#include <vector>
#include <utility> // std::pair
#include <queue>
#include <stack>
#include <functional> // std::greater

const int moveY[8] = { 0, 0, 1,-1, 1 ,1,-1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
const int moveX[8] = { 1,-1, 0, 0, 1,-1 ,1,-1 };

//const int moveY[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
//const int moveX[4] = { 1,-1,0,0 };

using std::vector;
using std::pair;
using Pair = pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //�񎟌��z���̃O���t
using PP = pair<long long, pair<int, int>>;//first�ɃR�X�g�Bsecond�ɂ��̃R�X�g�̈ʒu�Ɠ������W������
using PqPP = std::priority_queue<PP, vector<PP>, std::greater<PP>>; //�����ŗv�f�����Ă���.�������ď����������ĈӖ��������
//new �����@�ŋ߂̌����ɂ��priorty���̃y�A�^��first�̒l�������肵�ĕ��ёւ����邱�Ƃ������������܂����B�Ȃ̂Ŋo���Ă����Ă�

//�����ȂƂ���y��x�t������C��t����

/// <summary>
/// �q���[���X�e�B�b�N��dist�ɒl�����Ă邹���ŃR�X�g�̌��ʂ��q���[���X�e�B�b�N������������Ă邯�ǋC�ɂ��Ȃ��ŁB���ʂƂ��Ă͕ς��Ȃ��������I�ɂȂ��Ă邩������
/// </summary>
class Astar
{
public:

	Astar();

	void CreateAstar();

private:

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



	PqPP que_; //�T���ς݂̏ꏊ���L�����Ă����B��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���
	//new���� �q���[���X�e�B�b�N�ŒT�������v����ԋ߂�����Ă���ł����񂶂��
	//���̈ʒu�܂ł̃q���[���X�e�B�b�N�ƃR�X�g�����킹����Ȃ�Ȃ肷��Ƃ���

	std::stack <Pair> ans_;

	//�ǂ̂��炢���s�񐔏d�˂��̂��̊m�F
	int total_;
};

