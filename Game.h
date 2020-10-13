//
// Game.h
//

#pragma once

#include <mouse.h>
#include <CommonStates.h>

#include "Game/Common/DeviceResources.h"
#include "Game/Common/StepTimer.h"
#include "Game/Common/Projection.h"
#include "Game/Common/GameContext.h"

#include "Game/Objects/Camera.h"
#include "Game/Objects/Boid.h"
#include "Game/Objects/Unit.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

private: // �ϐ�

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_pDeviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// �ˉe�s��
	std::unique_ptr<Projection>				m_pProjection;

	// �J����
	std::unique_ptr<Camera>    				m_pCamera;
		
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_pState;

	// �Q��
	std::unique_ptr<Boid>					m_pBoid;

};