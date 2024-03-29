#pragma once
#include "config.h"
#include <string>
#include <vector>
namespace Ares
{
	class _ARES_API StringUtils
	{
	public:
		static void RemoveWhiteSpace(std::string& str);
		static void SeperateString(const std::string& str, const char delim, std::vector<std::string>& result);
	};
}