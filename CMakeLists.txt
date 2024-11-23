cmake_minimum_required(VERSION 3.28)
project(cpp-rasterizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    set_property(
        TARGET ${PROJECT_NAME} 
        PROPERTY VS_DEBUGGER_WORKING_DIRECTORY 
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

if(WIN32)
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(SDL_ARCH "x64")
    else()
        set(SDL_ARCH "x86")
    endif()

    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_DIR}/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${SDL2_DIR}/lib/${SDL_ARCH})
    
    target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2main
        SDL2
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DIR}/bin/${SDL_ARCH}/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
else()
    find_package(SDL2 REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif()
