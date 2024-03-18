#include <stdio.h>

// Structure to represent a process
typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completed; // Flag to check if process completed
} Process;

// find shortest job
// find turnaround and waiting time
// gantt chart display

// Function to find the process with the shortest remaining time
int findShortestJob(Process processes[], int n, int current_time) {
    int shortest_job_index = -1;
    int shortest_time = __INT_MAX__; // Initialize with maximum possible value

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !processes[i].completed && processes[i].remaining_time < shortest_time) {
            shortest_job_index = i;
            shortest_time = processes[i].remaining_time;
        }
    }
    return shortest_job_index;
}

// Function to calculate waiting time and turnaround time for each process
void calculateTimes(Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n]; // Array to store the processes

    // Input the arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completed = 0;
    }

    int current_time = 0;
    int completed_processes = 0;
    int shortest_job_index;

    printf("\nGantt Chart:\n");
    while (completed_processes < n) {
        shortest_job_index = findShortestJob(processes, n, current_time);

        if (shortest_job_index == -1) {
            printf("IDLE ");
            current_time++;
            continue;
        }

        printf("P%d ", processes[shortest_job_index].process_id);
        processes[shortest_job_index].remaining_time--;
        current_time++;

        if (processes[shortest_job_index].remaining_time == 0) {
            completed_processes++;
            processes[shortest_job_index].completed = 1;
            processes[shortest_job_index].waiting_time = current_time - processes[shortest_job_index].arrival_time - processes[shortest_job_index].burst_time;
        }
    }
    printf("\n");

    // Calculate waiting time and turnaround time for each process
    calculateTimes(processes, n);

    return 0;
}
