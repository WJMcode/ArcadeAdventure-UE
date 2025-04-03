#include "UI/Widgets/LoginRegisterWidget.h"

void ULoginRegisterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!RegisterBtn)
	{
		UE_LOG(LogTemp, Error, TEXT("RegisterBtn이 nullptr입니다!"));

	}
	RegisterBtn->OnClicked.AddDynamic(this, &ULoginRegisterWidget::HandleRegisterButtonClicked);
}

void ULoginRegisterWidget::HandleRegisterButtonClicked()
{
	OnRegisterButtonClicked.Broadcast();
}
