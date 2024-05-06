#pragma once
#include "Page/Page.h"

namespace BeinzPlugin {
	class Actor;

	class ActorPage: public Page {
	public:
		ActorPage(size_t page, size_t pageSize);
		ActorPage(const std::vector<std::shared_ptr<Actor>> &actors, size_t page, size_t pageSize);
		~ActorPage() override = default;

		RE::BSFixedString GenerateName() override;

		std::vector<std::shared_ptr<Actor>>& Actors() { return m_Actors; }
		const std::vector<std::shared_ptr<Actor>>& Actors() const { return m_Actors; }

		RE::BSTArray<RE::Actor*> GetActors() const;

	private:
		std::vector<std::shared_ptr<Actor>> m_Actors;
	};
}
