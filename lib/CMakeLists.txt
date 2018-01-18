
# build shared library.
fips_begin_module( bm_sdi_camera_control )
  fips_files( packet.c )

  include_directories( ${BMSDI_INCLUDE_DIRS} )

fips_end_module()
