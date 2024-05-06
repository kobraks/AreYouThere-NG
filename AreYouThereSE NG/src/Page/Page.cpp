#include "pch.h"
#include "Page/Page.h"

namespace BeinzPlugin {
	Page::Page(bool empty, size_t pageNumber, size_t maxItems) : m_Page(pageNumber), m_MaxItems(maxItems), m_Empty(true) {
	}

}