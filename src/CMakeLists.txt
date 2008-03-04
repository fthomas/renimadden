SET(renimadden_SOURCES
    main.cpp
    board.cpp
    game.cpp
    listener.cpp
    move.cpp
)

SET(renimadden_HEADERS
    board.h
    game.h
    listener.h
    move.h
    playerid.h
)

ADD_EXECUTABLE(renimadden ${renimadden_SOURCES})
