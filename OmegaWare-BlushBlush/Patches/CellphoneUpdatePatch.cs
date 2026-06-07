using HarmonyLib;

namespace OmegaWare_BlushBlush.Patches;

[HarmonyPatch(typeof(Cellphone), "Update")]
internal class CellphoneUpdatePatch
{
    [HarmonyPrefix]
    private static void Prefix(Cellphone __instance)
    {
        ModContext.State.CellphoneInstance = __instance;
    }
}