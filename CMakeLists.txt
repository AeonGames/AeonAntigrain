# Copyright (C) 2019 Rodrigo Jose Hernandez Cordoba
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

cmake_minimum_required(VERSION 3.0.0 )

set(AGG_MAJOR_VERSION 2 )
set(AGG_MINOR_VERSION 4 )
set(AGG_BUILD_VERSION 1 )

project(antigrain VERSION "${AGG_MAJOR_VERSION}.${AGG_MINOR_VERSION}.${AGG_BUILD_VERSION}" DESCRIPTION "Anti-Grain Geometry")

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# additional are modified Find routines
set ( CMAKE_MODULE_PATH "${antigrain_SOURCE_DIR}/cmake" )

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET( AGG_FLAGS "" )
SET( AGG_INCLUDE_DIRS "" )
SET( AGG_LIBRARY_DIRS "" )
SET( AGG_LIBRARIES "" )

SET( AGG_LIBRARY_DIRS  lib )

find_program(SED_EXECUTABLE sed
    HINTS ENV
        MINGW_PREFIX
        MSYS2_PATH
        ProgramFiles
    PATH_SUFFIXES bin usr/bin Git/usr/bin)
find_program(GREP_EXECUTABLE grep
    HINTS ENV
        MINGW_PREFIX
        MSYS2_PATH
        ProgramFiles
    PATH_SUFFIXES bin usr/bin Git/usr/bin)
find_program(BASH_EXECUTABLE bash
    HINTS ENV
        MINGW_PREFIX
        MSYS2_PATH
        ProgramFiles
    PATH_SUFFIXES bin usr/bin Git/usr/bin)

configure_file("${CMAKE_SOURCE_DIR}/cmake/pre-commit.in"
               "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit")


option( agg_USE_GPC "Use Gpc Boolean library" OFF)
option( agg_USE_FREETYPE "Use Freetype library" OFF)
option( agg_USE_EXPAT "Use Expat library" OFF)
option( agg_USE_SDL_PLATFORM "Use SDL as platform" OFF)
option( agg_USE_PACK "Package Agg" OFF)
option( agg_USE_AGG2D "Agg 2D graphical context" OFF)
option(BUILD_SHARED_LIBS "BUILD_SHARED_LIBS" ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE
                    PROPERTY STRINGS
                            "Debug"
                            "Release"
                            "MinSizeRel"
                            "RelWithDebInfo")
endif()

set(CMAKE_DEBUG_POSTFIX "d")

define_property(TARGET PROPERTY DEBUG_ARGUMENTS INHERITED
    BRIEF_DOCS "Debug Arguments"
    FULL_DOCS "Arguments to be passed when debugging")

# for the moment this decides the platform code.
IF(WIN32)
    ADD_DEFINITIONS( -D_MSWVC_ -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE )
    SET( WIN32GUI WIN32 )
    INCLUDE_DIRECTORIES( ${antigrain_SOURCE_DIR}/font_win32_tt )
    SET( AGG_INCLUDE_DIRS ${AGG_INCLUDE_DIRS} font_win32_tt )
ENDIF(WIN32)

IF(UNIX)
    ADD_DEFINITIONS( -D__UNIX__  )
    SET( WIN32GUI "" )

    FIND_PACKAGE(X11)
    IF(X11_FOUND)
        INCLUDE_DIRECTORIES(${X11_INCLUDE_DIRS})
    ENDIF(X11_FOUND)

ENDIF(UNIX)

# more specific set platform code part to use for different compilers/tool sets
IF ( ${CMAKE_GENERATOR} STREQUAL "MSYS Makefiles" )
	SET (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE STRING
		"Flags used by the compiler during release builds" FORCE)
	SET (CMAKE_CX_FLAGS_RELEASE "-DNDEBUG" CACHE STRING
		"Flags used by the compiler during release builds" FORCE)
ENDIF ( ${CMAKE_GENERATOR} STREQUAL "MSYS Makefiles" )

