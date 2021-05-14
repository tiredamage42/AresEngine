#pragma once
#include "Ares/Events/Event.h"
#include "Ares/Input/InputCodes.h"
namespace Ares
{
	struct _ARES_API KeyEvent : public Event
	{
		KeyCode Code;
		bool Pressed;
		int KeyMods;
		KeyEvent(KeyCode code, bool pressed, int keymods) : Code(code), Pressed(pressed), KeyMods(keymods) { }
		_EVENT_DECLARE
	};
	struct _ARES_API CharTypedEvent : public Event
	{
		unsigned int Code;
		CharTypedEvent(unsigned int code) : Code(code) { }
		_EVENT_DECLARE
	};
	struct _ARES_API MouseMoveEvent : public Event
	{
		float X, Y;
		MouseMoveEvent(float x, float y) : X(x), Y(y) { }
		_EVENT_DECLARE
	};
	struct _ARES_API MouseScrollEvent : public Event
	{
		float X, Y;
		MouseScrollEvent(float x, float y) : X(x), Y(y) { }
		_EVENT_DECLARE
	};
	struct _ARES_API MouseButtonEvent : public Event
	{
		MouseCode Code;
		bool Pressed;
		int KeyMods;
		MouseButtonEvent(MouseCode code, bool pressed, int keymods) : Code(code), Pressed(pressed), KeyMods(keymods) { }
		_EVENT_DECLARE
	};
	struct _ARES_API GamepadConnectionEvent : public Event
	{
		bool Connected;
		int Gamepad;
		GamepadConnectionEvent(int gamepad, bool connected) : Gamepad(gamepad), Connected(connected) {}
		_EVENT_DECLARE
	};
}