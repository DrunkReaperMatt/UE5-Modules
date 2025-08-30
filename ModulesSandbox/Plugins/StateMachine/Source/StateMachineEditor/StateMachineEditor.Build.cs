using UnrealBuildTool;

public class StateMachineEditor : ModuleRules
{
    public StateMachineEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "StateMachine",
        });
    }
}