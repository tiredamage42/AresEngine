#include "Ares/Input/ButtonMapping.h"

#define BUTTON_MAP_KEY static_cast<unsigned char>(1)
#define BUTTON_MAP_MOUSE static_cast<unsigned char>(2)
#define BUTTON_MAP_GAMEPAD static_cast<unsigned char>(4)

namespace Ares
{
	ButtonMapping::ButtonMapping(KeyCode key)
	{
		SetKeyCode(key);
	}
	ButtonMapping::ButtonMapping(MouseCode mouse)
	{
		SetMouseCode(mouse);
	}
	ButtonMapping::ButtonMapping(GamepadButton btn, Gamepad gamepadID)
	{
		SetGamepadButton(btn, gamepadID);
	}
	ButtonMapping::ButtonMapping(KeyCode key, MouseCode mouse)
	{
		SetKeyCode(key);
		SetMouseCode(mouse);
	}
	ButtonMapping::ButtonMapping(KeyCode key, GamepadButton btn, Gamepad gamepadID)
	{
		SetKeyCode(key);
		SetGamepadButton(btn, gamepadID);
	}
	ButtonMapping::ButtonMapping(MouseCode mouse, GamepadButton btn, Gamepad gamepadID)
	{
		SetMouseCode(mouse);
		SetGamepadButton(btn, gamepadID);
	}
	ButtonMapping::ButtonMapping(KeyCode key, MouseCode mouse, GamepadButton btn, Gamepad gamepadID)
	{
		SetKeyCode(key);
		SetMouseCode(mouse);
		SetGamepadButton(btn, gamepadID);
	}
	bool ButtonMapping::HasKeyCode() const
	{
		return m_Mode & BUTTON_MAP_KEY;
	}
	bool ButtonMapping::HasMouseCode() const
	{
		return m_Mode & BUTTON_MAP_MOUSE;
	}
	bool ButtonMapping::HasGamepadButton() const
	{
		return m_Mode & BUTTON_MAP_GAMEPAD;
	}
	void ButtonMapping::SetKeyCode(KeyCode code)
	{
		m_Mode |= BUTTON_MAP_KEY;
		m_Keycode = static_cast<unsigned char>(code);
	}
	void ButtonMapping::RemoveKeyCode()
	{
		m_Mode &= ~BUTTON_MAP_KEY;
	}
	void ButtonMapping::SetMouseCode(MouseCode code)
	{
		m_Mode |= BUTTON_MAP_MOUSE;
		m_MouseCode = static_cast<unsigned char>(code);
	}
	void ButtonMapping::RemoveMouseCode()
	{
		m_Mode &= ~BUTTON_MAP_MOUSE;
	}
	void ButtonMapping::SetGamepadButton(GamepadButton btn, Gamepad gamepadID)
	{
		m_Mode |= BUTTON_MAP_GAMEPAD;
		m_GamepadButton = static_cast<unsigned char>(btn);
		m_GamepadID = static_cast<unsigned char>(gamepadID);
	}
	void ButtonMapping::RemoveGamepadButton()
	{
		m_Mode &= ~BUTTON_MAP_GAMEPAD;
	}
}