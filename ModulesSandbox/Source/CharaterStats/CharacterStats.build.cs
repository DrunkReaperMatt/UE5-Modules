using UnrealBuildTool;

public class CharacterStats: ModuleRules
{
	public CharacterStats(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine"]);
	}
}