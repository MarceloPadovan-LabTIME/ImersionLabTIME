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


        //Isso desativar� a combina��o de arquivos de origem e tamb�m informa
		//ao Unreal Build Tool para sempre criar um cabe�alho pr�-compilado,
		//o que pode resultar em tempos de itera��o muito r�pidos.
		//Mas n�o � garantido.
		//Recomenda��o do curso Unreal C++ Udemy.
        MinFilesUsingPrecompiledHeaderOverride = 1;

		bFasterWithoutUnity = true;

	}
}
