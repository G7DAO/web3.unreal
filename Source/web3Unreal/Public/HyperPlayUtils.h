// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once

#include "Json.h"

class HyperPlayUtils
{
public:
	static TSharedPtr<FJsonValue> CreateJsonValue(FString obj);

	static bool StatusCodeIsSuccess(int32 statusCode);
};