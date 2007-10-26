PROJECT(ReniMadden)
SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(renimadden_SOURCES
    main.cpp
    board.cpp
)

SET(renimadden_HEADERS
    board.h
)

ADD_EXECUTABLE(renimadden ${renimadden_SOURCES})
