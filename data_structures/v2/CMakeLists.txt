cmake_minimum_required(VERSION 3.16)

project(data_structures_v2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands" FORCE)

set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/arena.c
)

add_executable(queue_example
    ${COMMON_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/queue/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/queue/main.c
)

add_executable(heap_example
    ${COMMON_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/heap/heap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/heap/main.c
)

add_executable(priority_queue_example
    ${COMMON_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/priority_queue/priority_queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/priority_queue/main.c
)

set(EXAMPLE_TARGETS
    queue_example
    heap_example
    priority_queue_example
)

foreach(target_name IN LISTS EXAMPLE_TARGETS)
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_compile_options(${target_name} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endforeach()

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E rm -f
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    )
endif()
