// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySubObject.h"
#include "Components/StaticMeshComponent.h"
#include "MyStaticMeshComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class MYSUBOBJECTTEST_API UMyStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()
	
public:
	UMyStaticMeshComponent();

	virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

		UPROPERTY(VisibleAnywhere, Instanced, BlueprintReadOnly,meta = (ShowOnlyInnerProperties))
		UMySubObject* MySubObject;
};


/** �ؿ��༭ʱ��
 1. ��ͼ�������Ըı�ᴥ����ͼ�Զ����±��롢��ͼ�����ؽ�
 2. ���ؽ�ʱ����Ҫ���Ӷ������������⴦��
 3. ��ν�����⴦����Ҫ�ǰ��ϵ��Ӷ������ԣ����Ƶ��µ��Ӷ�����
*/
USTRUCT()
struct FMyComponentInstanceData : public FActorComponentInstanceData
{
	GENERATED_BODY()
public:
	FMyComponentInstanceData()
		: MySubObject(nullptr)
	{}
	FMyComponentInstanceData(const UActorComponent* InSourceComponent);
	virtual ~FMyComponentInstanceData() = default;

	virtual bool ContainsData() const override
	{
		return (MySubObject != nullptr) || Super::ContainsData();
	}

	virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UPROPERTY()
		UMySubObject* MySubObject;
};