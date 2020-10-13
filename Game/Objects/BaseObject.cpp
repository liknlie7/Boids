#include "../../pch.h"
#include "BaseObject.h"

// ���a
const float BaseObject::CONE_DIAMETER = 0.3f;

// ����
const float BaseObject::CONE_HEIGHT = 0.3f;

// �R�[����|�����߂̊p�x
const float BaseObject::INIT_ANGLE = 0.0f;

// �R���X�g���N�^
BaseObject::BaseObject()
	: m_pos(DirectX::SimpleMath::Vector3::Zero)
	, m_vel(DirectX::SimpleMath::Vector3::Zero)
	, m_dir(DirectX::SimpleMath::Vector3::Zero)
{
	// �R�[���쐬
	m_pCone = DirectX::GeometricPrimitive::CreateCone(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
		CONE_DIAMETER, CONE_HEIGHT);
}

// �`��
void BaseObject::Render(const DirectX::SimpleMath::Matrix& _view)
{

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	// �R�[����`��
	m_pCone->Draw(world, _view, GameContext::Get<Projection>()->GetMatrix(), m_color);
}