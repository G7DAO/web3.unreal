// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#pragma once

#include "Modules/ModuleManager.h"

class Fweb3UnrealModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
