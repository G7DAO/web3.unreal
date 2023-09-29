// Copyright (c) 2023 Game 7 DAO Ltd. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class web3Unreal : ModuleRules
{
	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
	}
	private List<string> GetSecpLibraryPath(ReadOnlyTargetRules Target)
	{
		List<string> secpLibs = new List<string>();
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			secpLibs.Add(Path.Combine(ThirdPartyPath, "lib", "libsecp256k1.lib"));
		}

		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			secpLibs.Add(Path.Combine(ThirdPartyPath, "lib", "libsecp256k1.a"));
		}

		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			if (Target.Architectures.ToString().Contains("x64"))
			{
				secpLibs.Add(Path.Combine(ThirdPartyPath, "lib", "libsecp256k1_mac_x86_64.a"));
			}
			if (Target.Architectures.ToString().Contains("arm64"))
			{
				secpLibs.Add(Path.Combine(ThirdPartyPath, "lib", "libsecp256k1_mac_arm64.a"));
			}
		}

		return secpLibs;
	}
	public web3Unreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ThirdPartyPath,"include")
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Json",
				"Http",
				"JsonUtilities"
				// ... add other public dependencies that you statically link with here ...
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		List<string> libraryPaths = GetSecpLibraryPath(Target);

		foreach (string secpPath in libraryPaths)
		{
			PublicAdditionalLibraries.Add(secpPath);
		}
	}
}
