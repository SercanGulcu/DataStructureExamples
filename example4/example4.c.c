#include <stdio.h>
#include <stdlib.h>

int minute;

struct customer {
	int customer_number;
	int start;
	int process_time;
	int end;
	int employee_number;
	int queue_time;
	int queue_flag;
	struct customer *next;
}*front, *rear, *temp, *front1;

struct employee {
	int employee_number;
	struct employee *next;
};

struct employee* employees = NULL;

void push_employee(int val) {
	front1 = front;
	while (front1 != rear) {
		if (front1->queue_flag == 1) {
			front1->employee_number = val;
			front1->queue_flag = 0;
			front1->start = minute;
			front1->end = front1->process_time + minute;
			return;
		}
		front1 = front1->next;
	}
	if (front1 == rear && front1 != NULL) {
		if (front1->queue_flag == 1) {
			front1->employee_number = val;
			front1->queue_flag = 0;
			front1->start = minute;
			front1->end = front1->process_time + minute;
			return;
		}
	}
	struct employee *ptr;
	ptr = (struct employee*) malloc(sizeof(struct employee));
	ptr->employee_number = val;
	if (employees == NULL) {
		ptr->next = NULL;
		employees = ptr;
	} else {
		ptr->next = employees;
		employees = ptr;
	}
}

void insert_customer(int customer_number, int start, int process_time) {
	if (rear == NULL) {
		temp = (struct customer *) malloc(sizeof(struct customer));
		temp->next = NULL;
		temp->customer_number = customer_number;
		temp->start = start;
		temp->process_time = process_time;
		temp->employee_number = 0;
		temp->end = 0;
		temp->queue_time = 0;
		temp->queue_flag = 0;
		rear = temp;

		front = rear;
	} else {
		temp = (struct customer *) malloc(sizeof(struct customer));
		rear->next = temp;
		temp->customer_number = customer_number;
		temp->start = start;
		temp->process_time = process_time;
		temp->employee_number = 0;
		temp->end = 0;
		temp->queue_time = 0;
		temp->queue_flag = 0;
		temp->next = NULL;

		rear = temp;
	}
}

int pop_employee() {
	struct employee *ptr;
	ptr = employees;
	employees = employees->next;
	return ptr->employee_number;
}

void display_employees() {
	struct employee *ptr;
	ptr = employees;

	while (ptr != NULL) {
		printf("\n %d", ptr->employee_number);
		ptr = ptr->next;
	}

}

void display_customers() {
	front1 = front;
	while (front1 != rear) {
		printf("%d %d %d %d %d\n", front1->customer_number,
				front1->employee_number, front1->start, front1->end,
				front1->queue_time);
		front1 = front1->next;
	}
	if (front1 == rear)
		printf("%d %d %d %d %d\n", front1->customer_number,
				front1->employee_number, front1->start, front1->end,
				front1->queue_time);
}

void process_customer() {

	int emp[] = { 0, 0, 0, 0, 0, 0 };
	int emp2[] = { 0, 0, 0, 0, 0, 0, 0 };
	int emp_index = 0;
	int i;

	if (minute == rear->start) {
		if (employees == NULL) {
			rear->queue_flag = 1;
			return;
		}
		rear->employee_number = pop_employee();
		rear->end = rear->process_time + minute;
	} else {
		minute++;
		front1 = front;
		while (front1 != rear) {
			if (front1->end == minute) {
				emp[emp_index] = front1->employee_number;
				emp_index++;
			}
			if (front1->queue_flag == 1) {
				front1->queue_time = front1->queue_time + 1;
			}
			front1 = front1->next;
		}
		if (front1 == rear) {
			if (front1->end == minute) {
				emp[emp_index] = front1->employee_number;
				emp_index++;
			}
			if (front1->queue_flag == 1) {
				front1->queue_time = front1->queue_time + 1;
			}
		}
		if (emp_index == 1) {
			push_employee(emp[0]);
		} else if (emp_index > 1) {
			for (i = 0; i < 6; ++i) {
				if (emp[i] != 0) {
					emp2[emp[i]] = 1;
				}
			}
			for (i = 1; i <= 6; ++i) {
				if (emp2[i] != 0) {
					push_employee(i);
				}
			}
		}
		rear->employee_number = pop_employee();
		rear->end = rear->process_time + minute;
	}
}

int end_process() {
	int continued = 0;
	int emp[] = { 0, 0, 0, 0, 0, 0 };
	int emp2[] = { 0, 0, 0, 0, 0, 0, 0 };
	int emp_index = 0;
	int i;
	minute++;
	front1 = front;
	while (front1 != rear) {
		if (front1->end == minute) {
			emp[emp_index] = front1->employee_number;
			emp_index++;
		}
		if (front1->queue_flag == 1) {
			front1->queue_time = front1->queue_time + 1;
		}
		if (front1->end >= minute) {
			continued = 1;
		}
		front1 = front1->next;
	}
	if (front1 == rear) {
		if (front1->end == minute) {
			emp[emp_index] = front1->employee_number;
			emp_index++;
		}
		if (front1->queue_flag == 1) {
			front1->queue_time = front1->queue_time + 1;
		}
	}
	if (emp_index == 1) {
		push_employee(emp[0]);
	} else if (emp_index > 1) {
		for (i = 0; i < 6; ++i) {
			if (emp[i] != 0) {
				emp2[emp[i]] = 1;
			}
		}
		for (i = 1; i <= 6; ++i) {
			if (emp2[i] != 0) {
				push_employee(i);
			}
		}
	}
	return continued;
}

int main(void) {

	int customer_number, start, process_time, i;
	FILE *fp = fopen("/customer.txt", "r");
	front = rear = NULL;
	minute = 1;
	for (i = 1; i <= 6; ++i) {
		push_employee(i);
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &customer_number, &start, &process_time);
		insert_customer(customer_number, start, process_time);
		process_customer();
	}
	while (1 == 1) {
		if (end_process() == 0) {
			break;
		}
	}
	display_customers();

	int emp_process_time[] = { 0, 0, 0, 0, 0, 0 };
	front1 = front;
	while (front1 != rear) {
		emp_process_time[front1->employee_number-1] =
				emp_process_time[front1->employee_number-1]
						+ front1->process_time;
		front1 = front1->next;
	}
	if (front1 == rear) {
		emp_process_time[front1->employee_number-1] =
				emp_process_time[front1->employee_number-1]
						+ front1->process_time;
	}
	for (i = 6; i > 0; --i) {
		printf("%d %d\n", i, emp_process_time[i - 1]);
	}
	return 0;
}
