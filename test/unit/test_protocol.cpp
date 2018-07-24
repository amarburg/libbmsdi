
#include <gtest/gtest.h>

#include "libbmsdi/bmsdi_message.h"

struct Fixed16TestData {
    float f;
    int16_t d;
} testData[] = {
  { 0.15, 0x0133 },
  { -0.3, (int16_t)0xfd9a }
};


// Test the float to fixed16 conversion
TEST(TestFixed16Conversions, floatToFixed16) {

  for( unsigned long i = 0; i < (sizeof(testData)/sizeof(Fixed16TestData)); ++i ) {
    int16_t c = floatToFixed16( testData[i].f );

    ASSERT_NEAR( c, testData[i].d, 1 );
  }

}
