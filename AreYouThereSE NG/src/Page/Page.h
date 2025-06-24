#pragma once

namespace BeinzPlugin {
	class Page {
	public:
		virtual ~Page() = default;
		virtual RE::BSFixedString GenerateName() = 0;

		std::size_t ID() const { return m_Page; }
		std::size_t MaxItems() const { return m_MaxItems; }

		bool IsEmpty() const { return m_Empty; }

	protected:
		Page(bool empty, std::size_t pageNumber, std::size_t maxItems);

		void Empty(bool empty = true) { m_Empty = empty; }

		RE::BSFixedString m_Name;

	private:
		const std::size_t m_MaxItems;
		std::size_t m_Page;
		bool m_Empty;
	};
}