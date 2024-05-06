BOOST = os.getenv("BOOST_DIR")

IncludeDir = {}
IncludeDir["Boost"] = "%{BOOST}"

IncludeDir["Spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["Fmt"] = "%{wks.location}/vendor/fmt/include"
IncludeDir["CommonLibSSE"] = "%{wks.location}/vendor/CommonLibSSE-NG/include"
IncludeDir["Rapidcsv"] = "%{wks.location}/vendor/rapidcsv/src"
IncludeDir["Binary_io"] = "%{wks.location}/vendor/binary_io/include"
--IncludeDir["SpanLite"] = "%{wks.location}/vendor/span-lite/include"
--IncludeDir["Xbyak"] = "%{wks.location}/vendor/xbyak"

LibraryDir = {}
LibraryDir["Boost"] = "%{BOOST}/stage/lib"

Library = {}