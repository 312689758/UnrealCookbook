// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "QuestDataAsset.generated.h"

//-- ��������ö��
UENUM(Blueprintable, Category="DataDemo")
enum class EQuestType :uint8
{
	Outland,
	Classes,
	Dungeons,
	Professions,
	Battlegrounds
};

//-- �������ݶ���
USTRUCT(Blueprintable, Category="DataDemo")
struct FQuestDef
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	int RequiresLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	TArray<int> Rewards;
};

/**
 * ��ʾʹ��DataAsset����������
 */
UCLASS(Blueprintable, Category="DataDemo")
class UNREALCOOKBOOK_API UQuestDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	FString QuestSetName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataDemo")
	TArray<FQuestDef> QuestArray;
	
	
};
