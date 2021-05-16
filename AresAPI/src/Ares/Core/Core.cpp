#include "Ares/Core/Core.h"
#include "Ares/Utils/StringUtils.h"
namespace Ares
{
	
}

namespace AresInternal
{
	const std::vector<std::string> BuildEnumNames(const char* nameschar)
	{
		std::string names = nameschar;
		Ares::StringUtils::RemoveWhiteSpace(names);
		std::vector<std::string> result;
		Ares::StringUtils::SeperateString(names, ',', result);
		return result;
	}
}