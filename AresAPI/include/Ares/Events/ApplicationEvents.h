#pragma once
#include "Ares/Events/Event.h"
namespace Ares 
{
	struct _ARES_API WindowResolutionResizeEvent : public Event
	{
		int Width, Height;
		WindowResolutionResizeEvent(int width, int height) : Width(width), Height(height) { }
		_EVENT_DECLARE
	};
	struct _ARES_API WindowFramebufferResizeEvent : public Event
	{
		int Width, Height;
		WindowFramebufferResizeEvent(int width, int height) : Width(width), Height(height) { }
		_EVENT_DECLARE
	};
	struct _ARES_API WindowContentRescaleEvent : public Event
	{
		float X, Y;
		WindowContentRescaleEvent(float x, float y) : X(x), Y(y) { }
		_EVENT_DECLARE
	};
	struct _ARES_API WindowMaximizedEvent : public Event
	{
		_EVENT_DECLARE
	};
	struct _ARES_API WindowMinimizedEvent : public Event
	{
		_EVENT_DECLARE
	};
	struct _ARES_API WindowRestoredEvent : public Event
	{
		_EVENT_DECLARE
	};
	struct WindowFocusChangeEvent : public Event
	{
		bool Focused;
		WindowFocusChangeEvent(bool focused) : Focused(focused) { }
		_EVENT_DECLARE
	};
	struct _ARES_API WindowHoveredChangeEvent : public Event
	{
		bool Hovered;
		WindowHoveredChangeEvent(bool hovered) : Hovered(hovered) { }
		_EVENT_DECLARE
	};
	struct _ARES_API WindowPosChangeEvent : public Event
	{
		int X, Y;
		WindowPosChangeEvent(int x, int y) : X(x), Y(y) { }
		_EVENT_DECLARE
	};
	struct _ARES_API FilesDroppedEvent : public Event
	{
		const char** Paths;
		int Count;
		FilesDroppedEvent(const char** paths, int count) : Paths(paths), Count(count) { }
		_EVENT_DECLARE
	};
	struct _ARES_API WindowCloseEvent : public Event
	{
		_EVENT_DECLARE
	};
}