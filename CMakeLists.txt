cmake_minimum_required(VERSION 3.25)

set(NAME calculator)
project(NAME)

file(GLOB_RECURSE source_files
    "src/*.cpp"
)
add_executable(${NAME} ${source_files})

target_include_directories(${NAME} PRIVATE 
    "include/"
)

target_compile_features(${NAME} PRIVATE cxx_std_20)