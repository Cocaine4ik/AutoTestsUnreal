#pragma once

#include "CoreMinimal.h"
namespace ATU
{
	template<typename T1, typename  T2>
	struct TestPayLoad
	{
		T1 TestValue;
		T2 ExpectedValue;
	    float Tolerance = KINDA_SMALL_NUMBER;
	};
}