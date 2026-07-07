// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Spatial/Cpp_WGT_InventoryGrid.h"

#include "Components/UniformGridPanel.h"
#include "InventoryManagement/Cpp_AC_Inventory.h"
#include "InventoryManagement/Cpp_BFL_InventoryStatics.h"
#include "Items/Cpp_InventoryItem.h"
#include "Items/Components/Cpp_AC_Item.h"
#include "Items/Fragment/Cpp_ItemFragment.h"
#include "Items/Manifest/Cpp_ItemManifest.h"
#include "Widgets/GridSlots/Cpp_WGT_GridSlot.h"
#include "Widgets/Inventory/Cpp_WGT_SlottedItem.h"
#include "Widgets/Utils/Cpp_BFL_WidgetUtils.h"

FSlotAvailabilityResult UCpp_WGT_InventoryGrid::HasRoomForItem(const UCpp_AC_Item* ItemComp) {
	return HasRoomForItem(ItemComp->GetItemManifest());
}

void UCpp_WGT_InventoryGrid::AddItem(UCpp_InventoryItem* Item, bool bRemoved) {
	if (bRemoved) {
		return;
	}
	if (!MatchesCategory(Item)) {
		return; 
	}

	const FSlotAvailabilityResult Result = HasRoomForItem(Item);
	AddItemToIndices(Result, Item);
}

void UCpp_WGT_InventoryGrid::NativeOnInitialized() {
	Super::NativeOnInitialized();
	
	ConstructGrid();
	
	InventoryComponent = UCpp_BFL_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	InventoryComponent->OnItemUpdated.AddDynamic(this, &ThisClass::AddItem);
}

void UCpp_WGT_InventoryGrid::ConstructGrid() {
	GridSlots.Reserve(GridRowCount * GridColumnCount);
	for (int16 Row = 0; Row < GridRowCount; Row++) {
		for (int16 Col = 0; Col < GridColumnCount; Col++) {
			UCpp_WGT_GridSlot* GridSlot = CreateWidget<UCpp_WGT_GridSlot>(this, GridSlotClass);
			GridPanel->AddChildToUniformGrid(GridSlot ,Row, Col);

			const int16 Index = UCpp_BFL_WidgetUtils::GetIndexFromPosition(FIntPoint(Row, Col), GridColumnCount);
			GridSlot->InitGridSlot(Index, GridSlotSize);
		}
	}
}

bool UCpp_WGT_InventoryGrid::MatchesCategory(const UCpp_InventoryItem* Item) const {
	return Item->GetItemManifest().GetItemCategory() == GetItemCategory();
}

FVector2D UCpp_WGT_InventoryGrid::GetDrawSize(const FGridItemFragment* Fragment) const {
	const float IconTileWidth = GridSlotSize - (Fragment->GetGridPadding() * 2);
	const FVector2D IconSize = Fragment->GetGridSize() * IconTileWidth;
	return IconSize;
}

void UCpp_WGT_InventoryGrid::SetSlottedItemImage(const UCpp_WGT_SlottedItem* SlottedItem, const FGridItemFragment* GridFrag,
	const FIconItemFragment* IconFrag) const {
	FSlateBrush Brush;
	Brush.SetResourceObject(IconFrag->GetIcon());
	Brush.DrawAs = ESlateBrushDrawType::Image;
	Brush.ImageSize = GetDrawSize(GridFrag);
	SlottedItem->SetImageBrush(Brush);
}

FSlotAvailabilityResult UCpp_WGT_InventoryGrid::HasRoomForItem(const UCpp_InventoryItem* Item) {
	return HasRoomForItem(Item->GetItemManifest());
}
FSlotAvailabilityResult UCpp_WGT_InventoryGrid::HasRoomForItem(const FCpp_ItemManifest& Item) {
	FSlotAvailabilityResult Result;
	Result.TotalAmountToFill = 1;
	
	FSlotAvailability SlotAvailability;
	SlotAvailability.AmountToFill = 1;
	SlotAvailability.Index = 0;
	
	Result.AvailableSlots.Emplace(SlotAvailability);
	return Result;
}

void UCpp_WGT_InventoryGrid::AddItemToIndices(const FSlotAvailabilityResult& Result, UCpp_InventoryItem* Item) {
	for (const auto& Slot : Result.AvailableSlots) {
		AddItemToIndex(Item, Slot.Index, Result.bStackable, Slot.AmountToFill);
	}
}

void UCpp_WGT_InventoryGrid::AddItemToIndex(UCpp_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount) const {
	const FGridItemFragment* GridFrag = GetFragment<FGridItemFragment>(Item, Fragment::Grid);
	const FIconItemFragment* IconFrag = GetFragment<FIconItemFragment>(Item, Fragment::Icon);
	if (!GridFrag || !IconFrag) {
		return;
	}
	
	auto* SlottedItem = CreateSlottedItem(Item, Index, bStackable, StackAmount, GridFrag, IconFrag);
	
}

UCpp_WGT_SlottedItem* UCpp_WGT_InventoryGrid::CreateSlottedItem(UCpp_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount, const FGridItemFragment* GridFrag, const FIconItemFragment* IconFrag) const {
	UCpp_WGT_SlottedItem* SlottedItem = CreateWidget<UCpp_WGT_SlottedItem>(GetOwningPlayer(), SlottedItemClass);
	SlottedItem->SetInventoryItem(Item);
	SetSlottedItemImage(SlottedItem, GridFrag, IconFrag);
	SlottedItem->SetGridIndex(Index);
	return SlottedItem;
}
 