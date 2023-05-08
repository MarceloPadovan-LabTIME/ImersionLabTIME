// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#include "PoolManagerBase.h"
#include "ObjectPoolInterface.h"
#include "ObjectPooling/ObjectPoolingLogDeclaration.h"

UPoolManagerBase::UPoolManagerBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPoolManagerBase::BeginPlay()
{
	Super::BeginPlay();

	// If we should spawn objects on the begin play:
	if (bSpawnPoolObjectsOnBeginPlay)
	{
		// Add the initial pool size amount of object to the pool
		AddObjectsToPool(InitialPoolSize);
	}
}

void UPoolManagerBase::AddObjectsToPool(int const ObjectsNumber)
{
	// If we do not have the pool object to create, return error
	if (!ObjectToBePooled)
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("Could not add new object to the pool \
			as Object to create is null."));
		return;
	}

	// Create all the objects:
	for (int i = 0; i < ObjectsNumber; i++)
	{
		// Instantiates a new object from the reference set on properties
		UObject* Object = CreateObject();
		if (!Object)
		{
			UE_LOG(LogObjectPooling, Error,
				TEXT("Error while creating new object for pool"));
			continue;
		}

		// Add the newly created object to the inactive objects list
		InactiveObjects.Add(Object);
	}
}

UObject* UPoolManagerBase::SpawnObjectFromPool()
{
	// Check if there is any inactive object
	if (InactiveObjects.Num() < 1)
	{
		UE_LOG(LogObjectPooling, Warning, TEXT("No inactive objects to spawn.\
			Consider increasing the pool size"));
		return nullptr;
	}

	// Pop the first object from the inactive objects array for reuse
	UObject* SpawnedObject = InactiveObjects.Pop();
	if (!SpawnedObject)
	{
		UE_LOG(LogObjectPooling, Error, 
			TEXT("Spawned object from pool is null."));
		return nullptr;
	}

	// Remove the object from the inactive objects array and 
	// add it to the active objects array
	InactiveObjects.Remove(SpawnedObject);
	ActiveObjects.Add(SpawnedObject);

	// Broadcast that a new object is being reused from the pool
	OnObjectSpawnedFromPool.Broadcast(SpawnedObject);

	// Call the OnSpawnedFromPool function on the object
	IObjectPoolInterface::Execute_OnSpawnedFromPool(SpawnedObject);
	return SpawnedObject;
}

void UPoolManagerBase::ReturnObjectToPool(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("Can not return null object to pool."));
		return;
	}

	// Check if the object is on the active objects list
	if (!ActiveObjects.Contains(Object))
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("Object is not on active object \
			lists when returning to pool"));
		return;
	}

	// Remove the object from the active objects array and 
	// add it to the inactive objects array
	ActiveObjects.Remove(Object);
	InactiveObjects.Add(Object);

	// Broadcast that this object has returned to the pool
	OnObjectReturnedToPool.Broadcast(Object);

	// Call the OnDespawnedToPool function on the object
	IObjectPoolInterface::Execute_OnDespawnedToPool(Object);
}

void UPoolManagerBase::EmptyPool()
{
	// Clear the list of active and inactive objects
	ClearListOfObjects(ActiveObjects);
	ClearListOfObjects(InactiveObjects);
}

UObject* UPoolManagerBase::CreateObject()
{
	if (!ObjectToBePooled)
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("Could not create new object on the pool \
			as Object to create is null."));
		return nullptr;
	}

	// Check if the object to create is a AActor
	const bool bIsObjectAActor = ObjectToBePooled->
		IsChildOf(AActor::StaticClass());
	
	// Create the new object. If it's a actor, create it as so
	// If not, just create a new UObject
	UObject* Object =  (bIsObjectAActor) ?
		Object = CreateActor() :
		Object = NewObject<UObject>(this, ObjectToBePooled);

	// Call the OnCreated function on the created object 
	IObjectPoolInterface::Execute_OnCreated(Object);
	return Object;
}

AActor* UPoolManagerBase::CreateActor()
{
	if (!ObjectToBePooled)
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("Could not create new actor object on the pool \
			as Object to create is null."));
		return nullptr;
	}

	// Check if the object to be pooled is an AActor
	if (!ObjectToBePooled->IsChildOf(AActor::StaticClass()))
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("Object to create on pool is not a actor."));
		return nullptr;
	}

	// Spawn the new actor
	const auto& NewActorObject = GetWorld()->SpawnActor(ObjectToBePooled);
	if (!NewActorObject)
	{
		UE_LOG(LogObjectPooling, Error,
			TEXT("There was an error while creating \
			the new actor object on pool."));
		return nullptr;
	}

	// Set the actor properties. It should be hidden as the actor is inactive
	NewActorObject->SetActorHiddenInGame(true);
	NewActorObject->SetActorEnableCollision(false);
	NewActorObject->SetActorTickEnabled(false);

	// Call the OnCreated function on the object
	IObjectPoolInterface::Execute_OnCreated(NewActorObject);
	return NewActorObject;
}

void UPoolManagerBase::ClearListOfObjects
	(TArray<UObject*>& ListOfObjectsToClear)
{
	// Foreach object on the list:
	for (const auto& Object : ListOfObjectsToClear)
	{
		if (!Object)
		{
			continue;
		}

		// Ensure that the object implements the interface
		if (!Object->GetClass()->ImplementsInterface
			(UObjectPoolInterface::StaticClass()))
		{
			continue;
		}

		// Call the OnDespawnedToPool function on the object
		IObjectPoolInterface::Execute_OnClearedFromPool(Object);
	}

	// Clear the list
	ListOfObjectsToClear.Empty();
}
