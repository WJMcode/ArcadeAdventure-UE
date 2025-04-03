#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginRegisterGameMode.generated.h"

/*
 * 로그인과 계정 생성을 위한 화면에서 진행되는 게임 모드입니다.
 * 블루프린트에서는 ALoginRegisterGameMode를 상속받아 BP_LoginRegisterGameMode를 만들었습니다.
 * 그리고 월드 세팅에서 BP_LoginRegisterGameMode를 오버라이드하여 적용했습니다.
 * ALoginRegisterGameMode를 상속한 BP_LoginRegisterGameMode를 만들어 사용하는 이유는,
 * 이미 블루프린트로 디자인한 LoginRegisterScreenWidget을 바로 사용하기 위함입니다. (게임 모드는 UI를 미리 배치된 위젯을 갖고 있지 않기 때문에 BindWidget 불가능)
 * 에디터상에서 ALoginRegisterGameMode를 상속받은 BP_LoginRegisterGameMode의 LoginRegisterScreenWidgetClass값을
 * LoginRegisterScreenWidget로 바꾸어 저장할 수 있습니다.
 * 
 * 이렇게 하면
 * 게임 디자이너는 블루프린트에서 쉽게 디자인을 만들 수 있고 
 * 게임 프로그래머는 C++의 성능을 활용하면서 작업이 가능합니다.
 */
UCLASS()
class ARCADEADVENTURE_API ALoginRegisterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void ShowLoginRegisterScreen();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class ULoginRegisterScreenWidget> LoginRegisterScreenWidgetClass;

private:
	UPROPERTY()
	ULoginRegisterScreenWidget* LoginRegisterScreenWidget = nullptr;
};
