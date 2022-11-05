/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Neal Archival and Ahmed Ali (TODO: your name)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling
 * algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and
// member functions init, print_results, and simulate here
SchedulerRR::SchedulerRR(int time_quantum) {
    waitAvg = 0.0;
    turnAvg = 0.0;
    processTotal = 0;
    this->time_quantum = time_quantum;
}

SchedulerRR::~SchedulerRR() {}

void SchedulerRR::init(vector<PCB>& process_list) {
    processTotal = process_list.size();

    for (int i = 0; i < processTotal; i++) {
        processes.push(&process_list[i]);  // Push into the queue
        originalProcList.push_back(&process_list[i]); // Create an original list order containing pointers to the PCBs 
    }
}

void SchedulerRR::simulate() {
    double waitCount = 0;
    double turnCount = 0;  
    double trailing = 0; // The cumulative total

    while (!processes.empty()) {
        PCB *currentProcess = processes.front();
        if (currentProcess->time_remaining > time_quantum) {
            currentProcess->time_remaining -= time_quantum; // Subtract the remaining burst time with the time quantum
            trailing += time_quantum; // Increment by the time quantum
            processes.push(currentProcess); // Push the process back to the queue
            std::cout << "Running process " << currentProcess->name << " for "
                      << time_quantum << " time units." << endl; // Print out the process that completed and the time quantum
        } else if (currentProcess->time_remaining <= time_quantum) { // Condition for when the time_remaining can be completed within the time quantum
            trailing += currentProcess->time_remaining; // Increment by how much time is left
            currentProcess->r_turn_time = trailing; // Only assign turnaround and waiting time when the process has completed (burst time <= time quantum)
            currentProcess->r_wait_time = trailing - currentProcess->burst_time;
            // First print the process name and the remaining burst time
            std::cout << "Running process " << currentProcess->name << " for "
                      << currentProcess->time_remaining << " time units." << endl; 
            currentProcess->time_remaining = 0; // Set the time remaining to 0 since it can be completed here
            // The processes has been completed, no need to push back into the queue
        }
        processes.pop(); // Remove the completed process from the queue
    }

    for (int i = 0; i < processTotal; i++) {
        PCB* proc = originalProcList[i]; // Get the process
        turnCount += proc->r_turn_time; // Add to the total turn count
        waitCount += proc->r_wait_time; // Add to the total wait count

        // Then print out
        std::cout << proc->name << " has turn-around time " << proc->r_turn_time
                  << ", average waiting time " << proc->r_wait_time
                  << endl;
    }

    // Then calculate the averages
    turnAvg = turnCount / processTotal;
    waitAvg = waitCount / processTotal;
}

void SchedulerRR::print_results() {
    std::cout << "Average turn-around time = " << turnAvg
              << ", Average waiting = " << waitAvg << "\n";
}