#include "pch.h"
#include "Page/ActorBasePage.h"

#include "Actor.h"
#include "Utils.h"

namespace BeinzPlugin {
	RE::BSFixedString ActorBasePage::GenerateName() {
		SPDLOG_DEBUG("Creating NPC page for ID: {}", ID());

		const auto buffer = GenerateActorPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_TRACE("Creating NPC page {}", buffer.data());
		return m_Name = buffer.data();
	}

	RE::BSTArray<RE::TESNPC*> ActorBasePage::GetActors() const {
		return GetTESContainer<RE::BSTArray<RE::TESNPC*>>([](const std::shared_ptr<ActorBase> &actor) {
													   return actor->Form<RE::TESNPC>();
												   }
		);
	}
}
