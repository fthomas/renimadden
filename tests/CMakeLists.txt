SET(rmtests_SOURCES
    main.cpp
)

SET(rmtests_HEADERS
    boardtest.h
)

INCLUDE_DIRECTORIES(../src)

ADD_EXECUTABLE(rmtests ${rmtests_SOURCES})
TARGET_LINK_LIBRARIES(rmtests cppunit)
