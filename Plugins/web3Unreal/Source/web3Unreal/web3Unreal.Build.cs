// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class web3Unreal : ModuleRules
{
	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/")); }
	}
	private string GetSecpLibraryPath(ReadOnlyTargetRules Target)
	{
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			return Path.Combine(ThirdPartyPath,"lib", "libsecp256k1.lib");
		}

		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			return Path.Combine(ThirdPartyPath,"lib", "libsecp256k1.a");
		}

		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			return Path.Combine(ThirdPartyPath,"lib", "libsecp256k1.a");
		}

		return null;
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
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Http",
				"Json",
				"JsonUtilities"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		
		//PublicAdditionalLibraries.Add("libsecp256k1.a");
		//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory,"lib", "libsecp256k1.a"));
		//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory,"Public", "libsecp256k1.a"));
		string libraryPath = GetSecpLibraryPath(Target);

		if (libraryPath != null)
		{
			PublicAdditionalLibraries.Add(libraryPath);
		}
	}
}
