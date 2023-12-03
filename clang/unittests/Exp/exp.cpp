#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;

class Visitor : public RecursiveASTVisitor<Visitor> {
public:
  explicit Visitor(ASTContext *ctx) : ctx_(ctx) {}
  bool VisitCXXRecordDecl(CXXRecordDecl *dcl) {
    dcl->dump(llvm::outs());
    return true;
  }

  bool VisitFunctionDecl(FunctionDecl *dcl) {
    dcl->dump(llvm::outs());
    return true;
  }

private:
  ASTContext *ctx_;
};

class TranslationUnitConsumer : public clang::ASTConsumer {
public:
  explicit TranslationUnitConsumer(ASTContext *ctx) : visitor_(ctx) {}

  void HandleTranslationUnit(clang::ASTContext &ctx) override {
    visitor_.TraverseDecl(ctx.getTranslationUnitDecl());
  }

private:
  Visitor visitor_;
};

class ExpAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &compiler,
                    llvm::StringRef) override {
    return std::make_unique<TranslationUnitConsumer>(&compiler.getASTContext());
  }
};

int main(int argc, char **argv) {
  const char *code = R"cpp(
type Mat {
    void foo() {}
};

int main() {
  Mat mat;
  Mat* bar = nullptr;
}
    )cpp";
  if (argc == 2) {
    code = argv[1];
  }
  clang::tooling::runToolOnCode(std::make_unique<ExpAction>(), code);
}
