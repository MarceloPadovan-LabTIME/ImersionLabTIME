// 2023 Copyright Labverso, Brazil. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolManagerBase.generated.h"

/** 
* Delegate called when a new object is spawned from the pool. 
* It will broadcast the object that is being reused.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectSpawnedFromPool, 
	UObject*, SpawnedObject);

/**
* Delegate called when a new object returns to the pool.
* It will broadcast the object that is returning to the pool.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectReturnedToPool, 
	UObject*, ReturnedObject);

/** 
* This is the actor component that deals with the object pooling managment.
* Thus, it has properties such as to set which object should be created and 
* the pool size.
* 
* Also, deals with the pool managment by creating new objects, reusing and
* returning objects to the pool.
* 
* @note The pool is consists of a list of both active and inactive objects.
* The active objects are the ones that are being used at the moment. The list
* of inactive objects are the ones that can be reused when we have a spawn
* request for a new object.
* 
* @see ObjectPoolInterface
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OBJECTPOOLING_API UPoolManagerBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPoolManagerBase();

public:
	/** 
	* Add the given number of objects to the pool.
	* This will create new objects instances and store them on a list of 
	* inactive objects.
	* 
	* @param ObjectsNumber The amount of objects to create
	*/
	UFUNCTION(BlueprintCallable, Meta=(Keywords="object pool, pool, object"))
	void AddObjectsToPool(int const ObjectsNumber);

	/** 
	* Retrieves an object from the pool. 
	* This is the equivalent of spawning a new object. Here instead, we will
	* reuse a object from the inactive objects list and 
	* add it to the active list (as it's being used at the moment).
	* 
	* This is where we call the delegate that the object has exited the pool 
	* for a new usage.
	* 
	* The reuse logic should be done by the IObjectPoolInterface object's 
	* implementation.
	* 
	* @return The object ready for reuse
	*/
	UFUNCTION(BlueprintCallable, Meta=(Keywords="object pool, pool, object"))
	UObject* SpawnObjectFromPool();

	/** 
	* Returns an object to the pool.
	* This is where we call the delegate that the object has returned to the 
	* pool.
	* 
	* Here, we will get the object from the active list of objects and add it
	* to the inactive objects list.
	* 
	* @param Object The object reference to return to the pool
	*/
	UFUNCTION(BlueprintCallable)
	void ReturnObjectToPool(UObject* Object);

	/** Empties the pool, clearing both active and inactive objects list. */
	UFUNCTION(BlueprintCallable)
	void EmptyPool();

public:
	/** 
	* Getter to the pool's current size. 
	* I.e, the amount of objects being managed by the pool manager. 
	* 
	* @return The current size of the pool being managed
	*/
	UFUNCTION(BlueprintCallable)
	inline int32 GetPoolSize() const 
		{ return ActiveObjects.Num() + InactiveObjects.Num(); }

	/** 
	* Checks if the given object is in use at the moment. 
	* 
	* @param Object The object to check if it's being used
	* @return True if the objet is being used and false otherwise
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool IsObjectInUse(UObject* Object) const
		{ return ActiveObjects.Contains(Object); }

	/** 
	* Check if there is any free object in the pool. 
	* I.e., if there's any object is ready for reuse. 
	* 
	* @return True if there's at least one object ready for reuse
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool HasPoolFreeObject() const
		{ return InactiveObjects.Num() > 0; }

	/** Get the current active objects from the pool */
	UFUNCTION(BlueprintCallable)
	inline TArray<UObject*> GetActiveObjectsFromPool() const
		{ return ActiveObjects; }

	/** Get the current inactive objects from the pool */
	UFUNCTION(BlueprintCallable)
	inline TArray<UObject*> GetInactiveObjectsFromPool() const
		{ return InactiveObjects; }

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Creates a new instance of the object set on this pool manager. */
	virtual UObject* CreateObject();

	/** 
	* Creates a new instance of the object that is of Actor type.
	* This is needed as the instantiation of a AActor is diferent than a 
	* simple UObject.
	*/
	virtual AActor* CreateActor();

private:
	/** 
	* Clears the given list of objects.
	*
	* @param Pool The list of objects to clear from the pool
	*/
	virtual void ClearListOfObjects(TArray<UObject*>& Pool);

public:
	/** The class of the object to be pooled. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSubclassOf<UObject> ObjectToBePooled;

	/** 
	* The initial pool size. This is the size of the pool at begin play,
	* but it might be resized according to the pool's usage.
	* 
	* This is used to initialize the pool on begin play if needed.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 InitialPoolSize = 0;

	/** 
	* Flag that indicates if we should fill the pool of objects on BeginPlay.
	* This will create the amount of objects to fill the whole pool size and
	* add them to the inactive objects list.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn="true"))
	bool bSpawnPoolObjectsOnBeginPlay = true;

	/** Event dispatcher for when a new object is being spawned from pool */
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FObjectSpawnedFromPool OnObjectSpawnedFromPool;

	/** Event dispatcher for when a active object is returning to the pool */
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FObjectReturnedToPool OnObjectReturnedToPool;

protected:
	/**
	* The list of active objects of the pool.
	* These are the ones that is being used at the moment.
	*/
	TArray<UObject*> ActiveObjects;

	/** 
	* The list of inactive objects of the pool. 
	* These are the ones ready for reuse.
	*/
	TArray<UObject*> InactiveObjects;
};
