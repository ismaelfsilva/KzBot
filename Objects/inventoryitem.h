#ifndef INVENTORYITEM_OBJ_H
#define INVENTORYITEM_OBJ_H

#include "../Util/Enums.h"
#include <cstdint>


namespace Objects
{

class InventoryItem
{
public:
    InventoryItem(uint32_t slotId, uint32_t addr);

    uint32_t getId();
    uint32_t getCount();
    bool isEquipped();
    InventorySlot getSlot();
    uint32_t getItemData();
private:
    uint32_t m_slotId;
    uint32_t m_address;
};
}
#endif // INVENTORYITEM_H
