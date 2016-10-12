#ifndef _TEACHING_BOX_T_AST_NODE_GOSUB_SENTENCE_H_
#define _TEACHING_BOX_T_AST_NODE_GOSUB_SENTENCE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TAstNodeGosubSentence.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/10
//  Description:	程序跳转语句，用于跳转到其它文件执行程序
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/10
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TAstNode.h"
#include <memory>

class TAstNodeGosubSentence:public TAstNode
{
public:
	TAstNodeGosubSentence(const std::shared_ptr<TToken> token = nullptr);

	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer);

	virtual ValueReturned Execute() const override;
	virtual void ParseSemantic() const override;

private:
	QString GetDestinationProgramNode() const;

};

#endif