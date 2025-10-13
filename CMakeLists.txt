cmake_minimum_required(VERSION 3.0...3.30)
project(iteration)

include_directories(/usr/local/include
    /usr/include
    src)

link_directories(/usr/local/lib)

file(GLOB SOURCE_C src/*c)

if(NOT DEFINED _Release_)
    add_definitions(-ggdb -Wno-switch)
endif()

## main executable file
add_executable(iteration
    ${SOURCE_C}
)

## debug target

add_custom_target(run
    COMMAND	./iteration
    COMMENT "run applic"
    DEPENDS ./iteration
)

add_custom_target(debug
    COMMAND	gdb ./iteration
    COMMENT "GDB Debug"
    DEPENDS ./iteration
)

install(TARGETS iteration DESTINATION /usr/local/bin)
