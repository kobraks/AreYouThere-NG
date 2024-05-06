#include "pch.h"
#include "Actor.h"

namespace BeinzPlugin {
	ActorBase::ActorBase(uint32_t id) : ActorBase(GetNpcForm(id)) {
	}

	ActorBase::ActorBase(RE::TESNPC *form) {
		if (form) {
			m_Form = skyrim_cast<RE::TESForm*>(form);
			m_ID = form->formID;

			m_Name = form->fullName.c_str() ? form->fullName.c_str() : "";
			m_ShortName = form->shortName.c_str() ? form->shortName.c_str() : "";
		} else {
			m_ID = 0;
			m_Form = nullptr;

			m_Name = m_ShortName = "";
		}
	}

	RE::TESNPC * ActorBase::GetNpcForm(uint32_t baseID) {
		if (auto form = RE::TESForm::LookupByID(baseID); form && form->formType == RE::FormType::NPC)
			if (auto npc = skyrim_cast<RE::TESNPC*>(form); npc)
				return npc;

		return nullptr;
	}

	Actor::Actor(uint32_t refID) : ActorBase(GetActorBaseForm(refID)) {
		if (const auto form = GetActorForm(refID)) {
			m_Form = skyrim_cast<RE::TESForm*>(form);
			m_ID = refID;
		} else {
			m_ID = 0;
			m_Form = nullptr;
		}
	}

	RE::TESObjectREFR * Actor::GetActorForm(uint32_t refID) {
		if (auto actor = skyrim_cast<RE::TESObjectREFR*>(RE::TESForm::LookupByID(refID)); actor && actor->formType == RE::FormType::ActorCharacter)
			return actor;

		return nullptr;
	}

	RE::TESNPC * Actor::GetActorBaseForm(uint32_t refId) {
		if (auto actor = GetActorForm(refId); actor) {
			if (auto form = skyrim_cast<RE::TESForm*>(actor->GetBaseObject()); form && form->formType == RE::FormType::NPC) {
				if (auto npc = skyrim_cast<RE::TESNPC*>(form))
					return npc;
			}
		}

		return nullptr;
	}
}
