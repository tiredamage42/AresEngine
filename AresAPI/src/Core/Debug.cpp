#include "Ares/Core/Debug.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>

namespace Ares
{
	std::shared_ptr<spdlog::logger> Debug::s_Logger = nullptr;
}

namespace AresInternal
{
	std::shared_ptr<spdlog::logger> Debug::s_Logger = nullptr;

	static constexpr const char* k_LogFileName = "Ares.log";

	static std::shared_ptr<spdlog::logger> CreateLogger(const char* name, const std::vector<spdlog::sink_ptr>& logSinks)
	{
		std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>(name, begin(logSinks), end(logSinks));
		spdlog::register_logger(logger);
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		return logger;
	}
	
	void Debugging::Initialize()
	{
		std::vector<spdlog::sink_ptr> logSinks;

		// only log to console in debug builds
#ifdef ARES_DEBUG
		logSinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
		// logs :: [time] [name]: message
		logSinks.back()->set_pattern("%^[%T] [%n]: %v%$"); 
#endif

		// delete current log file
		std::error_code err;
		std::filesystem::remove(k_LogFileName, err);

		// set up logging to file
		logSinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(k_LogFileName, true));
		// files :: [time] [level] [name]: message
		logSinks.back()->set_pattern("[%T] [%l] [%n]: %v"); 

		AresInternal::Debug::s_Logger = CreateLogger("ARES", logSinks);
		Ares::Debug::s_Logger = CreateLogger("CLIENT", logSinks);
	}
}
