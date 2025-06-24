#pragma once
#include "Page/TypedPage.h"

namespace BeinzPlugin {
	class Mod;

	class ModPage : TypedPage<Mod> {
	public:
		using TypedPage::TypedPage;

		~ModPage() override = default;

		RE::BSFixedString GenerateName() override;

		RE::BSTArray<RE::BSFixedString> GetNames() const;
		RE::BSTArray<uint32_t> GetActorCounts() const;
		RE::BSTArray<uint32_t> GetNPCCounts() const;
		RE::BSTArray<uint32_t> GetIndexes() const;
	};
}