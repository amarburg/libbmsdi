
gtest_begin( bmsdi_protocol )
    fips_files(
      test_protocol.cpp
      test_new_config_message.cpp
    )
    fips_deps( bmsdi_protocol )

    include_directories( ${TEST_DATA_DIR} )
gtest_end()
