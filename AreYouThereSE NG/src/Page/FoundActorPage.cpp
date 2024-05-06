#include "pch.h"
#include "Page/FoundActorPage.h"
#include "Utils.h"

namespace BeinzPlugin {
	FoundActorPage::FoundActorPage(size_t page, size_t pageSize, bool empty) : Page(empty, page, pageSize) {
		
	}

	RE::BSFixedString FoundActorPage::GenerateName() {
		SPDLOG_DEBUG("Creating NPC page for ID: {}", ID());

		const auto buffer = GenerateActorPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_TRACE("Creating NPC page {}", buffer.data());
		return m_Name = buffer.data();
	}
}
