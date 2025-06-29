#pragma once
#include "Utils.h"

#include <unordered_map>
#include <vector>
#include <memory>

namespace BeinzPlugin {
	template <typename TKey, typename TPage>
	class TypedPages {
	public:
		TypedPages(std::size_t pageSize) : m_PageSize(pageSize) {}

		using PageVectorType = std::vector<std::shared_ptr<TPage>>;

		std::unordered_map<TKey, PageVectorType> Pages;

		virtual ~TypedPages() = default;

		std::shared_ptr<TPage> GetPage(std::size_t page, TKey key) const {
			if (auto it = Pages.find(key); it != Pages.end()) {
				SPDLOG_TRACE("Found page: {}", page);
				const auto& vec = it->second;

				if (page < vec.size()) {
					return vec[page];
				}
			}
			SPDLOG_TRACE("Page doesnt exists {} !", page);

			return nullptr;
		}

		RE::BSTArray<RE::BSFixedString> GetNames(TKey key) const {
			if (auto it = Pages.find(key); it != Pages.end()) {
				const auto& vec = it->second;
				return CopyPage<RE::BSTArray<RE::BSFixedString>>(vec, m_PageSize, [](const auto& page) {
					return page->GenerateName();
					});
			}

			return GetEmptyNamesList();
		}

		std::size_t PageCount() const { return m_PageSize; }

		void Clear() {
			Pages.clear();
		}

	protected:
		std::size_t m_PageSize;
	};
}
