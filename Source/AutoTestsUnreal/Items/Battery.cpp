// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Battery.h"

using namespace ATU;

constexpr float ChargeAmount = 0.1f;

ATU::Battery::Battery(float PercentIn)
{
    SetPercent(PercentIn);
}

void ATU::Battery::Charge()
{
    SetPercent(Percent + ChargeAmount);
}

void ATU::Battery::UnCharge()
{
    SetPercent(Percent - ChargeAmount);
}

float ATU::Battery::GetPercent() const
{
    return Percent;
}

FColor ATU::Battery::GetColor() const
{
    if (Percent > 0.8f) return FColor::Green;
    if (Percent > 0.3f) return FColor::Yellow;
    return FColor::Red;
}

FString ATU::Battery::ToString() const
{
    return FString::Printf(TEXT("%i%%"), FMath::RoundToInt(Percent * 100));
}

void ATU::Battery::SetPercent(float PercentIn)
{
    Percent = FMath::Clamp(PercentIn, 0.0f, 1.0f);
}