// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AgainOneMoreTime : ModuleRules
{
	public AgainOneMoreTime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
            "AgainOneMoreTime/Public/Player",
            "AgainOneMoreTime/Public/Dev",
            "AgainOneMoreTime/Public/Light",
            "AgainOneMoreTime/Public/Components",
            "AgainOneMoreTime/Public/Weapons",
            "AgainOneMoreTime/Public/Animations",
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
