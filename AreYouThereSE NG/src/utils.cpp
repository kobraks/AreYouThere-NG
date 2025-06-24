#include "pch.h"
#include "Utils.h"

namespace BeinzPlugin {
	std::array<char, 256> GenerateActorPageName(bool empty, std::size_t page, std::size_t pageSize) {
		std::array<char, 256> buffer{};

		SPDLOG_TRACE("Empty: {}, Page: {}, PageSize: {}", empty, page, pageSize);

		if(empty) {
			auto [out, size] = fmt::format_to_n(buffer.data(), buffer.size(), "Empty");

			*out = '\0';
		}
		else {
			auto [out, size] = fmt::format_to_n(
			                                    buffer.data(),
			                                    buffer.size() - 1,
			                                    "p{0} ({1:0>2}00~{1:0>2}99)",
			                                    page + 1,
			                                    page
			                                   );

			*out = '\0';
		}


		return buffer;
	}

	std::array<char, 256> GenerateModPageName(bool empty, std::size_t page, std::size_t pageSize) {
		std::array<char, 256> buffer{};

		if(empty) {
			auto [out, size] = fmt::format_to_n(buffer.data(), buffer.size(), "Empty");

			*out = '\0';
		}
		else {
			auto [out, size] = fmt::format_to_n(
			                                    buffer.data(),
			                                    buffer.size() - 1,
			                                    "#{:>2} ({:04X}~{:04X})",
			                                    page + 1,
			                                    page * pageSize,
			                                    (page + 1) * pageSize
			                                   );

			*out = '\0';
		}

		return buffer;
	}

	RE::BSTArray<uint32_t> GetEmptyIndicesList() {
		static bool initialized = false;
		static RE::BSTArray<uint32_t> result;

		if (!initialized) {
			initialized = true;
			result.clear();
			result.reserve(1);
			result.emplace_back(0);
		}

		return result;
	}

	RE::BSTArray<RE::BSFixedString> GetEmptyNamesList() {
		static bool initialized = false;
		static RE::BSTArray<RE::BSFixedString> result;

		if (!initialized) {
			initialized = true;
			result.clear();
			result.reserve(1);
			result.emplace_back("Empty");
		}

		return result;
	}
}