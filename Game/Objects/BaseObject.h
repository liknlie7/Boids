#pragma once

#include <GeometricPrimitive.h>
#include <SimpleMath.h>

#include "../Common/GameContext.h"
#include "../Common/DeviceResources.h"
#include "../Common/Projection.h"

// オブジェクト基底クラス
class BaseObject
{
public: // 基本

	// コンストラクタ
	BaseObject();

	// デストラクタ
	~BaseObject() {};

public: // アクセサ

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		return m_pos;
	}

	// 速度の取得
	DirectX::SimpleMath::Vector3 GetVelocity() const
	{
		return m_vel;
	}

	// 座標の設定
	void SetPosition(const DirectX::SimpleMath::Vector3 _pos)
	{
		m_pos = _pos;
	}

	// 速度設定
	void SetVelocity(const DirectX::SimpleMath::Vector3 _vel)
	{
		m_vel = _vel;
	}

public: // 関数

	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view);

protected: // 定数

	// 直径
	static const float CONE_DIAMETER;

	// 高さ
	static const float CONE_HEIGHT;

	// コーンを倒すための角度
	static const float INIT_ANGLE;

protected: // 変数

	// 形状
	std::unique_ptr<DirectX::GeometricPrimitive> m_pCone;

	// 座標
	DirectX::SimpleMath::Vector3 m_pos;

	// 速度
	DirectX::SimpleMath::Vector3 m_vel;

	// 色
	DirectX::SimpleMath::Vector4 m_color;

	// 向き
	DirectX::SimpleMath::Vector3 m_dir;

	// 角度
	DirectX::SimpleMath::Quaternion m_rotate;
};

