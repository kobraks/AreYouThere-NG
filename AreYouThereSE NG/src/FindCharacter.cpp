#include "pch.h"
#include "FindCharacter.h"

#include "Plugin.h"
#include "Mod.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>

namespace BeinzPlugin {
	ActorSearchResultTableT FindCharacter::m_Empty{};

	size_t FindCharacter::FindCharacters(const char *name) {
		std::string sName = name;
		boost::trim(sName);
		boost::to_upper(sName);

		SPDLOG_INFO("Looking for: {}", sName);

		if (const auto it = m_Results.find(sName); it != m_Results.end()) {
			SPDLOG_INFO("Returing cached search result: {}", it->second);
			return it->second;
		}

		m_Cache.emplace_back(Find(sName));

		return m_Results.emplace(sName, m_Results.size() - 1).first->second;
	}

	const ActorSearchResultTableT & FindCharacter::GetSearchResult(size_t index) const {
		if (index < m_Cache.size()) {
			return m_Cache.at(index);
		}

		SPDLOG_ERROR("Provided invalid search result pointer: {}", index);

		return m_Empty;
	}

	ActorSearchResultTableT & FindCharacter::GetSearchResult(size_t index) {
		if (index < m_Cache.size())
			return m_Cache.at(index);

		SPDLOG_ERROR("Provided invalid search result pointer: {}", index);

		return m_Empty;
	}

	FindCharacter * FindCharacter::GetInstance() {
		static FindCharacter instance;

		return &instance;
	}

	void FindCharacter::Clear() {
		GetInstance()->m_Cache.clear();
		GetInstance()->m_Results.clear();
	}

	ActorSearchResultTableT FindCharacter::Find(const std::string_view name) {
		ActorSearchResultTableT table;

		size_t i = 0;
		for (const auto &mod : Plugin::GetInstance()->Mods) {
			for (const auto &actor : mod->GetActors()) {
				std::string actorName = actor->Name();
				boost::trim(actorName);
				boost::to_upper(actorName);
				if (actorName.find(name) != std::string::npos)
					table.emplace_back(i, mod, actor);
			}

			++i;
		}

		return table;
	}
}
