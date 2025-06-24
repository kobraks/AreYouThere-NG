#include "pch.h"
#include "Page/ModPage.h"

#include "Mod.h"
#include "Utils.h"

namespace BeinzPlugin {
	RE::BSFixedString ModPage::GenerateName() {
		SPDLOG_TRACE("Generating mod page for ID: ", ID());

		const auto buffer = GenerateModPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_DEBUG("Creating mod page: {}", buffer.data());
		return buffer.data();
	}

	RE::BSTArray<RE::BSFixedString> ModPage::GetNames() const {
		if(m_Items.empty()) {
			return GetEmptyNamesList();
		}

		return GetTESContainer<RE::BSTArray<RE::BSFixedString>>([](const std::shared_ptr<Mod>& mod) {
			return mod->CombinedName().data();
			});
	}

	RE::BSTArray<uint32_t> ModPage::GetActorCounts() const {
		if(m_Items.empty()) {
			return GetEmptyIndicesList();
		}

		return GetTESContainer<RE::BSTArray<uint32_t>>([](const std::shared_ptr<Mod>& mod) { return static_cast<uint32_t>(mod->ActorCount()); });
	}

	RE::BSTArray<uint32_t> ModPage::GetIndexes() const {
		if(m_Items.empty()) {
			return GetEmptyIndicesList();
		}

		return GetTESContainer<RE::BSTArray<uint32_t>>([](const std::shared_ptr<Mod>& mod) { return static_cast<uint32_t>(mod->ID()); });
	}

	RE::BSTArray<uint32_t> ModPage::GetNPCCounts() const {
		if(m_Items.empty()) {
			return GetEmptyIndicesList();
		}

		return GetTESContainer<RE::BSTArray<uint32_t>>([](const std::shared_ptr<Mod>& mod) { return static_cast<uint32_t>(mod->NPCCount()); });
	}
}
