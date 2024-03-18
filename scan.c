#include <stdio.h>
#include <stdlib.h>

#define DIRECTION_LEFT -1
#define DIRECTION_RIGHT 1

// Function to sort an array in ascending order
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find the index of the disk request nearest to the head position
int findNearestRequest(int arr[], int n, int head, int direction) {
    int index = -1;

    if (direction == DIRECTION_RIGHT) {
        for (int i = 0; i < n; i++) {
            if (arr[i] >= head) {
                index = i;
                break;
            }
        }
    } else if (direction == DIRECTION_LEFT) {
        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] <= head) {
                index = i;
                break;
            }
        }
    }

    return index;
}

// Function to simulate SCAN disk scheduling algorithm
void scan(int requests[], int n, int head, int direction) {
    int total_head_movement = 0;
    int current_track = head;

    // Sort the requests array
    sort(requests, n);

    printf("Sequence of disk head movement: %d ", head);

    if (direction == DIRECTION_RIGHT) {
        // Move towards the right
        int nearest_index = findNearestRequest(requests, n, head, direction);

        // Handle the requests towards the right
        for (int i = nearest_index; i < n; i++) {
            printf("-> %d ", requests[i]);
            total_head_movement += abs(requests[i] - current_track);
            current_track = requests[i];
        }

        // Move to the end
        total_head_movement += abs(current_track - 199);
        printf("-> 199 ");
        current_track = 199;

        // Move towards the left
        printf("-> ");
        int left_nearest_index = findNearestRequest(requests, n, current_track, DIRECTION_LEFT);
        for (int i = left_nearest_index; i >= 0; i--) {
            printf("%d ", requests[i]);
            total_head_movement += abs(requests[i] - current_track);
            current_track = requests[i];
        }
    } else if (direction == DIRECTION_LEFT) {
        // Move towards the left
        int nearest_index = findNearestRequest(requests, n, head, direction);

        // Handle the requests towards the left
        for (int i = nearest_index; i >= 0; i--) {
            printf("-> %d ", requests[i]);
            total_head_movement += abs(requests[i] - current_track);
            current_track = requests[i];
        }

        // Move to the beginning
        total_head_movement += abs(current_track - 0);
        printf("-> 0 ");
        current_track = 0;

        // Move towards the right
        printf("-> ");
        int right_nearest_index = findNearestRequest(requests, n, current_track, DIRECTION_RIGHT);
        for (int i = right_nearest_index; i < n; i++) {
            printf("%d ", requests[i]);
            total_head_movement += abs(requests[i] - current_track);
            current_track = requests[i];
        }
    }

    printf("\nTotal head movement: %d\n", total_head_movement);
}

int main() {
    int n; // Number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n]; // Array to store the disk requests

    // Input the disk requests
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int head; // Head position
    printf("Enter the current head position: ");
    scanf("%d", &head);

    int direction; // Direction of head movement
    printf("Enter the direction of head movement (1 for right, -1 for left): ");
    scanf("%d", &direction);

    scan(requests, n, head, direction); // Perform SCAN algorithm

    return 0;
}
