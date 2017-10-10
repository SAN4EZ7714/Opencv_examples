project( example )
find_package( OpenCV REQUIRED )

add_executable( example main.cpp )
target_link_libraries( example ${OpenCV_LIBS} )