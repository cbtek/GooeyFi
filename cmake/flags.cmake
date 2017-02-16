# This file contains compiler flags for different platforms
if (WIN32)
    if (MSVC)

    else()
        set(CMAKE_CXX_FLAGS_RELEASE "-g -Wl,--no-as-needed -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0")
        set(CMAKE_CXX_FLAGS_DEFAULT "-g -Wl,--no-as-needed -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0")
        set(CMAKE_CXX_FLAGS_DEBUG "-g -Wl,--no-as-needed -std=c++11  -D_GLIBCXX_USE_CXX11_ABI=0")
    endif()

else()
    set(CMAKE_CXX_FLAGS_RELEASE "-g -Wl,--no-as-needed -std=c++11 -pthread -fPIC -ldl -D_GLIBCXX_USE_CXX11_ABI=0")
    set(CMAKE_CXX_FLAGS_DEFAULT "-g -Wl,--no-as-needed -std=c++11 -pthread -fPIC -ldl -D_GLIBCXX_USE_CXX11_ABI=0")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wl,--no-as-needed -std=c++11 -pthread -fPIC -ldl -D_GLIBCXX_USE_CXX11_ABI=0")
endif()
