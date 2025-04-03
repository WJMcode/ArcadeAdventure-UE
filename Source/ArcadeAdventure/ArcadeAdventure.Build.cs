// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArcadeAdventure : ModuleRules
{
	public ArcadeAdventure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "ArcadeAdventureHost" });

        // Source/ArcadeAdventure/ 아래의 폴더를 포함 경로로 설정합니다.
        PublicIncludePaths.AddRange(new string[] 
		{
			this.Name
        });
	}
}
