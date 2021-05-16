#include "Ares/Events/ApplicationEvents.h"
#include <sstream>
namespace Ares
{
	_EVENT_DEFINE(WindowResolutionResizeEvent, Width << ", " << Height)
	_EVENT_DEFINE(WindowFramebufferResizeEvent, Width << ", " << Height)
	_EVENT_DEFINE(WindowCloseEvent, "")
	_EVENT_DEFINE(WindowMaximizedEvent, "")
	_EVENT_DEFINE(WindowMinimizedEvent, "")
	_EVENT_DEFINE(WindowRestoredEvent, "")
	_EVENT_DEFINE(WindowContentRescaleEvent, X << ", " << Y)
	_EVENT_DEFINE(WindowPosChangeEvent, X << ", " << Y)
	_EVENT_DEFINE(WindowFocusChangeEvent, "Focused: " << Focused)
	_EVENT_DEFINE(WindowHoveredChangeEvent, "Hovered: " << Hovered)
	_EVENT_DEFINE(FilesDroppedEvent, "Count: " << Count)
}