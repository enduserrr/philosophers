# PHILO

This project is an implementation of Edsger Dijkstra's dining philosophers problem using threads and mutexes in C programming language.

## Description

This implementation uses threads to represent each philosopher and mutexes to represent each fork. The program manages the philosophers' actions, ensuring they can eat and think without causing deadlock or starvation.

## Execute

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<meal_goal>]
