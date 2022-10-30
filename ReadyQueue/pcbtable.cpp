/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Neal Archival, Ahmed Ali
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h" 

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   table = vector<PCB *>(size); // Initialize array with specified size.
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    // For loop that iterates through the entire table
    for (int i = 0; i < table.size(); i++) 
    { // Loop
        delete table[i]; // Delete the allocated memory
    }
    table.clear(); // Clear all pointers in the PCB table
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    return table[idx]; // Return the requested PCB
}

/**
 * @brief Add a PCB to the PCBTable.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    table[idx] = pcb; // Assign the current index to the PCB pointer
}