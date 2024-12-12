cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest  
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2  
  TLS_VERIFY false
)
# Для Windows: предотвращение переопределения настроек компилятора/линковщика родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем директорию с заголовочными файлами
include_directories(include)

# Собираем список всех .cpp файлов в директории src
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Добавляем main.cpp из корневого каталога
list(APPEND SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Создаем исполняемый файл main
add_executable(main_${PROJECT_NAME} ${SRC_FILES})

# Создаем библиотеку проекта (если она еще не была создана)
add_library(${PROJECT_NAME}_lib STATIC ${SRC_FILES})

# Добавление тестов
enable_testing()

# Создание тестового исполняемого файла и связывание его с Google Test и библиотекой проекта
add_executable(test_${PROJECT_NAME} tests/unit.cpp)
target_link_libraries(test_${PROJECT_NAME} PRIVATE gtest_main ${PROJECT_NAME}_lib)

# Добавление тестов в тестовый набор
include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})