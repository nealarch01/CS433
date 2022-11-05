/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Neal Archival and Ahmed Ali (TODO: your name)
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <iostream>
#include "scheduler_fcfs.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here


SchedulerFCFS::SchedulerFCFS() {
  waitAvg = 0.0;
  turnAvg = 0.0;
  processTotal = 0;
}


SchedulerFCFS::~SchedulerFCFS() {} // Nothing needs to be destructed


void SchedulerFCFS::init(std::vector<PCB> &process_list) {
  processTotal = process_list.size();

  for (int i = 0; i < processTotal; i++) {
      processes.push(&process_list[i]);
      std::cout << "Running process " << process_list[i].name << 
        " for " << process_list[i].burst_time << " time units." << endl;
    }
  
}

//FCFS Wait time is the total burst time added 
//and then subtracted by the last 
void SchedulerFCFS::simulate() {
  double waitCount = processes.front()->burst_time;
  double turnCount = 0; // The cumulative number
  double trailing = 0;
    
  for (int i = 0; i < processTotal; i++) {
    PCB *proc = processes.front();
    trailing += proc->burst_time; // Build the trailing total

    std::cout << proc->name << " has turn-around time " << trailing
      << ", average waiting time " << trailing - proc->burst_time << endl;
    
    turnCount += trailing; // Build the 
    processes.pop(); // Pop the front-most Process
  }
  
  waitAvg = ((turnCount - trailing)) / processTotal; 
  turnAvg = turnCount / processTotal;
}

void SchedulerFCFS::print_results() {
  std::cout << "Average turn-around time = " << turnAvg << ", Average waiting = " << waitAvg << "\n";
}