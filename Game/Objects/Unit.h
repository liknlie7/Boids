#pragma once

#include <SimpleMath.h>

#include "BaseObject.h"

// ���j�b�g�N���X
class Unit :public BaseObject
{
public: // ��{

	// �R���X�g���N�^
	Unit();
	// �f�X�g���N�^
	~Unit() {};

public: // �֐�

	// �X�V
	void Update(std::vector<std::unique_ptr<Unit>>& _units);

	// ���x�E�ʒu�̍X�V
	void UpdateMove();

private: // �T�u�֐�

	// ���Ԃ�������
	void SearchFriend(std::vector<std::unique_ptr<Unit>>& _units);

	// �����s��
	DirectX::SimpleMath::Vector3 Separation();

	// �����s��
	DirectX::SimpleMath::Vector3 Cohesion();

	// ����s��
	DirectX::SimpleMath::Vector3 Alignment();

	// �G���A�O�ɏo�����Ȏ�����
	void ReflectingAtWall();

	// �ǂ������
	DirectX::SimpleMath::Vector3 CalcAccelAgainstWall(float _distance, DirectX::SimpleMath::Vector3 _direction);

private: // �萔

	// �ő呬�x
	static const float MAX_SPEED;

	// �ŏ����x
	static const float MIN_SPEED;

	// �����
	static const float MAX_STEER;

	// �ǂ܂ł̋���
	static const float UP_TO_WALL;

	// �d��
	static const float WALL_WEIGHT;

	// �ǂ̑傫��
	static const float WALL_SCALE;

	// ����p
	static const float FIELD_OF_VIEW;

	// ����̍L�����a
	static const float FIELD_OF_VIEW_RADIUS;

	// ��������
	static const float SEPARATION_DIST;

	// �����s���d��
	static const float SEPARATION_WEIGHT;

	// ����s���d��
	static const float ALIGNMENT_WEIGHT;

	// �����s���d��
	static const float COHESION_WEIGHT;

	// ��Ԏ���
	static const float LERP_TIME;


private: // �ϐ�

	// �����x
	DirectX::SimpleMath::Vector3	m_accel;

	// ����
	std::vector<Unit*>				m_friends;

	// �ł��߂�����
	Unit*							m_nearestFriend;

	// �ł��߂����ԂƂ̋���
	float							m_distNearestFriend;
};

