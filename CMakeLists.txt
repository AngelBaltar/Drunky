cmake_minimum_required (VERSION 2.6)
project (Drunky)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/scripts/cmake")
include("${CMAKE_SOURCE_DIR}/scripts/cmake/FindSDL2.cmake")
include("${CMAKE_SOURCE_DIR}/scripts/cmake/FindSDL2_ttf.cmake")
include("${CMAKE_SOURCE_DIR}/scripts/cmake/FindSDL2_image.cmake")


# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_LIBRARY})

# Find SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_TTF_LIBRARY})

# Find SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_IMAGE_LIBRARY})

# Find SDL2_mixer
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIR})
set(LIBS ${LIBS} ${SDL2_MIXER_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall")

#add_definitions(-DRESOURCES=${PROJECT_SOURCE_DIR}/Resources)
#better use relative paths
add_definitions(-DRESOURCES=../../Resources)
#because executables will be on ./build/bin/ or ./executables/platform/

add_executable(${PROJECT_NAME} 
                main.cpp
                utils/Debug.cpp
                GameFrameWork/GameContainer.cpp
                GameFrameWork/GameObject.cpp
		GameFrameWork/TextObject.cpp
                GameFrameWork/GameInfoPrinter.cpp
                GameFrameWork/DrinkObject.cpp
                GameFrameWork/BoardObject.cpp
                GameFrameWork/PointerObject.cpp
                GameFrameWork/GameFactory.cpp)



TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
                        ${LIBS}
                    )
