#pragma once
#include "Page/ActorPage.h"
#include "Pages/TypedPages.h"

namespace BeinzPlugin {
	class Mod;

	class ActorPages : public TypedPages<uint32_t, ActorPage> {
	public:
		void Generate(std::shared_ptr<Mod> mod, uint32_t modIndex);

		static ActorPages *GetInstance();
	protected:
		ActorPages();
	};
}
