#include "pch.h"
#include "Pages/FoundActorPages.h"

#include "FindCharacter.h"
#include "Plugin.h"
#include "Utils.h"

#include <boost/algorithm/string.hpp>

namespace BeinzPlugin {
	void FoundActorPages::Generate(size_t searchIndex) {
		if(Pages.contains(searchIndex)) {
			SPDLOG_DEBUG("Page already exits, returning cached version");
			return;
		}

		auto &pages  = Pages[searchIndex];
		const auto &result = FindCharacter::GetInstance()->GetSearchResult(searchIndex);

		const auto count = HowManyPages(result.size(), m_PageSize);

		if(count == 0) {
			pages.emplace_back(std::make_shared<FoundActorPage>(0, m_PageSize, true));
		}

		for(size_t i = 0; i < count; ++i) {
			pages.emplace_back(std::make_shared<FoundActorPage>(i, m_PageSize, false));
		}

		SPDLOG_DEBUG("Generated {} found actor pages", pages.size());
	}

	// std::vector<std::shared_ptr<FoundActorPage>>& FoundActorPages::GetPages(size_t searchIndex) {
		// if(auto it = Pages.find(searchIndex); it != Pages.end()) {
			// return it->second;
		// }
		// Generate(searchIndex);

		// return Pages[searchIndex];
	// }

	FoundActorPages* FoundActorPages::GetInstance() {
		static FoundActorPages instance;

		return &instance;
	}

	FoundActorPages::FoundActorPages() : TypedPages<unsigned long long, BeinzPlugin::FoundActorPage>(PAGE_ACTORS) {

	}
}
