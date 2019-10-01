// Fill out your copyright notice in the Description page of Project Settings.


#include "BPNode_TriGate.h"
#include "EdGraphSchema_K2.h"	// BlueprintGraph
#include "BlueprintNodeSpawner.h"	// BlueprintGraph
#include "BlueprintActionDatabaseRegistrar.h"	// BlueprintGraph
#include "BPTerminal.h"
#include "KismetCompilerMisc.h"
#include "KismetCompiler.h"
#include "Kismet/KismetMathLibrary.h"

namespace TriGatePN
{
	FName Input = TEXT("Integer");
	FName Positive = TEXT("Positive");
	FName Zero = TEXT("Zero");
	FName Negative = TEXT("Negative");
}

class FKCHandler_TriGate : public FNodeHandlingFunctor
{
protected:
	// Ϊÿ��Node����һ����ʱbool�����������洢��������ıȽϽ��
	TMap<UEdGraphNode*, FBPTerminal*> BoolTermMap;
	FBPTerminal* LiteralZeroTerm;

public:
	FKCHandler_TriGate(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext)
	{
	}

	virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override
	{
		FNodeHandlingFunctor::RegisterNets(Context, Node);

		FBPTerminal* BoolTerm = Context.CreateLocalTerminal();
		BoolTerm->Type.PinCategory = UEdGraphSchema_K2::PC_Boolean;
		BoolTerm->Source = Node;
		BoolTerm->Name = Context.NetNameMap->MakeValidName(Node) + TEXT("_CmpResult");
		BoolTermMap.Add(Node, BoolTerm);

		LiteralZeroTerm = Context.CreateLocalTerminal(ETerminalSpecification::TS_Literal);
		LiteralZeroTerm->bIsLiteral = true;
		LiteralZeroTerm->Type.PinCategory = UEdGraphSchema_K2::PC_Int;
		LiteralZeroTerm->Name = TEXT("0");

	}

	virtual void RegisterNet(FKismetFunctionContext& Context, UEdGraphPin* Pin)
	{
	}

	virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override
	{
		UBPNode_TriGate* MyNode = CastChecked<UBPNode_TriGate>(Node);

		//UEdGraphPin* PositivePin = Context.FindRequiredPinByName(Node, TriGatePN::Positive, EGPD_Input);
		//UEdGraphPin* ZeroPin = Context.FindRequiredPinByName(Node, TriGatePN::Zero, EGPD_Output);
		UEdGraphPin* NegativePin = Context.FindRequiredPinByName(Node, TriGatePN::Negative, EGPD_Output);
		
		FBPTerminal* BoolTerm = BoolTermMap.FindRef(MyNode);
		
		//// TODO:
		//FBPTerminal* InputTerm = new FBPTerminal();

		//UClass* MathLibClass = UKismetMathLibrary::StaticClass();
		//UFunction* CreaterFuncPtr = FindField<UFunction>(MathLibClass, "Greater_IntInt");
		//UFunction* EqualFuncPtr = FindField<UFunction>(MathLibClass, "EqualEqual_IntInt");

		//// Statement 1: BoolTerm = Interger > 0
		//FBlueprintCompiledStatement& Statement = Context.AppendStatementForNode(MyNode);
		//Statement.Type = KCST_CallFunction;
		//Statement.FunctionToCall = CreaterFuncPtr;
		//Statement.LHS = BoolTerm;
		//Statement.RHS.Add(InputTerm);
		//Statement.RHS.Add(LiteralZeroTerm);

		//// Statement 2: GotoIfNot(BoolTerm)

		//// Statement 3: BoolTerm = Interger == 0

		//// Statement 4: GotoIfNot(BoolTerm)

		// Statement 5: Exec
		FBlueprintCompiledStatement& GotoThen = Context.AppendStatementForNode(Node);
		GotoThen.Type = KCST_UnconditionalGoto;
		Context.GotoFixupRequestMap.Add(&GotoThen, NegativePin);


	}
};

void UBPNode_TriGate::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, TriGatePN::Input);

	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TriGatePN::Positive);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TriGatePN::Zero);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TriGatePN::Negative);

}

void UBPNode_TriGate::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FNodeHandlingFunctor * UBPNode_TriGate::CreateNodeHandler(FKismetCompilerContext & CompilerContext) const
{
	return new FKCHandler_TriGate(CompilerContext);
}
