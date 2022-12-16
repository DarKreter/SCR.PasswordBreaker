set(HEADER_LIST inc/password.hpp inc/utils.hpp)
set(SRC_LIST src/utils.cpp)
set(DEPENDENCIES_LIST SuperiorList)

add_library(utils STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(utils PUBLIC . inc src)

add_dependencies(utils ${DEPENDENCIES_LIST})
target_link_libraries(utils PUBLIC ${DEPENDENCIES_LIST})