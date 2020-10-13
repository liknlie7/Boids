#include "../../pch.h"
#include "Camera.h"

// 視点位置
const DirectX::SimpleMath::Vector3 Camera::EYE_POSITION = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -10.0f);

// 注視点位置
const DirectX::SimpleMath::Vector3 Camera::TARGET_POSITION = DirectX::SimpleMath::Vector3::Zero;

// カメラ上面
const DirectX::SimpleMath::Vector3 Camera::CAMERA_UP = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

// コンストラクタ
Camera::Camera()
{
	// ビュー行列作成
	m_eye = EYE_POSITION;
	m_target = TARGET_POSITION;
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, CAMERA_UP);
}