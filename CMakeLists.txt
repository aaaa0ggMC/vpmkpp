cmake_minimum_required(VERSION 3.10)
project(vpmkpp)

set(CMAKE_CXX_STANDARD 23 )

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--allow-multiple-definition -Wl,--rpath,./") 

aux_source_directory("./src" VPM_SRC)
add_executable(vpmkpp ${VPM_SRC})
set_target_properties(vpmkpp PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(vpmkpp PUBLIC cryptopp)
