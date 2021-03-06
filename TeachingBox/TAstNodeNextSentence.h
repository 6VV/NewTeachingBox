﻿#ifndef _TEACHING_BOX_T_AST_NODE_NEXT_SENTENCE_H_
#define _TEACHING_BOX_T_AST_NODE_NEXT_SENTENCE_H_

#include "TAstNode.h"

class TLexer;

class TAstNodeNextSentence:public TAstNode
{
public:
	TAstNodeNextSentence(const std::shared_ptr<TToken> token = nullptr);
	~TAstNodeNextSentence();

	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer);
	static const std::shared_ptr<TAstNode> GetAstNode(std::shared_ptr<TToken> token);


	virtual ValueReturned Execute() const override;

	virtual void ParseSemantic() const override;

};

#endif