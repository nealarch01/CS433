/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Ahmed Ali, Neal Archival (TODO: your name)
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>

#include "buffer.h"

// TODO: Add your implementation of the buffer class here

Buffer::Buffer(int size) {
    maxSize = size;
    count = 0;
}

Buffer::~Buffer() {}

bool Buffer::insert_item(buffer_item item) {
    if (!is_full()) {
        items.push_back(item);
        count++;
        return true;
    }
    return false;
}

bool Buffer::remove_item(buffer_item *item) {
    if (!is_empty()) {
        *item = items.front();
        items.pop_front();
        count--;

        return true;
    }

    return false;
}

int Buffer::get_size() {
    return maxSize;
}

int Buffer::get_count() {
    return count;
}

bool Buffer::is_empty() {
  if (count == 0) {
    return true;
  }
  return false; 
}

bool Buffer::is_full() {
    return count >= maxSize;
}

void Buffer::print_buffer() {

  std::cout << "Buffer: [";
  
  if (!is_empty()) {
    // Iterate through the list and display
    for (std::list<buffer_item>::iterator it = items.begin(); it != items.end(); ++it) { // Pointer arithmetic
      std::cout << *it;
      if (it != --items.end()) {
        std::cout << ", ";
      }
    } 
  }

  std::cout << "]" << std::endl;
}