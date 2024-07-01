#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LEN 100

typedef struct {
    char task[MAX_TASK_LEN];
    int times_worked;
    int streak;
} Todo;

void load_tasks(Todo tasks[], int *task_count) {
    FILE *file = fopen("todo.csv", "r");
    if (file == NULL) {
        *task_count = 0;
        return;
    }

    int i = 0;
    char line[MAX_TASK_LEN + 20];
    fgets(line, sizeof(line), file); // Skip the header line
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%99[^,],%d,%d", tasks[i].task, &tasks[i].times_worked, &tasks[i].streak) == 3) {
            i++;
        }
    }
    *task_count = i;
    fclose(file);
}

void save_tasks(Todo tasks[], int task_count) {
    FILE *file = fopen("todo.csv", "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "task,worked,streak\n"); // Write the header line
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s,%d,%d\n", tasks[i].task, tasks[i].times_worked, tasks[i].streak);
    }
    fclose(file);
}

int task_exists(Todo tasks[], int task_count, const char *new_task) {
    for (int i = 0; i < task_count; i++) {
        if (strcmp(tasks[i].task, new_task) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_task(Todo tasks[], int *task_count) {
    if (*task_count >= MAX_TASKS) {
        printf("Task list is full.\n");
        return;
    }

    char new_task[MAX_TASK_LEN];
    printf("Enter new task: ");
    if (fgets(new_task, MAX_TASK_LEN, stdin) == NULL) {
        printf("\nExiting...\n");
        exit(0);
    }
    new_task[strcspn(new_task, "\n")] = 0; // Remove newline character

    if (task_exists(tasks, *task_count, new_task)) {
        printf("Task already exists.\n");
        return;
    }

    strcpy(tasks[*task_count].task, new_task);
    tasks[*task_count].times_worked = 0;
    tasks[*task_count].streak = 0;
    (*task_count)++;
    save_tasks(tasks, *task_count);
}

void display_tasks(Todo tasks[], int task_count) {
    for (int i = 0; i < task_count; i++) {
        printf("[%d] %s (%d, %d)\n", i + 1, tasks[i].task, tasks[i].times_worked, tasks[i].streak);
    }
}

void work_on_task(Todo tasks[], int task_count) {
    int task_number;
    printf("Enter task number to work on: ");
    if (scanf("%d", &task_number) != 1) {
        printf("\nExiting...\n");
        exit(0);
    }
    getchar(); // Consume newline character

    if (task_number < 1 || task_number > task_count) {
        printf("Invalid task number.\n");
        return;
    }

    task_number--; // Adjust to zero-based index
    tasks[task_number].times_worked++;
    tasks[task_number].streak++;
    save_tasks(tasks, task_count);
}

void delete_task(Todo tasks[], int *task_count) {
    int task_number;
    printf("Enter task number to delete: ");
    if (scanf("%d", &task_number) != 1) {
        printf("\nExiting...\n");
        exit(0);
    }
    getchar(); // Consume newline character

    if (task_number < 1 || task_number > *task_count) {
        printf("Invalid task number.\n");
        return;
    }

    task_number--; // Adjust to zero-based index
    for (int i = task_number; i < *task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    (*task_count)--;
    save_tasks(tasks, *task_count);
}

int main() {
    Todo tasks[MAX_TASKS];
    int task_count;

    load_tasks(tasks, &task_count);

    while (1) {
        printf("\n1. Add task\n2. Display tasks\n3. Work on task\n4. Delete task\n5. Exit\nChoose an option: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nExiting...\n");
            break;
        }
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                add_task(tasks, &task_count);
                break;
            case 2:
                display_tasks(tasks, task_count);
                break;
            case 3:
                work_on_task(tasks, task_count);
                break;
            case 4:
                delete_task(tasks, &task_count);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
