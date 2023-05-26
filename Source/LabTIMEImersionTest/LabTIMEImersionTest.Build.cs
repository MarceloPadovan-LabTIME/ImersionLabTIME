// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LabTIMEImersionTest : ModuleRules
{
	public LabTIMEImersionTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"UMG",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"Slate",
			"SlateCore",
			"WidgetModule"
		});

	}
}
