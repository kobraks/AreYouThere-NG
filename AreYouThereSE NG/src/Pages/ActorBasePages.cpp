#include "pch.h"
#include "Pages/ActorBasePages.h"

#include "Mod.h"
#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	std::shared_ptr<ActorBasePage> ActorBasePages::GetPage(size_t page, uint32_t modID) {
		if(auto it = Pages.find(modID); it != Pages.end()) {
			const auto &vec = it->second;
			if(page < vec.size())
				return vec[page];
		}

		return nullptr;
	}

	void ActorBasePages::Generate(std::shared_ptr<Mod> mod, uint32_t modIndex) {
		if(Pages.contains(modIndex)) {
			SPDLOG_DEBUG("Page already exits returing cached");
			return;
		}

		auto &pages = Pages[modIndex];
		if(mod) {
			const auto &actors = mod->GetActorBases();

			const auto count = HowManyPages(actors.size(), PAGE_ACTORS);

			if(count == 0) {
				pages.emplace_back(std::make_shared<ActorBasePage>(0, PAGE_ACTORS));
			}

			for(size_t i = 0; i < count; ++i) {
				pages.emplace_back(std::make_shared<ActorBasePage>(actors, i, PAGE_ACTORS));
			}

			SPDLOG_DEBUG("Generated {} Actor pages", pages.size());
			return;
		}

		pages.emplace_back(std::make_shared<ActorBasePage>(0, PAGE_ACTORS));
		SPDLOG_ERROR("Incorrect mod, generated {} NPC pages", 1);
	}

	RE::BSTArray<RE::BSFixedString> ActorBasePages::GetNames(uint32_t modIndex) {
		if(auto it = Pages.find(modIndex); it != Pages.end()) {
			const auto &pages = it->second;

			return CopyPage<RE::BSTArray<RE::BSFixedString>>(
			                                                pages,
			                                                PAGE_ACTORS,
			                                                [](const auto &page) { return page->GenerateName(); }
			                                               );
		}

		RE::BSTArray<RE::BSFixedString> empty;
		empty.emplace_back("Empty");
		return empty;
	}

	ActorBasePages* ActorBasePages::GetInstance() {
		static ActorBasePages instance;

		return &instance;
	}

	void ActorBasePages::Clear() {
		GetInstance()->Pages.clear();
	}
}
