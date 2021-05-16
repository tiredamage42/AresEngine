#pragma once
#include "config.h"
#include <vector>
#include <string>

namespace AresInternal
{
    _ARES_API const std::vector<std::string> BuildEnumNames(const char* nameschar);
}

/*
	declare an enum so that we can also get the string version of the names
*/
#define ARES_ENUM(name, ...) \
	enum class name : unsigned char { __VA_ARGS__ }; \
	static const std::vector<std::string> name##AsStrings = AresInternal::BuildEnumNames(#__VA_ARGS__);

#define ARES_ENUM_TO_STRING(name, enum_value) name##AsStrings[static_cast<unsigned char>(name::enum_value)]