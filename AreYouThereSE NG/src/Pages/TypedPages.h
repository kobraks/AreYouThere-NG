#pragma once
#include "Utils.h"

#include <unordered_map>
#include <vector>
#include <memory>

#include <RE/B/BSTArray.h>
#include <RE/B/BSFixedString.h>

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
			const auto it = Pages.find(key);
			if (it == Pages.end()) {
				return GetEmptyNamesList();
			}

			if (!m_Cached || m_CachedKey != key) {
				const auto& pages = it->second;
				m_CachedNames = CopyPage<RE::BSTArray<RE::BSFixedString>>(pages, pages.size(), [](const auto& page) {
					return page->GenerateName();
					});

				m_CachedKey = key;
				m_Cached = true;
			}

			return m_CachedNames;
		}

		std::size_t PageCount() const { return m_PageSize; }

		void Clear() {
			Pages.clear();
			ClearCache();
		}

		void ClearCache() {
			m_Cached = false;
			m_CachedNames.clear();
		}

	protected:
		std::size_t m_PageSize;
		mutable bool m_Cached = false;
		mutable TKey m_CachedKey{};
		mutable RE::BSTArray<RE::BSFixedString> m_CachedNames;
	};
}
