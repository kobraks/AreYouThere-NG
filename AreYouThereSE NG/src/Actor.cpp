#include "pch.h"
#include "Actor.h"

#include <boost/algorithm/string.hpp>

namespace BeinzPlugin {
	FullName::FullName(RE::TESNPC* form) {
		if (form) {
			Name = !form->fullName.empty() ? form->fullName : "";
			ShortName = !form->shortName.empty() ? form->shortName : "";
		} else {
			Name = ShortName = "";
		}
	}

	FullName::FullName(const std::string& name, const std::string& shortName) : Name(name), ShortName(shortName) {
	}

	FullName FullName::ToUpper() const {
		return { boost::trim_copy(boost::to_upper_copy(Name)), boost::trim_copy(boost::to_upper_copy(ShortName)) };
	}

	ActorBase::ActorBase(uint32_t id) : ActorBase(GetNpcForm(id)) {
	}

	ActorBase::ActorBase(RE::TESNPC *form) {
		if (form) {
			m_BaseForm = skyrim_cast<RE::TESForm*>(form);
			m_NPCForm = form;

			m_ID = form->formID;

			m_Name = FullName(form);
			m_UpperName = m_Name.ToUpper();
		} else {
			m_ID = 0;
			m_BaseForm = nullptr;

			m_UpperName = m_Name = FullName("", "");
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
			m_RefForm = skyrim_cast<RE::TESForm*>(form);
			m_Actor = skyrim_cast<RE::Actor*>(form);
			m_RefID = refID;
		} else {
			m_RefID = 0;
			m_RefForm = nullptr;
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
