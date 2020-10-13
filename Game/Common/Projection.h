#pragma once

#include "SimpleMath.h"

// プロジェクション用クラス
class Projection final
{
public: // 基本

	// コンストラクタ
	Projection() = default;
	
	// デストラクタ
	~Projection() = default;

private: // 変数

	// 行列
	DirectX::SimpleMath::Matrix m_matrix;

public: // アクセサ

	// 行列取得
	const DirectX::SimpleMath::Matrix& GetMatrix() const;

public: // 関数

	void SetPerspectiveFieldOfView(float _fov, float _aspectRatio, float _nearPlane, float _farPlane);
};

inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}

inline void Projection::SetPerspectiveFieldOfView(float _fov, float _aspectRatio, float _nearPlane, float _farPlane)
{
	m_matrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(_fov, _aspectRatio, _nearPlane, _farPlane);
}