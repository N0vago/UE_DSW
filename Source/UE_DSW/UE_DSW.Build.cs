// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_DSW : ModuleRules
{
	public UE_DSW(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
