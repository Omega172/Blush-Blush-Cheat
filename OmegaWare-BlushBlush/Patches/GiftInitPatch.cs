using System;
using HarmonyLib;
using OmegaWare_BlushBlush.Services;
using UnityEngine;

namespace OmegaWare_BlushBlush.Patches;

[HarmonyPatch(typeof(Gift), "Init", typeof(OutfitModel), typeof(Sprite))]
internal class GiftInitPatch
{
    [HarmonyPostfix]
    private static void Postfix(Gift __instance)
    {
        if (!ModContext.Config.UnlockAllOutfits.Value)
            return;

        if (Girls.CurrentGirl == null)
            return;

        if (!GameActionsService.TryGetGiftOutfitType(__instance, out OutfitModel outfitModel))
            return;

        if (outfitModel == null)
            return;

        try
        {
            if (!GameActionsService.TryUnlockOutfitForGirl(Girls.CurrentGirl, outfitModel))
                return;

            Girls.CurrentGirl.StoreState();

            if (ModContext.State.ExtraDebugLogs)
                ModContext.Logger.LogInfo($"Unlocked outfit model for {Enum.GetName(typeof(Balance.GirlName), Girls.CurrentGirl.GirlName)}");
        }
        catch (Exception ex)
        {
            if (ModContext.State.ExtraDebugLogs)
                ModContext.Logger.LogWarning($"Failed to unlock outfit from Gift.Init: {ex.Message}");
        }
    }
}