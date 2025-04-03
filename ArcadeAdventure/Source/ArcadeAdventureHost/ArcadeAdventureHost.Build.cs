// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArcadeAdventureHost : ModuleRules
{
	public ArcadeAdventureHost(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

		PrivateDependencyModuleNames.AddRange(new string[] { "HTTP", "JSON" });

        // Source/ArcadeAdventure/ 아래의 폴더를 포함 경로로 설정합니다.
        PublicIncludePaths.AddRange(new string[] 
		{
			this.Name
        });
	}
}
