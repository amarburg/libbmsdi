
gtest_begin( bmsdi )
    fips_files(
      test_protocol.cpp
      test_new_cmd_packet.cpp
      test_new_config_packet.cpp
      test_new_config_helpers.cpp
    )
    fips_deps( bmsdi )

    include_directories( ${TEST_DATA_DIR} )
gtest_end()
