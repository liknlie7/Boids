#pragma once

#include <SimpleMath.h>

// カメラクラス
class Camera
{
public: // 基本

	// コンストラクタ
	Camera();

	// デストラクタ
	~Camera() {};

public: // アクセサ

	// ビュー行列取得
	DirectX::SimpleMath::Matrix GetViewMatrix() const
	{
		return m_view;
	}

	// カメラ位置取得
	DirectX::SimpleMath::Vector3 GetEyePosition() const
	{
		return m_eye;
	}

	// カメラ注視点取得
	DirectX::SimpleMath::Vector3 GetTargetPosition() const
	{
		return m_target;
	}

private: // 定数

	// 視点位置
	static const DirectX::SimpleMath::Vector3 EYE_POSITION;

	// 注視点位置
	static const DirectX::SimpleMath::Vector3 TARGET_POSITION;

	// カメラ上面
	static const DirectX::SimpleMath::Vector3 CAMERA_UP;

private: // 変数

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
};