#pragma once

#include "Json.h"
#include "HyperPlayLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HyperPlayLibraryLog, Display, All);

class UHyperPlayLibrary
{
public:
	static TSharedPtr<FJsonValue> CreateJsonValue(FString obj);
};