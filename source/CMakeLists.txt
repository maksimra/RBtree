add_executable (RBtree
                compare.cpp
                main.cpp
)

target_link_libraries (RBtree PRIVATE rb_tree_lib)

target_include_directories (RBtree PUBLIC ${PROJECT_SOURCE_DIR})
