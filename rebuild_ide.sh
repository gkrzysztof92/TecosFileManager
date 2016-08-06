#!/bin/bash

clear
echo

#Usuwanie istniejącego katalogu środowiska programistycznego
rm -fR build

#usuwanie plików generowanych w trakcie przetwarzania pliku CMakeLists.txt

#Utworzenie nowego katalogu dla środowiska programistycznego
mkdir build/

#Przejście do katalogu środowiska programistycznego
cd build/

#Wywołanie narzędzia CMake
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-raspberry-pi.cmake -G "CodeBlocks - Unix Makefiles" ../

echo

read -p "Wciśnij ENTER aby kontynuować..."
