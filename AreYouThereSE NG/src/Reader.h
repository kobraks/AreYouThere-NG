#pragma once
#include <fstream>
#include <string_view>

namespace BeinzPlugin {
	class Reader {
	public:
		using TESType = uint32_t;

		struct Field {
			TESType Type{};
			uint16_t DataSize{};
			uint8_t *Data = nullptr; //Not implemented
		};

		struct Record {
			TESType Type{};
			uint32_t DataSize{}, Flags{}, ID{};
			uint16_t TimeStamp{}, Revision{};
			uint16_t Version{}, Unknown{};
			uint8_t *Data = nullptr; //Not implemented
		};

		struct Group {
			TESType Type{};
			uint32_t GroupSize{}, Label{};
			int32_t GroupType{};
			uint16_t TimeStamp{}, Version{};
			uint32_t Unknown{};
			Record *Data = nullptr; //Not implemented
		};

		Reader(std::string_view fileName);
		~Reader();

		bool Read(Field &field, size_t offset);
		bool Read(Record &record, size_t offset);
		bool Read(Group &group, size_t offset);

		bool IsGood() const;
	private:
		template <typename T>
		auto& Get(T &result);


		std::ifstream m_Stream;
	};

	template <typename T>
	auto& Reader::Get(T &result) {
		return m_Stream.read(reinterpret_cast<char*>(&result), sizeof(T));
	}
}
