#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Json.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HyperPlayLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HyperPlayLibraryLog, Display, All);

UCLASS()
class UHyperPlayLibrary : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	static TSharedPtr<FJsonValue> CreateJsonValue(FString obj);

};