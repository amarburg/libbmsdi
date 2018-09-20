#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// The BM API maps a variety of non-linear values (sensor gain, ISO, etc)
// onto linear, integer values for transmission in the API.

//== Constants for handling sensor gain ordinal ==

typedef enum {
  BM_SENSOR_GAIN_MINUS_12DB = 1,
  BM_SENSOR_GAIN_MINUS_6DB = 2,
  BM_SENSOR_GAIN_ZERO_DB = 4,
  BM_SENSOR_GAIN_PLUS_6DB = 8,
  BM_SENSOR_GAIN_PLUS_12DB = 16,
  BM_SENSOR_GAIN_MAX = 16
} BmSensorGainOrd;

struct BmSensorGainRef {
#ifdef __cplusplus
  typedef BmSensorGainOrd OrdType;
  typedef int ValType;
#endif

  BmSensorGainOrd ord;
  int             val;
};

static const BmSensorGainRef BmSensorGainTable[] = {
  { BM_SENSOR_GAIN_MINUS_12DB, -12 },
  { BM_SENSOR_GAIN_MINUS_6DB,   -6 },
  { BM_SENSOR_GAIN_ZERO_DB,      0 },
  { BM_SENSOR_GAIN_PLUS_6DB,     6 },
  { BM_SENSOR_GAIN_MAX,         12 }
};

static const size_t BmSensorGainTableLen = (sizeof(BmSensorGainTable)/sizeof(BmSensorGainRef));

//== Constants for handling f-stop ==
// f-stops are all designated by the denominator e.g. BM_FSTOP_1_4 == f/1.4

typedef enum {
  BM_FSTOP_1_4 = 1
} BmApertureOrd;

struct BmApertureRef {
#ifdef __cplusplus
  typedef BmApertureOrd OrdType;
  typedef float ValType;
#endif

  BmApertureOrd   ord;
  float           val;
  const char     *str;
};

static const BmApertureRef BmApertureTable[] = {
  { BM_FSTOP_1_4, 1.4, "f/1.4" }
};

static const size_t BmApertureTableLen = (sizeof(BmApertureTable)/sizeof(BmApertureRef));

#ifdef __cplusplus
}
#endif
