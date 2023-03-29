#pragma once

#include "Json.h"

class HyperPlayUtils
{
public:
	static TSharedPtr<FJsonValue> CreateJsonValue(FString obj);
};