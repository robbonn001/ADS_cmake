# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(DataStructure)

# затем следует список инструкций для подключения проектов из подкаталогов

include(cmake/function.cmake)         # подхватываем функции, реализованные в файле function.cmake
                                      # для простоты мы объединили наборы команд для создания статической библиотеки
								      # и для создания исполняемого проекта в отдельные функции

add_subdirectory(LibStackOnMass)

add_subdirectory(Algorithms)    # подключаем дополнительный CMakeLists.txt из подкаталога с именем Algorithms

add_subdirectory(DS_APP)                # подключаем дополнительный CMakeLists.txt из подкаталога с именем main

option(BTEST "build test?" ON)        # указываем подключаем ли google-тесты (ON или YES) или нет (OFF или NO)

if(BTEST)                             # если тесты подключены         
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(DS_TESTS)
endif()


