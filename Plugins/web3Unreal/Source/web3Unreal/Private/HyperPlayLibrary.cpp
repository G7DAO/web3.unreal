#include "HyperPlayLibrary.h"

DEFINE_LOG_CATEGORY(HyperPlayLibraryLog);

TSharedPtr<FJsonValue> UHyperPlayLibrary::CreateJsonValue(FString obj) {
	TSharedPtr<FJsonValue> val;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(obj);
	FJsonSerializer::Deserialize(Reader, val);
	return val;
}
