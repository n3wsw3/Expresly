# Include google test library
# include_directories("${Expresly_SOURCE_DIR}/tests/vendor/googletest/googletest/include")

# Include all test cpp files.
# file(GLOB TEST_SOURCES "${Expresly_SOURCE_DIR}/tests/tests.cpp")
# add_executable(unit-tests ${TEST_SOURCES})

add_subdirectory("${Expresly_SOURCE_DIR}/tests/vendor")
####
set(BINARY ${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)