using HarmonyLib;

namespace OmegaWare_BlushBlush.Patches;

[HarmonyPatch(typeof(BlayFapIntegration), "HasItem", typeof(BlayFapIntegration.ServerItem))]
internal class BlayFapInventoryHasItemPatch
{
    [HarmonyPostfix]
    private static void Postfix(ref bool __result, BlayFapIntegration.ServerItem item)
    {
        if (!__result && ModContext.Config.UnlockAllItems.Value)
        {
            if (ModContext.State.ExtraDebugLogs)
                ModContext.Logger.LogInfo($"Pretending player has item {item}");

            __result = true;
        }
    }
}