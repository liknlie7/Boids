#include "../../pch.h"

#include "Unit.h"

#include "../Common/Utility.h"

// �ő呬�x
const float Unit::MAX_SPEED = 0.03f;

// �ŏ����x
const float Unit::MIN_SPEED = 0.01f;

// �����
const float Unit::MAX_STEER = 0.3f;

// �ǂ܂ł̋���
const float Unit::UP_TO_WALL = 0.3f;

// �d��
const float Unit::WALL_WEIGHT = 0.01f;

// �ǂ̑傫��
const float Unit::WALL_SCALE = 5.0f;

// ����p
const float Unit::FIELD_OF_VIEW = 90.0f;

// ����̍L�����a
const float Unit::FIELD_OF_VIEW_RADIUS = 1.0f;

// �����͈�
const float Unit::SEPARATION_DIST = 1.5f;

// �����s���d��
const float Unit::SEPARATION_WEIGHT = 3.0f;

// ����s���d��
const float Unit::ALIGNMENT_WEIGHT = 3.0f;

// �����s���d��
const float Unit::COHESION_WEIGHT = 3.0f;

// ��Ԏ���
const float Unit::LERP_TIME = 0.0005f;

// �R���X�g���N�^
Unit::Unit()
	: m_accel(DirectX::SimpleMath::Vector3::Zero)
{
	// ����
	m_dir = DirectX::SimpleMath::Vector3::Up;

	// ��ԋ߂�����
	m_nearestFriend = NULL;

	// ��ԋ߂����Ԃ܂ł̋����ݒ�
	m_distNearestFriend = INFINITY;

	// �F�ݒ�
	m_color = DirectX::Colors::Yellow;
}

// �X�V
void Unit::Update(std::vector<std::unique_ptr<Unit>>& _units)
{
	// ���Ԃ�T��
	SearchFriend(_units);

	if (!m_friends.empty())
	{
		// ���[����K�p����i�����A����A�����j
		m_accel = Separation() + Alignment() + Cohesion();
	}

	// �ʒu�E���x�X�V
	UpdateMove();
}

// ���Ԃ�T��
void Unit::SearchFriend(std::vector<std::unique_ptr<Unit>>& _units)
{
	// ������
	m_friends.clear();

	// ����̋����ݒ�
	float distThresh = FIELD_OF_VIEW_RADIUS;

	for (std::unique_ptr<Unit>& other : _units)
	{
		// �������g�Ȃ珈�����Ȃ�
		if (other.get() == this) continue;

		// �������v�Z
		DirectX::SimpleMath::Vector3 to = other->m_pos - m_pos;
		float dist = to.Length();
		if (dist < distThresh)
		{
			// �������Z�o
			DirectX::SimpleMath::Vector3 dir = to;
			dir.Normalize();
			DirectX::SimpleMath::Vector3 foward = m_vel;
			foward.Normalize();

			// ���F�ł����̂Ń��X�g�ɒǉ�
			m_friends.push_back(other.get());

			// �ł��߂�������
			if (dist < m_distNearestFriend)
			{
				m_distNearestFriend = dist;
				m_nearestFriend = other.get();
			}
		}
	}
}

// ���x�E�ʒu�̍X�V
void Unit::UpdateMove()
{
	// �ǂŔ��˂�����
	ReflectingAtWall();

	// ���x�X�V
	DirectX::SimpleMath::Vector3 steer = DirectX::SimpleMath::Vector3::Lerp(m_vel, m_accel, LERP_TIME);

	// �����X�V
	m_dir = steer;
	m_dir.Normalize();

	// ������ƌ��݂̕����œ��ς��v�Z
	float angle = std::acosf(DirectX::SimpleMath::Vector3::Up.Dot(m_dir));

	// ������̃x�N�g���ƌ��݂̕����̃x�N�g���ŊO�ς��v�Z
	DirectX::SimpleMath::Vector3 axis = DirectX::SimpleMath::Vector3::Up.Cross(m_dir);

	// ��]������
	m_rotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(axis, angle);

	// ���x��͈͓��Ɏ��߂�
	m_vel = Utility::Clamp(MIN_SPEED, m_vel.Length(), MAX_SPEED) * m_dir;

	// ���W�X�V
	m_pos += m_vel;

	// �����x������
	m_accel = DirectX::SimpleMath::Vector3::Zero;
}

// �����s��
DirectX::SimpleMath::Vector3 Unit::Separation()
{
	if (m_friends.size() == 0) return DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

	for (auto& friends : m_friends)
	{
		DirectX::SimpleMath::Vector3 to = friends->m_pos - m_pos;

		// ���ԂƋ߂������痣���
		if (m_distNearestFriend < SEPARATION_DIST)
		{
			DirectX::SimpleMath::Vector3 f = (m_pos - friends->m_pos);
			f.Normalize();
			force += f;
		}
		// ���ԂƉ���������߂Â�
		else if (m_distNearestFriend > SEPARATION_DIST)
		{
			DirectX::SimpleMath::Vector3 f = (friends->m_pos - m_pos);
			f.Normalize();
			force += f;
		}
		// ���x�����ʒu�Ȃ�Ȃɂ����Ȃ�
		else
		{
			force = DirectX::SimpleMath::Vector3::Zero;
		}
	}
	// �͂𕽋ς�
	force /= (float)m_friends.size();

	// �����x�X�V
	return force * SEPARATION_WEIGHT;
}

// ����s��
DirectX::SimpleMath::Vector3 Unit::Alignment()
{
	if (m_friends.size() == 0) return DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Vector3 averageVelocity = DirectX::SimpleMath::Vector3::Zero;
	for (auto& friends : m_friends)
	{
		averageVelocity += friends->m_vel;
	}
	// ���ϑ��x�̎Z�o
	averageVelocity /= m_friends.size();
	averageVelocity.Normalize();

	// �����x�X�V
	return (averageVelocity - m_vel) * ALIGNMENT_WEIGHT;
}

// �����s��
DirectX::SimpleMath::Vector3 Unit::Cohesion()
{
	if (m_friends.size() == 0) return DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Vector3 averagePos = DirectX::SimpleMath::Vector3::Zero;

	for (auto& friends : m_friends)
	{
		averagePos += friends->m_pos;
	}
	// ���S�̍��W���Z�o����
	averagePos /= m_friends.size();

	// ���S�̍��W�Ɍ������x�N�g��
	averagePos.Normalize();

	// �����x�X�V
	return (averagePos - m_pos) * COHESION_WEIGHT;
}

// �ǂŔ��˂�����
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

// �ǂ������
DirectX::SimpleMath::Vector3 Unit::CalcAccelAgainstWall(float _distance, DirectX::SimpleMath::Vector3 _direction)
{
	if (-UP_TO_WALL < _distance && _distance < UP_TO_WALL)
	{
		return _direction * (WALL_WEIGHT / abs(_distance / UP_TO_WALL));
	}
	return DirectX::SimpleMath::Vector3::Zero;
}
