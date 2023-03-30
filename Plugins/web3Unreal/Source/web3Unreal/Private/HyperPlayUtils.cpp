#include "HyperPlayUtils.h"

TSharedPtr<FJsonValue> HyperPlayUtils::CreateJsonValue(FString obj) {
	TSharedPtr<FJsonValue> val;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(obj);
	FJsonSerializer::Deserialize(Reader, val);
	return val;
}

bool HyperPlayUtils::StatusCodeIsSuccess(int32 statusCode)
{
	if (statusCode > 199 && statusCode < 300)
	{
		return true;
	}
	return false;
}