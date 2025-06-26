#pragma once

namespace BeinzPlugin {
	class ActorBase {
	public:
		ActorBase(uint32_t id);

		uint32_t ID() const { return m_ID; }
		const std::string &ShortName() const { return m_ShortName; }
		const std::string &Name() const { return m_Name; }

		RE::TESForm* Form() { return m_BaseForm; }
		const RE::TESForm *Form() const { return m_BaseForm; }

		RE::TESNPC* GetNpcForm() { return m_NPCForm; }
		const RE::TESNPC* GetNpcForm() const { return m_NPCForm; }

		bool IsValid() const { return m_BaseForm; }

		constexpr bool operator==(const ActorBase &other) const {
			return m_ID == other.m_ID;
		}

		template <typename T>
		std::add_pointer_t<std::remove_pointer_t<T>> Form() {
			return skyrim_cast<std::add_pointer_t<std::remove_pointer_t<T>>>(m_BaseForm);
		}

		template <typename T>
		const std::add_pointer_t<std::remove_pointer_t<T>> Form() const {
			return skyrim_cast<const std::add_pointer_t<std::remove_pointer_t<T>>>(m_BaseForm);
		}

		static RE::TESNPC *GetNpcForm(uint32_t baseID);
	protected:
		ActorBase(RE::TESNPC *form);

	private:
		RE::TESForm *m_BaseForm;
		RE::TESNPC* m_NPCForm{ nullptr }; // Skyrims NPC Form, not the base form

		uint32_t m_ID;

		std::string m_Name;
		std::string m_ShortName;
	};

	class Actor : public ActorBase{
	public:
		Actor(uint32_t refID);

		bool IsValid() const { return m_RefForm; }

		constexpr bool operator==(const Actor &other) const {
			return other.m_ID == m_ID && other.BaseID() == BaseID();
		}

		uint32_t ID() const { return m_ID; }
		uint32_t BaseID() const { return ActorBase::ID(); }

		const RE::TESForm* GetBaseForm() const { return ActorBase::Form(); }
		RE::TESForm *GetBaseForm() { return ActorBase::Form(); }

		const RE::TESForm* GetRefForm() const { return m_RefForm; }
		RE::TESForm* GetRefForm() { return m_RefForm; }

		template<typename  T>
		std::add_pointer_t<std::remove_pointer_t<T>> GetRefForm() { return skyrim_cast<std::add_pointer_t<std::remove_pointer_t<T>>>(m_RefForm); }
		
		template<typename  T>
		const std::add_pointer_t<std::remove_pointer_t<T>> GetRefForm() const { return skyrim_cast<const std::add_pointer_t<std::remove_pointer_t<T>>>(m_RefForm); }

		RE::Actor* GetActor() { return m_Actor; }
		const RE::Actor* GetActor() const { return m_Actor; }

		template<typename  T>
		auto GetBaseForm() { return ActorBase::Form<T>(); }
		
		template<typename  T>
		const auto GetBaseForm() const { return ActorBase::Form<T>(); }

		static RE::TESObjectREFR* GetActorForm(uint32_t refID);
		static RE::TESNPC* GetActorBaseForm(uint32_t refId);
	private:
		uint32_t m_ID;
		RE::TESForm* m_RefForm;
		RE::Actor* m_Actor{ nullptr }; // Skyrims Actor Form, not the base form
	};

}