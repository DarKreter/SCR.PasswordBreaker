set(HEADER_LIST inc/password.hpp inc/utils.hpp)
set(SRC_LIST src/utils.cpp)

add_library(utils STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(utils PUBLIC . inc src)