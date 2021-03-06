﻿#ifndef _TEACHING_BOX_T_GRAMMAR_H_
#define _TEACHING_BOX_T_GRAMMAR_H_

#include "TTokenType.h"

class TLexer;
class TAstNode;

class TAstNodeFactory
{
private:
	typedef TTokenType::Type TYPE;

public:
	static const std::shared_ptr<TAstNode> CreateAstFromProject(const QString& project);

	static const std::shared_ptr<TAstNode> GetNode(TLexer* const lexer);

};

#endif