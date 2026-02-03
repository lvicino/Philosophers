# Philosophers
42 Philosophers

A simulation of the classic **Dining Philosophers** problem. This project illustrates the basics of threading a process, sharing resources between threads/processes, and solving concurrency issues such as data races and deadlocks.

## Overview

The simulation consists of *n* philosophers sitting around a round table.
* There is one fork between each pair of philosophers.
* A philosopher needs two forks to eat.
* Philosophers cycle through three states: **Eating**, **Sleeping**, and **Thinking**.
* If a philosopher does not eat within a specific time frame, they die.
* The simulation stops when a philosopher dies or when everyone has eaten enough times.

This repository includes:
* **Mandatory Part:** Each philosopher is a thread, and forks are protected by mutexes.
* **Bonus Part:** Each philosopher is a separate process, and forks are represented by a named semaphore.
