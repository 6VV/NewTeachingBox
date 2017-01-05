#ifndef _TEACHING_BOX_T_TOKEN_TYPE_H_
#define _TEACHING_BOX_T_TOKEN_TYPE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TTokenType.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/09
//  Description:	记录Token的类型及分类 
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QHash"

class TTokenType
{
public:
	enum Type
	{
		ID = 1,

		LITERAL_INTERGER = 100,
		LITERAL_DOUBLE,
		LITERAL_BOOL,
		LITERAL_STRING,

		LITERAL_VALUE_TRUE,
		LITERAL_VALUE_FALSE,

		OPERATOR_PLUS = 200,
		OPERATOR_MINUS,
		OPERATOR_MULTIPLY,
		OPERATOR_DIVIDE,
		OPERATOR_POWER,
		OPERATOR_PERCENT,

		OPERATOR_AND,
		OPERATOR_OR,

		OPERATOR_EQUAL,
		OPERATOR_NOT_EQUAL,
		OPERATOR_GREATE_THAN,
		OPERATOR_GREATE_EQUAL,
		OPERATOR_LESS_THAN,
		OPERATOR_LESS_EQUAL,

		OPERATOR_ASSIGN,
		OPERATOR_NEGATION,
		OPERATOR_NEGATIVE,

		OPERATOR_LEFT_BRACKET,
		OPERATOR_RIGHT_BRACKET,
		OPERATOR_LEFT_BRACE,
		OPERATOR_RIGHT_BRACE,

		SEPARATOR_EOL = 300,
		SEPARATOR_EOF,
		SEPARATOR_COMMA,

		STRUCTURE_FOR = 500,
		STRUCTURE_TO,
		STRUCTURE_STEP,
		STRUCTURE_NEXT,
		STRUCTURE_BREAK,
		STRUCTURE_CONTINUE,
		STRUCTURE_IF,
		STRUCTURE_THEN,
		STRUCTURE_ELSE_IF,
		STURCTURE_ELSE,
		STURCTURE_END_IF,
		STURCTURE_SWITCH,
		STURCTURE_CASE,
		STURCTURE_DEFAULT,
		STURCTURE_END_SWITCH,
		STURCTURE_GOSUB,

		//MACRO_MOVL = 600,
		//MACRO_MOVC,
	};

	//static const QHash<QString, Type> STRUCTURE_MAP;
	//static const QHash<QString, Type> MACRO_MAP;
	//static const QHash<QString, Type> VALUE_MAP;

	static QHash<QString, Type> KEY_MAP;
	
//private:
//	class Initialization
//	{
//	public:
//		Initialization();
//	};
//
//	static Initialization initialization;
};


#endif