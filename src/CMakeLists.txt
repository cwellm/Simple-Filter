# main framework of plugin
target_sources(${PROJ_NAME} PRIVATE 
	Editor.cpp 
	Editor.h 
	Processor.cpp 
	Processor.h
)

# further sources
target_sources(${PROJ_NAME} PRIVATE 
    test.h
    test.cpp
)