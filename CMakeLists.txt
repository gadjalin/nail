CMAKE_MINIMUM_REQUIRED(VERSION 3.20 FATAL_ERROR)

# Read version numbers and stage from version.hpp
FILE(READ include/nail/version.hpp NAIL_VERSION_FILE)
STRING(REGEX MATCH "#define[ ]+NAIL_VERSION_MAJOR[ ]+([0-9]+)" _ ${NAIL_VERSION_FILE})
SET(NAIL_VERSION_MAJOR "${CMAKE_MATCH_1}")
STRING(REGEX MATCH "#define[ ]+NAIL_VERSION_MINOR[ ]+([0-9]+)" _ ${NAIL_VERSION_FILE})
SET(NAIL_VERSION_MINOR "${CMAKE_MATCH_1}")
STRING(REGEX MATCH "#define[ ]+NAIL_VERSION_REV[ ]+([0-9]+)" _ ${NAIL_VERSION_FILE})
SET(NAIL_VERSION_REV "${CMAKE_MATCH_1}")
STRING(REGEX MATCH "#define[ ]+NAIL_VERSION_STAGE[ ]+\"([A-Za-z]+)\"" _ ${NAIL_VERSION_FILE})
SET(NAIL_VERSION_STAGE "${CMAKE_MATCH_1}")

# Set the SemVer version variable
SET(NAIL_VERSION ${NAIL_VERSION_MAJOR}.${NAIL_VERSION_MINOR}.${NAIL_VERSION_REV})

PROJECT(LIBNAIL
        VERSION ${NAIL_VERSION}
        LANGUAGES CXX)

# Nail version is formatted as "1-2.3a"
MESSAGE(STATUS "Configuring Nail ${NAIL_VERSION_MAJOR}-${NAIL_VERSION_MINOR}.${NAIL_VERSION_REV}${NAIL_VERSION_STAGE}...")

FIND_PACKAGE(Threads REQUIRED)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

SET(CMAKE_DEBUG_POSTFIX -d)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

ADD_SUBDIRECTORY(deps/fmt)
#ADD_SUBDIRECTORY(deps/backward-cpp)

ADD_LIBRARY(nail)

IF(WIN32)
   SET(BUILD_SHARED_LIBS OFF)
ELSE()
   SET(BUILD_SHARED_LIBS ON)
ENDIF()

SET_TARGET_PROPERTIES(nail PROPERTIES
                      OUTPUT_NAME nail
                      VERSION ${NAIL_VERSION}
                      SOVERSION ${NAIL_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "Nail")

SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(HPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/nail")
SET(CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

#TARGET_PRECOMPILE_HEADERS(nail PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:nailpch.hpp>")

TARGET_COMPILE_DEFINITIONS(nail PRIVATE
                           $<$<CONFIG:Release>:NDEBUG>)

TARGET_INCLUDE_DIRECTORIES(nail PUBLIC
                           "${INCLUDE_DIR}"
                           "${DEPS_DIR}/fmt/include"
                           "${PROJECT_BINARY_DIR}")

#TARGET_INCLUDE_DIRECTORIES(nail PRIVATE
#                           "${DEPS_DIR}/backward-cpp")

TARGET_INCLUDE_DIRECTORIES(nail SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>)

TARGET_SOURCES(nail PRIVATE
               ${CPP_DIR}/version.cpp
               ${CPP_DIR}/Common/System.cpp
               ${CPP_DIR}/Common/DynamicLibrary.cpp
               ${CPP_DIR}/Debug/Assert.cpp
               )

TARGET_LINK_DIRECTORIES(nail PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

# Add backward-cpp to search paths
#LIST(APPEND CMAKE_PREFIX_PATH ${DEPS_DIR}/backward-cpp)
#FIND_PACKAGE(Backward REQUIRED)

TARGET_LINK_LIBRARIES(nail PRIVATE
                      fmt
#                      Backward::Backward

                      Threads::Threads
                      ${CMAKE_DL_LIBS}
                      $<$<PLATFORM_ID:Windows>:version>
                      )

