#include "pch.h"
#include "FindCharacter.h"

#include "Plugin.h"
#include "Mod.h"

#include <boost/algorithm/string.hpp>

namespace BeinzPlugin {
	ActorSearchResultTableT &FindCharacter::FindCharacters(const char *name) {
		std::string sName = name;

		boost::trim(sName);
		boost::to_upper(sName);

		SPDLOG_INFO("Looking for: {}", sName);

		if (const auto it = m_Cache.find(sName); it != m_Cache.end()) {
			SPDLOG_INFO("Returing cached search results: {}", it->second.size());
			return it->second;
		}

		return m_Cache.emplace(sName, Find(sName)).first->second;
	}

	FindCharacter * FindCharacter::GetInstance() {
		static FindCharacter instance;

		return &instance;
	}

	void FindCharacter::Clear() {
		GetInstance()->m_Cache.clear();
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
