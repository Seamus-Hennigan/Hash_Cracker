cmake_minimum_required(VERSION 4.0)
project(Hash_Cracker)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

if(WIN32 AND NOT DEFINED OPENSSL_ROOT_DIR AND EXISTS "C:/msys64/mingw64/include/openssl/evp.h")
    set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
endif()
find_package(OpenSSL REQUIRED)

add_executable(Hash_Cracker
        main.cpp
        src/hash/Md5.cpp
        src/hash/sha1.cpp
        src/crack/dictionary.cpp
        src/crack/bruteforce.cpp
        src/ui/app.cpp
        include/hash/Md5.hpp
        include/hash/sha1.hpp
)

target_include_directories(Hash_Cracker PRIVATE include)

target_link_libraries(Hash_Cracker
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        PRIVATE OpenSSL::Crypto
)

if(WIN32 AND OPENSSL_ROOT_DIR)
    foreach(_dll libcrypto-3-x64.dll libssl-3-x64.dll)
        if(EXISTS "${OPENSSL_ROOT_DIR}/bin/${_dll}")
            add_custom_command(TARGET Hash_Cracker POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${OPENSSL_ROOT_DIR}/bin/${_dll}"
                        $<TARGET_FILE_DIR:Hash_Cracker>
            )
        endif()
    endforeach()
endif()
