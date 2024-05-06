#pragma once

namespace BeinzPlugin {
	class ActorBase {
	public:
		ActorBase(uint32_t id);

		uint32_t ID() const { return m_ID; }
		const std::string &ShortName() const { return m_ShortName; }
		const std::string &Name() const { return m_Name; }

		RE::TESForm* Form() { return m_Form; }
		const RE::TESForm *Form() const { return m_Form; }

		bool IsValid() const { return m_Form; }

		constexpr bool operator==(const ActorBase &other) const {
			return m_ID == other.m_ID;
		}

		template <typename T>
		std::add_pointer_t<std::remove_pointer_t<T>> Form() {
			return skyrim_cast<std::add_pointer_t<std::remove_pointer_t<T>>>(m_Form);
		}

		template <typename T>
		const std::add_pointer_t<std::remove_pointer_t<T>> Form() const {
			return skyrim_cast<const std::add_pointer_t<std::remove_pointer_t<T>>>(m_Form);
		}

		static RE::TESNPC *GetNpcForm(uint32_t baseID);
	protected:
		ActorBase(RE::TESNPC *form);

	private:
		RE::TESForm *m_Form;

		uint32_t m_ID;

		std::string m_Name;
		std::string m_ShortName;
	};

	class Actor : public ActorBase{
	public:
		Actor(uint32_t refID);

		bool IsValid() const { return m_Form; }

		constexpr bool operator==(const Actor &other) const {
			return other.m_ID == m_ID && other.BaseID() == BaseID();
		}

		uint32_t ID() const { return m_ID; }
		uint32_t BaseID() const { return ActorBase::ID(); }

		const RE::TESForm* BaseForm() const { return ActorBase::Form(); }
		RE::TESForm *BaseForm() { return ActorBase::Form(); }

		const RE::TESForm* Form() const { return m_Form; }
		RE::TESForm* Form() { return m_Form; }

		template<typename  T>
		std::add_pointer_t<std::remove_pointer_t<T>> Form() { return skyrim_cast<std::add_pointer_t<std::remove_pointer_t<T>>>(m_Form); }
		
		template<typename  T>
		const std::add_pointer_t<std::remove_pointer_t<T>> Form() const { return skyrim_cast<const std::add_pointer_t<std::remove_pointer_t<T>>>(m_Form); }

		template<typename  T>
		auto BaseForm() { return ActorBase::Form<T>(); }
		
		template<typename  T>
		const auto BaseForm() const { return ActorBase::Form<T>(); }

		static RE::TESObjectREFR* GetActorForm(uint32_t refID);
		static RE::TESNPC* GetActorBaseForm(uint32_t refId);
	private:
		uint32_t m_ID;
		RE::TESForm* m_Form;
	};

}