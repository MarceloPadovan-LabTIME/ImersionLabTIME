// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolInterface.generated.h"

/**
* This is the interface definition for UObjects.
* This is needed so we can create blueprint types from this interface.
*/
UINTERFACE(BlueprintType)
class UObjectPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/** 
* Actual implementation of the interface.
* This will deal with the functionalities called from the pool manager.
* Thus, has methods for when the object is created, when it's spawned from 
* the pool, when it's despawned to pool and etc.
*/
class OBJECTPOOLING_API IObjectPoolInterface
{
	GENERATED_BODY()

public:
	/** 
	* Called when the object is created for the first time. 
	* This is where we should put the object's initialization that 
	* it's called when the object is actually created.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCreated();

	/** 
	* Called when the object is removed from the pool. 
	* This means this object will no longer be available to be retrived and
	* reused by the pool manager.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnClearedFromPool();

	/** 
	* Called when the actor is spawned from the pool.
	* This is may be where we put the object's reutilization code.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSpawnedFromPool();

	/** 
	* Called when the actor is returned to the pool.
	* This is may be where we put the object's reutilization code.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDespawnedToPool();
};
