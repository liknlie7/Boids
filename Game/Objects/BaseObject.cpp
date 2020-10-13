#include "../../pch.h"
#include "BaseObject.h"

// 直径
const float BaseObject::CONE_DIAMETER = 0.3f;

// 高さ
const float BaseObject::CONE_HEIGHT = 0.3f;

// コーンを倒すための角度
const float BaseObject::INIT_ANGLE = 0.0f;

// コンストラクタ
BaseObject::BaseObject()
	: m_pos(DirectX::SimpleMath::Vector3::Zero)
	, m_vel(DirectX::SimpleMath::Vector3::Zero)
	, m_dir(DirectX::SimpleMath::Vector3::Zero)
{
	// コーン作成
	m_pCone = DirectX::GeometricPrimitive::CreateCone(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(),
		CONE_DIAMETER, CONE_HEIGHT);
}

// 描画
void BaseObject::Render(const DirectX::SimpleMath::Matrix& _view)
{

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	// コーンを描画
	m_pCone->Draw(world, _view, GameContext::Get<Projection>()->GetMatrix(), m_color);
}