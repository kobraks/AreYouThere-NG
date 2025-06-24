#include "pch.h"
#include "Pages/ActorPages.h"

#include "Mod.h"
#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	void ActorPages::Generate(std::shared_ptr<Mod> mod, uint32_t modIndex) {
		if (Pages.contains(modIndex)) {
			SPDLOG_DEBUG("Page already exits returing cached");
			return;
		}

		auto &pages = Pages[modIndex];

		if(mod) {
			const auto &actors = mod->GetActors();

			const auto count = HowManyPages(actors.size(), m_PageSize);
			if(count == 0) {
				pages.emplace_back(std::make_shared<ActorPage>(0, m_PageSize));
			}

			for(size_t i = 0; i < count; ++i) {
				pages.emplace_back(std::make_shared<ActorPage>(actors, i, m_PageSize));
			}

			SPDLOG_DEBUG("Generated {} Actor pages", pages.size());
			return;
		}

		pages.emplace_back(std::make_shared<ActorPage>(0, m_PageSize));
		SPDLOG_ERROR("Incorrect mod, generated {} Actor pages", 1);
	}

	ActorPages* ActorPages::GetInstance() {
		static ActorPages instance;

		return &instance;
	}

	ActorPages::ActorPages() : TypedPages<unsigned, BeinzPlugin::ActorPage>(PAGE_ACTORS){
	}
}
