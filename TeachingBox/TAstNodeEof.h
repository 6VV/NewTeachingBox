#ifndef _TEACHING_BOX_T_AST_NODE_EOF_H_
#define _TEACHING_BOX_T_AST_NODE_EOF_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TAstNodeEof.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/23
//  Description:    文档结束节点，用于控制文档结束后的操作
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/23
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TAstNode.h"


class TAstNodeEof:public TAstNode
{
public:
	TAstNodeEof(const std::shared_ptr<TToken> token = nullptr);
	~TAstNodeEof()=default;

	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer);

	virtual TAstNode* FindNextValidNode() const override;

	virtual ValueReturned Execute() const override;

	virtual void ParseSemantic() const override;


private:
};

#endif