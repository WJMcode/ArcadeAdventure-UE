// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcadeAdventureHost.h"
#include "Modules/ModuleManager.h"

// ArcadeAdventureHost는 메인 게임 모듈이 아니라 서브 모듈
// 그래서 IMPLEMENT_PRIMARY_GAME_MODULE이 아니라 IMPLEMENT_MODULE을 사용해야 합니다.
IMPLEMENT_MODULE(FDefaultModuleImpl, ArcadeAdventureHost);
 