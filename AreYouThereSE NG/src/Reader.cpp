#include "pch.h"
#include "Reader.h"
BeinzPlugin::Reader::Reader(std::string_view fileName) {
	m_Stream.open(fileName.data(), std::ios::in | std::ios::binary);
}

BeinzPlugin::Reader::~Reader() {
	m_Stream.close();
}

bool BeinzPlugin::Reader::Read(Field &field, size_t offset) {
	try {
		m_Stream.seekg(static_cast<std::istream::pos_type>(offset), std::ios::beg);
		if (m_Stream.eof())
			return false;

		Get(field.Type);
		Get(field.DataSize);
	} catch(...) {
		return false;
	}

	return true;
}

bool BeinzPlugin::Reader::Read(Record &record, size_t offset) {
	try {
		m_Stream.seekg(static_cast<std::iostream::pos_type>(offset), std::ios::beg);

		if (m_Stream.eof())
			return false;

		Get(record.Type);
		Get(record.DataSize);
		Get(record.Flags);
		Get(record.ID);
		Get(record.TimeStamp);
		Get(record.Revision);
		Get(record.Version);
		Get(record.Unknown);
	} catch(...) {
		return false;
	}

	return true;
}

bool BeinzPlugin::Reader::Read(Group &group, size_t offset) {
	try {
		m_Stream.seekg(static_cast<std::iostream::pos_type>(offset), std::ios::beg);

		if (m_Stream.eof())
			return false;

		Get(group.Type);
		Get(group.GroupSize);
		Get(group.Label);
		Get(group.GroupType);
		Get(group.TimeStamp);
		Get(group.Version);
		Get(group.Unknown);
	} catch(...) {
		return false;
	}

	return true;
}

bool BeinzPlugin::Reader::IsGood() const {
	return m_Stream.good();
}
