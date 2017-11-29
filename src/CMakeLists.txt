add_library(m7 SHARED
	demangle.C
	Exception.C
	StringTable.C
	FrameAllocator.C)

target_link_libraries(m7 unwind)
