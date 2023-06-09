#include "Controller.h"

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <Xinput.h>

using namespace dae;

class Controller::ControllerImpl
{
public:
    ControllerImpl(unsigned int controllerIndex) :
        m_ControllerIndex{ controllerIndex }
    {
        ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    }

    void Update()
    {
        CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
        XInputGetState(m_ControllerIndex, &m_CurrentState);

        m_ButtonsPressedThisFrame = m_CurrentState.Gamepad.wButtons & ~m_PreviousState.Gamepad.wButtons;
    }

    bool IsButtonDown(ControllerButton button) const
    {
        return (m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0;
    }

    bool IsUpThisFrame(ControllerButton button) const
    {
        return (m_ButtonsPressedThisFrame & static_cast<unsigned int>(button)) != 0;
    }

    bool IsPressed(ControllerButton button) const
    {
        return (m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button)) != 0;
    }

    unsigned int GetControllerIndex() const { return m_ControllerIndex; }

private:
    XINPUT_STATE m_CurrentState{};
    XINPUT_STATE m_PreviousState{};
    unsigned int m_ButtonsPressedThisFrame{};

    unsigned int m_ControllerIndex{};
};



Controller::Controller(unsigned int controllerIndex)
{
    m_pImpl = std::make_shared<ControllerImpl>(controllerIndex);
}


void Controller::Update() const
{
    m_pImpl->Update();
}

bool Controller::IsButtonDown(ControllerButton button) const
{
    return m_pImpl->IsButtonDown(button);
}

bool Controller::IsUpThisFrame(ControllerButton button) const
{
    return m_pImpl->IsUpThisFrame(button);
}

bool Controller::IsPressed(ControllerButton button) const
{
    return m_pImpl->IsPressed(button);
}

unsigned int Controller::GetControllerIndex() const
{
    return m_pImpl->GetControllerIndex();
}
