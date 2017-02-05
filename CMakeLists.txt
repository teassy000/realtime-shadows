cmake_minimum_required (VERSION 2.6)

# set solution name
project (rtsp)

# only support windows system
if(NOT WIN32)
   MESSAGE(FATAL_ERROR "The operating system *MUST* be Windows!")
endif(NOT WIN32)

# add subfolders
add_subdirectory(src)


