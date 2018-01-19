
# build shared library.
fips_begin_module( bmsdi )
  fips_files( packet.c )

  include_directories( ${BMSDI_INCLUDE_DIRS} )

fips_end_module()
