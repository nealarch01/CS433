/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Ahmed Ali, Neal Archival (TODO: your name)
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <iostream>
#include "fifo_replacement.h"

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    page_table[page_num].frame_num = max_frames - num_frames; // Assigning it
    page_table[page_num].valid = true; // 
    page_queue.push(page_num);
    num_frames--;
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    int front_num = page_queue.front(); // Get the page number top of the queue
    page_queue.pop();
    page_queue.push(page_num);
    // page_table[page_num].frame_num = page_table[front_num].frame_num; // Set the frame number
    page_table[page_num].valid = true;
    page_table[front_num].valid = false; // Set to false
    return 0;
}