cmake_minimum_required(VERSION 3.12)
set(PICO_BOARD pico_w)
set(FREERTOS_KERNEL_PATH /Users/vlad/programming/pico/FreeRTOS-Kernel)

include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

project(button C CXX ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE Release)

pico_sdk_init()

add_executable(${PROJECT_NAME}
main.c
)

add_subdirectory(button_handler)
target_link_libraries(${PROJECT_NAME}
button_handler
FreeRTOS-Kernel-Heap4
pico_stdlib
pico_cyw43_arch_none
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/button_handler
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    configNUMBER_OF_CORES=1
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})
