// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrowdSimDemo : ModuleRules
{
	public CrowdSimDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
