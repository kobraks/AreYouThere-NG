#pragma once
#include "Page/Page.h"

namespace BeinzPlugin {
	class FoundActorPage : public Page {
	public:
		FoundActorPage(std::size_t page, std::size_t pageSize, bool empty = false);

		~FoundActorPage() override = default;
		RE::BSFixedString GenerateName() override;
	};
}