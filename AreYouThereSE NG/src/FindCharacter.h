#pragma once

namespace BeinzPlugin {
	class Mod;
	class Actor;

	struct ActorSearchResult {
		size_t ModIndex;
		std::shared_ptr<Mod> Mod;
		std::shared_ptr<Actor> Actor;
	};

	using ActorSearchResultTableT   = std::vector<ActorSearchResult>;
	using ActorSearchResultCacheT   = std::vector<ActorSearchResultTableT>;
	using ActorSearchResultResultsT = std::unordered_map<std::string, size_t>;

	class FindCharacter {
	public:
		size_t FindCharacters(const char *name);

		const ActorSearchResultCacheT& GetCache() const { return m_Cache; }
		ActorSearchResultCacheT& GetCache() { return m_Cache; }

		const ActorSearchResultTableT &GetSearchResult(size_t index) const;
		ActorSearchResultTableT &GetSearchResult(size_t index);

		static FindCharacter* GetInstance();
		static void Clear();

	private:
		static ActorSearchResultTableT Find(std::string_view name);

		static ActorSearchResultTableT m_Empty;
		ActorSearchResultCacheT m_Cache;
		ActorSearchResultResultsT m_Results;
	};
}
