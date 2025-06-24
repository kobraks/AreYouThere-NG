#include "pch.h"
#include "Page/ActorPage.h"

#include "Actor.h"
#include "Utils.h"

namespace BeinzPlugin {
	RE::BSFixedString ActorPage::GenerateName() {
		SPDLOG_DEBUG("Creating Actor page for ID: {}", ID());

		const auto buffer = GenerateActorPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_TRACE("Creating Actor page {}", buffer.data());
		return m_Name = buffer.data();
	}

	RE::BSTArray<RE::Actor*> ActorPage::GetActors() const {
		return GetTESContainer<RE::BSTArray<RE::Actor*>>([](const std::shared_ptr<Actor>& actor) {
			return actor->Form<RE::Actor>();
			});
	}
}
