#include "pch.h"
#include "Mod.h"

#include "Actor.h"
#include "Reader.h"

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <array>

constexpr std::size_t RECORD_HEADER_SIZE = 0x18;

namespace {
	bool IsRootToCheck(uint32_t label) {
		constexpr static BeinzPlugin::RecordType s_RootCheck[] = {BeinzPlugin::RecordType::CELL, BeinzPlugin::RecordType::WRLD, BeinzPlugin::RecordType::NPC_};

		for (const auto &recordType : s_RootCheck) {
			if (BeinzPlugin::IsRecordType(label, recordType))
				return true;
		}

		return false;
	}

	bool IsTypeToCheck(BeinzPlugin::TESType type) {
		constexpr static BeinzPlugin::RecordType s_ToCheck[] = { BeinzPlugin::RecordType::CELL, BeinzPlugin::RecordType::WRLD, BeinzPlugin::RecordType::ACHR, BeinzPlugin::RecordType::NPC_};

		for(const auto recordType : s_ToCheck) {
			if(BeinzPlugin::IsRecordType(type, recordType))
				return true;
		}

		return false;
	}
}

namespace BeinzPlugin {
	Mod::Mod(const RE::TESFile &file) {
		std::array<char, sizeof(file.fileName) + sizeof(file.path) + 1> buffer;

		if(file.IsLight()) {
			m_ID = file.smallFileCompileIndex;

			auto [out, size] = fmt::format_to_n(
			                                    buffer.data(),
			                                    buffer.size(),
			                                    "[FE:{:03X}]{}",
			                                    static_cast<uint16_t>(m_ID),
			                                    file.fileName
			                                   );

			*out = '\0';

			m_CombinedName = buffer.data();
			m_IsLight      = true;
		}
		else {
			m_ID = file.compileIndex;

			auto [out, size] = fmt::format_to_n(
			                                    buffer.data(),
			                                    buffer.size(),
			                                    "[{:02X}]{}",
			                                    static_cast<uint8_t>(m_ID),
			                                    file.fileName
			                                   );

			*out = '\0';

			m_CombinedName = buffer.data();
			m_IsLight      = false;
		}

		m_Name = file.fileName;

		auto [out, size] = fmt::format_to_n(buffer.data(), buffer.size(), "{}{}", file.path, file.fileName);

		*out = '\0';

		ParseESP(buffer.data(), file);

		if(IsLight()) {
			SPDLOG_DEBUG(
			             "Mod: [FE:{:03X}] \"{}\" ActorCount: {}, NPCCount: {}",
			             ID(),
			             Name(),
			             ActorCount(),
			             NPCCount()
			            );
		}
		else {
			SPDLOG_DEBUG("Mod: [{:02X}] \"{}\" ActorCount: {}, NPCCount: {}", ID(), Name(), ActorCount(), NPCCount());
		}
	}

	uint32_t Mod::ModID() const {
		if(IsLight())
			return 0xFE000 + ID();
		return ID();
	}

	bool Mod::Contains(uint32_t id) const {
		if(IsWithin(id, m_ID, m_IsLight))
			return m_LookupTable.contains(id);

		return false;
	}

	const std::shared_ptr<Actor> Mod::GetActor(std::size_t index) const {
		if(index < m_Actors.size())
			return m_Actors[index];

		return nullptr;
	}

	const std::shared_ptr<ActorBase> Mod::GetActorBase(std::size_t index) const {
		if(index < m_ActorBases.size())
			return m_ActorBases[index];

		return nullptr;
	}

	std::shared_ptr<Actor> Mod::GetActor(std::size_t index) {
		if(index < m_Actors.size())
			return m_Actors[index];

		return nullptr;
	}

	std::shared_ptr<ActorBase> Mod::GetActorBase(std::size_t index) {
		if(index < m_ActorBases.size())
			return m_ActorBases[index];

		return nullptr;
	}

	void Mod::ParseESP(std::string_view fileName, const RE::TESFile &mod) {
		Reader reader(fileName);
		if(!reader.IsGood()) {
			SPDLOG_ERROR("Unable to parse: \"{}\"", fileName);
			return;
		}

		std::size_t offset = 0;
		if(Record record{}; reader.Read(record, offset)) {
			if(IsRecordType(record.Type, RecordType::TES4)) {
				offset = RECORD_HEADER_SIZE + record.DataSize;

				uint32_t groupSize = 0;
				do {
					groupSize = ProcessGroup(reader, offset, mod, true);
					offset += groupSize;
				}
				while(groupSize);
			}
		}
	}

