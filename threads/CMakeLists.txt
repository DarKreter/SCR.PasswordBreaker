set(HEADER_LIST inc/threads.hpp)
set(SRC_LIST src/threads.cpp)
set(DEPENDENCIES_LIST utils SuperiorList)

add_library(Threads STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(Threads PUBLIC . inc src)

add_dependencies(Threads ${DEPENDENCIES_LIST})
target_link_libraries(Threads PUBLIC ${DEPENDENCIES_LIST})
