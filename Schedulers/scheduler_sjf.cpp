/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Neal Archival and Ahmed Ali (TODO: your name)
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
// TODO: add implementation of SchedulerFCFS constructor, destrcutor and
// member functions init, print_results, and simulate here

SchedulerSJF::SchedulerSJF() {
    waitAvg = 0.0;
    turnAvg = 0.0;
    processTotal = 0;
}

SchedulerSJF::~SchedulerSJF() {}

void SchedulerSJF::init(std::vector<PCB>& process_list) {
    processTotal = process_list.size();
    originalProcList = process_list; // Save the original process list

    std::sort(process_list.begin(), process_list.end(), [](PCB &left, PCB &right) {
        return left.burst_time < right.burst_time;
    });

    for (int i = 0; i < processTotal; i++) {
        processes.push(&process_list[i]); // While the processes

        std::cout << "Running process " << process_list[i].name << " for "
                  << process_list[i].burst_time << " time units." << endl;
    }
}

void SchedulerSJF::simulate() {
    double trailing = 0;       // The cumulative time of all processes
    double sumOfTrailing = 0;  // The sum of all trailing times

    std::unordered_map<string, PCB*> umap; // <nameOfPCB, pointerToPCB>

    // Print the entire array starting from T1
    for (int i = 0; i < processTotal; i++) {
        PCB* proc = processes.front(); // Get the front of the queue
        proc->r_wait_time = trailing; // Set the relative wait time
        trailing += proc->burst_time; // Add the burst time to the trailing
        proc->r_turn_time = trailing; // Set the relative turn around time
        umap[proc->name] = proc; // Access the PCB by name and set the pointer to the PCB
        sumOfTrailing += trailing; // Get the cumulative sum of trailing
        processes.pop(); // Continue to the next process
    }

    waitAvg = ((sumOfTrailing - trailing) / processTotal); // Calculate average wait time
    turnAvg = sumOfTrailing / processTotal; // Calculate average turn around time

    // Loop to print starting from T1 to T8
    for (int i = 0; i < processTotal; i++) {
        PCB* proc = umap[originalProcList[i].name];  // Returns PCB object
        std::cout << originalProcList[i].name << " turn-around time "
                  << proc->r_turn_time
                  << ", waiting time = " << proc->r_wait_time << endl;
    }
}

void SchedulerSJF::print_results() {
    std::cout << "Average turn-around time = " << turnAvg
              << ", Average waiting = " << waitAvg << "\n";
}
