#pragma once
#include "Page/TypedPage.h"

namespace BeinzPlugin {
	class Actor;

	class ActorPage: public TypedPage<Actor> {
	public:
		using TypedPage::TypedPage;

		~ActorPage() override = default;

		RE::BSFixedString GenerateName() override;

		RE::BSTArray<RE::Actor*> GetActors() const;
	};
}
