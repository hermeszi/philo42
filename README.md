# Philosopher Program (42 Project)

This repository contains an implementation of the **Dining Philosophers Problem** using threads and mutexes in C. The project is part of the 42 curriculum and focuses on concurrency, synchronization, and avoiding data races.

## 🚀 Learning Plan & Action Steps  

Action Plan to study the required concepts and implement the project step by step.

### 🧠 **Concepts to Learn & Implement**
- [ ] **Understanding Threads in C**
  - Learn how to create and manage threads using `pthread_create`, `pthread_join`, and `pthread_detach`.
- [ ] **Mutexes and Synchronization**
  - Learn how `pthread_mutex_lock` and `pthread_mutex_unlock` work.
  - Understand deadlocks and race conditions.
- [ ] **Time Management in C**
  - Learn how to use `gettimeofday` for precise timestamping.
  - Implement `usleep` for time delays.
- [ ] **Handling Shared Resources**
  - Learn how to safely share data between threads.
  - Implement a simple thread-safe shared counter.
- [ ] **Debugging Multi-threaded Programs**
  - Learn how to debug race conditions and deadlocks using `printf`, `valgrind`, and `helgrind`.

---

## 🏗 **Step-by-Step Implementation Plan**
### ✅ **1. Setting Up the Project**
- [ ] Create `Makefile` with `all`, `clean`, `fclean`, and `re` rules.
- [ ] Set up a basic project structure (`philo.h`, `main.c`, `utils.c`).

### ✅ **2. Handling Program Input**
- [ ] Parse command-line arguments.
- [ ] Validate input values and handle errors.

### ✅ **3. Creating and Managing Threads**
- [ ] Create `n` philosopher threads.
- [ ] Print messages when threads start and exit.

### ✅ **4. Implementing Philosopher Behavior**
- [ ] Implement eating, sleeping, and thinking in loops.
- [ ] Use `usleep` to simulate these actions.

### ✅ **5. Synchronizing Forks with Mutexes**
- [ ] Implement a mutex-protected fork system.
- [ ] Prevent multiple philosophers from using the same fork.

### ✅ **6. Avoiding Starvation**
- [ ] Implement a check to track the last time a philosopher ate.
- [ ] If a philosopher doesn't eat within `time_to_die`, print a death message.

### ✅ **7. Implementing a Monitor**
- [ ] Create a monitoring thread that checks if a philosopher has died.
- [ ] Ensure the program stops within 10ms of a philosopher’s death.

### ✅ **8. Handling the Optional Meal Limit**
- [ ] Implement an optional meal counter.
- [ ] If all philosophers reach the meal count, stop the simulation.

### ✅ **9. Preventing Deadlocks**
- [ ] Implement a strategy to prevent deadlocks (e.g., an even/odd philosopher strategy).
- [ ] Test with different philosopher counts.

### ✅ **10. Debugging & Testing**
- [ ] Use `helgrind` to check for race conditions.
- [ ] Stress test the program with different input values.
- [ ] Handle edge cases (1 philosopher, high values, etc.).

---

## 🛠 **Usage**
Compile the program:
```sh
make
```
Run it
```sh
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_times_each_philosopher_must_eat]
./philo 5 800 200 200


