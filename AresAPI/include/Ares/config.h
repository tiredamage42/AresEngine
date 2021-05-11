#pragma once

#ifdef _ARESAPI_BUILD_DLL
#define _ARES_API __declspec(dllexport)
#else
#define _ARES_API __declspec(dllimport)
#endif
