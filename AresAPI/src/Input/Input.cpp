#include "Ares/Input/Input.h"
#include "Ares/Input/ButtonMapping.h"
#include "Ares/Events/InputEvents.h"
#include <GLFW/glfw3.h>

namespace Ares
{

#define INPUT_STATUS_OFF static_cast<unsigned char>(0)
#define INPUT_STATUS_HELD static_cast<unsigned char>(1)
#define INPUT_STATUS_DOWN static_cast<unsigned char>(2)
#define INPUT_STATUS_RELEASED static_cast<unsigned char>(4)

	bool Input::s_InputEnabled = true;
	std::function<void(float&, float&)> Input::s_MousePositionModifier = nullptr;
	std::pair<float, float> Input::s_MousePosCurrent = { 0.0f, 0.0f };
	std::pair<float, float> Input::s_MousePosLast = { 0.0f, 0.0f };
	std::pair<float, float> Input::s_MouseDelta = { 0.0f, 0.0f };
	std::pair<float, float> Input::s_MouseScroll = { 0.0f, 0.0f };

	unsigned char Input::s_KeyStatuses[ARES_NUM_KEYCODES] = {};
	unsigned char Input::s_MouseButtonStatuses[ARES_NUM_KEYCODES] = {};
	Input::GamePadStatus Input::s_GamepadStatuses[ARES_NUM_GAMEPADS] = {};
	std::unordered_map<std::string, ButtonMapping> Input::s_ButtonMaps = {};

	bool Input::OnKeyEvent(const KeyEvent& e)
	{
		unsigned char code = static_cast<unsigned char>(e.Code);
		if (e.Pressed)
		{
			// was not pressed before or just released
			if (!s_KeyStatuses[code] || s_KeyStatuses[code] == INPUT_STATUS_RELEASED)
			{
				s_KeyStatuses[code] = INPUT_STATUS_HELD | INPUT_STATUS_DOWN;
			}
		}
		else
		{
			s_KeyStatuses[code] = INPUT_STATUS_RELEASED;
		}
		return false;
	}

	bool Input::OnMouseButtonEvent(const MouseButtonEvent& e)
	{
		unsigned char code = static_cast<unsigned char>(e.Code);
		if (e.Pressed)
		{
			// was not pressed before or just released
			if (!s_MouseButtonStatuses[code] || s_MouseButtonStatuses[code] == INPUT_STATUS_RELEASED)
			{
				s_MouseButtonStatuses[code] = INPUT_STATUS_HELD | INPUT_STATUS_DOWN;
			}
		}
		else
		{
			s_MouseButtonStatuses[code] = INPUT_STATUS_RELEASED;
		}
		return false;
	}
	bool Input::OnMouseScrollEvent(const MouseScrollEvent& e)
	{
		s_MouseScroll = { e.X, e.Y };
		return false;
	}


	ButtonMapping* Input::GetButtonMapping(const std::string& name)
	{
		if (s_ButtonMaps.find(name) != s_ButtonMaps.end())
		{
			return &s_ButtonMaps.at(name);
		}
		return nullptr;
	}

	void Input::SetButtonMapping(const std::string& name, const ButtonMapping& mapping)
	{
		s_ButtonMaps.insert_or_assign(name, mapping);
	}

	bool Input::GetButtonDown(const std::string& name)
	{
		return GetButtonDown(GetButtonMapping(name));
	}

	bool Input::GetButtonUp(const std::string& name)
	{
		return GetButtonUp(GetButtonMapping(name));
	}

	bool Input::GetButtonHeld(const std::string& name)
	{
		return GetButtonHeld(GetButtonMapping(name));
	}

	static bool CheckDown(unsigned char status)
	{
		return status & INPUT_STATUS_DOWN;
	}
	static bool CheckUp(unsigned char status)
	{
		return status & INPUT_STATUS_RELEASED;
	}
	static bool CheckHeld(unsigned char status)
	{
		return status & INPUT_STATUS_HELD;
	}

