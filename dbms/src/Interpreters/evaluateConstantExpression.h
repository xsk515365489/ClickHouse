#pragma once

#include <memory>
#include <Core/Block.h>
#include <Core/Field.h>
#include <Parsers/IAST.h>
#include <Parsers/IParser.h>


namespace DB
{

class Context;
class ExpressionActions;
class IDataType;

using ExpressionActionsPtr = std::shared_ptr<ExpressionActions>;

/** Evaluate constant expression and its type.
  * Used in rare cases - for elements of set for IN, for data to INSERT.
  * Quite suboptimal.
  */
std::pair<Field, std::shared_ptr<const IDataType>> evaluateConstantExpression(const ASTPtr & node, const Context & context);


/** Evaluate constant expression
  *  and returns ASTLiteral with its value.
  */
ASTPtr evaluateConstantExpressionAsLiteral(const ASTPtr & node, const Context & context);


/** Evaluate constant expression
  *  and returns ASTLiteral with its value.
  * Also, if AST is identifier, then return string literal with its name.
  * Useful in places where some name may be specified as identifier, or as result of a constant expression.
  */
ASTPtr evaluateConstantExpressionOrIdentifierAsLiteral(const ASTPtr & node, const Context & context);

// FIXME: collapse returned blocks into a single block.
Blocks evaluateConstantExpressionAsBlock(const ASTPtr & node, const ExpressionActionsPtr & target_expr);

}
