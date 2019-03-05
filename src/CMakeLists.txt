set(LIB_PROJECT_NAME ${PROJECT_NAME}_project)
set(PROJECT_SRCS 
  project/macro_defines.cc
  project/time.cc)
add_library(${LIB_PROJECT_NAME} ${PROJECT_SRCS})