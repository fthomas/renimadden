PROJECT(ReniMadden)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(renimadden_SOURCES
    main.cpp
    board.cpp
    move.cpp
)

SET(renimadden_HEADERS
    board.h
    move.h
    playerid.h
)

ADD_EXECUTABLE(renimadden ${renimadden_SOURCES})
