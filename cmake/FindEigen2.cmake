# - Try to find the Eigen2 headers
# Once done this will define
#  EIGEN2_FOUND - System has Eigen2
#  EIGEN2_INCLUDE_DIRS - The Eigen2 include directories

find_package(PkgConfig)
pkg_check_modules(PC_EIGEN2 eigen2)

find_path(EIGEN2_INCLUDE_DIR Eigen/Eigen
          HINTS ${PC_EIGEN2_INCLUDEDIR} ${PC_EIGEN2_INCLUDE_DIRS}
          PATH_SUFFIXES eigen2 )

set(EIGEN2_INCLUDE_DIRS ${EIGEN2_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set EIGEN2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Eigen2  DEFAULT_MSG
                                  EIGEN2_INCLUDE_DIR)

mark_as_advanced(EIGEN2_INCLUDE_DIR)

