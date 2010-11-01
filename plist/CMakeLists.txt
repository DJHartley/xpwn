link_directories (${PROJECT_BINARY_DIR}/common)
add_library(plist plist.c)
target_link_libraries(plist common)

