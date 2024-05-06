#pragma once

namespace BeinzPlugin {
	constexpr size_t HowManyPages(const size_t items, const size_t pageSize) {
		return (items / pageSize) + ((items % pageSize) ? 1 : 0);
	}

	std::array<char, 256> GenerateActorPageName(bool empty, size_t page, size_t pageSize);
	std::array<char, 256> GenerateModPageName(bool empty, size_t page, size_t pageSize);

	// template <class T, class From, typename Fn>
	// T CopyPage(const From &from, size_t page, size_t pageSize, Fn func) {
	// 	T items{};
	//
	// 	const size_t start = page * pageSize;
	// 	const size_t end = (page + 1) * pageSize;
	//
	// 	SPDLOG_TRACE("page: {} [start: {}, end: {}, pageSize: {}, pageSize: {}]", page, start, end, from.size(), pageSize);
	//
	// 	if (start >= from.size())
	// 		return items;
	//
	// 	items.reserve(pageSize);
	//
	// 	const auto beginI = from.begin() + start;
	// 	const auto endI = end < from.size() ? from.begin() + end : from.end();
	//
	// 	std::transform(beginI, endI, std::back_inserter(items), func);
	//
	// 	return items;
	// }

	template <class T, class From, typename Fn>
	T CopyPage(const From &from, size_t pageSize, Fn func) {
		T items{};

		SPDLOG_TRACE("From size: {}, pageSize: {}", from.size(), pageSize);

		items.reserve(static_cast<T::size_type>(pageSize));
		std::transform(from.begin(), from.end(), std::back_inserter(items), func);

		return items;
	}

	template <class T>
	T CopyPage(const T &from, size_t page, size_t pageSize) {
		T items{};

		const size_t start = page * pageSize;
		const size_t end   = (page + 1) * pageSize;

		SPDLOG_TRACE(
		             "page: {} [start: {}, end: {}, pageSize: {}, pageSize: {}]",
		             page,
		             start,
		             end,
		             from.size(),
		             pageSize
		            );

		if(start >= from.size())
			return items;

		items.reserve(static_cast<T::size_type>(pageSize));

		const auto beginI = from.begin() + start;
		const auto endI   = end < from.size() ? from.begin() + end : from.end();

		std::copy(beginI, endI, std::back_inserter(items));

		return items;
	}

	template<class Iterator, class DstIterator, typename Fn>
	static void Copy(const Iterator begin, const Iterator end, DstIterator dst, Fn function) {
		std::transform(begin, end, dst, function);
	}
}
