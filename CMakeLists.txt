cmake_minimum_required(VERSION 3.1.0)
project (Teste)

# OpenCV
find_package(OpenCV REQUIRED core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

# Código fonte
file(GLOB SRC *.cpp *.h)

# Executável
add_executable(Teste ${SRC})

set_target_properties(Teste PROPERTIES OUTPUT_NAME teste)
set_target_properties(Teste PROPERTIES OUTPUT_NAME_DEBUG tested)

# Bibliotecas
target_link_libraries(Teste ${OpenCV_LIBS})