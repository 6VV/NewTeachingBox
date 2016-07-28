#include "stdafx.h"
#include "TeachingBoxContext.h"


namespace
{
	TeachingBoxContext::ExecuteMode g_executeMode = TeachingBoxContext::AUTO;
}

void TeachingBoxContext::SetExecuteMode(ExecuteMode mode)
{
	g_executeMode = mode;
}
