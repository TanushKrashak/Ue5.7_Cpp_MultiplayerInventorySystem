// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Cpp_GridTypes.h"
#include "Cpp_WGT_InventoryGrid.generated.h"

struct FIconItemFragment;
struct FGridItemFragment;
// Forward Declarations
class UCpp_WGT_SlottedItem;
struct FCpp_ItemManifest;
class UCpp_AC_Item;
class UCpp_AC_Inventory;
class UUniformGridPanel;
class UCpp_WGT_GridSlot;

/**
 * 
 */
UCLASS()
class MULTIPLAYERINVENTORY_API UCpp_WGT_InventoryGrid : public UUserWidget {
	GENERATED_BODY()
	
public:
	//=================================================================================================================
	// FUNCTIONS
	//=================================================================================================================
	FORCEINLINE EItemCategory GetItemCategory() const { return ItemCategory; }
	FSlotAvailabilityResult HasRoomForItem(const UCpp_AC_Item* ItemComp);
	
	UFUNCTION()
	void AddItem(UCpp_InventoryItem* Item, bool bRemoved);
	
protected:
	//=================================================================================================================
	// FUNCTIONS
	//=================================================================================================================
	virtual void NativeOnInitialized() override;
	
	void ConstructGrid();
	
	bool MatchesCategory(const UCpp_InventoryItem* Item) const;
	FVector2D GetDrawSize(const FGridItemFragment* Fragment) const;
	
	void SetSlottedItemImage(const UCpp_WGT_SlottedItem* SlottedItem, const FGridItemFragment* GridFrag, const FIconItemFragment* IconFrag) const;
	
	
	FSlotAvailabilityResult HasRoomForItem(const UCpp_InventoryItem* Item);
	FSlotAvailabilityResult HasRoomForItem(const FCpp_ItemManifest& Item);
	
	void AddItemToIndices(const FSlotAvailabilityResult& Result, UCpp_InventoryItem* Item);
	void AddItemToIndex(UCpp_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount) const;
	UCpp_WGT_SlottedItem* CreateSlottedItem(UCpp_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount, const FGridItemFragment* GridFrag, const FIconItemFragment* IconFrag) const;
	
	//=================================================================================================================
	// PROPERTIES & VARIABLES
	//=================================================================================================================
	TWeakObjectPtr<UCpp_AC_Inventory> InventoryComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	EItemCategory ItemCategory;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UCpp_WGT_GridSlot> GridSlotClass;
	UPROPERTY() 
	TArray<TObjectPtr<UCpp_WGT_GridSlot>> GridSlots;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UCpp_WGT_SlottedItem> SlottedItemClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel;
	UPROPERTY(EditAnywhere, Category="Inventory")
	int16 GridRowCount = 5;
	UPROPERTY(EditAnywhere, Category="Inventory")
	int16 GridColumnCount = 10;
	UPROPERTY(EditAnywhere, Category="Inventory")
	float GridSlotSize = 50.f;
	
};
