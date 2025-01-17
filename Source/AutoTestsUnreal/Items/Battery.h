// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace ATU
{
class AUTOTESTSUNREAL_API Battery
{
public:
    Battery() = default;
    Battery(float PercentIn);

private:
    float Percent = 1.0f;

public:
    bool operator <= (const Battery& rhs) const
    {
        return GetPercent() <= rhs.GetPercent();
    }

    bool operator < (const Battery& rhs) const
    {
        return GetPercent() < rhs.GetPercent();
    }

    bool operator > (const Battery& rhs) const
    {
        return GetPercent() > rhs.GetPercent();
    }

    bool operator == (const Battery& rhs) const
    {
        return FMath::IsNearlyEqual(GetPercent(), rhs.GetPercent());
    }
    void Charge();
    void UnCharge();

    float GetPercent() const;
    FColor GetColor() const;
    FString ToString() const;

private:
    void SetPercent(float PercentIn);
};
}