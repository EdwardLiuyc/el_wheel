################################
# GTest
################################
add_subdirectory(gtest)
#find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

################################
# Unit Tests
################################
# eulers and transform
add_executable( eulers_transform_test math/eulers_transform_test.cc )
# Link test executable against gtest & gtest_main
target_link_libraries(eulers_transform_test gtest gtest_main)
add_test( eulers_transform_test eulers_transform_test )

# math
add_executable( math_test math/math_test.cc )
target_link_libraries(math_test gtest gtest_main)
add_test( math_test math_test )

# math
add_executable( macro_test project/macro_test.cc )
target_link_libraries(macro_test gtest gtest_main el_wheel_project)
add_test( macro_test macro_test )