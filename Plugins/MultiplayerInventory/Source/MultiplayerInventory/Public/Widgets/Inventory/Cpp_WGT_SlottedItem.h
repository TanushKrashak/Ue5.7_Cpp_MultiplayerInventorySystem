// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_SlottedItem.generated.h"

class UCpp_InventoryItem;
// Forward Declarations
class UImage;

/**
 * 
 */
UCLASS()
class MULTIPLAYERINVENTORY_API UCpp_WGT_SlottedItem : public UUserWidget {
	GENERATED_BODY()
	
public:
	//=================================================================================================================
	// FUNCTIONS
	//=================================================================================================================
	FORCEINLINE UImage* GetImageIcon() const { return IMG_Icon; }
	
	FORCEINLINE void SetGridIndex(const int32 Index) { GridIndex = Index; }
	FORCEINLINE int32 GetGridIndex() const { return GridIndex; }
	FORCEINLINE void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
	FORCEINLINE FIntPoint GetGridDimensions() const { return GridDimensions; }
	
	FORCEINLINE void SetIsStackable(const bool bStackable) { bIsStackable = bStackable; }
	

private:
	//=================================================================================================================
	// PROPERTIES & VARIABLES
	//=================================================================================================================
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IMG_Icon;
	
	FIntPoint GridDimensions;
	int32 GridIndex;
	
	TWeakObjectPtr<UCpp_InventoryItem> InventoryItem;
	
	bool bIsStackable = false;
};
