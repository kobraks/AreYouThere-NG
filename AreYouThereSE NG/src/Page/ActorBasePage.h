#pragma once
#include "Page/Page.h"

namespace BeinzPlugin {
	class ActorBase;

	class ActorBasePage: public Page {
	public:
		ActorBasePage(size_t page, size_t pageSize);
		ActorBasePage(const std::vector<std::shared_ptr<ActorBase>> &actors, size_t page, size_t pageSize);
		~ActorBasePage() override = default;

		RE::BSFixedString GenerateName() override;

		std::vector<std::shared_ptr<ActorBase>>& Actors() { return m_Actors; }
		const std::vector<std::shared_ptr<ActorBase>>& Actors() const { return m_Actors; }

		RE::BSTArray<RE::TESNPC*> GetActors() const;

	private:
		std::vector<std::shared_ptr<ActorBase>> m_Actors;
	};
}