#pragma once

namespace BeinzPlugin {
	class Page {
	public:
		virtual ~Page() = default;
		virtual RE::BSFixedString GenerateName() = 0;

		size_t ID() const { return m_Page; }
		size_t MaxItems() const { return m_MaxItems; }

		bool IsEmpty() const { return m_Empty; }

	protected:
		Page(bool empty, size_t pageNumber, size_t maxItems);

		void Empty(bool empty = true) { m_Empty = empty; }

		RE::BSFixedString m_Name;

	private:
		const size_t m_MaxItems;
		size_t m_Page;
		bool m_Empty;
	};
}