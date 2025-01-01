cmake_minimum_required (VERSION 3.12)
set(TARGET_NAME button_handler)

message("Adding ${PROJECT_NAME} C files: " )
file(GLOB CPPFILE "*.c")
foreach(source ${CPPFILE})
    message("  - " ${source})
endforeach(source)
 
message("Adding ${PROJECT_NAME} H files: " )
file(GLOB HFILE "*.h")
foreach(source ${HFILE})
    message("  - " ${source})
endforeach(source)
 
add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME} INTERFACE
${CPPFILE}
${HFILE}
)

target_link_libraries(${TARGET_NAME} INTERFACE
pico_stdlib
FreeRTOS-Kernel-Heap4
)

target_include_directories(${TARGET_NAME} INTERFACE

    ${CMAKE_CURRENT_LIST_DIR}
)
 