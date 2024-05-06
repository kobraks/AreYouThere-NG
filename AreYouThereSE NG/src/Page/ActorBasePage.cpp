#include "pch.h"
#include "Page/ActorBasePage.h"

#include "Actor.h"
#include "Utils.h"

namespace BeinzPlugin {
	ActorBasePage::ActorBasePage(size_t page, size_t pageSize) : Page(true, page, pageSize) {}

	ActorBasePage::ActorBasePage(
		const std::vector<std::shared_ptr<ActorBase>> &actors,
		size_t page,
		size_t pageSize
		) : Page(false, page, pageSize) {
		m_Actors = CopyPage(actors, page, pageSize);
	}

	RE::BSFixedString ActorBasePage::GenerateName() {
		SPDLOG_DEBUG("Creating NPC page for ID: {}", ID());

		const auto buffer = GenerateActorPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_TRACE("Creating NPC page {}", buffer.data());
		return m_Name = buffer.data();
	}

	RE::BSTArray<RE::TESNPC*> ActorBasePage::GetActors() const {
		return CopyPage<RE::BSTArray<RE::TESNPC*>>(
		                                           m_Actors,
		                                           MaxItems(),
		                                           [](const std::shared_ptr<ActorBase> &actor) {
			                                           return actor->Form<RE::TESNPC>();
		                                           }
		                                          );
	}
}
