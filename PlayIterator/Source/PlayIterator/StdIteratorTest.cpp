// Fill out your copyright notice in the Description page of Project Settings.

#include "StdIteratorTest.h"
#include <vector>

void AStdIteratorTest::BeginPlay()
{
	Super::BeginPlay();

	TestStdVector();
}

void AStdIteratorTest::TestStdVector() {

	std::vector<int> MyVector;

	// ����������
	for (int i = 0; i < 16; i++) {
		MyVector.push_back(i);
	}

	UE_LOG(LogTemp, Warning, _T("AStdIteratorTest: vector size = %d."), MyVector.size());

	// ��ѭ����ɾ��vector�е�Ԫ��
	// std��׼�����Ĳ��������������Ƶ�
	for (auto iter = MyVector.begin(); iter != MyVector.end();) {
		int num = *iter;
		if (num % 2)
			iter = MyVector.erase(iter);	// std::vector::erase() �ķ���ֵ���Ǹ�����õ�
		else
			++iter;
	}

	UE_LOG(LogTemp, Warning, _T("AStdIteratorTest: vector size after delete = %d."), MyVector.size());

}