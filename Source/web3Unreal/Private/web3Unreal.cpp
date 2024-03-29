// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.
#include "web3Unreal.h"

#define LOCTEXT_NAMESPACE "Fweb3UnrealModule"

void Fweb3UnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void Fweb3UnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fweb3UnrealModule, web3Unreal)