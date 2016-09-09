#ifndef _TEACHING_BOX_T_AST_NODE_OPERATOR_H_
#define _TEACHING_BOX_T_AST_NODE_OPERATOR_H_

#include "TAstNode.h"
#include <memory>
#include "TSymbol.h"

class TLexer;

class TAstNodeOperator:public TAstNode
{
private:
	typedef TSymbol::SymbolType SYMBOL_TYPE;

public:
	TAstNodeOperator(const std::shared_ptr<TToken> token = nullptr);
	~TAstNodeOperator();

	virtual ValueReturned Execute() const override;


	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer);
	static const SYMBOL_TYPE GetSymbolType(const std::shared_ptr<TAstNode>& node);

private:
	static const std::shared_ptr<TAstNode> GetNode(const std::shared_ptr<TToken>& token);
	static const int GetPriority(const TOKEN_TYPE type);
	static const bool IsLeftAssociativity(const TOKEN_TYPE type);
	static const bool IsExistOperator(const TOKEN_TYPE type);
	static const std::shared_ptr<TAstNode> GetValue(TLexer* const lexer);
	static const std::shared_ptr<TAstNode> GetShiftOperator(const std::shared_ptr<TAstNode>& leftValue,
		const std::shared_ptr<TAstNode>& leftOper, TLexer* const lexer);

	static const std::shared_ptr<TAstNode> PeekOperator(TLexer* const lexer);

	static const bool IsRightExpr(const std::shared_ptr<TAstNode>& leftOper, const std::shared_ptr<TAstNode>& rightOper);

private:
	static const SYMBOL_TYPE GetNonTerminalSymbol(const std::shared_ptr<TAstNode>& node);
	static const SYMBOL_TYPE GetTerminalSymbolType(const std::shared_ptr<TAstNode>& node);

	ValueReturned ReturnValue(const TAstNode* const node) const;
	ValueReturned ReturnTerminalValue(const TAstNode* const node) const;
	ValueReturned ReturnNonTerminalValue(const TAstNode* const node) const;


private:
	struct OperatorProperty 
	{
		OperatorProperty(){};
		OperatorProperty(const int p, const bool l);
		int priority=0;
		bool isLeft = true;
	};

	static QHash<TOKEN_TYPE, OperatorProperty> m_operatorProperties;
	
	class Inilization
	{
	public:
		Inilization();
	};
	static Inilization m_inilization;
};

#endif