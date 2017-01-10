#ifndef _TEACHING_BOX_MACRO_COMMON_H_
#define _TEACHING_BOX_MACRO_COMMON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TAstNodeMacroCommon.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/28
//  Description:    通用型命令，该类依据xml文件中定义的语法，进而进行语法解析、语义分析以及解释执行。
		此类命令仅适用于需要进行远程数据传输的命令
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TAstNode.h"

class TAstNodeMacroCommon:public TAstNode
{
public:
	TAstNodeMacroCommon(const std::shared_ptr<TToken> token = nullptr);

	static const std::shared_ptr<TAstNode> GetAstNode(TLexer* const lexer);

	virtual ValueReturned Execute() const override;

	virtual void ParseSemantic() const override;


private:
	static const std::shared_ptr<TAstNode> GetParameter(TLexer* const lexer);
	static void CheckComma(TLexer* const lexer);
	void CheckParameterType(std::shared_ptr<TAstNode> node, const QString& typeName) const;
	void SendData() const;
};

#endif