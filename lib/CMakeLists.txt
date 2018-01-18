# Set source files
file(GLOB BMSDI_SRC_FILES *.c )

# build shared library.
fips_begin_module( bm_sdi_camera_control )
  fips_files( ${BMSDI_SRC_FILES} )

  include_directories( ${BMSDI_INCLUDE_DIRS} )

fips_end_module()
