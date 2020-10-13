#include "../../pch.h"

#include "Boid.h"

// ユニットの総数
const int Boid::NUM_UNITS = 50;

// 中心からの出現できる距離
const float Boid::SPAWN_AREA = 5.0f;

// コンストラクタ
Boid::Boid()
{
	// 配列の初期化
	m_units.clear();
	m_units.resize(NUM_UNITS);

	for (unsigned int i = 0; i < m_units.size(); i++)
	{
		// ユニット作成
		m_units[i] = std::make_unique<Unit>();

		// 初期座標設定
		m_units[i]->SetPosition(DirectX::SimpleMath::Vector3(GetRandomNumber(-SPAWN_AREA, SPAWN_AREA), GetRandomNumber(-SPAWN_AREA, SPAWN_AREA), GetRandomNumber(-SPAWN_AREA, SPAWN_AREA)));

		// 初期速度設定
		m_units[i]->SetVelocity(DirectX::SimpleMath::Vector3(GetRandomNumber(-1.0f, 1.0f) * 0.05f, GetRandomNumber(-1.0f, 1.0f)*0.05f, GetRandomNumber(-1.0f, 1.0f) * 0.05f));
	}
}

// 更新
void Boid::Update()
{
	for (unsigned int i = 0; i < m_units.size(); i++)
	{
		m_units[i]->Update(m_units);
	}
}

// 描画
void Boid::Render(const DirectX::SimpleMath::Matrix& _view)
{
	for (unsigned int i = 0; i < m_units.size(); i++)
	{
		// 描画
		m_units[i]->Render(_view);
	}
}

// 乱数の取得
float Boid::GetRandomNumber(float _min, float _max)
{
	// シード値生成
	std::random_device seedGenerator;
	std::mt19937 mt(seedGenerator());

	// 範囲指定
	std::uniform_real_distribution<float> rand(_min, _max);

	return rand(seedGenerator);
}
