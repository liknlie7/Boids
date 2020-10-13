#pragma once

#include "SimpleMath.h"

// �v���W�F�N�V�����p�N���X
class Projection final
{
public: // ��{

	// �R���X�g���N�^
	Projection() = default;
	
	// �f�X�g���N�^
	~Projection() = default;

private: // �ϐ�

	// �s��
	DirectX::SimpleMath::Matrix m_matrix;

public: // �A�N�Z�T

	// �s��擾
	const DirectX::SimpleMath::Matrix& GetMatrix() const;

public: // �֐�

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