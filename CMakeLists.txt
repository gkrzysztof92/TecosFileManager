##Określa jaka minimalna wersja programu CMake jest potrzebna do
##przetworzenia tego pliku

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

#Definiuje nazwę projektu oraz jakie języki programowania będą
#wykorzystywane w projekcie

project(tecos_kernel C CXX ASM)

#Ustawia zmienną przechowującą aktualny numer wersji projektu
set(${PROJECT_NAME}_version "lab06")

#Ustawianie odpowiednich ścieżek w plikach źródłowych
configure_file(${PROJECT_SOURCE_DIR}/code/arch.h.in ${PROJECT_SOURCE_DIR}/code/arch.h)

#Ustawienia kompilacji
set(COMMON_FLAGS "-march=armv6zk -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -Wall")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -O3 -nostartfiles -std=c++11 -fno-rtti -fno-exceptions")

#Źródła w języku assemblera
set(ASM_SOURCE_FILES ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/bootstrap.S
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/time.S)

#Źródła w języku c++
set(CXX_SOURCE_FILES ${PROJECT_SOURCE_DIR}/code/kernel_main.cc
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/io.h
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/io.cc
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/memory.h
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/memory.cc
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/time.h
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/time.cc
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/serial.h
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/serial.cc
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/framebuffer.h
                        ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/framebuffer.cc
                        ${PROJECT_SOURCE_DIR}/code/output.h
                        ${PROJECT_SOURCE_DIR}/code/output.cc
                        ${PROJECT_SOURCE_DIR}/code/kernel_main.cc
                        ${PROJECT_SOURCE_DIR}/code/stub.cc)

#Tworzony będzie wykonywalny plik binarny

add_executable(${PROJECT_NAME} ${ASM_SOURCE_FILES} ${CXX_SOURCE_FILES})

#Ustawienia wynikowego pliku wykonywalnego

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${${PROJECT_NAME}_version}.elf")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-Map,${CMAKE_BINARY_DIR}/${PROJECT_NAME}-${${PROJECT_NAME}_version}.map -T ${PROJECT_SOURCE_DIR}/code/arch/${${PROJECT_NAME}_architecture}/linker.ld")

#Tworzenie obrazu jądra systemu

add_custom_command(TARGET ${PROJECT_NAME} COMMAND ${CROSS_COMPILER_PREFIX}objcopy ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-${${PROJECT_NAME}_version}.elf -O binary ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-${${PROJECT_NAME}_version}.img)

#Generuje skrypt do uruchamiania emulatora

configure_file(${PROJECT_SOURCE_DIR}/run_kernel.sh.in ${PROJECT_SOURCE_DIR}/run_kernel.sh)
execute_process(COMMAND chmod 755 ${PROJECT_SOURCE_DIR}/run_kernel.sh)
