#include "stdafx.h"
#include "Macro.h"



const QString Macro::CATEGORY_MOVEMENT{ "MOVEMENT" };

const QString Macro::CATEGORY_FUNCTION{ "FUNCTION" };

const QString Macro::CATEGORY_IO{ "IO" };

const QString Macro::CATEGORY_WELD{ "WELD" };

const QString Macro::TYPE_MOVEMENT{ "MOVEMENT" };

const QString Macro::TYPE_MATH{ "MATH" };

const QString Macro::TYPE_STRUCTURE{ "STRUCTURE" };

const QString Macro::TYPE_PROGRAM{ "PROGRAM" };

const QString Macro::TYPE_FUNCTION{ "FUNCTION" };

const QString Macro::TYPE_OTHERS{ "OTHERS" };

const QString Macro::TYPE_DIGITAL{ "DIGITAL" };

const QString Macro::TYPE_ANALOG{ "ANALOG" };

const QString Macro::TYPE_ARC_WELDING{ "ARC WELDING" };

const QString Macro::TYPE_SPOT_WELDING{ "SPOT WELDING" };

const std::vector<QString> Macro::CATEGORYS{
	CATEGORY_MOVEMENT,
	CATEGORY_FUNCTION,
	CATEGORY_IO,
	CATEGORY_WELD
};

const std::map<QString, std::set<QString>> Macro::TYPE_MAP{
	{
		CATEGORY_MOVEMENT,
		std::set<QString>{
			TYPE_MOVEMENT,
		}
	},
	{
		CATEGORY_FUNCTION,
		std::set<QString>{
			TYPE_MATH,
			TYPE_STRUCTURE,
			TYPE_PROGRAM,
			TYPE_FUNCTION,
			TYPE_OTHERS
		}
	},
	{
		CATEGORY_IO,
		std::set<QString>{
			TYPE_DIGITAL,
			TYPE_ANALOG
		}
	},
	{
		CATEGORY_WELD,
		std::set<QString>{
			TYPE_ARC_WELDING,
			TYPE_SPOT_WELDING
		}
	}
};

const QString Macro::MACRO_MOVL{ "MOVL" };

const QString Macro::MACRO_MOVJ{ "MOVJ" };

const QString Macro::MACRO_MOVJX{ "MOVJX" };

const QString Macro::MACRO_MOVC{ "MOVC" };

const QString Macro::MACRO_MOVX{ "MOVX" };

const QString Macro::MACRO_MOVY{ "MOVY" };

const QString Macro::MACRO_MOVZ{ "MOVZ" };

const QString Macro::MACRO_ROTX{ "ROTX" };

const QString Macro::MACRO_ROTY{ "ROTY" };

const QString Macro::MACRO_ROTZ{ "ROTZ" };

const QString Macro::MACRO_SIN{ "SIN" };

const QString Macro::MACRO_COS{ "COS" };

const QString Macro::MACRO_TAN{ "TAN" };

const QString Macro::MACRO_SQRT{ "SQRT" };

const QString Macro::MACRO_GOSUB{ "GOSUB" };

const QString Macro::MACRO_FOR{ "FOR" };

const QString Macro::MACRO_IF{ "IF" };

const QString Macro::MACRO_ELSEIF{ "ELSEIF" };

const QString Macro::MACRO_SWITCH{ "SWITCH" };

const QString Macro::MACRO_CASE{ "CASE" };

const QString Macro::MACRO_BREAK{ "BREAK" };

const QString Macro::MACRO_ABORT{ "ABORT" };

const QString Macro::MACRO_WAIT{ "WAIT" };

const QString Macro::MACRO_SET_TOOLFRAME{ "SET TOOLFRAME" };

const QString Macro::MACRO_SET_USERFRAME{ "SET USERFRAME" };

const QString Macro::MACRO_DIN{ "DIN" };

const QString Macro::MACRO_DOUT{ "DOUT" };

const QString Macro::MACRO_AIN{ "AIN" };

const QString Macro::MACRO_AOUT{ "AOUT" };

const QString Macro::MACRO_ARC_ON{ "ARC ON" };

const QString Macro::MACRO_ARC_OFF{ "ARC OFF" };

const QString Macro::MACRO_SET_ARC{ "SET ARC" };

const QString Macro::MACRO_SPOT_ON{ "SOPT ON" };

const QString Macro::MACRO_SPOT_OFF{ "SPOT OFF" };

const QString Macro::MACRO_SET_SPOT{ "SET SPOT" };

const std::map<QString, std::set<QString>> Macro::MACRO_MAP{
	{
		TYPE_MOVEMENT,
		std::set<QString>{
			MACRO_MOVL,
			MACRO_MOVJ,
			MACRO_MOVJX,
			MACRO_MOVC,
			MACRO_MOVX,
			MACRO_MOVY,
			MACRO_MOVZ,
			MACRO_ROTX,
			MACRO_ROTY,
			MACRO_ROTZ,
		}
	},
	{
		TYPE_MATH,
		std::set<QString>{
			MACRO_SIN,
			MACRO_COS,
			MACRO_TAN,
			MACRO_SQRT
		}
	},
	{
		TYPE_STRUCTURE,
		std::set<QString>{
			MACRO_GOSUB,
			MACRO_FOR,
			MACRO_IF,
			MACRO_ELSEIF,
			MACRO_SWITCH,
			MACRO_CASE,
			MACRO_BREAK,
		}
	},
	{
		TYPE_PROGRAM,
		std::set<QString>{
			MACRO_ABORT
		}
	},
	{
		TYPE_FUNCTION,
		std::set<QString>{
			MACRO_WAIT
		}
	},
	{
		TYPE_OTHERS,
		std::set<QString>{
			MACRO_SET_TOOLFRAME,
			MACRO_SET_USERFRAME
		}
	},

	{
		TYPE_DIGITAL,
		std::set<QString>{
			MACRO_DIN,
			MACRO_DOUT,
			MACRO_AIN,
			MACRO_AOUT
		}
	},
	{
		TYPE_ANALOG,
		std::set<QString>{
			MACRO_AIN,
			MACRO_AOUT
		}
	},

	{
		TYPE_ARC_WELDING,
		std::set<QString>{
			MACRO_ARC_ON,
			MACRO_ARC_OFF,
			MACRO_SET_ARC
		}
	},
	{
		TYPE_SPOT_WELDING,
		std::set<QString>{
			MACRO_SPOT_ON,
			MACRO_SPOT_OFF,
			MACRO_SET_SPOT
		}
	}
};

const std::map<QString, QString> Macro::TEXT_MAP{
	{ MACRO_MOVL, "MOVL *,*,*" },
	{ MACRO_MOVC, "MOVC *,*,*,*" },
	{ MACRO_SIN, "SIN *" },
	{ MACRO_COS, "COS *" },
	{ MACRO_TAN, "TAN *" },
	{ MACRO_SQRT, "SQRT *" },
	{ MACRO_GOSUB, "GOSUB *" },
	{ MACRO_FOR, "FOR *\nNEXT" },
	{ MACRO_IF, "IF *\nENDIF" },
	{ MACRO_ELSEIF, "ELSEIF *" },
	{ MACRO_SWITCH, "SWITCH *\nDEFAULT\nBREAK\nENDSWITCH" },
	{ MACRO_CASE, "CASE *\nBREAK" },
	{ MACRO_BREAK, "BREAK" },
	{ MACRO_ABORT, "ABORT" },
	{ MACRO_WAIT, "WAIT *" },
};
