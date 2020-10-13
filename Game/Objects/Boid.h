#pragma once

#include <vector>
#include <random>

#include "../Common/GameContext.h"
#include "../Objects/Unit.h"

// �Q��N���X
class Boid
{
public: // ��{

	// �R���X�g���N�^
	Boid();

	// �f�X�g���N�^
	~Boid() {};

public: // �֐�

	// �X�V
	void Update();

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view);

private: // �T�u�֐�

	// �����̎擾
	float GetRandomNumber(const float _min, const float _max);

private: // �萔

	// ���j�b�g�̑���
	static const int NUM_UNITS;

	// ���S����̏o���ł��鋗��
	static const float SPAWN_AREA;

private: // �ϐ�

	// ���j�b�g
	std::vector<std::unique_ptr<Unit>> m_units;
};

