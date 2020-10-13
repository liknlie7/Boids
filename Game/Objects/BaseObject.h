#pragma once

#include <GeometricPrimitive.h>
#include <SimpleMath.h>

#include "../Common/GameContext.h"
#include "../Common/DeviceResources.h"
#include "../Common/Projection.h"

// �I�u�W�F�N�g���N���X
class BaseObject
{
public: // ��{

	// �R���X�g���N�^
	BaseObject();

	// �f�X�g���N�^
	~BaseObject() {};

public: // �A�N�Z�T

	// ���W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		return m_pos;
	}

	// ���x�̎擾
	DirectX::SimpleMath::Vector3 GetVelocity() const
	{
		return m_vel;
	}

	// ���W�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3 _pos)
	{
		m_pos = _pos;
	}

	// ���x�ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3 _vel)
	{
		m_vel = _vel;
	}

public: // �֐�

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view);

protected: // �萔

	// ���a
	static const float CONE_DIAMETER;

	// ����
	static const float CONE_HEIGHT;

	// �R�[����|�����߂̊p�x
	static const float INIT_ANGLE;

protected: // �ϐ�

	// �`��
	std::unique_ptr<DirectX::GeometricPrimitive> m_pCone;

	// ���W
	DirectX::SimpleMath::Vector3 m_pos;

	// ���x
	DirectX::SimpleMath::Vector3 m_vel;

	// �F
	DirectX::SimpleMath::Vector4 m_color;

	// ����
	DirectX::SimpleMath::Vector3 m_dir;

	// �p�x
	DirectX::SimpleMath::Quaternion m_rotate;
};

