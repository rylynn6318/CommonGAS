// Copyright 2026 rylynn6318. All rights reserved.

#include "CommonInputComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CommonInputComponent)

void UCommonInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 BindHandle : BindHandles)
	{
		RemoveBindingByHandle(BindHandle);
	}

	BindHandles.Empty();
}
