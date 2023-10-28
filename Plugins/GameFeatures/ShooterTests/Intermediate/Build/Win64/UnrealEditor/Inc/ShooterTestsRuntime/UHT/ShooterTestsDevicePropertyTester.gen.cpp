// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShooterTestsRuntime/Private/ShooterTestsDevicePropertyTester.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
#include "../../Source/Runtime/Engine/Classes/GameFramework/InputDevicePropertyHandle.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeShooterTestsDevicePropertyTester() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FPlatformUserId();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UInputDeviceProperty_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FInputDevicePropertyHandle();
	SHOOTERTESTSRUNTIME_API UClass* Z_Construct_UClass_AShooterTestsDevicePropertyTester();
	SHOOTERTESTSRUNTIME_API UClass* Z_Construct_UClass_AShooterTestsDevicePropertyTester_NoRegister();
	UPackage* Z_Construct_UPackage__Script_ShooterTestsRuntime();
// End Cross Module References
	DEFINE_FUNCTION(AShooterTestsDevicePropertyTester::execOnEndOverlap)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnEndOverlap(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AShooterTestsDevicePropertyTester::execOnOverlapBegin)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_GET_UBOOL(Z_Param_bFromSweep);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepHitResult);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOverlapBegin(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepHitResult);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AShooterTestsDevicePropertyTester::execRemoveDeviceProperties)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RemoveDeviceProperties();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AShooterTestsDevicePropertyTester::execApplyDeviceProperties)
	{
		P_GET_STRUCT(FPlatformUserId,Z_Param_UserId);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ApplyDeviceProperties(Z_Param_UserId);
		P_NATIVE_END;
	}
	void AShooterTestsDevicePropertyTester::StaticRegisterNativesAShooterTestsDevicePropertyTester()
	{
		UClass* Class = AShooterTestsDevicePropertyTester::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ApplyDeviceProperties", &AShooterTestsDevicePropertyTester::execApplyDeviceProperties },
			{ "OnEndOverlap", &AShooterTestsDevicePropertyTester::execOnEndOverlap },
			{ "OnOverlapBegin", &AShooterTestsDevicePropertyTester::execOnOverlapBegin },
			{ "RemoveDeviceProperties", &AShooterTestsDevicePropertyTester::execRemoveDeviceProperties },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics
	{
		struct FPlatformUserId
		{
			int32 InternalId;
		};

		struct ShooterTestsDevicePropertyTester_eventApplyDeviceProperties_Parms
		{
			FPlatformUserId UserId;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UserId_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_UserId;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::NewProp_UserId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::NewProp_UserId = { "UserId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventApplyDeviceProperties_Parms, UserId), Z_Construct_UScriptStruct_FPlatformUserId, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::NewProp_UserId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::NewProp_UserId_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::NewProp_UserId,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::Function_MetaDataParams[] = {
		{ "Category", "Device Property" },
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AShooterTestsDevicePropertyTester, nullptr, "ApplyDeviceProperties", nullptr, nullptr, sizeof(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::ShooterTestsDevicePropertyTester_eventApplyDeviceProperties_Parms), Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics
	{
		struct ShooterTestsDevicePropertyTester_eventOnEndOverlap_Parms
		{
			UPrimitiveComponent* OverlappedComponent;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnEndOverlap_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OverlappedComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OverlappedComponent_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnEndOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnEndOverlap_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherComp_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnEndOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OverlappedComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::NewProp_OtherBodyIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AShooterTestsDevicePropertyTester, nullptr, "OnEndOverlap", nullptr, nullptr, sizeof(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::ShooterTestsDevicePropertyTester_eventOnEndOverlap_Parms), Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics
	{
		struct ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms
		{
			UPrimitiveComponent* OverlappedComponent;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
			bool bFromSweep;
			FHitResult SweepHitResult;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
		static void NewProp_bFromSweep_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SweepHitResult_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SweepHitResult;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OverlappedComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OverlappedComponent_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherComp_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit(void* Obj)
	{
		((ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms*)Obj)->bFromSweep = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms), &Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_SweepHitResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_SweepHitResult = { "SweepHitResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms, SweepHitResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_SweepHitResult_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_SweepHitResult_MetaData)) }; // 1287526515
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OverlappedComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_OtherBodyIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_bFromSweep,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::NewProp_SweepHitResult,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AShooterTestsDevicePropertyTester, nullptr, "OnOverlapBegin", nullptr, nullptr, sizeof(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::ShooterTestsDevicePropertyTester_eventOnOverlapBegin_Parms), Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties_Statics::Function_MetaDataParams[] = {
		{ "Category", "Device Property" },
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AShooterTestsDevicePropertyTester, nullptr, "RemoveDeviceProperties", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AShooterTestsDevicePropertyTester);
	UClass* Z_Construct_UClass_AShooterTestsDevicePropertyTester_NoRegister()
	{
		return AShooterTestsDevicePropertyTester::StaticClass();
	}
	struct Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_DeviceProperties_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DeviceProperties_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_DeviceProperties;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CollisionVolume_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_CollisionVolume;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_PlatformMesh;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ActivePropertyHandles_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActivePropertyHandles_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_ActivePropertyHandles;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ShooterTestsRuntime,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AShooterTestsDevicePropertyTester_ApplyDeviceProperties, "ApplyDeviceProperties" }, // 3718432134
		{ &Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnEndOverlap, "OnEndOverlap" }, // 129900333
		{ &Z_Construct_UFunction_AShooterTestsDevicePropertyTester_OnOverlapBegin, "OnOverlapBegin" }, // 1213644529
		{ &Z_Construct_UFunction_AShooterTestsDevicePropertyTester_RemoveDeviceProperties, "RemoveDeviceProperties" }, // 2287167935
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** This tester will apply device properties to a Player Controller on overlap, and remove them once overlap ends. */" },
		{ "IncludePath", "ShooterTestsDevicePropertyTester.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
		{ "ToolTip", "This tester will apply device properties to a Player Controller on overlap, and remove them once overlap ends." },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties_Inner = { "DeviceProperties", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_UInputDeviceProperty_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties_MetaData[] = {
		{ "Category", "Device Property" },
		{ "Comment", "/** Device properties to apply on overlap with a player controller. */" },
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
		{ "ToolTip", "Device properties to apply on overlap with a player controller." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties = { "DeviceProperties", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AShooterTestsDevicePropertyTester, DeviceProperties), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_CollisionVolume_MetaData[] = {
		{ "Category", "Device Property" },
		{ "Comment", "/** The volume that will trigger device properties to be added and removed on overlap */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
		{ "ToolTip", "The volume that will trigger device properties to be added and removed on overlap" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_CollisionVolume = { "CollisionVolume", nullptr, (EPropertyFlags)0x001400000009001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AShooterTestsDevicePropertyTester, CollisionVolume), Z_Construct_UClass_UCapsuleComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_CollisionVolume_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_CollisionVolume_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_PlatformMesh_MetaData[] = {
		{ "Category", "Device Property" },
		{ "Comment", "/** A little mesh to make this collision volume visible */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
		{ "ToolTip", "A little mesh to make this collision volume visible" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_PlatformMesh = { "PlatformMesh", nullptr, (EPropertyFlags)0x001400000009001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AShooterTestsDevicePropertyTester, PlatformMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_PlatformMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_PlatformMesh_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles_ElementProp = { "ActivePropertyHandles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UScriptStruct_FInputDevicePropertyHandle, METADATA_PARAMS(nullptr, 0) }; // 1447277002
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles_MetaData[] = {
		{ "ModuleRelativePath", "Private/ShooterTestsDevicePropertyTester.h" },
	};
#endif
	static_assert(TModels<CGetTypeHashable, FInputDevicePropertyHandle>::Value, "The structure 'FInputDevicePropertyHandle' is used in a TSet but does not have a GetValueTypeHash defined");
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles = { "ActivePropertyHandles", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(AShooterTestsDevicePropertyTester, ActivePropertyHandles), METADATA_PARAMS(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles_MetaData)) }; // 1447277002
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_DeviceProperties,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_CollisionVolume,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_PlatformMesh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::NewProp_ActivePropertyHandles,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShooterTestsDevicePropertyTester>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::ClassParams = {
		&AShooterTestsDevicePropertyTester::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AShooterTestsDevicePropertyTester()
	{
		if (!Z_Registration_Info_UClass_AShooterTestsDevicePropertyTester.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShooterTestsDevicePropertyTester.OuterSingleton, Z_Construct_UClass_AShooterTestsDevicePropertyTester_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AShooterTestsDevicePropertyTester.OuterSingleton;
	}
	template<> SHOOTERTESTSRUNTIME_API UClass* StaticClass<AShooterTestsDevicePropertyTester>()
	{
		return AShooterTestsDevicePropertyTester::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AShooterTestsDevicePropertyTester);
	AShooterTestsDevicePropertyTester::~AShooterTestsDevicePropertyTester() {}
	struct Z_CompiledInDeferFile_FID_Unreal_Projects_LyraStarterGameEx1_Plugins_GameFeatures_ShooterTests_Source_ShooterTestsRuntime_Private_ShooterTestsDevicePropertyTester_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_LyraStarterGameEx1_Plugins_GameFeatures_ShooterTests_Source_ShooterTestsRuntime_Private_ShooterTestsDevicePropertyTester_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AShooterTestsDevicePropertyTester, AShooterTestsDevicePropertyTester::StaticClass, TEXT("AShooterTestsDevicePropertyTester"), &Z_Registration_Info_UClass_AShooterTestsDevicePropertyTester, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShooterTestsDevicePropertyTester), 1217995105U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_LyraStarterGameEx1_Plugins_GameFeatures_ShooterTests_Source_ShooterTestsRuntime_Private_ShooterTestsDevicePropertyTester_h_3436054768(TEXT("/Script/ShooterTestsRuntime"),
		Z_CompiledInDeferFile_FID_Unreal_Projects_LyraStarterGameEx1_Plugins_GameFeatures_ShooterTests_Source_ShooterTestsRuntime_Private_ShooterTestsDevicePropertyTester_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_LyraStarterGameEx1_Plugins_GameFeatures_ShooterTests_Source_ShooterTestsRuntime_Private_ShooterTestsDevicePropertyTester_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
