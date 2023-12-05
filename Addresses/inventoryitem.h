#ifndef INVENTORYITEM_ADDR_H
#define INVENTORYITEM_ADDR_H


#include <cstdint>
namespace Addresses {

class InventoryItem
{
public:
    static uint32_t getItemDataPointer() { return m_itemDataPointer; }
    static void setItemDataPointer(uint32_t value) { m_itemDataPointer = value; }

    static uint32_t getItemDataId() { return m_itemDataId; }
    static void setItemDataId(uint32_t value) { m_itemDataId = value; }

    static uint32_t getItemSlot() { return m_itemSlot; }
    static void setItemSlot(uint32_t value) { m_itemSlot = value; }

private:
    static uint32_t m_itemDataPointer;

    static uint32_t m_itemDataId;
    static uint32_t m_itemSlot;
};
}
#endif // INVENTORYITEM_ADDR_H
