# Todo List
Simple CLI tool to create todo.csv list

Menu Options

	1.	Add Task: Adds a new task to the task list.
	2.	Display Tasks: Displays all tasks with the format [task_number] task (times_worked, streak).
	3.	Work on Task: Prompts for a task number to work on and increments the times_worked and streak counters for that task.
	4.	Delete Task: Prompts for a task number to delete and removes that task from the task list.
	5.	Exit: Exits the application.

 task,worked,streak

Learn Common Lisp,10,3
Write a Compiler in C,5,2

Example Usage

```shell
./todo

1. Add task
2. Display tasks
3. Work on task
4. Delete task
5. Exit
Choose an option: 1
Enter new task: Learn Python

1. Add task
2. Display tasks
3. Work on task
4. Delete task
5. Exit
Choose an option: 1
Enter new task: Write a blog post

1. Add task
2. Display tasks
3. Work on task
4. Delete task
5. Exit
Choose an option: 2
[1] Learn Python (0, 0)
[2] Write a blog post (0, 0)

1. Add task
2. Display tasks
3. Work on task
4. Delete task
5. Exit
Choose an option: 3
Enter task number to work on: 1

1. Add task
2. Display tasks
3. Work on task
4. Delete task
5. Exit
Choose an option: 2
[1] Learn Python (1, 1)
[2] Write a blog post (0, 0)

1. Add task
2. Display tasks
3. Work on task
4. Delete task
5. Exit
Choose an option: 5
```

To use it as a regular program invoked in the terminal move it to: `/usr/local/bin/`
