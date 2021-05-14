#pragma once
#include "Ares/config.h"

namespace Ares
{

	enum class KeyCode : unsigned char;
	enum class MouseCode : unsigned char;
	enum class GamepadButton : unsigned char;
	enum class Gamepad : unsigned char;

	/*
		Holds a single input, either or all (KeyCode, MouseCode, gamepad button).
		this way we can assing a code/button to a name
	*/
	class _ARES_API ButtonMapping
	{
		friend class Input;

	public:
		ButtonMapping() = default;
		ButtonMapping(KeyCode key);
		ButtonMapping(MouseCode mouse);
		ButtonMapping(GamepadButton btn, Gamepad gamepadID);
		ButtonMapping(KeyCode key, MouseCode mouse);
		ButtonMapping(KeyCode key, GamepadButton btn, Gamepad gamepadID);
		ButtonMapping(MouseCode mouse, GamepadButton btn, Gamepad gamepadID);
		ButtonMapping(KeyCode key, MouseCode mouse, GamepadButton btn, Gamepad gamepadID);

		bool HasKeyCode() const;
		bool HasMouseCode() const;
		bool HasGamepadButton() const;

		void SetKeyCode(KeyCode code);
		void RemoveKeyCode();
		
		void SetMouseCode(MouseCode code);
		void RemoveMouseCode();
		
		void SetGamepadButton(GamepadButton btn, Gamepad gamepadID);
		void RemoveGamepadButton();

	private:
		unsigned char m_GamepadButton = 0;
		unsigned char m_GamepadID = 0;
		unsigned char m_Keycode = 0;
		unsigned char m_MouseCode = 0;
		unsigned char m_Mode = 0;
	};
}