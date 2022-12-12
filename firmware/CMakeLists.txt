set(DEPENDENCIES_LIST utils SuperiorList Threads OpenSSL::SSL)

add_executable(firmware main.cpp)

target_include_directories(firmware PUBLIC .)

add_dependencies(firmware ${DEPENDENCIES_LIST})
target_link_libraries(firmware PUBLIC ${DEPENDENCIES_LIST})