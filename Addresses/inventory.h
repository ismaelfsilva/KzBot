#ifndef INVENTORY_ADDR_H
#define INVENTORY_ADDR_H


#include <cstdint>
namespace Addresses {

class Inventory
{
public:
    static uint32_t getPointer() { return m_pointer; }
    static void setPointer(uint32_t value) { m_pointer = value; }

    static uint32_t getInventoryContainerPointer() { return m_inventoryContainerPointer; }
    static void setInventoryContainerPointer(uint32_t value) { m_inventoryContainerPointer = value; }

    static uint32_t getInventoryContainerItemList() { return m_inventoryContainerItemList; }
    static void setInventoryContainerItemList(uint32_t value) { m_inventoryContainerItemList = value; }

    static uint32_t getContainersPointer() { return m_containersPointer; }
    static void setContainersPointer(uint32_t value) { m_containersPointer = value; }

private:
    static uint32_t m_pointer;

    static uint32_t m_inventoryContainerPointer;
    static uint32_t m_inventoryContainerItemList;
    static uint32_t m_containersPointer;
};
}
#endif // INVENTORY_ADDR_H