	bool Input::CheckButton(const ButtonMapping* mapping, bool(*checker)(unsigned char))
	{
		if (mapping == nullptr)
			return false;
		if (mapping->HasKeyCode() && checker(s_KeyStatuses[mapping->m_Keycode]))
			return true;
		if (mapping->HasMouseCode() && checker(s_MouseButtonStatuses[mapping->m_MouseCode]))
			return true;
		if (mapping->HasGamepadButton() && CheckGamepadStatus(mapping->m_GamepadButton, mapping->m_GamepadID, checker))
			return true;
		return false;
	}


	bool Input::GetButtonDown(const ButtonMapping* mapping)
	{
		return CheckButton(mapping, &CheckDown);
	}
	bool Input::GetButtonUp(const ButtonMapping* mapping)
	{
		return CheckButton(mapping, &CheckUp);
	}
	bool Input::GetButtonHeld(const ButtonMapping* mapping)
	{
		return CheckButton(mapping, &CheckHeld);
	}

	bool Input::GetKeyDown(KeyCode code)
	{
		return CheckDown(s_KeyStatuses[static_cast<unsigned char>(code)]);
	}
	bool Input::GetKeyUp(KeyCode code)
	{
		return CheckUp(s_KeyStatuses[static_cast<unsigned char>(code)]);
	}
	bool Input::GetKeyHeld(KeyCode code)
	{
		return CheckHeld(s_KeyStatuses[static_cast<unsigned char>(code)]);
	}

	bool Input::GetMouseButtonDown(MouseCode code)
	{
		return CheckDown(s_MouseButtonStatuses[static_cast<unsigned char>(code)]);
	}
	bool Input::GetMouseButtonUp(MouseCode code)
	{
		return CheckUp(s_MouseButtonStatuses[static_cast<unsigned char>(code)]);
	}
	bool Input::GetMouseButtonHeld(MouseCode code)
	{
		return CheckHeld(s_MouseButtonStatuses[static_cast<unsigned char>(code)]);
	}

	bool Input::CheckGamepadStatus(unsigned char code, unsigned char gamepadID, bool(*checker)(unsigned char))
	{
		if (gamepadID == static_cast<unsigned char>(Gamepad::ANY))
		{
			for (unsigned char i = 0; i < ARES_NUM_GAMEPADS; ++i)
			{
				if (checker(s_GamepadStatuses[i].Buttons[code]))
				{
					return true;
				}
			}
			return false;
		}
		return checker(s_GamepadStatuses[gamepadID].Buttons[code]);
	}
	bool Input::GetGamepadButtonDown(GamepadButton code, Gamepad gamepadID)
	{
		return CheckGamepadStatus(static_cast<unsigned char>(code), static_cast<unsigned char>(gamepadID), &CheckDown);
	}
	bool Input::GetGamepadButtonUp(GamepadButton code, Gamepad gamepadID)
	{
		return CheckGamepadStatus(static_cast<unsigned char>(code), static_cast<unsigned char>(gamepadID), &CheckUp);
	}
	bool Input::GetGamepadButtonHeld(GamepadButton code, Gamepad gamepadID)
	{
		return CheckGamepadStatus(static_cast<unsigned char>(code), static_cast<unsigned char>(gamepadID), &CheckHeld);
	}




	void Input::SetMousePositionModifier(const std::function<void(float&, float&)>& modifier)
	{
		s_MousePositionModifier = modifier;
	}
	void Input::EnableInputs(bool enabled)
	{
		s_InputEnabled = enabled;
	}

