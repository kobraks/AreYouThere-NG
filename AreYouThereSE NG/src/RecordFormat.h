#pragma once

namespace BeinzPlugin {
	using TESType = uint32_t;

	enum class RecordType : TESType {
		TES4 = '4SET',
		GRUP = 'PURG',
		CELL = 'LLEC',
		WRLD = 'DLRW',
		NPC_ = '_CPN',
		ACHR = 'RHCA'
	};

	inline bool IsRecordType(TESType type, RecordType recordType) {
		return type == static_cast<TESType>(recordType);
	}

#pragma pack(push, 1)
	struct Field {
		TESType Type{};
		uint16_t DataSize{};
		uint8_t* Data = nullptr; //Not implemented
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Record {
		TESType Type{};
		uint32_t DataSize{}, Flags{}, ID{};
		uint16_t TimeStamp{}, Revision{};
		uint16_t Version{}, Unknown{};
		uint8_t* Data = nullptr; //Not implemented
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Group {
		TESType Type{};
		uint32_t GroupSize{}, Label{};
		int32_t GroupType{};
		uint16_t TimeStamp{}, Version{};
		uint32_t Unknown{};
		Record* Data = nullptr; //Not implemented
	};
#pragma pack(pop)

}