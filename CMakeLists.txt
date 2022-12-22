cmake_minimum_required(VERSION 3.25)
project(WatermarkProject LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

#SET("OpenCV_DIR" "/usr/share/OpenCV")
#SET("OpenCV_DIR" "C:/opencv")
find_package( OpenCV REQUIRED )

add_executable(WatermarkProject main.cpp src/ImageEditor.cpp src/ImageEditor.h)
target_link_libraries(WatermarkProject ${OpenCV_LIBS})