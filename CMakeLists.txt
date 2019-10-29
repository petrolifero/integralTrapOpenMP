cmake_minimum_required(VERSION 3.10)

add_custom_target(todos)


add_executable(mainOpenMP mainOpenMP.c)
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
	target_link_libraries(mainOpenMP PUBLIC OpenMP::OpenMP_CXX)
endif()


add_executable(mainMPI mainMPI.c)
find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_link_libraries(mainMPI ${MPI_C_LIBRARIES})

add_dependencies(todos mainOpenMP mainMPI)
