#include "Ares/Utils/StringUtils.h"
#include <sstream>


namespace Ares
{
	void StringUtils::RemoveWhiteSpace(std::string& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
	}

	void StringUtils::SeperateString(const std::string& str, const char delim, std::vector<std::string>& result)
	{
		std::stringstream ss(str);
		while (ss.good())
		{
			std::string substr;
			getline(ss, substr, delim);
			result.push_back(substr);
		}
	}
}