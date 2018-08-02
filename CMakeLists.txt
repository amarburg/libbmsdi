cmake_minimum_required(VERSION 3.5)
if( NOT FIPS_IMPORT )
	get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
	include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

	fips_setup(PROJECT libbmsdi)
endif()


# list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

## C++ flags applied to all builds
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# ## Set global include paths
set( BMSDI_INCLUDE_DIRS
 	${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories( ${BMSDI_INCLUDE_DIRS} )

#
fips_begin_module( bmsdi_protocol )
  fips_src( lib/ )
fips_end_module()

if( NOT FIPS_IMPORT )

	fips_add_subdirectory("apps/")

	if( FIPS_UNITTESTS )
		gtest_begin( bmsdi_protocol )
		    fips_src(unit/test/)
		    fips_deps( bmsdi_protocol )
		    # include_directories( ${TEST_DATA_DIR} )
		gtest_end()
	endif()

	fips_finish()
endif()
