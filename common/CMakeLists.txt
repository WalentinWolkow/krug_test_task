project(TestTaskCommon VERSION ${PROJECT_VERSION})

set(SOURCES_DIR src)
set(PROJ_HEADERS_DIR ${SOURCES_DIR}/headers)

file(GLOB SRC_FILES ${SOURCES_DIR}/*.cpp)

set(TARGET_NAME TestTaskCommon)
add_library(${TARGET_NAME} SHARED ${SRC_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${VERSION_MAJOR}
)

target_include_directories(${TARGET_NAME} PUBLIC ${PROJ_HEADERS_DIR})
