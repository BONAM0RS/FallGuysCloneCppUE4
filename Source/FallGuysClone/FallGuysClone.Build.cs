// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FallGuysClone : ModuleRules
{
	public FallGuysClone(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
