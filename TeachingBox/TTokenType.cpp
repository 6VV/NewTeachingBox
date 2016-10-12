#include "stdafx.h"
#include "TTokenType.h"

const QHash<QString, TTokenType::Type> TTokenType::STRUCTURE_MAP{
	{ "FOR", STRUCTURE_FOR },
	{"TO", STRUCTURE_TO},
	{"STEP", STRUCTURE_STEP},
	{"NEXT", STRUCTURE_NEXT},
	{"BREAK", STRUCTURE_BREAK},
	{"CONTINUE", STRUCTURE_CONTINUE},
	{"IF", STRUCTURE_IF},
	{"ELSEIF", STRUCTURE_ELSE_IF},
	{"ELSE", STURCTURE_ELSE},
	{"ENDIF", STURCTURE_END_IF},
	{"SWITCH", STURCTURE_SWITCH},
	{"CASE", STURCTURE_CASE},
	{"DEFAULT", STURCTURE_DEFAULT},
	{"ENDSWITCH", STURCTURE_END_SWITCH},
	{"EOF", SEPARATOR_EOF},
	{"GOSUB", STURCTURE_GOSUB},
};

const QHash<QString, TTokenType::Type> TTokenType::MACRO_MAP{
	{"MOVL", MACRO_MOVL},
	{"MOVC", MACRO_MOVC}
};

const QHash<QString, TTokenType::Type> TTokenType::VALUE_MAP{
	{"TRUE", LITERAL_VALUE_TRUE},
	{"FALSE", LITERAL_VALUE_FALSE}
};

QHash<QString, TTokenType::Type> TTokenType::KEY_MAP{};

TTokenType::Initialization TTokenType::initialization{};

TTokenType::Initialization::Initialization()
{
	KEY_MAP.unite(STRUCTURE_MAP);
	KEY_MAP.unite(MACRO_MAP);
	KEY_MAP.unite(VALUE_MAP);
}
