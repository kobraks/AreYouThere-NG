#include "pch.h"
#include "Page/ModPage.h"

#include "Mod.h"
#include "Utils.h"

namespace BeinzPlugin {
	ModPage::ModPage() : ModPage(0, 0) {}

	ModPage::ModPage(size_t page, size_t pageSize) : Page(true, page, pageSize) {}

	ModPage::ModPage(
		const std::vector<std::shared_ptr<Mod>> &mods,
		size_t page,
		size_t pageSize
		) : Page(false, page, pageSize) {
		m_Mods = CopyPage(mods, page, pageSize);
		Empty(m_Mods.empty());
	}

	RE::BSFixedString ModPage::GenerateName() {
		SPDLOG_TRACE("Generating mod page for ID: ", ID());

		const auto buffer = GenerateModPageName(IsEmpty(), ID(), MaxItems());

		SPDLOG_DEBUG("Creating mod page: {}", buffer.data());
		return buffer.data();
	}

	RE::BSTArray<RE::BSFixedString> ModPage::GetNames() const {
		if(m_Mods.empty()) {
			RE::BSTArray<RE::BSFixedString> result;
			result.emplace_back("Empty");
			return result;
		}

		return CopyPage<RE::BSTArray<RE::BSFixedString>>(
		                                                 m_Mods,
		                                                 MaxItems(),
		                                                 [](const std::shared_ptr<Mod> &mod) {
			                                                 return mod->CombinedName().data();
		                                                 }
		                                                );
	}

	RE::BSTArray<uint32_t> ModPage::GetActorCounts() const {
		if(m_Mods.empty()) {
			RE::BSTArray<uint32_t> result;
			result.emplace_back(0);
			return result;
		}
		return CopyPage<RE::BSTArray<uint32_t>>(
		                                        m_Mods,
		                                        MaxItems(),
		                                        [](const std::shared_ptr<Mod> &mod) { return mod->ActorCount(); }
		                                       );
	}

	RE::BSTArray<uint32_t> ModPage::GetIndexes() const {
		if(m_Mods.empty()) {
			RE::BSTArray<uint32_t> result;
			result.emplace_back(0);
			return result;
		}
		return CopyPage<RE::BSTArray<uint32_t>>(
		                                        m_Mods,
		                                        MaxItems(),
		                                        [](const std::shared_ptr<Mod> &mod) { return mod->ID(); }
		                                       );
	}

	RE::BSTArray<uint32_t> ModPage::GetNPCCounts() const {
		if(m_Mods.empty()) {
			RE::BSTArray<uint32_t> result;
			result.emplace_back(0);
			return result;
		}
		return CopyPage<RE::BSTArray<uint32_t>>(
		                                        m_Mods,
		                                        MaxItems(),
		                                        [](const std::shared_ptr<Mod> &mod) { return mod->NPCCount(); }
		                                       );
	}
}
