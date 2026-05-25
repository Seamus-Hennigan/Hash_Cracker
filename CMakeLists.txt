cmake_minimum_required(VERSION 4.0)
project(Hash_Cracker)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(Hash_Cracker
        main.cpp
        src/hash/md5.cpp
        src/hash/sha1.cpp
        src/crack/dictionary.cpp
        src/crack/bruteforce.cpp
        src/ui/app.cpp
        include/hash/md5.hpp
        include/hash/md5_constants.hpp
)

target_include_directories(Hash_Cracker PRIVATE include)

target_link_libraries(Hash_Cracker
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)
