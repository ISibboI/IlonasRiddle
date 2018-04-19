CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(IlonasRiddle)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wimplicit-fallthrough=0")
ENABLE_TESTING(ON)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

ADD_LIBRARY(riddlelib lib/helpers.cpp)
TARGET_INCLUDE_DIRECTORIES(riddlelib PUBLIC lib)

ADD_EXECUTABLE(riddlesolver apps/riddlesolver.cpp)
TARGET_LINK_LIBRARIES(riddlesolver riddlelib)

ADD_EXECUTABLE(evaluate_term tests/evaluate_term.cpp)
TARGET_LINK_LIBRARIES(evaluate_term riddlelib)

ADD_TEST(NAME valid_term COMMAND evaluate_term 432+754-223-5+4+1-6 957)
ADD_TEST(NAME double_operator_term COMMAND evaluate_term 432+754+-223-5+4+1-6 957)
ADD_TEST(NAME begin_operator_term COMMAND evaluate_term +45+5-1 49)
ADD_TEST(NAME end_operator_term COMMAND evaluate_term 45+5-1+ 49)
ADD_TEST(NAME no_operator_term COMMAND evaluate_term 45 45)
ADD_TEST(NAME empty_term COMMAND evaluate_term "" 0)
SET_TESTS_PROPERTIES(
        double_operator_term
        begin_operator_term
        end_operator_term
        empty_term
        PROPERTIES WILL_FAIL 1)
SET_TESTS_PROPERTIES(
        valid_term
        PROPERTIES FIXTURES_REQUIRED evaluate_term)