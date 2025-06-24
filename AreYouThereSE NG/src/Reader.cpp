#include "pch.h"
#include "Reader.h"

namespace BeinzPlugin {
	inline bool StreamFailed(std::ifstream& stream) {
		return !stream.good() || stream.eof() || stream.fail();
	}

	inline bool SeekAndCheck(std::ifstream& stream, std::size_t offset) {
		stream.seekg(static_cast<std::istream::off_type>(offset), std::ios::beg);
		return !StreamFailed(stream);
	}

	Reader::Reader(std::string_view fileName) {
		m_Stream.open(fileName.data(), std::ios::in | std::ios::binary);
	}

	Reader::~Reader() {
		m_Stream.close();
	}

	bool Reader::Read(Field& field, std::size_t offset) {
		try {
			if (!SeekAndCheck(m_Stream, offset)) {
				SPDLOG_ERROR("Failed to seek to offset: {}", offset);
				return false;
			}

			Get(field.Type);
			Get(field.DataSize);
		}
		catch (const std::exception& ex) {
			SPDLOG_ERROR("Exception while reading field: {}", ex.what());
			return false;
		}
		catch (...) {
			SPDLOG_ERROR("Unknown exception while reading field");
			return false;
		}

		return true;
	}

	bool Reader::Read(Record& record, std::size_t offset) {
		try {
			if (!SeekAndCheck(m_Stream, offset)) {
				SPDLOG_ERROR("Failed to seek to offset: {}", offset);
				return false;
			}

			Get(record.Type);
			Get(record.DataSize);
			Get(record.Flags);
			Get(record.ID);
			Get(record.TimeStamp);
			Get(record.Revision);
			Get(record.Version);
			Get(record.Unknown);
		}
		catch (const std::exception& ex) {
			SPDLOG_ERROR("Exception while reading record: {}", ex.what());
			return false;
		}
		catch (...) {
			SPDLOG_ERROR("Unknown exception while reading record");
			return false;
		}

		return true;
	}

	bool Reader::Read(Group& group, std::size_t offset) {
		try {
			if (!SeekAndCheck(m_Stream, offset)) {
				SPDLOG_ERROR("Failed to seek to offset: {}", offset);
				return false;
			}

			Get(group.Type);
			Get(group.GroupSize);
			Get(group.Label);
			Get(group.GroupType);
			Get(group.TimeStamp);
			Get(group.Version);
			Get(group.Unknown);
		}
		catch (const std::exception& ex) {
			SPDLOG_ERROR("Exception while reading group: {}", ex.what());
			return false;
		}
		catch (...) {
			SPDLOG_ERROR("Unknown exception while reading group");
			return false;
		}

		return true;
	}

	bool Reader::IsGood() const {
		return m_Stream.good();
	}
}
