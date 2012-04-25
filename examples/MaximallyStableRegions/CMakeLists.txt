
ADD_EXECUTABLE( mser src/MSER.cpp )

TARGET_LINK_LIBRARIES( mser
    ${global_link_libs} ${OPENCV_LIBRARIES}  )
