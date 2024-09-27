set(LLVM_LINK_COMPONENTS
  Support
)

add_executable(Exp exp.cpp)

if (MSVC)
  target_compile_options(Exp PRIVATE "/EHsc")
endif()

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
