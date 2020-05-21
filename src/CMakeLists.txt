set(LIB_PROJECT_NAME ${PROJECT_NAME})

file(GLOB perf_srcs "performance/*.cc")
file(GLOB proj_srcs "project/*.cc")

add_library(${PROJECT_NAME} ${proj_srcs} ${perf_srcs})

install(TARGETS ${LIB_PROJECT_NAME}
  RUNTIME DESTINATION bin/${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} 
)