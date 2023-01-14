#pragma once

#include "Modules/ModuleManager.h"

class Fweb3UnrealModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
