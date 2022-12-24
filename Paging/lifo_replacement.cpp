/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the LIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    // TODO: Add necessary code here
    page_table[page_num].frame_num = max_frames - num_frames;
    page_table[page_num].valid = true;
    page_stack.push(page_num);
    num_frames--;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    // TODO: Add necessary code here
    int front_num = page_stack.top();
    page_stack.pop();
    page_stack.push(page_num);
    page_table[page_num].valid = true;
    page_table[front_num].valid = false;
    return 0;
}