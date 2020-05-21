#####################################################
# This cmake file is just for installation of headers
#####################################################

## math ## 
set(MATH_DIR math)
install(FILES 
  ${MATH_DIR}/math.h
  ${MATH_DIR}/eulers_transform.h
  ${MATH_DIR}/average_quaternion.h
  DESTINATION include/${PROJECT_NAME}/${MATH_DIR})

set(PROJ_DIR project)
install(FILES 
  ${PROJ_DIR}/macro_defines.h
  ${PROJ_DIR}/mutex.h
  ${PROJ_DIR}/time.h
  ${PROJ_DIR}/simple_time.h
  DESTINATION include/${PROJECT_NAME}/${PROJ_DIR})

set(PERF_DIR performance)
install(FILES 
  ${PERF_DIR}/process_info.h
  ${PERF_DIR}/simple_prof.h
  DESTINATION include/${PROJECT_NAME}/${PERF_DIR})