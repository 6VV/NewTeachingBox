#ifndef _TEACHING_BOX_T_AST_NODE_FOR_SENTENCE_H_
#define _TEACHING_BOX_T_AST_NODE_FOR_SENTENCE_H_

#include "TAstNode.h"
#include "TSymbol.h"

class TLexer;

class TAstNodeForSentence:public TAstNode
{
private:
	typedef TSymbol::SymbolType SYMBOL_TYPE;

public:
	TAstNodeForSentence(const std::shared_ptr<TToken> token = nullptr);
	~TAstNodeForSentence();

	static void UpdateValue(SYMBOL_TYPE type, const QString& scope, const QString& name, double value);

	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer);
	static double GetValue(SYMBOL_TYPE type, const QString& scope, const QString& name);

	virtual ValueReturned Execute() const override;
	virtual void ParseSemantic() const override;
	
private:
	static void AddToNode(TLexer* const lexer, std::shared_ptr<TToken> token, std::shared_ptr<TAstNode> result);
	static void AddStepNode(TLexer* const lexer, std::shared_ptr<TToken> token, std::shared_ptr<TAstNode> result);

};

#endif