	bool Input::OnMouseMoveEvent(const MouseMoveEvent& e)
	{
		float x = e.X;
		float y = e.Y;

		// we might need to modify the mouse position
		// i.e. when in editor mode, but playing, the game scripts will expect mouse position to be in relation
		// to the game view, not the entire glfw window...
		if (s_MousePositionModifier != nullptr)
		{
			s_MousePositionModifier(x, y);
		}
		s_MousePosCurrent = { x, y };
		return false;
	}
	bool Input::OnGamepadConnectionEvent(const GamepadConnectionEvent& e)
	{
		GamePadStatus& status = s_GamepadStatuses[e.Gamepad];

		status.Connected = e.Connected;
		//const char* name = glfwGetJoystickName(joystickID);
		//const char* name = glfwGetGamepadName(e.Gamepad);		
		if (!status.Connected)
		{
			for (unsigned char j = 0; j < ARES_NUM_GAMEPADBUTTONS; ++j)
				status.Buttons[j] = 0;
			for (unsigned char j = 0; j < ARES_NUM_GAMEPADAXES; ++j)
				status.Axes[j] = 0.0f;
		}
		return false;
	}

	void Input::OnEvent(Event& event)
	{	
		if (event.DispatchFuncIfType<KeyEvent>(&Input::OnKeyEvent)) 
			return;
		if (event.DispatchFuncIfType<MouseButtonEvent>(&Input::OnMouseButtonEvent)) 
			return;
		if (event.DispatchFuncIfType<MouseScrollEvent>(&Input::OnMouseScrollEvent)) 
			return;
		if (event.DispatchFuncIfType<MouseMoveEvent>(&Input::OnMouseMoveEvent)) 
			return;
		if (event.DispatchFuncIfType<GamepadConnectionEvent>(&Input::OnGamepadConnectionEvent)) 
			return;
	}
	void Input::RemoveSingleFrameStatuses()
	{
		s_MouseScroll = { 0.0f, 0.0f };

		for (unsigned char i = 0; i < ARES_NUM_KEYCODES; ++i)
		{
			s_KeyStatuses[i] &= ~(INPUT_STATUS_RELEASED | INPUT_STATUS_DOWN);
		}
		for (unsigned char i = 0; i < ARES_NUM_MOUSECODES; ++i)
		{
			s_MouseButtonStatuses[i] &= ~(INPUT_STATUS_RELEASED | INPUT_STATUS_DOWN);
		}

		for (unsigned char i = 0; i < ARES_NUM_GAMEPADS; ++i)
		{
			for (unsigned char j = 0; j < ARES_NUM_GAMEPADBUTTONS; ++j)
			{
				s_GamepadStatuses[i].Buttons[j] &= ~(INPUT_STATUS_RELEASED | INPUT_STATUS_DOWN);
			}
		}
	}


	void Input::PollInputs()
	{
		glfwPollEvents(); // launcher / play mode
		//glfwWaitEvents(); // editor mode

		s_MouseDelta = { s_MousePosCurrent.first - s_MousePosLast.first, s_MousePosCurrent.second - s_MousePosLast.second };
		s_MousePosLast = s_MousePosCurrent;

		for (unsigned char i = 0; i < ARES_NUM_GAMEPADS; ++i)
		{
			GLFWgamepadstate state;
			if (glfwGetGamepadState(i, &state))
			{
				GamePadStatus& status = s_GamepadStatuses[i];

				for (unsigned char j = 0; j < ARES_NUM_GAMEPADBUTTONS; ++j)
				{
					if (state.buttons[j])
					{
						// was not pressed before or just released
						if (!status.Buttons[j] || status.Buttons[j] == INPUT_STATUS_RELEASED)
						{
							status.Buttons[j] = INPUT_STATUS_HELD | INPUT_STATUS_DOWN;
						}
					}
					else
					{
						if (status.Buttons[j] & INPUT_STATUS_HELD)
						{
							status.Buttons[j] = INPUT_STATUS_RELEASED;
						}
					}
				}
				for (unsigned char j = 0; j < ARES_NUM_GAMEPADAXES; ++j)
				{
					status.Axes[j] = state.axes[j];
				}
			}
		}
	}

	
	


	
}
