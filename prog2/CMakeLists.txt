project(Prog2 VERSION ${PROJECT_VERSION})

set(SOURCES_DIR src)
set(PROJ_HEADERS_DIR ${SOURCES_DIR}/headers)

aux_source_directory(${SOURCES_DIR} SRC_FILES)

set(TARGET_NAME prog2)
add_executable(${TARGET_NAME} ${SRC_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
  OUTPUT_NAME ${TARGET_NAME}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${VERSION_MAJOR}
)

target_include_directories(${TARGET_NAME} PUBLIC ${PROJ_HEADERS_DIR})

target_link_libraries(${TARGET_NAME} TestTaskCommon)
