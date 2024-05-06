#include "pch.h"
#include "Page/ActorPage.h"

#include "Actor.h"
#include "Utils.h"

namespace BeinzPlugin {
	ActorPage::ActorPage(size_t page, size_t pageSize) : Page(true, page, pageSize) {}

	ActorPage::ActorPage(
		const std::vector<std::shared_ptr<Actor>> &actors,
		size_t page,
		size_t pageSize
		) : Page(false, page, pageSize) {
		m_Actors = CopyPage(actors, page, pageSize);
	}

	RE::BSFixedString ActorPage::GenerateName() {
		SPDLOG_DEBUG("Creating Actor page for ID: {}", ID());

		const auto buffer = GenerateActorPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_TRACE("Creating Actor page {}", buffer.data());
		return m_Name = buffer.data();
	}

	RE::BSTArray<RE::Actor*> ActorPage::GetActors() const {
		return CopyPage<RE::BSTArray<RE::Actor*>>(
		                                          m_Actors,
		                                          MaxItems(),
		                                          [](const std::shared_ptr<Actor> &actor) {
			                                          return actor->Form<RE::Actor>();
		                                          }
		                                         );
	}
}
