#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Mutexes for each fork
pthread_mutex_t forks[NUM_PHILOSOPHERS];
// Condition variables for each fork
pthread_cond_t fork_conditions[NUM_PHILOSOPHERS];

// Function to encapsulate the eat-think cycle of a philosopher
void use_forks(int philosopher_id) {
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    // Locking the forks before eating
    pthread_mutex_lock(&forks[left_fork]);
    pthread_mutex_lock(&forks[right_fork]);

    printf("Philosopher %d is eating\n", philosopher_id);
    sleep(rand() % 3 + 1);  // Simulate eating for a random duration

    printf("Philosopher %d is thinking\n", philosopher_id);

    // Unlocking the forks after eating
    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);

    // Signal other philosophers that forks are now available
    pthread_cond_signal(&fork_conditions[left_fork]);
    pthread_cond_signal(&fork_conditions[right_fork]);
}

// Thread function for each philosopher
void* philosopher_thread(void* arg) {
    int philosopher_id = *((int*)arg);
    
    while (1) {
        sleep(rand() % 3 + 1);  // Simulate thinking for a random duration
        printf("Philosopher %d is hungry\n", philosopher_id);

        // Attempt to pick up forks and eat
        use_forks(philosopher_id);
    }
}

int main() {
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes and condition variables for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&fork_conditions[i], NULL);
        philosopher_ids[i] = i; // Assigning philosopher IDs

        // Creating threads for each philosopher
        pthread_create(&philosopher_threads[i], NULL, philosopher_thread, &philosopher_ids[i]);
    }

    // Waiting for all philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosopher_threads[i], NULL);
        // Clean up: Destroy mutexes and condition variables
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&fork_conditions[i]);
    }

    return 0;
}

