cmake_minimum_required(VERSION 3.10)

project(PasswordBreaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# In case of emergency add this debugging flag do compiler option: ||-ggdb3||
set(CPU_OPTIONS -Werror -Wall -Wextra -pedantic -ffunction-sections -fdata-sections -Ofast)
add_compile_options(${CPU_OPTIONS})

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

add_subdirectory(utils)
add_subdirectory(list)
add_subdirectory(threads)
add_subdirectory(firmware)
