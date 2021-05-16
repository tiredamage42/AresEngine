#pragma once
#include "config.h"
#include <string>
namespace AresInternal
{
	enum class EventType
	{
		None = 0,

		WindowResolutionResizeEvent, WindowFramebufferResizeEvent, WindowContentRescaleEvent, WindowPosChangeEvent,
		WindowMaximizedEvent, WindowMinimizedEvent, WindowRestoredEvent,
		WindowFocusChangeEvent, WindowHoveredChangeEvent,
		FilesDroppedEvent, WindowCloseEvent,

		KeyEvent, CharTypedEvent, MouseMoveEvent, MouseScrollEvent, MouseButtonEvent, GamepadConnectionEvent,
	};

}
namespace Ares 
{

	/*
		events are currently blocking.
		when an event occurs it immediately gets dispatched
		and must be dealt with right away

		for the future, a better strategy might be to buffer
		events in an event bus and prcess them during the "event"
		part of the update stage
	*/
	

#define _EVENT_DECLARE \
	std::string ToString() const override; \
	private: \
	friend struct Event; \
	static AresInternal::EventType Type(); \
	virtual AresInternal::EventType GetType() const override;

#define _EVENT_DEFINE(CLASS, FIELDS) \
	AresInternal::EventType CLASS::Type() { return AresInternal::EventType::CLASS; } \
	AresInternal::EventType CLASS::GetType() const { return Type(); } \
	std::string CLASS::ToString() const \
	{ \
		std::stringstream ss; \
		ss << "[" << #CLASS << " (" << FIELDS << ")]"; \
		return ss.str(); \
	}


	struct _ARES_API Event 
	{
		friend class Application;	
		template<typename T, typename O>
		bool DispatchFuncIfType(O* obj, bool(O::*func)(const T&))
		{
			if (GetType() == T::Type())
			{
				m_Handled = (obj->*func)(static_cast<const T&>(*this));
				return true;
			}
			return false;
		}
		template<typename T>
		bool DispatchFuncIfType(bool(*func)(const T&))
		{
			if (GetType() == T::Type())
			{
				m_Handled = (*func)(static_cast<const T&>(*this));
				return true;
			}
			return false;
		}

		virtual std::string ToString() const = 0;
	
	private:
		virtual AresInternal::EventType GetType() const = 0;
		bool m_Handled = false;
	};

	_ARES_API std::ostream& operator<<(std::ostream& os, const Event& e);
}