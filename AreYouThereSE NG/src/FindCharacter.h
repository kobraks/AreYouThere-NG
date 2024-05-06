#pragma once

namespace BeinzPlugin {
	class Mod;
	class Actor;

	struct ActorSearchResult {
		size_t ModIndex;
		std::shared_ptr<Mod> Mod;
		std::shared_ptr<Actor> Actor;
	};

	using ActorSearchResultTableT = std::vector<ActorSearchResult>;
	using ActorSearchResultCacheT = std::unordered_map<std::string, ActorSearchResultTableT>;

	class FindCharacter {
	public:
		ActorSearchResultTableT &FindCharacters(const char *name);

		const ActorSearchResultCacheT &GetCache() const { return m_Cache; }
		ActorSearchResultCacheT &GetCache() { return m_Cache; }

		static FindCharacter *GetInstance();
		static void Clear();

	private:
		static ActorSearchResultTableT Find(const std::string_view name);

		ActorSearchResultCacheT m_Cache;
	};
}