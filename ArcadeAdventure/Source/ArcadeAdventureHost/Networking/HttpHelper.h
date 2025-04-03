// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"

/**
 * HTTP 요청을 처리하는 헬퍼 클래스입니다.
 *
 * - `Login()`: Flask 서버에 로그인 요청을 보냅니다.
 * - `Register()`: Flask 서버에 회원가입 요청을 보냅니다.
 * - 내부적으로 `SendRequest()`를 사용하여 HTTP POST 요청을 수행합니다.
 */
class ARCADEADVENTUREHOST_API FHttpHelper
{
public:
	static void Login(const FString& Username, const FString& Password);
	static void AccountRegister(const FString& Username, const FString& Password);
	
private:
	template<typename T>
	static void SendRequest(const FString& URL, const FString& Username, const FString& Password, T Callback, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request);
	static void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
