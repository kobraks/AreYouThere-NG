#include "pch.h"
#include "Pages/ActorBasePages.h"

#include "Mod.h"
#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	void ActorBasePages::Generate(std::shared_ptr<Mod> mod, uint32_t modIndex) {
		if(Pages.contains(modIndex)) {
			SPDLOG_DEBUG("Page already exits, returning cached version");
			return;
		}

		auto &pages = Pages[modIndex];
		if(mod) {
			const auto &actors = mod->GetActorBases();

			const auto count = HowManyPages(actors.size(), m_PageSize);

			if(count == 0) {
				pages.emplace_back(std::make_shared<ActorBasePage>(0, m_PageSize));
			}

			for(size_t i = 0; i < count; ++i) {
				pages.emplace_back(std::make_shared<ActorBasePage>(actors, i, m_PageSize));
			}

			SPDLOG_DEBUG("Generated {} Actor pages", pages.size());
			return;
		}

		pages.emplace_back(std::make_shared<ActorBasePage>(0, m_PageSize));
		SPDLOG_ERROR("Incorrect mod, generated {} NPC pages", 1);
	}

	ActorBasePages* ActorBasePages::GetInstance() {
		static ActorBasePages instance;

		return &instance;
	}

	ActorBasePages::ActorBasePages() : TypedPages<unsigned, BeinzPlugin::ActorBasePage>(PAGE_ACTORS) {
	}
}
