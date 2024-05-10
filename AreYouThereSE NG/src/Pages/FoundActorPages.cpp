#include "pch.h"
#include "Pages/FoundActorPages.h"

#include <boost/algorithm/string.hpp>

#include "FindCharacter.h"
#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	void FoundActorPages::Generate(size_t searchIndex) {
		if(Pages.contains(searchIndex)) {
			SPDLOG_DEBUG("Page already exist returning cache");
			return;
		}

		auto &pages  = Pages[searchIndex];
		auto &result = FindCharacter::GetInstance()->GetSearchResult(searchIndex);

		const auto count = HowManyPages(result.size(), PAGE_ACTORS);

		if(count == 0) {
			pages.emplace_back(std::make_shared<FoundActorPage>(0, PAGE_ACTORS, true));
		}

		for(size_t i = 0; i < count; ++i) {
			pages.emplace_back(std::make_shared<FoundActorPage>(i, PAGE_ACTORS, false));
		}

		SPDLOG_DEBUG("Generated {} found actor pages", pages.size());
	}

	std::vector<std::shared_ptr<FoundActorPage>>& FoundActorPages::GetPages(size_t searchIndex) {
		if(auto it = Pages.find(searchIndex); it != Pages.end()) {
			return it->second;
		}
		Generate(searchIndex);

		return Pages[searchIndex];
	}

	RE::BSTArray<RE::BSFixedString> FoundActorPages::GetNames(size_t searchIndex) {
		if(auto &page = GetPages(searchIndex); !page.empty()) {
			return CopyPage<RE::BSTArray<RE::BSFixedString>>(
			                                                 page,
			                                                 PAGE_ACTORS,
			                                                 [](const auto &page) { return page->GenerateName(); }
			                                                );
		}

		RE::BSTArray<RE::BSFixedString> empty;
		empty.emplace_back("Empty");
		return empty;
	}

	FoundActorPages* FoundActorPages::GetInstance() {
		static FoundActorPages instance;

		return &instance;
	}

	void FoundActorPages::Clear() {
		GetInstance()->Pages.clear();
	}
}
