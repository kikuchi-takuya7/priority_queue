#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>


using std::vector;
using std::pair;

//struct�ɂ������������H
using IntPair = pair<int, int>; // ���W������{ z,x }
using Graph = vector<vector<long>>; //�񎟌��z��Ń}�b�v��R�X�g��\��
using PP = pair<long, pair<int, int>>;//first�ɃR�X�g�Bsecond�ɂ��̃R�X�g�̈ʒu�Ɠ������W������


class Character;
class CharacterAI;
class Stage;
struct Status;

/// <summary>
/// �L�����N�^�[AI�ƃ��^AI�ɏ���񋟂���
/// </summary>
class NavigationAI : public AI
{
	//
public:

	//�R���X�g���N�^
	NavigationAI(GameObject* parent);

	//�f�X�g���N�^
	~NavigationAI();

	///////////�I�[�o�[���C�h�����֐�/////////
	
	//������
	void Initialize() override;
	
	//���
	void Release() override;

	//////////�����o�֐�///////////////

	/// <summary>
	/// ������ID�̃L�����N�^�[AI�ɂǂ��ɃI�u�W�F�N�g��u��������
	/// </summary>
	/// <param name="ID">�I�u�W�F�N�g��u���G��ID</param>
	/// <returns>�I�u�W�F�N�g��u���ꏊ</returns>
	Transform MoveSelectObject(int ID);

	/// <summary>
	/// �����̒l���v���C���[�̊J�n�ʒu�Ɣ���Ă��邩�𔻒f����
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	bool IsOverlapPos(XMFLOAT3 pos);

	/// <summary>
	/// �����̓�l�̋����𑪂�
	/// </summary>
	/// <param name="myID">������ID</param>
	/// <param name="targetID">�_���Ă��鑊���ID</param>
	/// <returns></returns>
	float Distance(int myID, int targetID);

	//////////////////Astar�A���S���Y���Ŏg���֐�//////////////////

	/// <summary>
	/// Astar���g���ڕW�n�_��T������
	/// </summary>
	XMFLOAT3 Astar(int myID, int targetID);

	/// <summary>
	/// Astar�A���S���Y���Ŏg���o�H�����p
	/// </summary>
	/// <param name="rest">��O�ɂ������W��2�����z��ŋL����������</param>
	/// <param name="start">�X�^�[�g�n�_</param>
	/// <param name="target">�ڕW�n�_</param>
	/// <returns></returns>
	XMFLOAT3 Path_Search(vector<vector<IntPair>> rest, IntPair start, IntPair target);

	/// <summary>
	/// �q���[���X�e�B�b�N�ōŒZ�����𑪂�
	/// </summary>
	/// <param name="x">���݂�x���W</param>
	/// <param name="y">���݂�y���W</param>
	/// <param name="target">�ڕW�n�_</param>
	/// <returns>�ŒZ�����̊��Ғl</returns>
	int Heuristic(int x, int y, IntPair target);

	/// <summary>
	/// �����_�ȉ���؂�̂ĂĐ����ɂ���
	/// </summary>
	/// <param name="z">�����ɂ�����z</param>
	/// <param name="x">�����ɂ�����x</param>
	/// <returns>�����ɂ���IntPair</returns>
	IntPair FloatToIntPair(float z, float x);

	///////////////�L�����N�^�[���ׂĂɎw�����o���֐�/////////////////////

	void AllResetStatus();
	void AllStopDraw();
	void AllStartDraw();
	void AllStopUpdate();
	void AllStartUpdate();
	void AllStopDrawPlayerUI();
	
	void AllEraseCollision();

	
	//////////////�A�N�Z�X�֐�//////////////

	/// <summary>
	/// �w�肵��ID�̃L�����̃C���X�^���X���l������
	/// </summary>
	/// <param name="ID">�~�����L������ID</param>
	/// <returns>�w�肵���L����</returns>
	Character* GetCaracter(int ID);

	/// <summary>
	/// �w�肵���L�����ɃX�e�[�^�X���Z�b�g����
	/// </summary>
	/// <param name="ID">�Z�b�g�������L������ID</param>
	/// <param name="status">�V�����X�e�[�^�X</param>
	void SetStatus(int ID, Status status);

	void PushCharacter(Character* chara) { pCharacterList_.emplace_back(chara); }
	void PushCharacterAI(CharacterAI* AI) { pCharacterAIList_.emplace_back(AI); }
	void SetStage(Stage* stage) { pStage_ = stage; }


private:

	/////////////////Astar�A���S���Y���Ŏg��///////////

	//�X�e�[�W�̏c���Ɖ���
	int height_, width_; 
	
	//�X�e�[�W�̏��
	Stage* pStage_;

	/////////////////////////////Character�̏��////////////////////////

	vector<Character*> pCharacterList_;

	vector<CharacterAI*> pCharacterAIList_;


	
};

