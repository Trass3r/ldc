//===-- gen/arrays.h - D array codegen helpers ------------------*- C++ -*-===//
//
//                         LDC – the LLVM D compiler
//
// This file is distributed under the BSD-style LDC license. See the LICENSE
// file for details.
//
//===----------------------------------------------------------------------===//
//
// Helper functions for manipulating D dynamic array (slice) types/values.
//
//===----------------------------------------------------------------------===//

#ifndef LDC_GEN_ARRAYS_H
#define LDC_GEN_ARRAYS_H

#include "lexer.h"
#include "gen/llvm.h"

class ArrayInitializer;
class ArrayLiteralExp;
class DSliceValue;
class DValue;
class Expression;
struct IRState;
struct Loc;
class Type;

llvm::StructType* DtoArrayType(Type* arrayTy);
llvm::StructType* DtoArrayType(LLType* elemTy);
llvm::ArrayType* DtoStaticArrayType(Type* sarrayTy);

LLType* DtoConstArrayInitializerType(ArrayInitializer* arrinit);
LLConstant* DtoConstArrayInitializer(ArrayInitializer* si);
LLConstant* DtoConstSlice(LLConstant* dim, LLConstant* ptr, Type *type = 0);

/// Returns whether the array literal can be evaluated to a (LLVM) constant.
bool isConstLiteral(ArrayLiteralExp* ale);

/// Returns the constant for the given array literal expression.
llvm::Constant* arrayLiteralToConst(IRState* p, ArrayLiteralExp* ale);

/// Initializes a chunk of memory with the contents of an array literal.
///
/// dstMem is expected to be a pointer to the array allocation.
void initializeArrayLiteral(IRState* p, ArrayLiteralExp* ale, LLValue* dstMem);

void DtoArrayCopySlices(Loc& loc, DSliceValue* dst, DSliceValue* src);
void DtoArrayCopyToSlice(Loc& loc, DSliceValue* dst, DValue* src);

void DtoArrayInit(Loc& loc, DValue* array, DValue* value, int op);
Type *DtoArrayElementType(Type *arrayType);
bool arrayNeedsPostblit(Type *t);
void DtoArrayAssign(Loc& loc, DValue *from, DValue *to, int op);
void DtoArraySetAssign(Loc& loc, DValue *array, DValue *value, int op);
void DtoSetArray(DValue* array, LLValue* dim, LLValue* ptr);
void DtoSetArrayToNull(LLValue* v);

DSliceValue* DtoNewDynArray(Loc& loc, Type* arrayType, DValue* dim, bool defaultInit=true);
DSliceValue* DtoNewMulDimDynArray(Loc& loc, Type* arrayType, DValue** dims, size_t ndims, bool defaultInit=true);
DSliceValue* DtoResizeDynArray(Loc& loc, Type* arrayType, DValue* array, llvm::Value* newdim);

void DtoCatAssignElement(Loc& loc, Type* type, DValue* arr, Expression* exp);
DSliceValue* DtoCatAssignArray(Loc& loc, DValue* arr, Expression* exp);
DSliceValue* DtoCatArrays(Loc& loc, Type* type, Expression* e1, Expression* e2);
DSliceValue* DtoAppendDCharToString(Loc& loc, DValue* arr, Expression* exp);
DSliceValue* DtoAppendDCharToUnicodeString(Loc& loc, DValue* arr, Expression* exp);

void DtoStaticArrayCopy(LLValue* dst, LLValue* src);

LLValue* DtoArrayEquals(Loc& loc, TOK op, DValue* l, DValue* r);
LLValue* DtoArrayCompare(Loc& loc, TOK op, DValue* l, DValue* r);

LLValue* DtoDynArrayIs(TOK op, DValue* l, DValue* r);

LLValue* DtoArrayCastLength(Loc& loc, LLValue* len, LLType* elemty, LLType* newelemty);

LLValue* DtoArrayLen(DValue* v);
LLValue* DtoArrayPtr(DValue* v);

DValue* DtoCastArray(Loc& loc, DValue* val, Type* to);

// generates an array bounds check
void DtoArrayBoundsCheck(Loc& loc, DValue* arr, DValue* index, DValue* lowerBound = 0);

#endif // LDC_GEN_ARRAYS_H
