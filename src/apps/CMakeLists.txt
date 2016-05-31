file(GLOB APPS_SRC_FILES "${PROJECT_SOURCE_DIR}/src/apps/*.cpp")

include_directories(${COMMON_INCLUDES})

add_executable(physarum "${PROJECT_SOURCE_DIR}/src/apps/physarum.cpp")
target_link_libraries(physarum qap)
install(TARGETS physarum DESTINATION bin)
