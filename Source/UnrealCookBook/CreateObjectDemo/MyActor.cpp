// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "UnrealCookBook.h"


// Sets default values
AMyActor::AMyActor()
{
	/* <CreateObjectDemo>
	* ����Component����Ҫʹ��CreateDefaultSubobjectģ�庯��
	*/
	MyComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyComponent"));

	/* <CreateObjectDemo>
	* ����ģ�͡���ͼ�ȶ���ʹ��StaticLoadObject����
	*/
	UStaticMesh* SM_Vase = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(),
		NULL,
		TEXT("/Game/Assets/StaticMeshes/SM_Vase"))
		);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetStaticMesh(SM_Vase);
}
