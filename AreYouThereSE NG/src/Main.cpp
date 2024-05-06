#include "pch.h"

#include "Plugin.h"
#include "Papyrus.h"

#ifndef NDEBUG
#include <spdlog/sinks/msvc_sink.h>
#endif
#include <spdlog/sinks/basic_file_sink.h>

#include <SKSE/SKSE.h>

#include <vector>
#include <memory>
#include <spdlog/spdlog.h>

#define DLLEXPORT __declspec(dllexport)

namespace {
	void InitializeLog() {
		std::vector<spdlog::sink_ptr> sinks;
#ifndef NDEBUG
		const auto level = spdlog::level::trace;
		sinks.emplace_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
#else
		const auto level = spdlog::level::info;
#endif

		auto path = logger::log_directory();
		if (!path)
			util::report_and_fail("Failed to find standard logging directory");

		*path /= fmt::format("{}.log", BeinzPlugin::NAME);
		sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));

		auto log = std::make_shared<spdlog::logger>("global log", sinks.begin(), sinks.end());

		log->set_level(level);
		log->flush_on(level);

		spdlog::register_logger(log);
		spdlog::set_default_logger(log);
		spdlog::set_pattern("%s(%#): [%^%l%$] %!() %v");
	}

	extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
		SKSE::PluginVersionData v;

		v.PluginVersion(BeinzPlugin::VERSION);
		v.PluginName(BeinzPlugin::NAME);

		v.UsesSigScanning();
		v.UsesStructsPost629();
		v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST_SE });

		return v;
	}();

	extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface *skse) {
		InitializeLog();

		SPDLOG_INFO("Plugin {}:{} loaded", BeinzPlugin::NAME, BeinzPlugin::VERSION.string());
		SPDLOG_INFO("Game version: {}", skse->RuntimeVersion().string());

		if (skse->IsEditor()) {
			SPDLOG_ERROR("Editor is not supported !");

			return false;
		}

		SKSE::Init(skse);

		if (SKSE::GetPapyrusInterface() && SKSE::GetPapyrusInterface()->Register(BeinzPlugin::RegisterFuncs))
			return true;

		return false;
	}
}