cmake_minimum_required(VERSION 3.5)


if( FIPS_CONFIG AND NOT FIPS_IMPORT )

	get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
	include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

	fips_setup(PROJECT libbmsdi)
else()
  find_package(catkin QUIET)
endif()

# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

## C++ flags applied to all builds
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# ## Set global include paths
set( BMSDI_INCLUDE_DIRS
 	${CMAKE_CURRENT_SOURCE_DIR}/include )


include_directories( ${BMSDI_INCLUDE_DIRS} )



if (FIPS_CONFIG)

	fips_begin_module( bmsdi-protocol )
	  fips_src( lib/ )
	fips_end_module()

	if( NOT FIPS_IMPORT )

		fips_add_subdirectory("apps/")

		if( FIPS_UNITTESTS )
			gtest_begin( bmsdi-protocol )
			    fips_src(unit/test/)
			    fips_deps( bmsdi-protocol )
			    # include_directories( ${TEST_DATA_DIR} )
			gtest_end()
		endif()

		fips_finish()
	endif()

else()
    project(libbmsdi)

    find_package(catkin REQUIRED)


    catkin_package(
         INCLUDE_DIRS include
         LIBRARIES libbmsdi_LIB
      )

    include_directories(
      ${catkin_INCLUDE_DIRS}
      include/
      ${BMSDI_INCLUDE_DIRS}
     )


    file(GLOB libbmsdi_SRCS
	lib/*.c
      )


    add_library(libbmsdi_LIB ${libbmsdi_SRCS})
    target_link_libraries(libbmsdi_LIB ${catkin_LIBRARIES})



    install(TARGETS libbmsdi_LIB
          ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
          LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
          RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

    ## Install headers
    install(DIRECTORY  include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
        PATTERN ".git" EXCLUDE)	
  

endif()
