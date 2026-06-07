using HarmonyLib;

namespace OmegaWare_BlushBlush.Patches;

[HarmonyPatch(typeof(Album), "IsPinupUnlocked", typeof(int), typeof(int))]
internal class AlbumIsPinupUnlockedPatch
{
    [HarmonyPostfix]
    private static void Postfix(ref bool __result, int pinupPage, int image)
    {
        if (!__result && ModContext.Config.ShowAllPinups.Value)
        {
            if (ModContext.State.ExtraDebugLogs)
                ModContext.Logger.LogInfo($"Pretending pinup {pinupPage}-{image} is unlocked");
            __result = true;
        }
    }
}