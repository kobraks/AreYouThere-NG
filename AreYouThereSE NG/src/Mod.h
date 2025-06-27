#pragma once

#include "Actor.h"
#include "Reader.h"

#include <cstdint>
#include <string_view>

#include <unordered_set>
#include <vector>

namespace BeinzPlugin {
	class Mod {
	public:
		explicit Mod(const RE::TESFile &file);

		uint32_t ID() const { return m_ID; }
		uint32_t ModID() const;

		std::string_view Name() const { return m_Name; }
		std::string_view CombinedName() const { return m_CombinedName; }

		bool IsLight() const { return m_IsLight; }
		bool Contains(uint32_t id) const;

		std::size_t ActorCount() const { return m_Actors.size(); }
		std::size_t NPCCount() const { return m_ActorBases.size(); }

		const std::shared_ptr<Actor> GetActor(std::size_t index) const;
		const std::shared_ptr<ActorBase> GetActorBase(std::size_t index) const;

		std::shared_ptr<Actor> GetActor(std::size_t index);
		std::shared_ptr<ActorBase> GetActorBase(std::size_t index);

		const std::vector<std::shared_ptr<Actor>>& GetActors() const { return m_Actors; }
		const std::vector<std::shared_ptr<ActorBase>>& GetActorBases() const { return m_ActorBases; }

		constexpr bool operator==(const Mod &other) const {
			return m_ID == other.m_ID;
		}

	private:
		void ParseESP(std::string_view fileName, const RE::TESFile &mod);
		uint32_t ProcessGroup(Reader &reader, std::size_t offset, const RE::TESFile &mod, bool isRoot = false);
		uint32_t ProcessRecords(Reader &reader, uint32_t groupSize, std::size_t offset, const RE::TESFile &mod);
		bool ProcessRecord(uint32_t id, int32_t type, const RE::TESFile &mod);

		void ProcessActor(uint32_t id, const RE::TESFile &mod);
		void ProcessActorBase(uint32_t id, const RE::TESFile &mod);

		static uint32_t GetModIndex4MasterMod(uint32_t srcId, const RE::TESFile &mod, bool npc = false);

		static bool IsWithin(uint32_t formID, uint32_t modID, bool isLight = false);
		static uint16_t GetFormModID(uint32_t formID, bool isLight = false);

		static constexpr uint32_t GetModID(uint16_t id, bool isLight = false);
		static constexpr uint32_t GetModID(const RE::TESFile &file);

		uint32_t m_ID{};

		bool m_IsLight = false;

		std::string m_Name;
		std::string m_CombinedName;

		std::unordered_set<uint32_t> m_LookupTable;

		std::vector<std::shared_ptr<Actor>> m_Actors;
		std::vector<std::shared_ptr<ActorBase>> m_ActorBases;
	};
}
