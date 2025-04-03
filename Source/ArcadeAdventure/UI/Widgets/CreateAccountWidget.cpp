// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/CreateAccountWidget.h"

void UCreateAccountWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!CreateBtn)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateBtn이 nullptr입니다!"));

	}
	CreateBtn->OnClicked.AddDynamic(this, &UCreateAccountWidget::HandleCreateButtonClicked);
}

void UCreateAccountWidget::HandleCreateButtonClicked()
{
	if(OnCreateButtonClicked.IsBound())
	{
		const FString& UserName = UserNameTextBox->GetText().ToString();
		const FString& Password = PasswordTextBox->GetText().ToString();
		OnCreateButtonClicked.Broadcast(UserName, Password);
	}
}
