using BepInEx.Logging;
using HarmonyLib;
using OmegaWare_BlushBlush.Config;
using OmegaWare_BlushBlush.Services;
using OmegaWare_BlushBlush.State;

namespace OmegaWare_BlushBlush;

internal static class ModContext
{
    internal static ManualLogSource Logger = null!;
    internal static Harmony HarmonyInstance = null!;
    internal static PluginConfig Config = null!;
    internal static PluginState State { get; } = new();
    internal static GameActionsService Actions = null!;
}