#include "../../pch.h"
#include "Camera.h"

// ���_�ʒu
const DirectX::SimpleMath::Vector3 Camera::EYE_POSITION = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -10.0f);

// �����_�ʒu
const DirectX::SimpleMath::Vector3 Camera::TARGET_POSITION = DirectX::SimpleMath::Vector3::Zero;

// �J�������
const DirectX::SimpleMath::Vector3 Camera::CAMERA_UP = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

// �R���X�g���N�^
Camera::Camera()
{
	// �r���[�s��쐬
	m_eye = EYE_POSITION;
	m_target = TARGET_POSITION;
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, CAMERA_UP);
}