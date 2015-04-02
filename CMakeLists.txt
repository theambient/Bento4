
cmake_minimum_required( VERSION 2.8 )

project( bento4 )

find_package( Threads REQUIRED )

include_directories(
	Source/C++/Adapters/
	Source/C++/Apps/
	Source/C++/CApi/
	Source/C++/Codecs/
	Source/C++/Core/
	Source/C++/Crypto/
	Source/C++/MetaData/
	Source/C++/System/
	Source/C++/Test/
)

set( LIBBENTO4_SOURCES )

set(SOURCE_DIRS Core Codecs Crypto MetaData System/Posix System/StdC)

foreach(DIR ${SOURCE_DIRS})

	file(GLOB_RECURSE TMP "Source/C++/${DIR}/*.cpp")
	list(APPEND LIBBENTO4_SOURCES ${TMP})
	file(GLOB_RECURSE TMP "Source/C++/${DIR}/*.h")
	list(APPEND LIBBENTO4_SOURCES ${TMP})

endforeach()

set( LIBS
	${CMAKE_THREAD_LIBS_INIT}
)

add_library( bento4 ${LIBBENTO4_SOURCES} )

################################################################
#############		MACRO DEFINITION			################
################################################################

macro( add_one_file_bin name )

	add_executable( ${name} Source/C++/Apps/${name}/${name}.cpp )
	target_link_libraries( ${name} bento4 ${LIBS} )

endmacro()

################################################################
#############				TARGETS				################
################################################################

add_one_file_bin(Aac2Mp4)
add_one_file_bin(AvcInfo)
add_one_file_bin(FixAacSampleDescription)
add_one_file_bin(Mp42Aac)
add_one_file_bin(Mp42Avc)
add_one_file_bin(Mp42Ts)
add_one_file_bin(Mp4AudioClip)
add_one_file_bin(Mp4Compact)
add_one_file_bin(Mp4DcfPackager)
add_one_file_bin(Mp4Decrypt)
add_one_file_bin(Mp4Dump)
add_one_file_bin(Mp4Edit)
add_one_file_bin(Mp4Encrypt)
add_one_file_bin(Mp4Extract)
add_one_file_bin(Mp4Fragment)
add_one_file_bin(Mp4Info)
add_one_file_bin(Mp4Mux)
add_one_file_bin(Mp4RtpHintInfo)
add_one_file_bin(Mp4Split)
add_one_file_bin(Mp4Tag)

################################################################
#############				INSTALL				################
################################################################

foreach(DIR ${SOURCE_DIRS})

	install(
		DIRECTORY Source/C++/${DIR}/
		DESTINATION include/bento4
		FILES_MATCHING PATTERN "*.h"
	)

endforeach()

install(TARGETS bento4 DESTINATION lib/)

################################################################
#############				PACKAGE				################
################################################################

set(CPACK_PACKAGE_NAME "bento4")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, modern, open source C++ toolkit for all your MP4 and MPEG DASH media format needs")
set(CPACK_PACKAGE_CONTACT "Ruslan Mullakhmetov <>")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "4")
set(CPACK_PACKAGE_VERSION_PATCH "2")

include(CPack)
