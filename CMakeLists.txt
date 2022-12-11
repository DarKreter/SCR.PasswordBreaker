cmake_minimum_required(VERSION 3.10)

project(PasswordBreaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPU_OPTIONS -Werror -Wall -Wextra -pedantic -ffunction-sections -fdata-sections -Os)
add_compile_options(${CPU_OPTIONS})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)


add_executable(firmware src/main.cpp src/md5.cpp)

target_include_directories(firmware PUBLIC . inc src)

# target_link_libraries(firmware PUBLIC OpenSSL::Crypto)
target_link_libraries(firmware PUBLIC OpenSSL::SSL)