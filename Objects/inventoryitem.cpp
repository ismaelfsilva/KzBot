#include "inventoryitem.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/inventoryitem.h"

using namespace Objects;

InventoryItem::InventoryItem(uint32_t slotId, uint32_t addr)
{
    m_slotId = slotId;
    m_address = addr;
}

InventorySlot InventoryItem::getSlot()
{
    return (InventorySlot)m_slotId;
}

uint32_t InventoryItem::getItemData()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::InventoryItem::getItemDataPointer());
}

uint32_t InventoryItem::getId()
{
    uint32_t itemData = getItemData();
    if (itemData == 0) return 0;
    uint32_t itemIdPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), getItemData() + Addresses::InventoryItem::getItemDataId());
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), itemIdPointer);
}
