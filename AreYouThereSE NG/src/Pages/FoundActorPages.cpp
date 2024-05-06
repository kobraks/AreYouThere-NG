#include "pch.h"
#include "Pages/FoundActorPages.h"

#include <boost/algorithm/string.hpp>

#include "FindCharacter.h"
#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	void FoundActorPages::Generate(const char *name) {
		auto sName = Prepare(name);
		if (Pages.contains(sName)) {
			SPDLOG_DEBUG("Page already exist returning cache");
			return;
		}

		auto &pages = Pages[sName];
		auto &result = FindCharacter::GetInstance()->FindCharacters(name);
		const auto count = HowManyPages(result.size(), PAGE_ACTORS);

		if (count == 0) {
			pages.emplace_back(std::make_shared<FoundActorPage>(0, PAGE_ACTORS, true));
		}

		for (size_t i = 0; i < result.size(); ++i) {
			pages.emplace_back(std::make_shared<FoundActorPage>(i, PAGE_ACTORS));
		}

		SPDLOG_DEBUG("Generated {} found actor pages", pages.size());
	}

	std::vector<std::shared_ptr<FoundActorPage>> &FoundActorPages::GetPages(const char *name) {
		if (auto it = Pages.find(Prepare(name)); it != Pages.end()) {
			return it->second;
		} else {
			Generate(name);
		}

		return Pages[Prepare(name)];
		
	}

	RE::BSTArray<RE::BSFixedString> FoundActorPages::GetNames(const char *name) {
		if(auto it = Pages.find(Prepare(name)); it != Pages.end()) {
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

	FoundActorPages* FoundActorPages::GetInstance() {
		static FoundActorPages instance;

		return &instance;
	}

	void FoundActorPages::Clear() {
		GetInstance()->Pages.clear();
	}

	std::string FoundActorPages::Prepare(const char *name) {
		std::string string = name;
		boost::trim(string);
		boost::to_upper(string);
		return string;
	}
}
