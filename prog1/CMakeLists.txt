project(Prog1 VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

set(SOURCES_DIR src)

aux_source_directory(${SOURCES_DIR} SRC_FILES)

set(TARGET_NAME prog1)
add_executable(${TARGET_NAME} ${SRC_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
  OUTPUT_NAME ${TARGET_NAME}-${VERSION_MAJOR}.${VERSION_MINOR}
)

target_link_libraries(${TARGET_NAME} TestTaskCommon)

install(TARGETS ${TARGET_NAME} DESTINATION ${BINARY_DEPLOY_DIR})
