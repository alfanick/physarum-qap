file(GLOB_RECURSE APPS_SRC_FILES "${PROJECT_SOURCE_DIR}/src/qap/*.cpp")

include_directories(${COMMON_INCLUDES})


add_executable(physarum ${APPS_SRC_FILES} "${PROJECT_SOURCE_DIR}/src/apps/physarum.cpp")
add_executable(physarum-debug ${APPS_SRC_FILES} "${PROJECT_SOURCE_DIR}/src/apps/physarum.cpp")

install(TARGETS physarum DESTINATION bin)
install(TARGETS physarum-debug DESTINATION bin)

target_compile_definitions(physarum PUBLIC -DNODEBUG -DNOLOG)
target_compile_definitions(physarum-debug PUBLIC -DDEBUG -DLOG)
