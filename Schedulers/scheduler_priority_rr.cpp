/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Neal Archival and Ahmed Ali (TODO: your name)
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and
// member functions init, print_results, and simulate here

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum)
{
    waitAvg = 0.0;
    turnAvg = 0.0;
    processTotal = 0;
    this->time_quantum = time_quantum;
}

SchedulerPriorityRR::~SchedulerPriorityRR() { }

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    processTotal = process_list.size();
    for (int i = 0; i < processTotal; i++) { // Initialze the list
        processes.push_back(&process_list[i]);
        originalProcList.push_back(&process_list[i]);
    }
}

void SchedulerPriorityRR::simulate() {
    PCB *currentProc;
    double trailing = 0;

    while (!processes.empty()) {
        processes.sort([](PCB *left, PCB *right) {
            return left->priority > right->priority; // Sort the array
        });
        currentProc = processes.front();
        if (currentProc->time_remaining > time_quantum) {
            currentProc->time_remaining -= time_quantum;
            trailing += time_quantum; // Increment by the time quantum
            processes.push_back(currentProc);
            std::cout << "Running process " << currentProc->name << " for "
                      << time_quantum << " time units." << endl;
        } else if (currentProc->time_remaining <= time_quantum) {
            trailing += currentProc->time_remaining; // Increment by how much time is left
            currentProc->r_turn_time = trailing; // Only assign turnaround and waiting time when the process has completed (burst time <= time quantum)
            currentProc->r_wait_time = trailing - currentProc->burst_time;
            // First print the process name and the remaining burst time
            std::cout << "Running process " << currentProc->name << " for "
                      << currentProc->time_remaining << " time units." << endl; 
            currentProc->time_remaining = 0; // Set the time remaining to 0 since it can be completed here
        }
        processes.pop_front();
    }

    double turnCount = 0;
    double waitCount = 0;

    for (int i = 0; i < processTotal; i++) {
        PCB *proc = originalProcList[i];
        turnCount += proc->r_turn_time;
        waitCount += proc->r_wait_time;
        std::cout << proc->name << " has turn-around time " << proc->r_turn_time
            << ", average waiting time " << proc->r_wait_time
            << endl;
    }
    turnAvg = turnCount / processTotal;
    waitAvg = waitCount / processTotal;
}

void SchedulerPriorityRR::print_results() {
    std::cout << "Average turn-around time = " << turnAvg 
              << ", Average waiting = " << waitAvg << "\n";
}