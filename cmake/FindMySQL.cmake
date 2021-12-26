#if( WIN32 )
#	find_path( MYSQL_INCLUDE_DIR
#		NAMES "mysql.h"
#		PATHS "$ENV{PROGRAMFILES}/MySQL/*/include"
#			  "$ENV{PROGRAMFILES(x86)}/MySQL/*/include"
#			  "$ENV{SYSTEMDRIVE}/MySQL/*/include" )
#	
#	find_library( MYSQL_LIBRARY
#		NAMES "mysqlclient" "mysqlclient_r"
#		PATHS "$ENV{PROGRAMFILES}/MySQL/*/lib"
#			  "$ENV{PROGRAMFILES(x86)}/MySQL/*/lib"
#			  "$ENV{SYSTEMDRIVE}/MySQL/*/lib" )
#else()
#	find_path( MYSQL_INCLUDE_DIR
#		NAMES "mysql.h"
#		PATHS "/usr/include/mysql"
#			  "/usr/local/include/mysql"
#			  "/usr/mysql/include/mysql" )
#	
#	find_library( MYSQL_LIBRARY
#		NAMES "mysqlclient" "mysqlclient_r"
#		PATHS "/lib/mysql"
#			  "/lib64/mysql"
#			  "/usr/lib/mysql"
#			  "/usr/lib64/mysql"
#			  "/usr/local/lib/mysql"
#			  "/usr/local/lib64/mysql"
#			  "/usr/mysql/lib/mysql"
#			  "/usr/mysql/lib64/mysql" )
#endif()



# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MYSQL_LIBRARIES   - List of libraries when using MySQL.
#  MYSQL_FOUND       - True if MySQL found.

IF (MYSQL_INCLUDE_DIR)
  # Already in cache, be silent
  SET(MYSQL_FIND_QUIETLY TRUE)
ENDIF (MYSQL_INCLUDE_DIR)

FIND_PATH(MYSQL_INCLUDE_DIR mysql.h
  /usr/local/include/mysql
  /usr/include/mysql
)

SET(MYSQL_NAMES mysqlclient mysqlclient_r)
FIND_LIBRARY(MYSQL_LIBRARY
  NAMES ${MYSQL_NAMES}
  PATHS /usr/lib /usr/local/lib
  PATH_SUFFIXES mysql
)

IF (MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)
  SET(MYSQL_FOUND TRUE)
  SET( MYSQL_LIBRARIES ${MYSQL_LIBRARY} )
ELSE (MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)
  SET(MYSQL_FOUND FALSE)
  SET( MYSQL_LIBRARIES )
ENDIF (MYSQL_INCLUDE_DIR AND MYSQL_LIBRARY)

IF (MYSQL_FOUND)
  IF (NOT MYSQL_FIND_QUIETLY)
    MESSAGE(STATUS "Found MySQL: ${MYSQL_LIBRARY}")
  ENDIF (NOT MYSQL_FIND_QUIETLY)
ELSE (MYSQL_FOUND)
  IF (MYSQL_FIND_REQUIRED)
    MESSAGE(STATUS "Looked for MySQL libraries named ${MYSQL_NAMES}.")
    MESSAGE(FATAL_ERROR "Could NOT find MySQL library")
  ENDIF (MYSQL_FIND_REQUIRED)
ENDIF (MYSQL_FOUND)

MARK_AS_ADVANCED(
  MYSQL_LIBRARY
  MYSQL_INCLUDE_DIR
  )




if( MYSQL_INCLUDE_DIR AND EXISTS "${MYSQL_INCLUDE_DIRS}/mysql_version.h" )
	file( STRINGS "${MYSQL_INCLUDE_DIRS}/mysql_version.h"
		MYSQL_VERSION_H REGEX "^#define[ \t]+MYSQL_SERVER_VERSION[ \t]+\"[^\"]+\".*$" )
	string( REGEX REPLACE
		"^.*MYSQL_SERVER_VERSION[ \t]+\"([^\"]+)\".*$" "\\1" MYSQL_VERSION_STRING
		"${MYSQL_VERSION_H}" )
endif()

# handle the QUIETLY and REQUIRED arguments and set MYSQL_FOUND to TRUE if
# all listed variables are TRUE
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( MYSQL DEFAULT_MSG
	REQUIRED_VARS	MYSQL_LIBRARY MYSQL_INCLUDE_DIR
	VERSION_VAR		MYSQL_VERSION_STRING )

set( MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_DIR} )
set( MYSQL_LIBRARIES ${MYSQL_LIBRARY} )

mark_as_advanced( MYSQL_INCLUDE_DIR MYSQL_LIBRARY )
