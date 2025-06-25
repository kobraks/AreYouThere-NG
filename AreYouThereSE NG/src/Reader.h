#pragma once
#include "RecordFormat.h"

#include <fstream>
#include <string_view>

namespace BeinzPlugin {
	class Reader {
	public:
		Reader(std::string_view fileName);
		~Reader();

		Reader(const Reader&) = delete;
		Reader(Reader&&) noexcept = default;

		Reader& operator=(const Reader&) = delete;
		Reader& operator=(Reader&&) noexcept = default;

		bool Read(Field &field, std::size_t offset);
		bool Read(Record &record, std::size_t offset);
		bool Read(Group &group, std::size_t offset);

		bool IsGood() const;
	private:
		bool StreamFailed() const;
		bool SeekAndCheck(std::size_t offset);

		std::ifstream m_Stream;
	};
}
