#pragma once
#include "Ares/config.h"

#pragma warning(push)
#pragma warning(disable:26812 26495 26451 26498)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#define DEBUG_DECLARATION(name, internalcall) \
	template<typename... Args> \
	static void name(const char* fmt, Args &&...args) \
	{ \
		if (s_Logger != nullptr) \
		{ \
			s_Logger->internalcall(fmt, std::forward<Args>(args)...); \
		} \
	} \
	template<typename T> \
	static void name(const T& msg) \
	{ \
		if (s_Logger != nullptr) \
		{ \
			s_Logger->internalcall(msg); \
		} \
	} 

namespace AresInternal
{
	struct _ARES_API Debugging
	{
		static void Initialize();
	};

	class _ARES_API Debug
	{
		friend struct Debugging;
	public:
		DEBUG_DECLARATION(Log, trace)
		DEBUG_DECLARATION(Info, info)
		DEBUG_DECLARATION(Warn, warn)
		DEBUG_DECLARATION(Error, error)
		DEBUG_DECLARATION(Critical, critical)
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}
namespace Ares
{
	class _ARES_API Debug
	{
		friend struct AresInternal::Debugging;
	public:
		DEBUG_DECLARATION(Log, trace)
		DEBUG_DECLARATION(Info, info)
		DEBUG_DECLARATION(Warn, warn)
		DEBUG_DECLARATION(Error, error)
		DEBUG_DECLARATION(Critical, critical)
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#ifdef ARES_DEBUG
#define _ARES_DEBUGBREAK() __debugbreak()
#define _ARES_ASSERT(x, errMsg) { if (!(x)) { AresInternal::Debug::Critical("Assertion Failed: {}", errMsg); _ARES_DEBUGBREAK(); } }
#else
#define _ARES_DEBUGBREAK()
#define _ARES_ASSERT(x, errMsg)
#endif

#undef DEBUG_DECLARATION