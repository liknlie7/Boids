#pragma once

#include <SimpleMath.h>

// �J�����N���X
class Camera
{
public: // ��{

	// �R���X�g���N�^
	Camera();

	// �f�X�g���N�^
	~Camera() {};

public: // �A�N�Z�T

	// �r���[�s��擾
	DirectX::SimpleMath::Matrix GetViewMatrix() const
	{
		return m_view;
	}

	// �J�����ʒu�擾
	DirectX::SimpleMath::Vector3 GetEyePosition() const
	{
		return m_eye;
	}

	// �J���������_�擾
	DirectX::SimpleMath::Vector3 GetTargetPosition() const
	{
		return m_target;
	}

private: // �萔

	// ���_�ʒu
	static const DirectX::SimpleMath::Vector3 EYE_POSITION;

	// �����_�ʒu
	static const DirectX::SimpleMath::Vector3 TARGET_POSITION;

	// �J�������
	static const DirectX::SimpleMath::Vector3 CAMERA_UP;

private: // �ϐ�

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;
};