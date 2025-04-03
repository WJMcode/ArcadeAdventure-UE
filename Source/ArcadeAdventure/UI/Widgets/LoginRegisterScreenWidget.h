// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoginRegisterWidget.h"
#include "CreateAccountWidget.h"
#include "LoginRegisterScreenWidget.generated.h"

/**
 * LoginRegisterWidget과 CreateAccount Widget을 보여주거나 숨길 수 있도록 관리하는 Widget입니다.
 */
UCLASS()
class ARCADEADVENTURE_API ULoginRegisterScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

private:
	// ========== LoginRegisterWidget의 버튼
	UFUNCTION()
	// RegisterBtn을 누르면 LoginRegisterWidget을 숨기고 CreateAccountWidget을 띄웁니다.
	void OnRegisterBtnClicked();

	// ========== CreateAccountWidget의 버튼
	UFUNCTION()
	// CreateBtn을 누르면 CreateAccountWidget을 숨기고 LoginRegisterWidget을 띄웁니다.
	void OnCreateBtnClicked(const FString& EnteredUsername, const FString& EnteredPassword);

private:
	UPROPERTY(meta = (BindWidget))
	ULoginRegisterWidget* LoginRegisterWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	UCreateAccountWidget* CreateAccountWidget = nullptr;

/*
* 서버에 요청하는 RPC 함수
*/ 
private:
	// Server	이 함수는 서버에서만 실행됩니다.(클라이언트에서 호출하면 서버에서 실행됩니다.).
	// Reliable	네트워크 패킷 손실이 발생해도 반드시 실행됩니다.(중요한 RPC 호출에 사용합니다.).
	// 서버 RPC(Server, Reliable) 함수를 선언하면, 반드시 _Implementation을 가진 구현 함수를 작성해야 합니다.
	UFUNCTION(Server, Reliable)
	void Server_RequestAccountRegister(const FString& EnteredUsername, const FString& EnteredPassword);
	void Server_RequestAccountRegister_Implementation(const FString& EnteredUsername, const FString& EnteredPassword);

};
