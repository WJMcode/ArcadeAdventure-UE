// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/LoginRegisterScreenWidget.h"
#include "ArcadeAdventureHost/Networking/HttpHelper.h"

void ULoginRegisterScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!LoginRegisterWidget || !CreateAccountWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("LoginRegisterWidget 또는 CreateAccountWidget이 nullptr입니다!"));
		return;
	}
	
	LoginRegisterWidget->OnRegisterButtonClicked.AddDynamic(this, &ULoginRegisterScreenWidget::OnRegisterBtnClicked);
	
	CreateAccountWidget->OnCreateButtonClicked.AddDynamic(this, &ULoginRegisterScreenWidget::OnCreateBtnClicked);
	CreateAccountWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ULoginRegisterScreenWidget::OnRegisterBtnClicked()
{
	// 위젯 관련 동작
	if (LoginRegisterWidget)
	{
		LoginRegisterWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (CreateAccountWidget)
	{
		CreateAccountWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ULoginRegisterScreenWidget::OnCreateBtnClicked(const FString& EnteredUsername, const FString& EnteredPassword)
{
	// 위젯 관련 동작
	if (CreateAccountWidget)
	{
		CreateAccountWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (LoginRegisterWidget)
	{
		LoginRegisterWidget->SetVisibility(ESlateVisibility::Visible);
	}

	// 계정 생성 동작
	{
		if (EnteredUsername.IsEmpty() || EnteredPassword.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("잘못된 입력입니다!"));
			return;
		}

		if (GetOwningPlayerPawn()->HasAuthority()) // 호스트라면 직접 처리
		{
			FHttpHelper::AccountRegister(EnteredUsername, EnteredPassword);
		}
		else // 클라이언트라면 서버에 RPC 요청
		{
			Server_RequestAccountRegister(EnteredUsername, EnteredPassword);
		}
	}
}

void ULoginRegisterScreenWidget::Server_RequestAccountRegister_Implementation(const FString& EnteredUsername, const FString& EnteredPassword)
{
	if (!GetOwningPlayerPawn()->HasAuthority()) return;

	FHttpHelper::AccountRegister(EnteredUsername, EnteredPassword);
}

