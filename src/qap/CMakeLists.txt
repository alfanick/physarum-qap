set(QAP_INCLUDES "${PROJECT_SOURCE_DIR}/src/qap")
file(GLOB_RECURSE QAP_SRC_FILES "${PROJECT_SOURCE_DIR}/src/qap/*.cpp")

include_directories(${COMMON_INCLUDES} ${QAP_INCLUDES})

add_library(qap SHARED ${QAP_SRC_FILES})

install(TARGETS qap DESTINATION bin)
