#pragma once
#include "Page/Page.h"

namespace BeinzPlugin {
	class FoundActorPage : public Page {
	public:
		FoundActorPage(size_t page, size_t pageSize, bool empty = false);

		~FoundActorPage() override = default;
		RE::BSFixedString GenerateName() override;
	};
}