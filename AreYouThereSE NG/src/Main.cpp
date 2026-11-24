#include "pch.h"

#include "Plugin.h"
#include "PapyrusRegistration.h"

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
		log->flush_on(spdlog::level::err);

		spdlog::register_logger(log);
		spdlog::set_default_logger(log);
		spdlog::set_pattern("%s(%#): [%^%l%$] %!() %v");
	}

	void OnSKSEMessage(SKSE::MessagingInterface::Message* message) {
		switch (message->type) {
		case SKSE::MessagingInterface::kPreLoadGame:
		case SKSE::MessagingInterface::kNewGame:
			BeinzPlugin::Plugin::GetInstance()->Clear();
			SPDLOG_INFO("Cleared mod index and search cache for game transition");
			break;
		default:
			break;
		}
	}

	extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
		SKSE::PluginVersionData v;

		v.PluginVersion(BeinzPlugin::VERSION);
		v.PluginName(BeinzPlugin::NAME);

		v.UsesSigScanning();
		v.UsesStructsPost629();
		v.CompatibleVersions({ SKSE::RUNTIME_SSE_LATEST_AE });

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

		const auto* messaging = SKSE::GetMessagingInterface();
		if (!messaging || !messaging->RegisterListener(OnSKSEMessage)) {
			SPDLOG_ERROR("Failed to register SKSE messaging listener");
			return false;
		}

		if (SKSE::GetPapyrusInterface() && SKSE::GetPapyrusInterface()->Register(BeinzPlugin::PapyrusRegistration::Register))
			return true;

		return false;
	}
}