// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpHelper.h"

void FHttpHelper::Login(const FString& Username, const FString& Password)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    
    // Request - Type을 세팅해 주면 디버깅 메시지를 출력할 때 유용
    Request->SetHeader("Request-Type", "Login");
    
    // T는 OnResponse의 인자를 통해 추론, 즉 void(*)(FHttpRequestPtr, FHttpResponsePtr, bool)로 추론
    SendRequest("http://127.0.0.1:5000/login", Username, Password, OnResponse, Request);
}

void FHttpHelper::AccountRegister(const FString& Username, const FString& Password)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetHeader("Request-Type", "Account Register");
    SendRequest("http://127.0.0.1:5000/register", Username, Password, OnResponse, Request);
}

template <typename T>
void FHttpHelper::SendRequest(const FString& URL, const FString& Username, const FString& Password, T Callback, TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)
{
    //TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

    // 동적으로 콜백을 처리하는 방법
    Request->OnProcessRequestComplete().BindLambda([Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            // 콜백 실행
            Callback(Request, Response, bWasSuccessful);
        });

    Request->SetURL(URL);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");

    FString RequestBody = FString::Printf(TEXT("{\"username\":\"%s\", \"password\":\"%s\"}"), *Username, *Password);
    Request->SetContentAsString(RequestBody);

    Request->ProcessRequest();
}

void FHttpHelper::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    // HTTP 요청 자체를 실패함
    if (!bWasSuccessful)
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed: %s"), *Request->GetURL());
        return;
    }

    FString ResponseString = Response->GetContentAsString();
    int32 ResponseCode = Response->GetResponseCode();
    FString RequestType = Request->GetHeader("Request-Type");  // 요청 타입 가져오기

    // 서버가 빈 응답을 반환함
    if (ResponseString.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Empty response from server"));
        return;
    }

    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
    
    // DB에 username과 password가 존재해 Server가 200을 반환함
    if(ResponseCode == 200)
    {
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            bool bSuccess = JsonObject->GetBoolField("success");
            FString Message = JsonObject->GetStringField("message");

            if (bSuccess)
            {
                UE_LOG(LogTemp, Warning, TEXT("[%s] Success: %s"), *RequestType, *Message);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("[%s] Failure: %s"), *RequestType, *Message);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("[%s] Failed to parse JSON response"), *RequestType);
        }
    }
    // 로그인 실패 (잘못된 인증 정보)
    else if (ResponseCode == 401)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] Unauthorized (Invalid credentials)"), *RequestType);
    }
    // 기타 에러
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] Unexpected response code: %d"), *RequestType, ResponseCode);
    }
}


