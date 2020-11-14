// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class maz3d : ModuleRules
{
	public maz3d(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"});
	}
}
