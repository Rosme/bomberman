cmake_minimum_required(VERSION 3.10)

project(Bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(SYSTEM ${CMAKE_PREFIX_PATH}/cereal/include)

file(GLOB SRC CONFIGURE_DEPENDS 
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} sfml-graphics)