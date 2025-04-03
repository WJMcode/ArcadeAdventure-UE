// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "CreateAccountWidget.generated.h"

//여러 개의 함수 바인딩 가능(Multicast 특징)
//블루프린트에서도 사용 가능(BlueprintAssignable)
//런타임에서 동적 바인딩 및 해제 가능
// 
//DECLARE_DYNAMIC_MULTICAST_DELEGATE는 UI 이벤트 시스템을 더 유연하게 만들고,
//블루프린트와 연동이 쉬워 디자이너& 프로그래머 협업이 편리합니다.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreateButtonClicked, const FString&, EnteredUsername, const FString&, EnteredPassword);

/**
 * 계정 생성을 진행할 수 있는 Widget입니다.
 */
UCLASS()
class ARCADEADVENTURE_API UCreateAccountWidget : public UUserWidget
{
	GENERATED_BODY()

	friend class ULoginRegisterScreenWidget;

protected:
	virtual void NativeOnInitialized() override;

private:
	// 계정 생성 버튼이 눌렸음을 알리기 위한 함수
	UFUNCTION()
	void HandleCreateButtonClicked();

protected:
	// 계정 이름 입력칸
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* UserNameTextBox = nullptr;
	// 비밀번호 입력칸
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PasswordTextBox = nullptr;
	// 계정 생성 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* CreateBtn = nullptr;

private:
	// 계정 생성 버튼을 눌렀음을 알립니다.
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCreateButtonClicked OnCreateButtonClicked;
};
