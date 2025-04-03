// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameCoreInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEADVENTURE_API UGameCoreInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

private:
	void test();
};
