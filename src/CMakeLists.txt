set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

SET(OpenCV_DIR /installation/OpenCV-master/lib/cmake/opencv4)

find_package(OpenCV REQUIRED)

# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_run ${SOURCES})

target_link_libraries(${PROJECT_NAME}_run ${OpenCV_LIBS} )
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
