project(Prog1 VERSION ${PROJECT_VERSION})

set(SOURCES_DIR src)

aux_source_directory(${SOURCES_DIR} SRC_FILES)

set(TARGET_NAME prog1)
add_executable(${TARGET_NAME} ${SRC_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
  OUTPUT_NAME ${TARGET_NAME}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${VERSION_MAJOR}
)

target_link_libraries(${TARGET_NAME} TestTaskCommon)
