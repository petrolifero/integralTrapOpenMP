cmake_minimum_required(VERSION 3.10)

add_executable(mainMPI mainMPI.c)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
	target_link_libraries(mainMPI PUBLIC OpenMP::OpenMP_CXX)
endif()
