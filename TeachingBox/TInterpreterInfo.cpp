#include "stdafx.h"
#include "TInterpreterInfo.h"
#include "TInterpreterException.h"


QString TInterpreterInfo::GetInfo(int id)
{
	switch (static_cast<TInterpreterException::InterpreterExceptionCode>(id))
	{
	case TInterpreterException::FOR_SENTENCE_SHOULD_END_WITH_NEXT:return tr("for sentence should end with next"); 
	case TInterpreterException::FOR_SENTENCE_SHOULD_USE_INTERGER_OR_DOUBLE: return tr("for sentence should use interger or double"); 
	case TInterpreterException::IF_SENTENCE_SHOULD_END_WITH_ENDIF: return tr("if sentence should end with endif");
	case TInterpreterException::IF_SENTENCE_SHOULD_WITH_BOOL: return  tr("if sentence should  with bool");
	case TInterpreterException::LOSE_COMMA: return tr("lose comma");
	case TInterpreterException::MOVL_SHOULD_WITH_POSITOIN_DYNAMIC_OVERLAP: return  tr("movl should should be with position,dynamic,overlap");
	case TInterpreterException::MISS_LEFT_BRACE: return  tr("miss left brace");
	case TInterpreterException::MISS_RIGHT_BRACE: return tr("miss right brace");
	case TInterpreterException::NOT_FIND_RIGHT_BRACKET: return  tr("not find right bracket");
	case TInterpreterException::NEGATION_SHOULD_WITH_BOOL: return  "\"!\"" + tr("should with bool");
	case TInterpreterException::NEGATIVE_SHOULD_WITH_INT_OR_DOUBLE: return  "\"-\" " + tr("should with integer or double");
	case TInterpreterException::NOT_FIND_VARIATE: return tr("not find variate");
	case TInterpreterException::NOT_MOVL_SENTENCE: return  tr("not movl sentence");
	case TInterpreterException::NOT_PROGRAM_NAME: return  tr("not program name");
	case TInterpreterException::ONLY_NUMBER_COULD_TAKE_ARITHMETICAL_OPERATION: return  tr("only number could take part in arithmetical opration");
	case TInterpreterException::ONLY_NUMBER_COULD_TAKE_RELATIONAL_OPERATION: return  tr("only number could take part in relational opration");
	case TInterpreterException::ONLY_BOOL_COULD_TAKE_LOGICAL_OPERATION: return tr("only bool could take part in logical opration");
	case TInterpreterException::ONLY_INTERGER_COULD_TAKE_MOD_OPERATION: return  tr("only interger could take part in mod opration");
	case TInterpreterException::SENTENCE_NOT_END_WITH_ABNORMAL_END: return  tr("sentence not end with abnormal end");
	case TInterpreterException::SENTENCE_SHOULD_END_WITH_LINE_BREAK: return tr("sentence should end with line break");
	case TInterpreterException::TYPE_NOT_MATCH: return  tr("type not match");
	case TInterpreterException::UNKNOWN_SENTENCE: return  tr("unknown sentence");
	case TInterpreterException::UNKNOWN_VARIATE: return  tr("unknown variate");
	case TInterpreterException::UNKNOWN_TOKEN: return  tr("unknown token");
	case TInterpreterException::WRONG_GRAMMAR: return tr("wrong grammar");
	case TInterpreterException::WRONG_PARAMETER: return  tr("wrong parameter");
	default:return{};
	}
}

QString TInterpreterInfo::InformationText()
{
	return tr("Information");
}

QString TInterpreterInfo::ProgramText()
{
	return tr("Program");
}

QString TInterpreterInfo::LineNumberText()
{
	return tr("Line Number");
}
