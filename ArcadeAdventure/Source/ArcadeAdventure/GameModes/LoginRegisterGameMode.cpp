#include "GameModes/LoginRegisterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/LoginRegisterScreenWidget.h"

void ALoginRegisterGameMode::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = nullptr;

    // 서버일 경우 (리슨 서버)
    if (HasAuthority())
    {
        PC = UGameplayStatics::GetPlayerController(this, 0);
    }

    // 클라이언트 또는 리슨 서버의 클라이언트 역할
    if (!PC)
    {
        if (ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
        {
            PC = LocalPlayer->GetPlayerController(GetWorld());
        }
    }

    // 최종적으로 PC가 존재하면 마우스 설정
    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
    ShowLoginRegisterScreen();
}

void ALoginRegisterGameMode::ShowLoginRegisterScreen()
{
    if (LoginRegisterScreenWidgetClass && !LoginRegisterScreenWidget)
    {
        LoginRegisterScreenWidget = CreateWidget<ULoginRegisterScreenWidget>(GetWorld(), LoginRegisterScreenWidgetClass);
        if (LoginRegisterScreenWidget)
        {
            LoginRegisterScreenWidget->AddToViewport();
        }
    }
}