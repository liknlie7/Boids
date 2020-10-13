#pragma once

#include <vector>
#include <random>

#include "../Common/GameContext.h"
#include "../Objects/Unit.h"

// 群れクラス
class Boid
{
public: // 基本

	// コンストラクタ
	Boid();

	// デストラクタ
	~Boid() {};

public: // 関数

	// 更新
	void Update();

	// 描画
	void Render(const DirectX::SimpleMath::Matrix& _view);

private: // サブ関数

	// 乱数の取得
	float GetRandomNumber(const float _min, const float _max);

private: // 定数

	// ユニットの総数
	static const int NUM_UNITS;

	// 中心からの出現できる距離
	static const float SPAWN_AREA;

private: // 変数

	// ユニット
	std::vector<std::unique_ptr<Unit>> m_units;
};

