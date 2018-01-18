include_directories( ${CMAKE_SOURCE_DIR}/lib )

file( GLOB UNIT_TEST_SRCS test_*.cpp )


gtest_begin( bmsdi )
    fips_files(
      ${UNIT_TEST_SRCS}
    )
    fips_deps( bm_sdi_camera_control )

    include_directories( ${TEST_DATA_DIR} )
gtest_end()

# Don't use ctest, instead just execture the Google test binaries
# add_custom_target( unit_test
#                     COMMAND ./videoio_test
#                     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin
#                     DEPENDS videoio_test )
