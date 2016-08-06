#Określenie systemu operacyjnego na jaki przeznaczony jest program
set(CMAKE_SYSTEM_NAME Generic)

#Określenie architektury na jaką tworzony jest program
set(${PROJECT_NAME}_architecture raspberry-pi)

#Prefiks narzędzi wykorzystywanych do kompilacji skrośnej
set(CROSS_COMPILER_PREFIX arm-none-eabi-)

#Określenie jakie kompilatory będą wykorzystywane
include(CMakeForceCompiler)
cmake_force_c_compiler(${CROSS_COMPILER_PREFIX}gcc GNU)
cmake_force_cxx_compiler(${CROSS_COMPILER_PREFIX}g++ GNU)
