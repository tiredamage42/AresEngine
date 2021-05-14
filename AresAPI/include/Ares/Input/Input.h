#pragma once
#include "InputCodes.h"
#include <functional>
namespace Ares
{
	struct Event;
	struct KeyEvent;
	struct MouseButtonEvent;
	struct MouseScrollEvent;
	struct MouseMoveEvent;
	struct GamepadConnectionEvent;

	class ButtonMapping;

	class _ARES_API Input
	{
		friend class Application;
	public:
		
		static bool GetKeyDown(KeyCode code);
		static bool GetKeyUp(KeyCode code);
		static bool GetKeyHeld(KeyCode code);

		static bool GetMouseButtonDown(MouseCode code);
		static bool GetMouseButtonUp(MouseCode code);
		static bool GetMouseButtonHeld(MouseCode code);

		static bool GetGamepadButtonDown(GamepadButton code, Gamepad gamepadID);
		static bool GetGamepadButtonUp(GamepadButton code, Gamepad gamepadID);
		static bool GetGamepadButtonHeld(GamepadButton code, Gamepad gamepadID);

		static ButtonMapping* GetButtonMapping(const std::string& name);
		static void SetButtonMapping(const std::string& name, const ButtonMapping& mapping);

		static bool GetButtonDown(const std::string& name);
		static bool GetButtonUp(const std::string& name);
		static bool GetButtonHeld(const std::string& name);

		static bool GetButtonDown(const ButtonMapping* mapping);
		static bool GetButtonUp(const ButtonMapping* mapping);
		static bool GetButtonHeld(const ButtonMapping* mapping);
	private:
		static bool CheckButton(const ButtonMapping* mapping, bool(*checker)(unsigned char));
		static bool CheckGamepadStatus(unsigned char code, unsigned char gamepadID, bool(*checker)(unsigned char));

		static void SetMousePositionModifier(const std::function<void(float&, float&)>& modifier);
		static void EnableInputs(bool enabled);

		static bool OnKeyEvent(const KeyEvent& e);
		static bool OnMouseButtonEvent(const MouseButtonEvent& e);
		static bool OnMouseScrollEvent(const MouseScrollEvent& e);
		static bool OnMouseMoveEvent(const MouseMoveEvent& e);
		static bool OnGamepadConnectionEvent(const GamepadConnectionEvent& e);

		static void OnEvent(Event& event);
		
		static void RemoveSingleFrameStatuses();
		static void PollInputs();

		static bool s_InputEnabled;
		static std::function<void(float&, float&)> s_MousePositionModifier;
		static std::pair<float, float> s_MousePosCurrent;
		static std::pair<float, float> s_MousePosLast;
		static std::pair<float, float> s_MouseDelta;
		static std::pair<float, float> s_MouseScroll;
		
		static unsigned char s_KeyStatuses[ARES_NUM_KEYCODES];
		static unsigned char s_MouseButtonStatuses[ARES_NUM_KEYCODES];

		struct GamePadStatus
		{
			bool Connected = false;
			unsigned char Buttons[ARES_NUM_GAMEPADBUTTONS] = {};
			float Axes[ARES_NUM_GAMEPADAXES] = {};
		};

		static GamePadStatus s_GamepadStatuses[ARES_NUM_GAMEPADS];

		static std::unordered_map<std::string, ButtonMapping> s_ButtonMaps;
	};
}