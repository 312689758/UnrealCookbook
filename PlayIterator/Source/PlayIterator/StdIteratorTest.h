// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StdIteratorTest.generated.h"

/*
 * ��ʾ��׼C++������iterator��ʹ��
*/
UCLASS()
class PLAYITERATOR_API AStdIteratorTest : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	void TestStdVector();
};
