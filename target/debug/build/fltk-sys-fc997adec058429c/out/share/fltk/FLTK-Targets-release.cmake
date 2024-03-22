#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fltk::z" for configuration "Release"
set_property(TARGET fltk::z APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk::z PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfltk_z.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk::z )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk::z "${_IMPORT_PREFIX}/lib/libfltk_z.a" )

# Import target "fltk::png" for configuration "Release"
set_property(TARGET fltk::png APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk::png PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfltk_png.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk::png )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk::png "${_IMPORT_PREFIX}/lib/libfltk_png.a" )

# Import target "fltk::jpeg" for configuration "Release"
set_property(TARGET fltk::jpeg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk::jpeg PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfltk_jpeg.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk::jpeg )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk::jpeg "${_IMPORT_PREFIX}/lib/libfltk_jpeg.a" )

# Import target "fltk::fltk" for configuration "Release"
set_property(TARGET fltk::fltk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk::fltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfltk.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk::fltk )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk::fltk "${_IMPORT_PREFIX}/lib/libfltk.a" )

# Import target "fltk::forms" for configuration "Release"
set_property(TARGET fltk::forms APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk::forms PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfltk_forms.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk::forms )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk::forms "${_IMPORT_PREFIX}/lib/libfltk_forms.a" )

# Import target "fltk::images" for configuration "Release"
set_property(TARGET fltk::images APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk::images PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfltk_images.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk::images )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk::images "${_IMPORT_PREFIX}/lib/libfltk_images.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
