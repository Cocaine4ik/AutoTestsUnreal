// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AutoTestsUnreal : ModuleRules
{
	public AutoTestsUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		
		PublicIncludePaths.Add("AutoTestsUnreal");
	}
}
