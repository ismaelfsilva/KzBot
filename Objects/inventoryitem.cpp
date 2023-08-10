#include "inventoryitem.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/client.h"

using namespace Objects;

InventoryItem::InventoryItem(uint32_t addr)
{
    m_address = addr;
}

InventorySlot InventoryItem::getSlot()
{
    return (InventorySlot)Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Client::getInventoryItemSlot());
}

bool InventoryItem::isEquipped()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Client::getInventoryItemIsEquipped()) > 0;
}

uint32_t InventoryItem::getId()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Client::getInventoryItemId());
}

uint32_t InventoryItem::getCount()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Client::getInventoryItemCount());
}
