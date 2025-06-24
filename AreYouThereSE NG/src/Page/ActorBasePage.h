#pragma once
#include "Page/TypedPage.h"

namespace BeinzPlugin {
	class ActorBase;

	class ActorBasePage: public TypedPage<ActorBase> {
	public:
		using TypedPage::TypedPage;

		~ActorBasePage() override = default;

		RE::BSFixedString GenerateName() override;

		RE::BSTArray<RE::TESNPC*> GetActors() const;
	};
}