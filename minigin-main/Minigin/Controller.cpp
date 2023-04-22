#include "Controller.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>


class Controller::ControllerImpl
{
public:
    ControllerImpl(unsigned int controllerIndex):
        m_ControllerIndex{controllerIndex}
    {
        ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    }

    void Update()
    {
        CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
        XInputGetState(m_ControllerIndex, &m_CurrentState);

        auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
        m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
        m_ButtonsPressedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
    }
    bool IsButtonDown(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
    bool IsUpThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
    bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }
    unsigned int GetControllerIndex() const { return m_ControllerIndex; }

private:
    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_PreviousState{};
    int m_ButtonsPressedThisFrame{};
    int m_ButtonsReleasedFrame{};

    unsigned int m_ControllerIndex{};
};


Controller::Controller(unsigned int controllerIdx)
{
    m_pImpl = new ControllerImpl(controllerIdx);
}

Controller::~Controller()
{
    delete m_pImpl;
}

void Controller::Update()
{
    m_pImpl->Update();
}

bool Controller::IsButtonDown(unsigned int button) const
{
    return m_pImpl->IsButtonDown(button);
}

bool Controller::IsUpThisFrame(unsigned int button) const
{
    return m_pImpl->IsUpThisFrame(button);
}

bool Controller::IsPressed(unsigned int button) const
{
    return m_pImpl->IsPressed(button);
}

unsigned int Controller::GetControllerIndex() const
{
    return m_pImpl->GetControllerIndex();
}
