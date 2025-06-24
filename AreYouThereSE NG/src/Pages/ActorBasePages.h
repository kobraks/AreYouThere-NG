#pragma once
#include "Page/ActorBasePage.h"
#include "Pages/TypedPages.h"

namespace BeinzPlugin {
	class Mod;

	class ActorBasePages : public TypedPages<uint32_t, ActorBasePage> {
	public:
		void Generate(std::shared_ptr<Mod> mod, uint32_t modIndex);

		static ActorBasePages *GetInstance();
	protected:
		ActorBasePages();
	};
}