#pragma once
#include "Page/FoundActorPage.h"
#include "Pages/TypedPages.h"

namespace BeinzPlugin {
	class FoundActorPages : public TypedPages<std::size_t, FoundActorPage> {
	public:
		std::unordered_map<size_t, std::vector<std::shared_ptr<FoundActorPage>>> Pages;

		void Generate(std::size_t searchIndex);
		// std::vector<std::shared_ptr<FoundActorPage>> &GetPages(size_t searchIndex);

		static FoundActorPages *GetInstance();
	private:
		FoundActorPages();
	};
}