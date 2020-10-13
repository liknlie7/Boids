#include "../../pch.h"

#include "Boid.h"

// ���j�b�g�̑���
const int Boid::NUM_UNITS = 50;

// ���S����̏o���ł��鋗��
const float Boid::SPAWN_AREA = 5.0f;

// �R���X�g���N�^
Boid::Boid()
{
	// �z��̏�����
	m_units.clear();
	m_units.resize(NUM_UNITS);

	for (unsigned int i = 0; i < m_units.size(); i++)
	{
		// ���j�b�g�쐬
		m_units[i] = std::make_unique<Unit>();

		// �������W�ݒ�
		m_units[i]->SetPosition(DirectX::SimpleMath::Vector3(GetRandomNumber(-SPAWN_AREA, SPAWN_AREA), GetRandomNumber(-SPAWN_AREA, SPAWN_AREA), GetRandomNumber(-SPAWN_AREA, SPAWN_AREA)));

		// �������x�ݒ�
		m_units[i]->SetVelocity(DirectX::SimpleMath::Vector3(GetRandomNumber(-1.0f, 1.0f) * 0.05f, GetRandomNumber(-1.0f, 1.0f)*0.05f, GetRandomNumber(-1.0f, 1.0f) * 0.05f));
	}
}

// �X�V
void Boid::Update()
{
	for (unsigned int i = 0; i < m_units.size(); i++)
	{
		m_units[i]->Update(m_units);
	}
}

// �`��
void Boid::Render(const DirectX::SimpleMath::Matrix& _view)
{
	for (unsigned int i = 0; i < m_units.size(); i++)
	{
		// �`��
		m_units[i]->Render(_view);
	}
}

// �����̎擾
float Boid::GetRandomNumber(float _min, float _max)
{
	// �V�[�h�l����
	std::random_device seedGenerator;
	std::mt19937 mt(seedGenerator());

	// �͈͎w��
	std::uniform_real_distribution<float> rand(_min, _max);

	return rand(seedGenerator);
}
