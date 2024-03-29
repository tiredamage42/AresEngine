#pragma once
#include "config.h"
#include "Ares/Core/Core.h"

namespace Ares
{
	// mod keys corresponding to glfw
	enum class KeyMods : unsigned char
	{
		Shift = 1 << 0,
		Ctrl = 1 << 1,
		Alt = 1 << 2,
		Super = 1 << 3,
		CapsLock = 1 << 4,
		NumLock = 1 << 5,
	};

#define ARES_NUM_MOUSECODES static_cast<unsigned char>(8)
	
	ARES_ENUM(MouseCode, 
		Left, Right, Middle, Button3, Button4, Button5, Button6, Button7
	)


#define ARES_NUM_GAMEPADS static_cast<unsigned char>(16)

	ARES_ENUM(Gamepad,
		Id0, Id1, Id2, Id3, Id4, Id5, Id6, Id7, Id8, Id9, Id10, Id11, Id12, Id13, Id14, Id15,
		ANY
	)

#define ARES_NUM_GAMEPADBUTTONS static_cast<unsigned char>(15)
#define ARES_NUM_GAMEPADAXES static_cast<unsigned char>(6)
	ARES_ENUM(GamepadButton,
		South, East, West, North,
		LShoulder, RShoulder,
		Back, Start, Guide,
		LThumb, RThumb,
		DPadUp, DPadRight, DPadDown, DPadLeft
	)
	ARES_ENUM(GamepadAxis, LX, LY, RX, RY, LT, RT)

#define ARES_NUM_KEYCODES static_cast<unsigned char>(121)
	ARES_ENUM(KeyCode,
		Unknown,
		Space,
		Apostrophe, /* ' */
		Comma, /* , */
		Minus, /* - */
		Period, /* . */
		Slash, /* / */

		/* numbers */
		D0, D1, D2, D3, D4, D5, D6, D7, D8, D9,

		Semicolon, /* ; */
		Equal,  /* = */

		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

		LeftBracket, /* [ */
		Backslash, /* \ */
		RightBracket, /* ] */
		GraveAccent, /* ` */
		World2, /* non-US #1 */
		World1, /* non-US #2 */

		/* Function keys */
		Escape,
		Enter,
		Tab,
		Backspace,
		Insert,
		Delete,
		Right, Left, Down, Up,
		PageUp, PageDown,
		Home,
		End,
		CapsLock,
		ScrollLock,
		NumLock,
		PrintScreen,
		Pause,

		/* fn */
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,

		/* keypad */
		KP0, KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9,

		KPDecimal, KPDivide, KPMultiply, KPSubtract, KPAdd, KPEnter, KPEqual,

		/* mods */
		LeftShift, LeftControl, LeftAlt, LeftSuper,
		RightShift, RightControl, RightAlt, RightSuper,
		Menu
	)

	/*
		keycodes map to GLFW keys
	*/
	_ARES_API KeyCode GLFWCode2Keycode(int glfwCode);
}
