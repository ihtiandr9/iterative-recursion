cmake_minimum_required(VERSION 3.0...3.30)
project(tree)

include_directories(/usr/local/include
    /usr/include
    src)

link_directories(/usr/local/lib)

file(GLOB SOURCE_C src/*c)

if(NOT DEFINED _Release_)
    add_definitions(-ggdb -Wno-switch)
endif()

## main executable file
add_executable(tree
    ${SOURCE_C}
)

## debug target

add_custom_target(run
    COMMAND	./tree
    COMMENT "Run application"
    DEPENDS ./tree
)

add_custom_target(debug
    COMMAND	gdb ./tree
    COMMENT "GDB Debug"
    DEPENDS ./tree
)

install(TARGETS tree DESTINATION /usr/local/bin)
