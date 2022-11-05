/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Neal Archival and Ahmed Ali (TODO: your name)
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_priority.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and
// member functions init, print_results, and simulate here

SchedulerPriority::SchedulerPriority() {
    waitAvg = 0.0;
    turnAvg = 0.0;
    processTotal = 0;
}

SchedulerPriority::~SchedulerPriority() {}

void SchedulerPriority::init(std::vector<PCB>& process_list) {
    processTotal = process_list.size();
    originalProcList = process_list; // Save the original process list

    std::sort(process_list.begin(), process_list.end(), [](PCB &left, PCB &right) {
        return left.priority > right.priority; // Since we are sorting by descending order, we need to reverse the comparison
    });

    for (int i = 0; i < processTotal; i++) {
        processes.push(&process_list[i]); // While the processes

        std::cout << "Running process " << process_list[i].name << " for "
                  << process_list[i].burst_time << " time units." << endl;
    }
}

void SchedulerPriority::simulate() {
    double trailing = 0;       // The cumulative time of all processes
    double sumOfTrailing = 0;  // The sum of all trailing times

    std::unordered_map<string, PCB*> umap;

    for (int i = 0; i < processTotal; i++) {
        PCB* proc = processes.front();
        proc->r_wait_time = trailing;
        trailing += proc->burst_time;
        proc->r_turn_time = trailing;
        umap[proc->name] = proc;
        sumOfTrailing += trailing;
        processes.pop();
    }

    waitAvg = ((sumOfTrailing - trailing) / processTotal);
    turnAvg = sumOfTrailing / processTotal;

    // Loop to print starting from T1 to T8
    for (int i = 0; i < processTotal; i++) {
        PCB* proc = umap[originalProcList[i].name];  // Returns PCB object
        std::cout << originalProcList[i].name << " turn-around time "
                  << proc->r_turn_time
                  << ", waiting time = " << proc->r_wait_time << endl;
    }
}

void SchedulerPriority::print_results() {
    std::cout << "Average turn-around time = " << turnAvg
              << ", Average waiting = " << waitAvg << "\n";
}
