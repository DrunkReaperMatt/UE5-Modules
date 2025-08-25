using UnrealBuildTool;

public class DialogManager: ModuleRules
{
	public DialogManager(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine"]);
	}
}