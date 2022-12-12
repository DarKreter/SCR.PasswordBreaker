set(HEADER_LIST inc/list.hpp fml/list.tpp)
set(SRC_LIST src/list.cpp)
# set(DEPENDENCIES_LIST )

add_library(SuperiorList STATIC ${SRC_LIST} ${HEADER_LIST})

target_include_directories(SuperiorList PUBLIC . inc src fml)

# add_dependencies(SuperiorList ${DEPENDENCIES_LIST})
# target_link_libraries(SuperiorList PUBLIC ${DEPENDENCIES_LIST})
