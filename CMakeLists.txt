cmake_minimum_required( VERSION 2.8)

project(structured_light_generator)

# opencv
set(OpenCV_DIR $ENV{OPENCV_DIR})
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_DIR}/include)
include_directories(${OpenCV_DIR}/include/opencv)
include_directories(${OpenCV_DIR}/include/opencv2)

aux_source_directory(. DIR_SRCS)

set(EXENAME1 structured_light_generator)
add_executable(${EXENAME1} 结构光栅生成器.cpp)
target_link_libraries(${EXENAME1} ${OpenCV_LIBS})

set(EXENAME2 generate_gray_codes)
add_executable(${EXENAME2} 格雷码生成.cpp)
target_link_libraries(${EXENAME2} ${OpenCV_LIBS})

set(EXENAME3 encoder_gray_code)
add_executable(${EXENAME3} EncoderGrayCode.cpp EncoderGrayCode.h)
target_link_libraries(${EXENAME3} ${OpenCV_LIBS})

set(EXENAME4 gray_code_test)
add_executable(${EXENAME4} 格雷码测试.cpp)
target_link_libraries(${EXENAME4} ${OpenCV_LIBS})

