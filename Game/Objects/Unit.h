#pragma once

#include <SimpleMath.h>

#include "BaseObject.h"

// ユニットクラス
class Unit :public BaseObject
{
public: // 基本

	// コンストラクタ
	Unit();
	// デストラクタ
	~Unit() {};

public: // 関数

	// 更新
	void Update(std::vector<std::unique_ptr<Unit>>& _units);

	// 速度・位置の更新
	void UpdateMove();

private: // サブ関数

	// 仲間を見つける
	void SearchFriend(std::vector<std::unique_ptr<Unit>>& _units);

	// 分離行動
	DirectX::SimpleMath::Vector3 Separation();

	// 結合行動
	DirectX::SimpleMath::Vector3 Cohesion();

	// 整列行動
	DirectX::SimpleMath::Vector3 Alignment();

	// エリア外に出そうな時反射
	void ReflectingAtWall();

	// 壁を避ける
	DirectX::SimpleMath::Vector3 CalcAccelAgainstWall(float _distance, DirectX::SimpleMath::Vector3 _direction);

private: // 定数

	// 最大速度
	static const float MAX_SPEED;

	// 最小速度
	static const float MIN_SPEED;

	// 旋回力
	static const float MAX_STEER;

	// 壁までの距離
	static const float UP_TO_WALL;

	// 重み
	static const float WALL_WEIGHT;

	// 壁の大きさ
	static const float WALL_SCALE;

	// 視野角
	static const float FIELD_OF_VIEW;

	// 視野の広さ半径
	static const float FIELD_OF_VIEW_RADIUS;

	// 分離距離
	static const float SEPARATION_DIST;

	// 分離行動重み
	static const float SEPARATION_WEIGHT;

	// 整列行動重み
	static const float ALIGNMENT_WEIGHT;

	// 結合行動重み
	static const float COHESION_WEIGHT;

	// 補間時間
	static const float LERP_TIME;


private: // 変数

	// 加速度
	DirectX::SimpleMath::Vector3	m_accel;

	// 仲間
	std::vector<Unit*>				m_friends;

	// 最も近い仲間
	Unit*							m_nearestFriend;

	// 最も近い仲間との距離
	float							m_distNearestFriend;
};

