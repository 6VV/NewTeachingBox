#include "TLexerTests.h"
#include "..\TeachingBox\TLexer.h"
#include "..\TeachingBox\TToken.h"
#include "..\TeachingBox\TInterpreterException.h"
#include "..\TeachingBox\TTokenWithValue.h"
#include <gtest\gtest.h>

TEST_F(TLexerTests, Parse_ParseDigit_Equal)
{
	try
	{
		QString text("123  231\t1.232");
		TLexer lexer(text);
		double num[3][2]{{TYPE::LITERAL_INTERGER, 123},
		{ TYPE::LITERAL_INTERGER, 231 },
		{ TYPE::LITERAL_DOUBLE, 1.232 }};

		auto ptr = lexer.GetToken();
		EXPECT_EQ(ptr->Type(), num[0][0]) << "Not Interger";
		EXPECT_EQ(static_cast<TTokenWithValue<int>*>(ptr.get())->GetValue(), num[0][1]);

		ptr = lexer.GetToken();
		EXPECT_EQ(ptr->Type(), num[1][0]) << "Not Interger";
		EXPECT_EQ(static_cast<TTokenWithValue<int>*>(ptr.get())->GetValue(), num[1][1]);

		ptr = lexer.GetToken();
		EXPECT_EQ(ptr->Type(), num[2][0]) << "Not Double";
		EXPECT_EQ(static_cast<TTokenWithValue<double>*>(ptr.get())->GetValue(), num[2][1]);
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString();
	}
}

TEST_F(TLexerTests, Parse_ParseId_Equal)
{
	try{
		QString text("abc _de d21");
		TLexer lexer(text);
		QStringList strList{ "abc", "_de", "d21" };

		auto ptr = lexer.GetToken();
		int index = 0;
		while (ptr->Type() != TYPE::SEPARATOR_EOF)
		{
			EXPECT_EQ(ptr->Type(), TYPE::ID) << "Not ID";
			QString c = ptr->Name();
				//dynamic_cast<TTokenWithValue<QString>*>(ptr.get())->GetValue();
			EXPECT_STREQ(c.toStdString().c_str(), strList.at(index).toStdString().c_str());
			++index;
			ptr = lexer.GetToken();
		}
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString();
	}
}

TEST_F(TLexerTests, Parse_ParseKeyWord_Equal)
{
	try{
		QString text(" IF NEXT");
		TLexer lexer(text);
		QStringList strList{  "IF", "NEXT" };

		auto ptr = lexer.GetToken();
		EXPECT_EQ(ptr->Type(), TYPE::STRUCTURE_IF) << "Not IF";

		ptr = lexer.GetToken();
		EXPECT_EQ(ptr->Type(), TYPE::STRUCTURE_NEXT) << "Not NEXT";

	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString();
	}
}

TEST_F(TLexerTests, Parse_ParseOtherWord_Equal)
{
	try
	{
		QString text{ "* + - /    ^ % \n &    | !> !< !=    > >= < <=    = == ( )" };
		int test[]{TYPE::OPERATOR_MULTIPLY, TYPE::OPERATOR_PLUS, TYPE::OPERATOR_MINUS,TYPE::OPERATOR_DIVIDE,
			TYPE::OPERATOR_POWER, TYPE::OPERATOR_PERCENT,TYPE::SEPARATOR_EOL, TYPE::OPERATOR_AND,
			TYPE::OPERATOR_OR,TYPE::OPERATOR_LESS_EQUAL, TYPE::OPERATOR_GREATE_EQUAL, TYPE::OPERATOR_NOT_EQUAL,
			TYPE::OPERATOR_GREATE_THAN, TYPE::OPERATOR_GREATE_EQUAL, TYPE::OPERATOR_LESS_THAN,TYPE::OPERATOR_LESS_EQUAL, 
			TYPE::OPERATOR_ASSIGN, TYPE::OPERATOR_EQUAL,TYPE::OPERATOR_LEFT_BRACKET, TYPE::OPERATOR_RIGHT_BRACKET};

		TLexer lexer(text);
		int index = 0;
		auto ptr = lexer.GetToken();
		while (ptr->Type() != TYPE::SEPARATOR_EOF)
		{
			EXPECT_EQ(ptr->Type(), test[index]);
			++index;
			ptr = lexer.GetToken();
		}
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString();
	}

}

TEST_F(TLexerTests, Parse_ParseString_Equal)
{
	try
	{
		QString text("\"hello world\"");
		QString strVerify("hello world");

		TLexer lexer(text);
		auto ptr = lexer.GetToken();

		EXPECT_STREQ(strVerify.toStdString().c_str(), /*(static_cast<TTokenWithValue<QString>*>(ptr.get()))->GetValue()*/ptr->Name().toStdString().c_str());
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString().c_str();
	}

}

TEST_F(TLexerTests, Parse_ParseNote_Skip)
{
	try
	{
		QString text("\\\\hello world");

		TLexer lexer(text);
		auto ptr = lexer.GetToken();

		if (ptr->Type() != TYPE::SEPARATOR_EOF)
		{
			FAIL() << "Not nullptr";
		}
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString().c_str();
	}
}

TEST_F(TLexerTests, Parse_ParseForbid_Skip)
{
	try
	{
		QString text1("#hello world");
		TLexer lexer1(text1);

		if (lexer1.GetToken()->Type() != TYPE::SEPARATOR_EOF)
		{
			FAIL() << "Not nullptr";
		}

		QString text2("#hello \nworld");
		TLexer lexer2(text2);
		EXPECT_EQ(lexer2.GetToken()->Type(), TYPE::SEPARATOR_EOL);
		EXPECT_EQ(lexer2.GetToken()->Type(), TYPE::ID);
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString().c_str();
	}
}

TEST_F(TLexerTests, Parse_ParseReserveValue_Equal)
{
	try
	{
		QString text("TRUE FALSE");
		TLexer lexer(text);

		EXPECT_EQ(lexer.GetToken()->Type(), TYPE::LITERAL_VALUE_TRUE);
		EXPECT_EQ(lexer.GetToken()->Type(), TYPE::LITERAL_VALUE_FALSE);
	}
	catch (TInterpreterException& e)
	{
		FAIL() << e.Info().toStdString().c_str();
	}
}