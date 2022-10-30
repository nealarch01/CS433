#include "readyqueue.h"
#include <iostream> 

using namespace std;

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done.
// Remember to add sufficient comments to your code

/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue() {
  currentSize = 0; // Initialize the array with 0 items.
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
  // When adding a PCB to the queue, you must change its state to READY.
  pcbPtr->setState(ProcState::READY); // Set the state

  pcbQueue[currentSize] = pcbPtr; // Add pointer to PCB into the queue
  currentSize++; // Increment the size of the ReadyQueue

  sort(); // Call the sorting algorithm
}

// An iterative sorting algorithm (Insertion Sort)
// This is the ideal sorting algorithm as the array is nearly sorted
void ReadyQueue::sort() {
  // Iterate through the elements of the ReadyQueue
  for (int i = 1; i < currentSize; i++) { 
    int j = i; // Set the inner loop variable counter j

    // Iterate backwards while j is greater than zero
    // - And the element previous to j (j - 1) is greater than the current index of j
    while (j > 0 && pcbQueue[j - 1]->priority > pcbQueue[j]->priority) {
      // Do a swap
      PCB *temp = pcbQueue[j]; // Temporarily stores our swapping element
      pcbQueue[j] = pcbQueue[j - 1]; // Overwrites the element with the previous
      pcbQueue[j - 1] = temp; // Sets the previous to the swapped element
      j--; // Decrement the trailing pointer
    }
  }
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB *ReadyQueue::removePCB() {
  // When removing a PCB from the queue, you must change its state to RUNNING.
  // 1, 2, 9 [Lowest to Highest] 
  PCB *temp = pcbQueue[currentSize - 1]; // Set a temporary pointer object to obtain the PCB with the greatest priority
  temp->setState(ProcState::RUNNING); // Set the current state to running
  pcbQueue[currentSize - 1] = nullptr; // Avoid a dangling pointer by setting the top most index to nullptr
  currentSize--; // Decrement the currentSize
  return temp; // Return 
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
  return currentSize; // Returns the current size of the ReadyQueue
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
  cout << "Display Processes in ReadyQueue: " << endl;
  // Iterate backwards to display the PCBs with the greatest priority at the top
  for (int i = currentSize - 1; i >= 0; i--) {
    pcbQueue[i]->display(); // Call the PCB display method
  }
}