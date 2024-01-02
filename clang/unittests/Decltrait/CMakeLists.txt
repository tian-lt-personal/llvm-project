set(LLVM_LINK_COMPONENTS
  Support
)

add_executable(Decltrait dt_exp.cpp)

if (MSVC)
  target_compile_options(Decltrait PRIVATE "/EHsc")
endif()

clang_target_link_libraries(Decltrait
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
