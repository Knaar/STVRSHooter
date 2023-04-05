// Fill out your copyright notice in the Description page of Project Settings.
#define _WIN32_WINNT 0x0A00 // Windows 10
#define WIN32_LEAN_AND_MEAN
#include "HostJoinWidget.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHostJoinWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UButton* HostButton = Cast<UButton>(GetWidgetFromName(TEXT("HostButton")));
	if (HostButton != nullptr)
	{
		HostButton->OnClicked.AddDynamic(this, &UHostJoinWidget::OpenLobby);
	}
	UButton* JoinButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinButton")));
	if (JoinButton != nullptr)
	{
		JoinButton->OnClicked.AddDynamic(this, &UHostJoinWidget::CallClientTravel);
	}
	UButton* JoinDedicatedButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinDedicatedButton")));
	if (JoinDedicatedButton != nullptr)
	{
		JoinDedicatedButton->OnClicked.AddDynamic(this, &UHostJoinWidget::CallDedicatedTravel);
	}
}

FString GetLocalIpAddress()
{
	FString IpAddress = "Unknown";
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		return IpAddress;
	}
	char hostname[256];
	iResult = gethostname(hostname, sizeof(hostname));
	if (iResult != 0) {
		WSACleanup();
		return IpAddress;
	}
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	iResult = getaddrinfo(hostname, NULL, &hints, &result);
	if (iResult != 0) {
		WSACleanup();
		return IpAddress;
	}
	char ipstr[INET_ADDRSTRLEN];
	struct sockaddr_in* sa = (struct sockaddr_in*)result->ai_addr;
	inet_ntop(AF_INET, &sa->sin_addr, ipstr, sizeof(ipstr));
	IpAddress = FString(ipstr);
	freeaddrinfo(result);
	WSACleanup();
	return IpAddress;
}

void UHostJoinWidget::OpenLobby()
{
	if(!GetWorld())return;
	
	Address = GetLocalIpAddress();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Local IP address: %s"), *Address));
	RemoveFromParent();
	GetWorld()->ServerTravel(Path);
}


void UHostJoinWidget::CallClientTravel()
{
	if(const auto PlayerController=GetGameInstance()->GetFirstLocalPlayerController())
	{
		RemoveFromParent();
		PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
	}
}

void UHostJoinWidget::CallDedicatedTravel()
{
	if(const auto PlayerController=GetGameInstance()->GetFirstLocalPlayerController())
	{
		RemoveFromParent();
		
		PlayerController->ClientTravel(DedicatedAddress,ETravelType::TRAVEL_Absolute);
	}

}
