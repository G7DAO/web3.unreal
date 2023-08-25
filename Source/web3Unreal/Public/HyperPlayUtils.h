// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once

#include "Json.h"

/**
* Static class of useful HyperPlay specific utilities.
*/
class HyperPlayUtils
{
public:
    /**
	* Parse an object string into a JSON value.
	*/
	static TSharedPtr<FJsonValue> CreateJsonValue(FString obj);

    /**
	* Determine if a status code integer represents a successful HTTP response code.
	*/
	static bool StatusCodeIsSuccess(int32 statusCode);
};