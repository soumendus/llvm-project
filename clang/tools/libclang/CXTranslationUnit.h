//===- CXTranslationUnit.h - Routines for manipulating CXTranslationUnits -===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines routines for manipulating CXTranslationUnits.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_CXTRANSLATIONUNIT_H
#define LLVM_CLANG_CXTRANSLATIONUNIT_H

#include "clang-c/Index.h"

namespace clang {
  class ASTUnit;
  class CIndexer;
  class SimpleFormatContext;
} // namespace clang

struct CXTranslationUnitImpl {
  void *CIdx;
  clang::ASTUnit *TheASTUnit;
  void *StringPool;
  void *Diagnostics;
  void *OverridenCursorsPool;
  clang::SimpleFormatContext *FormatContext;
  unsigned FormatInMemoryUniqueId;
};

namespace clang {
namespace cxtu {

CXTranslationUnitImpl *MakeCXTranslationUnit(CIndexer *CIdx, ASTUnit *AU);

static inline ASTUnit *getASTUnit(CXTranslationUnit TU) {
  return TU->TheASTUnit;
}

class CXTUOwner {
  CXTranslationUnitImpl *TU;
  
public:
  CXTUOwner(CXTranslationUnitImpl *tu) : TU(tu) { }
  ~CXTUOwner();

  CXTranslationUnitImpl *getTU() const { return TU; }

  CXTranslationUnitImpl *takeTU() {
    CXTranslationUnitImpl *retTU = TU;
    TU = 0;
    return retTU;
  }
};


}} // end namespace clang::cxtu

#endif
