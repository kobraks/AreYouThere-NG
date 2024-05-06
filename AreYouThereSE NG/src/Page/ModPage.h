#pragma once
#include "Page/Page.h"

namespace BeinzPlugin {
	class Mod;

	class ModPage : Page {
	public:
		ModPage();
		ModPage(size_t page, size_t pageSize);
		ModPage(const std::vector<std::shared_ptr<Mod>> &mods, size_t page, size_t pageSize);

		~ModPage() override = default;

		RE::BSFixedString GenerateName() override;

		std::vector<std::shared_ptr<Mod>>  &Mods() { return m_Mods; }
		const std::vector<std::shared_ptr<Mod>> &Mods() const { return m_Mods; }

		RE::BSTArray<RE::BSFixedString> GetNames() const;
		RE::BSTArray<uint32_t> GetActorCounts() const;
		RE::BSTArray<uint32_t> GetNPCCounts() const;
		RE::BSTArray<uint32_t> GetIndexes() const;

	private:
		std::vector<std::shared_ptr<Mod>> m_Mods;
	};
}