
#include <gtest/gtest.h>

#include "libbmsdi/helpers.h"

struct DecodeModeTestData {
    uint32_t mode;
    VideoModeStruct answer;
} testData[] = {
  { 0x48703239, {30,1,3,0,0} }
};


// Test the float to fixed16 conversion
TEST(TestDecodeMode, testDecodeKnownMode) {

  for( unsigned long i = 0; i < (sizeof(testData)/sizeof(DecodeModeTestData)); ++i ) {
    VideoModeStruct vms;

    ASSERT( decodeBMDMode( testData[i].mode, &vms ) );

    for( uint8_t j = 0; j < 5; ++j )
    ASSERT( testData[i].answer[j], vms[j] );
  }

}

TEST(TestDecodeMode, testDecodeUnknownMode) {
  VideoModeStruct vms;
  ASSERT( decodeBMDMode( 0x69756E6B, &vms ) == false );  // This is actually "bmdModeUnknown"
}
