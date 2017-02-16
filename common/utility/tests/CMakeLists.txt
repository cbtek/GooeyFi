#==============================================================================
# CMakeLists file for test_common_utils
#==============================================================================
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CURR_TARGET test_common_utils)
set(CURR_TARGET_SOURCES "${CURR_TARGET}_SOURCES")
set(CURR_TARGET_HEADERS"${CURR_TARGET}_HEADERS")

include_directories(src)
include_directories(inc)

#==============================================================================
# Include Source Files
#==============================================================================
file(GLOB CURR_TARGET_SOURCES "src/*.c*")
file(GLOB CURR_TARGET_HEADERS "inc/*.h*")
file(GLOB CURR_TARGET_DATA "data/*.*")

file(COPY ${CURR_TARGET_DATA} DESTINATION ${PROJECT_ROOT}/bin/testData/utility)
#==============================================================================
# Add Library
#==============================================================================
add_executable(${CURR_TARGET}
               ${PLATFORM}
               ${CURR_TARGET_SOURCES}
               ${CURR_TARGET_HEADERS})

add_dependencies(${CURR_TARGET} common_utils)
target_link_libraries(${CURR_TARGET} common_utils)
