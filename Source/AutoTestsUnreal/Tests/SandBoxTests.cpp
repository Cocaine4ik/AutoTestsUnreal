// Fill out your copyright notice in the Description page of Project Settings.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TESTS)

#include "AutoTestsUnreal/Tests/SandBoxTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/TestUtils.h"

using namespace ATU;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathMax, "AutoTestUnreal.Math.MaxInt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter |
    EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathMin, "AutoTestUnreal.Math.Min",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter |
    EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathSqrt, "AutoTestUnreal.Math.Sqrt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter |
    EAutomationTestFlags::HighPriority);

bool FMathMax::RunTest(const FString& Parameters)
{
    AddInfo("Max [int] func testing");

    using MaxTestPayLoad = TArray<TestPayLoad<TInterval<int32>, int32>>;

    MaxTestPayLoad TestData
    {
        {{13, 25}, 25},
        {{25, 25}, 25},
        {{0, 123}, 123},
        {{0, 0}, 0},
        {{-2345, 0}, 0},
        {{-45, -67}, -45},
        {{-9, -9}, -9},
        {{5, -5}, 5}
    };

    for (const auto Data : TestData)
    {
        TestTrueExpr(FMath::Max(Data.TestValue.Min, Data.TestValue.Max) == Data.ExpectedValue);
    }

    return true;
}

bool FMathMin::RunTest(const FString& Parameters)
{
    using MinTestPayLoad = TArray<TestPayLoad<TInterval<int32>, int32>>;

    MinTestPayLoad TestData
    {
        {{13, 25}, 13},
        {{25, 25}, 25},
        {{0, 123}, 0},
        {{0, 0}, 0},
        {{-2345, 0}, -2345},
        {{-45, -67}, -67},
        {{-9, -9}, -9},
        {{5, -5}, -5}
    };

    for (const auto Data : TestData)
    {
        TestTrueExpr(FMath::Min(Data.TestValue.Min, Data.TestValue.Max) == Data.ExpectedValue);
    }

    return true;
}

bool FMathSqrt::RunTest(const FString& Parameters)
{
    AddInfo("sqrt function testing");

    using SqrtTestPayLoad = TArray<TestPayLoad<float, float>>;

    SqrtTestPayLoad TestData
    {
        {4.0f, 2.0f},
        {3.0f, 1.7f, 0.1f},
        {3.0f, 1.73f, 0.01f},
        {3.0f, 1.73205f, 1.e-5f}
    };

    for (const auto Data : TestData)
    {
        const bool IsEqual = FMath::IsNearlyEqual(FMath::Sqrt(Data.TestValue), Data.ExpectedValue, Data.Tolerance);
        
        TestTrueExpr(IsEqual);
    }

    return true;
}

#endif