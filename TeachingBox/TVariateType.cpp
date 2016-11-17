#include "stdafx.h"
#include "TVariateType.h"


const QString TVariateType::STR_TYPE_INT = "Int";
const QString TVariateType::STR_TYPE_DOUBLE = "Float";
const QString TVariateType::STR_TYPE_STRING = "String";
const QString TVariateType::STR_TYPE_BOOL = "Bool";
const QString TVariateType::STR_TYPE_LABEL = "Label";
const QString TVariateType::STR_TYPE_POSITION = "Position";
const QString TVariateType::STR_TYPE_DYNAMIC = "Velocity";
const QString TVariateType::STR_TYPE_OVERLAP = "Overlap";

const QString TVariateType::STR_BOOL_TRUE = "TRUE";
const QString TVariateType::STR_BOOL_FALSE = "FALSE";
const QString TVariateType::STR_TRANSITION_MODE_ABSOLUTE = "ABSOLUTE";
const QString TVariateType::STR_TRANSITION_MODE_RELATIVE = "RELATIVE";

const QString TVariateType::STR_TYPE_REF_SYS="RefSys";

const QString TVariateType::STR_TYPE_TOOL_SYS="ToolSys";

const QStringList TVariateType::TYPE_COLLECTION{
	STR_TYPE_INT,
	STR_TYPE_DOUBLE,
	STR_TYPE_STRING,
	STR_TYPE_BOOL,
	STR_TYPE_POSITION,
	STR_TYPE_DYNAMIC,
	STR_TYPE_OVERLAP,
	STR_TYPE_REF_SYS,
	STR_TYPE_TOOL_SYS
};

TVariateType::TVariateType()
{

}

TVariateType::~TVariateType()
{

}

const QString TVariateType::STR_CATEGORY_BASE="BASE";
