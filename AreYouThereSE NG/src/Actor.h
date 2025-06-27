#pragma once

namespace BeinzPlugin {
	struct FullName {
		std::string Name;
		std::string ShortName;

		FullName() = default;
		FullName(RE::TESNPC* form);
		FullName(const std::string &name, const std::string &shortName);

		FullName ToUpper() const;
	};

	class ActorBase {
	public:
		ActorBase(uint32_t id);

		uint32_t ID() const { return m_ID; }

		const std::string &ShortName() const { return m_Name.ShortName; }
		const std::string &Name() const { return m_Name.Name; }

		const FullName& GetFullName() const { return m_Name; }

		const std::string& UpperName() const { return m_UpperName.Name; }
		const std::string& UpperShortName() const { return m_UpperName.ShortName; }

		const FullName& GetUpperFullName() const { return m_UpperName; }

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
		RE::TESForm *m_BaseForm { nullptr };
		RE::TESNPC* m_NPCForm{ nullptr }; // Skyrims NPC Form, not the base form

		uint32_t m_ID = 0;

		FullName m_Name;
		FullName m_UpperName;
	};

	class Actor : public ActorBase{
	public:
		Actor(uint32_t refID);

		bool IsValid() const { return m_RefForm; }

		constexpr bool operator==(const Actor &other) const {
			return other.m_RefID == m_RefID && other.BaseID() == BaseID();
		}

		uint32_t ID() const { return m_RefID; }
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
		uint32_t m_RefID = 0;
		RE::TESForm* m_RefForm { nullptr };
		RE::Actor* m_Actor{ nullptr }; // Skyrims Actor Form, not the base form
	};

}