IF ( ${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles" )

ENDIF ( ${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles" )

IF ( ${CMAKE_GENERATOR} STREQUAL "Unix Makefiles" )
    IF( CYGWIN OR MINGW )
		SET (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE STRING
			"Flags used by the compiler during release builds" FORCE)
		SET (CMAKE_C_FLAGS_RELEASE "-DNDEBUG" CACHE STRING
			"Flags used by the compiler during release builds" FORCE)
    ENDIF( CYGWIN OR MINGW )
ENDIF ( ${CMAKE_GENERATOR} STREQUAL "Unix Makefiles" )

IF ( ${CMAKE_GENERATOR} MATCHES "Visual Studio.*" )

ENDIF ( ${CMAKE_GENERATOR} MATCHES "Visual Studio.*" )

IF ( ${CMAKE_GENERATOR} MATCHES "Borland Makefiles" )

ENDIF ( ${CMAKE_GENERATOR} MATCHES "Borland Makefiles" )

##################################################
# Set all includes, flags, libraries, related to expat
##################################################

if( agg_USE_EXPAT )
    find_package( EXPAT )
    IF(EXPAT_FOUND)
        INCLUDE_DIRECTORIES(${EXPAT_INCLUDE_DIRS})
    ELSE()
        MESSAGE(SEND_ERROR "expat not found")
    ENDIF()
endif()

##################################################
# Set all includes, flags, libraries, related to freetype
##################################################

IF( agg_USE_FREETYPE )
    FIND_PACKAGE( Freetype )
    IF( FREETYPE_FOUND )
        INCLUDE_DIRECTORIES( ${FREETYPE_INCLUDE_DIRS} )
    ELSE( FREETYPE_FOUND )
        MESSAGE(SEND_ERROR "freetype not found")
    ENDIF( FREETYPE_FOUND )
ENDIF( agg_USE_FREETYPE )

##################################################
# Set all includes, flags, libraries, related to SDL
##################################################

FIND_PACKAGE( SDL QUIET )
IF( SDL_FOUND )
    IF ( agg_USE_SDL_PLATFORM )
        INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
    ENDIF ( agg_USE_SDL_PLATFORM )
ELSE( SDL_FOUND )
    IF ( agg_USE_SDL_PLATFORM )
        MESSAGE( "SDL libray was not found, disable agg_USE_SDL_PLATFORM please" )
    ENDIF ( agg_USE_SDL_PLATFORM )
ENDIF( SDL_FOUND )

# the main include dir of Agg
INCLUDE_DIRECTORIES( ${antigrain_SOURCE_DIR}/include )
SET( AGG_INCLUDE_DIRS ${AGG_INCLUDE_DIRS} include )

# freetype specific lib of Agg
IF( agg_USE_FREETYPE )
    INCLUDE_DIRECTORIES( ${antigrain_SOURCE_DIR}/font_freetype )
    SET( AGG_INCLUDE_DIRS ${AGG_INCLUDE_DIRS} font_freetype )
    ADD_DEFINITIONS( -DAGG_USE_FREETYPE )
    SET( AGG_FLAGS ${AGG_FLAGS} -DAGG_USE_FREETYPE )
    SET( AGG_LIBRARIES ${AGG_LIBRARIES} aggfontfreetype${PFDEBUG} )
ENDIF( agg_USE_FREETYPE )

# GPC lib if used within Agg
IF ( agg_USE_GPC )
    INCLUDE_DIRECTORIES( ${antigrain_SOURCE_DIR}/gpc )
    SET( AGG_INCLUDE_DIRS ${AGG_INCLUDE_DIRS} gpc )
    ADD_DEFINITIONS( -DAGG_USE_GPC )
    SET( AGG_FLAGS ${AGG_FLAGS} -DAGG_USE_GPC )
    SET( AGG_LIBRARIES ${AGG_LIBRARIES} gpc${PFDEBUG} )
ENDIF ( agg_USE_GPC )

# agg2d lib if used within Agg
IF ( agg_USE_AGG2D )
    INCLUDE_DIRECTORIES( ${antigrain_SOURCE_DIR}/agg2d )
    SET( AGG_INCLUDE_DIRS ${AGG_INCLUDE_DIRS} agg2d )
    ADD_DEFINITIONS( -DAGG_USE_AGG2D )
    option( agg_USE_AGG2D_FREETYPE "Agg 2D graphical context uses freetype" OFF)
    SET( AGG_FLAGS ${AGG_FLAGS} -DAGG_USE_AGG2D )
    SET( AGG_LIBRARIES ${AGG_LIBRARIES} agg2d${PFDEBUG} )
ENDIF ( agg_USE_AGG2D )

IF ( agg_USE_AGG2D_FREETYPE )
    ADD_DEFINITIONS( -DAGG2D_USE_FREETYPE )
    SET( AGG_FLAGS ${AGG_FLAGS} -DAGG2D_USE_FREETYPE )
ENDIF ( agg_USE_AGG2D_FREETYPE )

# sld as platform or os
IF( SDL_FOUND AND agg_USE_SDL_PLATFORM )
    SET( AGG_LIBRARIES ${AGG_LIBRARIES} aggctrl${PFDEBUG} aggsdlplatform${PFDEBUG} agg${PFDEBUG} )
ELSE( SDL_FOUND AND agg_USE_SDL_PLATFORM )
    SET( AGG_LIBRARIES ${AGG_LIBRARIES} aggctrl${PFDEBUG} aggplatform${PFDEBUG} agg${PFDEBUG} )
ENDIF( SDL_FOUND AND agg_USE_SDL_PLATFORM )

SET( AGG_FLAGS ${AGG_FLAGS} CACHE STRING "Agg package flags" FORCE )
SET( AGG_INCLUDE_DIRS ${AGG_INCLUDE_DIRS} CACHE STRING "Agg package libs include paths" FORCE )
SET( AGG_LIBRARY_DIRS ${AGG_LIBRARY_DIRS} CACHE STRING "Agg package libs directory paths" FORCE )
SET( AGG_LIBRARIES ${AGG_LIBRARIES} CACHE STRING "Agg package libraries" FORCE )

ADD_SUBDIRECTORY( src )

ADD_SUBDIRECTORY( examples )

#-------------------------------------------------------------------
# Build a CPack installer if CPack is available and this is a build
IF ( agg_USE_PACK )
    IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
        SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Agg - Vector Graphics")
        SET(CPACK_PACKAGE_VENDOR "Agg")
        SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/copying")
        SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/copying")
        SET(CPACK_PACKAGE_VERSION_MAJOR "${AGG_MAJOR_VERSION}")
        SET(CPACK_PACKAGE_VERSION_MINOR "${AGG_MINOR_VERSION}")
        SET(CPACK_PACKAGE_VERSION_PATCH "${AGG_BUILD_VERSION}")
        SET(CPACK_PACKAGE_INSTALL_DIRECTORY "AGG_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
        SET(CPACK_SOURCE_PACKAGE_FILE_NAME "agg-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
        SET(CPACK_PACKAGE_EXECUTABLES
        "agg" "AGG"
        )
        SET(CPACK_SOURCE_STRIP_FILES "")
        SET(CPACK_STRIP_FILES "bin/ccmake;bin/cmake;bin/cpack;bin/ctest")


        IF(WIN32)
            SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
            SET(CPACK_NSIS_HELP_LINK "http://agg.sourceforge.net")
            SET(CPACK_NSIS_URL_INFO_ABOUT "http://agg.sourceforge.net")
            SET(CPACK_NSIS_CONTACT "http://agg.sourceforge.net")
        ENDIF(WIN32)

        INCLUDE(CPack)
    ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
ENDIF ( agg_USE_PACK )

include(vscode)