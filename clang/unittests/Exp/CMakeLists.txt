set(LLVM_LINK_COMPONENTS
  Support
)

add_executable(Exp exp.cpp)

clang_target_link_libraries(Exp
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangDriver
  clangFrontend
  clangSerialization
  clangToolingCore
  clangTooling
)
