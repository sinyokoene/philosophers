
# Philosophers

This project is an implementation of the famous **Dining Philosophers Problem**, a classic concurrency problem that demonstrates synchronization issues and resource management. This project is part of the 42 curriculum and illustrates the use of mutexes and threads in C.

## Overview

The **Dining Philosophers Problem** describes a scenario where philosophers seated at a round table alternate between **eating** and **thinking**. Each philosopher needs two forks to eat, but only one fork is available on each side. The challenge is to allow all philosophers to eat and think without causing deadlock (where they wait indefinitely) or starvation (where a philosopher never gets a chance to eat).

In this project:

- Each philosopher is represented by a **thread**.
- Each fork is represented by a **mutex**.
- Deadlock is avoided by introducing specific synchronization techniques.

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/philosophers.git
cd philosophers
```

### 2. Build the Project

Run make to compile the project:
```
make
```
This will generate an executable named philo.
Usage

Run the program with the following syntax:
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
#### Parameters
Parameter Description
- number_of_philosophers Number of philosophers and forks.
- time_to_die Maximum time (in milliseconds) a philosopher can survive without eating.
- time_to_eat Time (in milliseconds) it takes for a philosopher to eat.
- time_to_sleep Time (in milliseconds) a philosopher spends sleeping.
- [number_of_times_each_philosopher_must_eat] Optional: Simulation ends after each philosopher has eaten this number of times.

Example

To simulate 5 philosophers where each dies after 800ms without eating, with 200ms to eat and 200ms to sleep:
```
./philo 5 800 200 200
```

### Key Concepts
#### Synchronization

Each philosopher’s actions are managed to prevent deadlocks:

- Philosophers can only pick up adjacent forks (mutexes).
- Odd/even philosopher timing differences reduce contention.
- A start_lock ensures all threads start simultaneously.

#### Time Management

Time is managed in milliseconds for precision, helping philosophers avoid starvation and follow designated intervals for eating, sleeping, and thinking. This improves time accuracy and reduces potential race conditions.

##### Avoiding Deadlock

To avoid deadlock, the following strategies are used:

- Philosophers are numbered, and odd/even philosophers pick up forks in different orders.
- Philosophers are also given a small delay before starting to pick up forks to reduce contention on resources.
- Each philosopher checks their own "last meal" time to avoid dying unnecessarily.

##### Additional Information

This project is a great example of applying concurrency and synchronization concepts in C, such as:

- Mutexes to prevent race conditions while accessing shared resources (forks).
- Threads to simulate independent entities (philosophers) running concurrently.
 - Handling timeouts to simulate real-life conditions (e.g., philosophers dying if not fed).

##### Learning Outcomes

By working on this project, you will understand:

- How to effectively manage shared resources using mutexes.
- How to design and implement solutions that avoid deadlocks and starvation.
 - How to work with POSIX threads and mutexes in a C program.

Feel free to reach out if you have any questions about the project or want to discuss how concurrency works in practice!

Happy coding!
