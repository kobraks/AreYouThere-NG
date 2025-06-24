#pragma once
#include "Page/Page.h"
#include "Utils.h"

namespace BeinzPlugin {
	template <typename T>
	class TypedPage : public Page {
	public:
		using ItemType = T;
		using ItemPtr = std::shared_ptr<T>;
		using ItemContainerType = std::vector<ItemPtr>;

		TypedPage() : Page(true, 0, 0) {}
		TypedPage(size_t page, size_t pageSize) : Page(true, page, pageSize) {}
		TypedPage(const std::vector<std::shared_ptr<T>> &source, size_t page, size_t pageSize) : Page(false, page, pageSize) {
			m_Items = CopyPage<ItemContainerType>(source, page, pageSize);
			if (m_Items.empty()) {
				Empty(true);
			}
		}

		ItemContainerType& Items() { return m_Items; }
		const ItemContainerType& Items() const { return m_Items; }

	protected:
		ItemContainerType m_Items;

		template<typename ReturnType, typename Function>
		ReturnType GetTESContainer(Function func) const {
			return CopyPage<ReturnType>(
				m_Items,
				MaxItems(),
				func);
		}
	};
}