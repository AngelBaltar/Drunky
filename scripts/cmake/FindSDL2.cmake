FIND_PATH(SDL2_INCLUDE_DIR SDL.h
HINTS
$ENV{SDL2DIR}
PATH_SUFFIXES include/SDL2 include
PATHS
~/Library/Frameworks
/Library/Frameworks
/usr/local/include/SDL2
/usr/include/SDL2
/sw # Fink
/opt/local # DarwinPorts
/opt/csw # Blastwave
/opt
)

FIND_LIBRARY(SDL2_LIBRARY
NAMES SDL2
HINTS
$ENV{SDL2DIR}
PATH_SUFFIXES lib64 lib
PATHS
/sw
/opt/local
/opt/csw
/opt
)

INCLUDE(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)

