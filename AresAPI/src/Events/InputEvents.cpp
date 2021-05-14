#include "Ares/Events/InputEvents.h"
#include <sstream>
namespace Ares
{
	_EVENT_DEFINE(KeyEvent, "Code: " << static_cast<unsigned char>(Code) << " :: Pressed: " << Pressed << " :: Mods: " << KeyMods)
	_EVENT_DEFINE(CharTypedEvent, Code)
	_EVENT_DEFINE(MouseMoveEvent, X << ", " << Y)
	_EVENT_DEFINE(MouseScrollEvent, X << ", " << Y)
	_EVENT_DEFINE(MouseButtonEvent, "Code: " << static_cast<unsigned char>(Code) << " :: Pressed: " << Pressed << " :: Mods: " << KeyMods)
	_EVENT_DEFINE(GamepadConnectionEvent, "Gamepad: " << Gamepad << " :: Connected: " << Connected)
}

