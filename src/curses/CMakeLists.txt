SET(crenimadden_SOURCES
    main.cpp
)

SET(crenimadden_HEADERS
    curseslistener.h
)

INCLUDE_DIRECTORIES(..)

ADD_EXECUTABLE(crenimadden ${crenimadden_SOURCES})
TARGET_LINK_LIBRARIES(crenimadden ncurses)
