#include "../../pch.h"

#include "Unit.h"

#include "../Common/Utility.h"

// 最大速度
const float Unit::MAX_SPEED = 0.03f;

// 最小速度
const float Unit::MIN_SPEED = 0.01f;

// 旋回力
const float Unit::MAX_STEER = 0.3f;

// 壁までの距離
const float Unit::UP_TO_WALL = 0.3f;

// 重み
const float Unit::WALL_WEIGHT = 0.01f;

// 壁の大きさ
const float Unit::WALL_SCALE = 5.0f;

// 視野角
const float Unit::FIELD_OF_VIEW = 90.0f;

// 視野の広さ半径
const float Unit::FIELD_OF_VIEW_RADIUS = 1.0f;

// 分離範囲
const float Unit::SEPARATION_DIST = 1.5f;

// 分離行動重み
const float Unit::SEPARATION_WEIGHT = 3.0f;

// 整列行動重み
const float Unit::ALIGNMENT_WEIGHT = 3.0f;

// 結合行動重み
const float Unit::COHESION_WEIGHT = 3.0f;

// 補間時間
const float Unit::LERP_TIME = 0.0005f;

// コンストラクタ
Unit::Unit()
	: m_accel(DirectX::SimpleMath::Vector3::Zero)
{
	// 方向
	m_dir = DirectX::SimpleMath::Vector3::Up;

	// 一番近い仲間
	m_nearestFriend = NULL;

	// 一番近い仲間までの距離設定
	m_distNearestFriend = INFINITY;

	// 色設定
	m_color = DirectX::Colors::Yellow;
}

// 更新
void Unit::Update(std::vector<std::unique_ptr<Unit>>& _units)
{
	// 仲間を探す
	SearchFriend(_units);

	if (!m_friends.empty())
	{
		// ルールを適用する（分離、整列、結合）
		m_accel = Separation() + Alignment() + Cohesion();
	}

	// 位置・速度更新
	UpdateMove();
}

// 仲間を探す
void Unit::SearchFriend(std::vector<std::unique_ptr<Unit>>& _units)
{
	// 初期化
	m_friends.clear();

	// 視野の距離設定
	float distThresh = FIELD_OF_VIEW_RADIUS;

	for (std::unique_ptr<Unit>& other : _units)
	{
		// 自分自身なら処理しない
		if (other.get() == this) continue;

		// 距離を計算
		DirectX::SimpleMath::Vector3 to = other->m_pos - m_pos;
		float dist = to.Length();
		if (dist < distThresh)
		{
			// 方向を算出
			DirectX::SimpleMath::Vector3 dir = to;
			dir.Normalize();
			DirectX::SimpleMath::Vector3 foward = m_vel;
			foward.Normalize();

			// 視認できたのでリストに追加
			m_friends.push_back(other.get());

			// 最も近いか判定
			if (dist < m_distNearestFriend)
			{
				m_distNearestFriend = dist;
				m_nearestFriend = other.get();
			}
		}
	}
}

// 速度・位置の更新
void Unit::UpdateMove()
{
	// 壁で反射させる
	ReflectingAtWall();

	// 速度更新
	DirectX::SimpleMath::Vector3 steer = DirectX::SimpleMath::Vector3::Lerp(m_vel, m_accel, LERP_TIME);

	// 向き更新
	m_dir = steer;
	m_dir.Normalize();

	// 上方向と現在の方向で内積を計算
	float angle = std::acosf(DirectX::SimpleMath::Vector3::Up.Dot(m_dir));

	// 上方向のベクトルと現在の方向のベクトルで外積を計算
	DirectX::SimpleMath::Vector3 axis = DirectX::SimpleMath::Vector3::Up.Cross(m_dir);

	// 回転させる
	m_rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle);

	// 速度を範囲内に収める
	m_vel = Utility::Clamp(MIN_SPEED, m_vel.Length(), MAX_SPEED) * m_dir;

	// 座標更新
	m_pos += m_vel;

	// 加速度初期化
	m_accel = DirectX::SimpleMath::Vector3::Zero;
}

// 分離行動
DirectX::SimpleMath::Vector3 Unit::Separation()
{
	if (m_friends.size() == 0) return DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

	for (auto& friends : m_friends)
	{
		DirectX::SimpleMath::Vector3 to = friends->m_pos - m_pos;

		// 仲間と近すぎたら離れる
		if (m_distNearestFriend < SEPARATION_DIST)
		{
			DirectX::SimpleMath::Vector3 f = (m_pos - friends->m_pos);
			f.Normalize();
			force += f;
		}
		// 仲間と遠すぎたら近づく
		else if (m_distNearestFriend > SEPARATION_DIST)
		{
			DirectX::SimpleMath::Vector3 f = (friends->m_pos - m_pos);
			f.Normalize();
			force += f;
		}
		// 丁度いい位置ならなにもしない
		else
		{
			force = DirectX::SimpleMath::Vector3::Zero;
		}
	}
	// 力を平均に
	force /= (float)m_friends.size();

	// 加速度更新
	return force * SEPARATION_WEIGHT;
}

// 整列行動
DirectX::SimpleMath::Vector3 Unit::Alignment()
{
	if (m_friends.size() == 0) return DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Vector3 averageVelocity = DirectX::SimpleMath::Vector3::Zero;
	for (auto& friends : m_friends)
	{
		averageVelocity += friends->m_vel;
	}
	// 平均速度の算出
	averageVelocity /= m_friends.size();
	averageVelocity.Normalize();

	// 加速度更新
	return (averageVelocity - m_vel) * ALIGNMENT_WEIGHT;
}

// 結合行動
DirectX::SimpleMath::Vector3 Unit::Cohesion()
{
	if (m_friends.size() == 0) return DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Vector3 averagePos = DirectX::SimpleMath::Vector3::Zero;

	for (auto& friends : m_friends)
	{
		averagePos += friends->m_pos;
	}
	// 中心の座標を算出する
	averagePos /= m_friends.size();

	// 中心の座標に向かうベクトル
	averagePos.Normalize();

	// 加速度更新
	return (averagePos - m_pos) * COHESION_WEIGHT;
}

// 壁で反射させる
void Unit::ReflectingAtWall()
{
	float scale = WALL_SCALE;

	m_vel +=
		CalcAccelAgainstWall(-scale - m_pos.x, DirectX::SimpleMath::Vector3::Right) +
		CalcAccelAgainstWall(-scale - m_pos.y, DirectX::SimpleMath::Vector3::Up) +
		CalcAccelAgainstWall(-scale - m_pos.z, DirectX::SimpleMath::Vector3::Backward) +
		CalcAccelAgainstWall(+scale - m_pos.x, DirectX::SimpleMath::Vector3::Left) +
		CalcAccelAgainstWall(+scale - m_pos.y, DirectX::SimpleMath::Vector3::Down) +
		CalcAccelAgainstWall(+scale - m_pos.z, DirectX::SimpleMath::Vector3::Forward);
}

// 壁を避ける
DirectX::SimpleMath::Vector3 Unit::CalcAccelAgainstWall(float _distance, DirectX::SimpleMath::Vector3 _direction)
{
	if (-UP_TO_WALL < _distance && _distance < UP_TO_WALL)
	{
		return _direction * (WALL_WEIGHT / abs(_distance / UP_TO_WALL));
	}
	return DirectX::SimpleMath::Vector3::Zero;
}
