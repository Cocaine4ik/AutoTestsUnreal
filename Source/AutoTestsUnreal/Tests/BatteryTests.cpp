﻿#include "BatteryTests.h"

// Fill out your copyright notice in the Description page of Project Settings.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "AutoTestsUnreal/Tests/BatteryTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Items/Battery.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBatteryTests, "AutoTestUnreal.Items.Battery",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter |
    EAutomationTestFlags::HighPriority);

bool FBatteryTests::RunTest(const FString& Parameters)
{
    using namespace ATU;

    AddInfo("Battery with default constructor");
    const Battery BatteryDefault;
    TestTrueExpr(FMath::IsNearlyEqual(BatteryDefault.GetPercent(), 1.0f));
    TestTrueExpr(BatteryDefault.GetColor() == FColor::Green);
    TestTrueExpr(BatteryDefault.ToString().Equals("100%"));

    AddInfo("Battery with custom constructor");

    const auto BatteryTestFunc = [this](float Percent, const FColor& Color, const FString& PercentString)
    {
        const Battery BatteryObject(Percent);
        TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), FMath::Clamp(Percent, 0.0f, 1.0f)));
        TestTrueExpr(BatteryObject.GetColor() == Color);
        TestTrueExpr(BatteryObject.ToString().Equals(PercentString));
    };

    BatteryTestFunc(1.0f, FColor::Green, "100%");
    BatteryTestFunc(0.46f, FColor::Yellow, "46%");
    BatteryTestFunc(0.2f, FColor::Red, "20%");
    BatteryTestFunc(3000.0f, FColor::Green, "100%");
    BatteryTestFunc(-3000.0f, FColor::Red, "0%");

    AddInfo("Battery charge / uncharge");
    Battery BatteryObject(0.6f);
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.6f));
    BatteryObject.UnCharge();
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.5f));
    BatteryObject.Charge();
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.6f));

    AddInfo("Battery charge / uncharge. Corner cases");
    for (int32 i = 0; i < 100; ++i)
    {
        BatteryObject.UnCharge();
    }
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 0.0f));

    for (int32 i = 0; i < 100; ++i)
    {
        BatteryObject.Charge();
    }
    TestTrueExpr(FMath::IsNearlyEqual(BatteryObject.GetPercent(), 1.0f));
    
    AddInfo("Battery comparison");
    const Battery BatteryLow(0.3f);
    const Battery BatteryHigh(0.9f);

    TestTrueExpr(BatteryLow <= BatteryLow);
    TestTrueExpr(FMath::Max(BatteryHigh, BatteryLow) == BatteryHigh);

    AddInfo("Battery in memory comparison");
    TestNotSame("Not the same batteries", BatteryLow, BatteryHigh);

    const Battery BatteryHighDup(0.9f);
    TestTrueExpr(BatteryHigh == BatteryHighDup);
    TestNotSame("Not the same batteries", BatteryHigh, BatteryHighDup);

    const Battery& BatteryHighRef = BatteryHigh;
    TestSame("The same batteries", BatteryHigh, BatteryHighRef);

    return true;
}

#endif