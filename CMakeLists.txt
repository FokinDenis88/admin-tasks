# CMakeList.txt : CMake project for artificial-neural-networks, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Can be different with target
project("admin-tasks" VERSION 1.0)

set(SOURCES
    src/admin-tasks.cpp
    src/copy-files-to-multiple-dirs.cpp
    src/unpack-archives-in-subfolders.cpp
    src/general.cpp
    src/exception-handling-console.cpp
    src/logs-support.cpp
    src/tag-management.cpp
    src/prefix-suffix.cpp
    src/delete-files-from-multiple-dirs.cpp
    src/copy-full-license-text-file.cpp
    )

set(INCLUDES
    include
    external/regex-boost/include
    external/file-stream-wrapper/include
    "C:/DevApps/!Libraries/!boost/boost-1-80"
    )

set(LIBRARIES
    "C:/DevApps/!Libraries/!boost/boost-1-80/bin.v2/libs/filesystem/build/msvc-14.3/debug/link-static/threading-multi/libboost_filesystem-vc143-mt-gd-x64-1_80.lib"
    #"C:/DevApps/!Libraries/!boost/boost-1-80/bin.v2/libs/filesystem/build/msvc-14.3/release/link-static/threading-multi/libboost_filesystem-vc143-mt-x64-1_80.lib"
    "C:/DevApps/!Libraries/!boost/boost-1-80/bin.v2/libs/regex/build/msvc-14.3/debug/link-static/threading-multi/libboost_regex-vc143-mt-gd-x64-1_80.lib"
    #"C:/DevApps/!Libraries/!boost/boost-1-80/bin.v2/libs/regex/build/msvc-14.3/release/link-static/threading-multi/libboost_regex-vc143-mt-x64-1_80.lib"
    )

set(HEADER_FILES_FILTER
    include/admin-tasks.hpp
    include/copy-files-to-multiple-dirs.hpp
    include/unpack-archives-in-subfolders.hpp
    include/general.hpp
    include/exception-handling-console.hpp
    include/logs-support.hpp
    include/tag-management.hpp
    include/prefix-suffix.hpp
    include/delete-files-from-multiple-dirs.hpp
    include/copy-full-license-text-file.hpp
    )

set(DOC_FILTER
    doc/to-do.txt
    doc/copy-past-helper.txt
    admin-tasks.ini
    #doc/!wiki.odt
    )

# Add source to this project's executable.
add_executable(admin-tasks ${SOURCES}
                ${HEADER_FILES_FILTER} ${DOC_FILTER})
# Include Directories
target_include_directories(admin-tasks PUBLIC ${INCLUDES})

# Link Libraries
target_link_libraries(admin-tasks ${LIBRARIES})

# Filters for Grouping files in project
source_group("Header Files" FILES ${HEADER_FILES_FILTER})
source_group("Doc" FILES ${DOC_FILTER})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET admin-tasks PROPERTY CXX_STANDARD 20)
  set_property(TARGET admin-tasks PROPERTY C_STANDARD 17)
endif()
set_property(TARGET admin-tasks PROPERTY SUBSYSTEM CONSOLE)





# Help Information
# TODO: Add tests and install targets if needed.


# Добавляет директории для дальнейшей обработки. В них нужно добавлять еще одни CMakeLists.txt файлы
# add_subdirectory (Hello)

#add_library (Hello hello.cxx)
#target_include_directories (Hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#add_executable (helloDemo demo.cxx demo_b.cxx)
#target_link_libraries (helloDemo LINK_PUBLIC Hello)

#set(SOURCE_EXE main.cpp)   set(SOURCE_LIB foo.cpp)
#add_library(foo STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем foo
#add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main
#target_link_libraries(main foo)
#include_directories(foo)			# Расположение заголовочных файлов
#file(GLOB <variable> [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS] [<globbing-expressions>...])
#target_compile_options(first-test PRIVATE -fexceptions)

#find_package(OpenMP)
#if (OPENMP_FOUND)
    #set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    #set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#endif()

#set_property(TARGET artificial-neural-networks PROPERTY SUBSYSTEM WINDOWS)
#CMAKE_CXX_FLAGS    /SUBSYSTEM:CONSOLE

#source_group("Header Files" FILES ${INCLUDES} REGULAR_EXPRESSION *)

#OpenMP
#find_package(OpenMP REQUIRED)
#target_link_libraries(artificial-neural-networks PRIVATE OpenMP::OpenMP_CXX)