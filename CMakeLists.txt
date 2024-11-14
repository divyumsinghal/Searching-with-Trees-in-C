cmake_minimum_required(VERSION 3.15)


project(BST C)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(COPY ${CMAKE_SOURCE_DIR}/db DESTINATION ${CMAKE_BINARY_DIR})

add_executable( task1
				bst.c
				bst.h
				task1.c
)

add_executable( task2
				bstdb.c
				bstdb.h
				bstdb2.c
				bstdb2.h
				task2.c
				${CMAKE_SOURCE_DIR}/db/database.c
				${CMAKE_SOURCE_DIR}/db/listdb.c
				${CMAKE_SOURCE_DIR}/db/profiler.c
				${CMAKE_SOURCE_DIR}/db/database.h
				${CMAKE_SOURCE_DIR}/db/listdb.h
				${CMAKE_SOURCE_DIR}/db/profiler.h
)
