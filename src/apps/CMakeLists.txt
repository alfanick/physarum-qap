file(GLOB_RECURSE APPS_SRC_FILES "${PROJECT_SOURCE_DIR}/src/qap/*.cpp")

include_directories(${COMMON_INCLUDES})


add_executable(physarum ${APPS_SRC_FILES} "${PROJECT_SOURCE_DIR}/src/apps/physarum.cpp")
add_executable(physarum-tsp ${APPS_SRC_FILES} "${PROJECT_SOURCE_DIR}/src/apps/physarum_tsp.cpp")
add_executable(physarum-debug ${APPS_SRC_FILES} "${PROJECT_SOURCE_DIR}/src/apps/physarum.cpp")
add_executable(physarum-tsp-debug ${APPS_SRC_FILES} "${PROJECT_SOURCE_DIR}/src/apps/physarum_tsp.cpp")

install(TARGETS physarum DESTINATION bin)
install(TARGETS physarum-debug DESTINATION bin)
install(TARGETS physarum-tsp DESTINATION bin)
install(TARGETS physarum-tsp-debug DESTINATION bin)

target_compile_definitions(physarum PUBLIC -DNODEBUG -DNOLOG)
target_compile_definitions(physarum-debug PUBLIC -DDEBUG -DLOG)
target_compile_definitions(physarum-tsp PUBLIC -DNODEBUG -DNOLOG)
target_compile_definitions(physarum-tsp-debug PUBLIC -DDEBUG -DLOG)

