// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TProject : ModuleRules
{
	public TProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore",
				"EnhancedInput",
                "Niagara"
            });

		PublicIncludePaths.AddRange(new string[]
		{
			//"EnhancedInput/Public",
            "TProject/Public/",
            "TProject/Public/GameCore/",
            "TProject/Public/UI/",
            "TProject/Public/UI/MenuUI/"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"Slate",
			"SlateCore",
            "EnhancedInput",
            "Niagara"
        });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
