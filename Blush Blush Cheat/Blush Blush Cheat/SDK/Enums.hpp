#pragma once

// {}::Balance::GirlName
namespace Guys
{
	enum Guy
	{
		Unknown = -1,
		Nimh,
		Volks,
		Kelby,
		Eli,
		Anon,
		Garret,
		Dmitri,
		Ichiban,
		William,
		Myx,
		Stirling,
		Scale,
		Sven,
		Cole,
		Poe,
		Cashew,
		Seth,
		Logan,
		Reece,
		MAX = 18
	};
}

namespace BlayFapIntegration
{
	enum ServerItems : DWORD
	{
		NSFW = 0x0,
		SpeedBoost2,
		SpeedBoost4,
		SpeedBoost8,
		StarterPack,
		Sven,
		FullVoices,
		Cole,
		NimhKigurumi,
		VolksKigurumi,
		KelbyKigurumi,
		BoxersBundle,
		HalloweenBundle,
		KigurumiBundle,
		NimhButler,
		VolksButler,
		Cashew,
		Poe,
		ButlerBundle,
		KelbyButler,
		EliButler,
		Seth,
		SummerBundle,
		AnonButler,
		GarretButler,
		DmitriButler,
		IchibanButler,
		WilliamButler,
		MyxButler,
		StirlingButler,
		ScaleButler,
		Logan,
		VolksDate,
		NimhSummer,
		VolksSummer,
		KelbySummer,
		Reece,
		MAX = 36
	};
}

namespace BlayFap
{
	enum ServerItemsOld : UINT32
	{
		None = 0U,
		NSFW = 1U,
		SpeedBoost2 = 2U,
		SpeedBoost4 = 4U,
		SpeedBoost8 = 8U,
		StarterPack = 16U,
		Sven = 32U,
		FullVoices = 64U,
		Cole = 128U,
		NimhKigurumi = 256U,
		VolksKigurumi = 512U,
		KelbyKigurumi = 1024U,
		BoxersBundle = 2048U,
		HalloweenBundle = 4096U,
		KigurumiBundle = 8192U,
		NimhButler = 16384U,
		VolksButler = 32768U,
		Cashew = 65536U,
		Poe = 131072U,
		ButlerBundle = 262144U,
		KelbyButler = 524288U,
		EliButler = 1048576U,
		Seth = 2097152U,
		SummerBundle = 4194304U,
		AnonButler = 8388608U,
		GarretButler = 16777216U,
		DmitriButler = 33554432U,
		IchibanButler = 67108864U,
		WilliamButler = 134217728U,
		MyxButler = 268435456U,
		StirlingButler = 536870912U,
		ScaleButler = 1073741824U,
		Logan = 2147483648U
	};
}

namespace Store2
{
	enum PurchaseType : int
	{
		Timeblock1 = 0,
		Timeblock5,
		Timeblock10,
		SkipReset,
		SpeedBoost2,
		SpeedBoost4,
		SpeedBoost8,
		JumpFourHours,
		Jump1Day,
		Jump7Day,
		Timelord,
		Consumable2,
		Consumable4,
		Consumable8,
		HalloweenBundle,
		BoxersBundle,
		PoeBundle,
		CashewBundle,
		KigurumiBundle,
		ButlerBundle,
		SummerBundle,
		SethBundle,
		LoganBundle,
		ReeceBundle,
		MAX = 23
	};
}