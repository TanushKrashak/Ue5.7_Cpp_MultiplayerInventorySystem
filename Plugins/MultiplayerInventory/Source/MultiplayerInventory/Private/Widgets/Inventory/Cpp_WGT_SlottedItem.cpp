// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Inventory/Cpp_WGT_SlottedItem.h"

#include "Items/Cpp_InventoryItem.h"

void UCpp_WGT_SlottedItem::SetInventoryItem(UCpp_InventoryItem* Item) {
	InventoryItem = Item;
}
