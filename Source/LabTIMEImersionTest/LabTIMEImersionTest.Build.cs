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
			"InputCore" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"WidgetModule"
		});


        //Isso desativará a combinação de arquivos de origem e também informa
		//ao Unreal Build Tool para sempre criar um cabeçalho pré-compilado,
		//o que pode resultar em tempos de iteração muito rápidos.
		//Mas não é garantido.
		//Recomendação do curso Unreal C++ Udemy.
        MinFilesUsingPrecompiledHeaderOverride = 1;

		bFasterWithoutUnity = true;

	}
}