	uint32_t Mod::ProcessGroup(Reader &reader, std::size_t offset, const RE::TESFile &mod, bool isRoot) {
		if(Group group{}; reader.Read(group, offset)) {
			if(!IsRecordType(group.Type, RecordType::GRUP))
				return 0;

			if(isRoot && !IsRootToCheck(group.Label))
				return group.GroupSize;

			return ProcessRecords(reader, group.GroupSize, offset, mod);
		}

		return 0;
	}

	uint32_t Mod::ProcessRecords(Reader &reader, uint32_t groupSize, std::size_t offset, const RE::TESFile &mod) {
		Record record{};
		uint32_t recordSize = 0;

		for(std::size_t groupOffset = RECORD_HEADER_SIZE; groupOffset < groupSize; groupOffset += (IsRecordType(record.Type, RecordType::GRUP)
			    ? record.DataSize
			    : recordSize)) {
			const std::size_t newOffset = offset + groupOffset;
			if(!reader.Read(record, newOffset))
				return 0;

			recordSize = RECORD_HEADER_SIZE + record.DataSize;

			if(!ProcessRecord(record.ID, record.Type, mod))
				ProcessGroup(reader, newOffset, mod);
		}

		return groupSize;
	}

	bool Mod::ProcessRecord(uint32_t id, int32_t type, const RE::TESFile &mod) {
		if (!IsRecordType(type, RecordType::GRUP) && IsTypeToCheck(type)) {
			switch(static_cast<RecordType>(type)) {
				case RecordType::ACHR: ProcessActor(id, mod); break;
				case RecordType::NPC_: ProcessActorBase(id, mod); break;
			default:
				break;
			}

			return true;
		}

		return false;
	}

	void Mod::ProcessActor(uint32_t id, const RE::TESFile &mod) {
		const auto newId = GetModIndex4MasterMod(id, mod);
		if (auto actor = std::make_shared<Actor>(newId); actor->IsValid()) {
			m_LookupTable.emplace(newId);
			m_Actors.emplace_back(actor);
			
		}
	}

	void Mod::ProcessActorBase(uint32_t id, const RE::TESFile &mod) {
		const auto newId = GetModIndex4MasterMod(id, mod, true);

		if (auto actor = std::make_shared<ActorBase>(newId); actor->IsValid()) {
			m_LookupTable.emplace(newId);
			m_ActorBases.emplace_back(actor);
		}
	}

	uint32_t Mod::GetModIndex4MasterMod(uint32_t srcId, const RE::TESFile &mod, bool npc) {
		auto *dataHandler = RE::TESDataHandler::GetSingleton();

		const uint32_t formID  = (srcId & 0xFFFFFF);
		const uint8_t modIdRef = (srcId & 0xFF000000) >> 24;

		if(mod.compileIndex == 0)
			return formID;

		if(modIdRef >= mod.masterCount)
			return GetModID(mod) + formID;

		for(auto master : dataHandler->files) {
			const auto refMod = mod.masterPtrs[modIdRef];

			const std::string_view masterName(master->fileName);
			const std::string_view refName(refMod->fileName);
			if(masterName == refName)
				return GetModID(mod) + formID;
		}

		return GetModID(0xFF) + formID;
	}

	bool Mod::IsWithin(uint32_t formID, uint32_t modID, bool isLight) {
		return GetFormModID(formID, isLight) == modID;
	}

	uint16_t Mod::GetFormModID(uint32_t formID, bool isLight) {
		if(isLight)
			return static_cast<uint16_t>(formID >> 12);
		return formID >> 24;
	}

	constexpr uint32_t Mod::GetModID(uint16_t id, bool isLight) {
		if(isLight)
			return (0xFE000 + id) << 12;
		return id << 24;
	}

	constexpr uint32_t Mod::GetModID(const RE::TESFile &file) {
		return file.IsLight() ? GetModID(file.smallFileCompileIndex, true) : GetModID(file.compileIndex);
	}
}
