#include "pch.h"
#include "Reader.h"

namespace BeinzPlugin {
	Reader::Reader(std::string_view fileName) {
		m_Stream.open(fileName.data(), std::ios::in | std::ios::binary);
	}

	Reader::~Reader() {
		m_Stream.close();
	}

	bool Reader::Read(Field& field, std::size_t offset) {
		try {
			if (!SeekAndCheck(offset)) {
				return false;
			}

			m_Stream.read(reinterpret_cast<char*>(&field), sizeof(field));
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
			if (!SeekAndCheck(offset)) {
				return false;
			}

			m_Stream.read(reinterpret_cast<char*>(&record), sizeof(record));
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
			if (!SeekAndCheck(offset)) {
				return false;
			}

			m_Stream.read(reinterpret_cast<char*>(&group), sizeof(group));
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
		return m_Stream.is_open() && m_Stream.good();
	}

	bool Reader::StreamFailed() const {
		return !m_Stream || m_Stream.fail() || m_Stream.eof();
	}

	bool Reader::SeekAndCheck(std::size_t offset) {
		m_Stream.seekg(static_cast<std::istream::off_type>(offset), std::ios::beg);

		if (StreamFailed()){
			SPDLOG_ERROR("Failed to seek to offset: {:#x}", offset);
			return false;
		}

		return true;
	}
}
