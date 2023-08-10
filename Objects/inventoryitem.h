#ifndef INVENTORYITEM_OBJ_H
#define INVENTORYITEM_OBJ_H

#include "../Util/Enums.h"
#include <cstdint>


namespace Objects
{

class InventoryItem
{
public:
    InventoryItem(uint32_t addr);

    uint32_t getId();
    uint32_t getCount();
    bool isEquipped();
    InventorySlot getSlot();
private:
    uint32_t m_address;
};
}
#endif // INVENTORYITEM_H
