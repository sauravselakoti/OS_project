
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
//==========================================================================================================================================================================================================//
struct jobs_for_students
{
	int process_id;
	int arrival_time;
	int burst_time;
	int exit_time;
	int response_time;
	int remaining_time;
	int completed;
};


struct jobs_for_faculty
{
	int process_id;
	int arrival_time;
	int burst_time;
	int priority;
	int response_time;
	int exit_time;
	int completed;
};
//=========================================================================================================================================================================================================//

void faculty_job_process(int n,struct jobs_for_faculty faculty_processes[])
{
	int process_id,arrival_time,burst_time,priority;
	printf("\nplease enter details for all %d processes:",n);
	for(int i=0;i<n;i++)
	{
		printf("\nPlease, enter process id number for process number %d:",i+1);
		scanf("%d",&process_id);
		printf("\nEnter the arrival time (only integer value will be accepted ranging from 01 to 120 (in minutes)):");
		scanf("%d",&arrival_time);
		printf("\n Enter the burst time for the process (only integers from 01 to 120 will be accepted (in minutes)):");
		scanf("%d",&burst_time);
		printf("\n Enter the priority of process (enter only integer value):");
		scanf("%d",&priority);
		faculty_processes[i].process_id=process_id;
		faculty_processes[i].arrival_time=arrival_time;
		faculty_processes[i].burst_time=burst_time;
		faculty_processes[i].priority=priority;
		faculty_processes[i].exit_time=0;
		faculty_processes[i].completed=0;
	}
	
}


void student_job_process(int n,struct jobs_for_students student_processes[])
{
	int process_id,arrival_time,burst_time;
	printf("\nPlease enter details for %d processes",n);
	for(int i=0;i<n;i++)
	{
		printf("\n enter process id  for process number %d::",i+1);
		scanf("%d",&process_id);
		printf("\nEnter arrival time (Integers only ranging from 01 to 120) :");
		scanf("%d",&arrival_time);
		printf("\nEnter burst time:");
		scanf("%d",&burst_time);
		student_processes[i].process_id=process_id;
		student_processes[i].arrival_time=arrival_time;
		student_processes[i].burst_time=burst_time;
		student_processes[i].exit_time=0;
		student_processes[i].remaining_time=burst_time;
		student_processes[i].completed=0;
	}

}



void sorting_by_arrival(int n,struct jobs_for_faculty faculty_processes[])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			if(faculty_processes[j].arrival_time>faculty_processes[j+1].arrival_time)
			{
				struct jobs_for_faculty temp;
				temp=faculty_processes[j];
				faculty_processes[j]=faculty_processes[j+1];
				faculty_processes[j+1]=temp;
			}
			else if(faculty_processes[j].arrival_time==faculty_processes[j+1].arrival_time)
			{
				if(faculty_processes[j].priority>faculty_processes[j+1].priority)
				{
					struct jobs_for_faculty temp;
					temp=faculty_processes[j];
					faculty_processes[j]=faculty_processes[j+1];
					faculty_processes[j+1]=temp;
				}
			}
		}
	}	
}
void sorting_by_exit_time(int n,struct jobs_for_faculty faculty_processes[])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-1;j++)
			{
				if(faculty_processes[j].exit_time>faculty_processes[j+1].exit_time)
				{	
					struct jobs_for_faculty temp;
					temp=faculty_processes[j];
					faculty_processes[j]=faculty_processes[j+1];
					faculty_processes[j+1]=temp;
				}
			}
	}
}

void print(int n,struct jobs_for_faculty faculty_processes[])
{
	printf("\n\tprocess_id     arrival_time       burst_time       priority        exit_Time       waiting_time\n");
	
	for(int i=0;i<n;i++)
	{
		printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n ",faculty_processes[i].process_id,faculty_processes[i].arrival_time,faculty_processes[i].burst_time,faculty_processes[i].priority,faculty_processes[i].exit_time,(faculty_processes[i].exit_time-faculty_processes[i].burst_time-faculty_processes[i].arrival_time));
	}
	printf("\n");
}


void execute_faculty(int n,struct jobs_for_faculty faculty_processes[])
{

	int time=faculty_processes[0].arrival_time;
	int loop_var=0;
	int total_time=0;
	for(int i=0;i<n;i++)
	{
		loop_var=loop_var+faculty_processes[i].burst_time;
	}
	//printf("\n it is loop_var=%d",loop_var);
	int next_process=0;
	while(time<=120 && total_time!=loop_var)
	{	
		 if(faculty_processes[next_process].completed==0)
                {
                faculty_processes[next_process].response_time=time-faculty_processes[next_process].arrival_time;
                total_time=total_time+faculty_processes[next_process].burst_time;
                time=time+faculty_processes[next_process].burst_time;
                faculty_processes[next_process].completed=1;
                faculty_processes[next_process].exit_time=time;
                }
                int priority=100;
                int any_process_found=0;
                for(int i=0;i<n;i++)
                {
                        if(faculty_processes[i].arrival_time<=time && faculty_processes[i].completed==0)
                        {
                                if(faculty_processes[i].priority<priority)                                                                                                                                                                         {
                                        next_process=i;
                                        priority=faculty_processes[i].priority;
                                        any_process_found=1;
                                }
                        }
                }
               // printf("\nit is priority %d",priority);
                if(any_process_found==0)
                {
                        time++;
                }
	}
}
//==========================================================================================================================================================================================================

void print_students(int n,struct jobs_for_students student_processes[])
{
	printf("\n\tprocess name     arrival time     burst time      response time      exit time       waiting time");
	for(int i=0;i<n;i++)
	{
		printf("\n\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d",student_processes[i].process_id,student_processes[i].arrival_time,student_processes[i].burst_time,student_processes[i].response_time,student_processes[i].exit_time,(student_processes[i].exit_time-student_processes[i].burst_time-student_processes[i].arrival_time));
	}
}


void sorting_students_by_arrival(int n,struct jobs_for_students student_processes[])
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-1;j++)
		{
			if(student_processes[j].arrival_time > student_processes[j+1].arrival_time)
			{
				struct jobs_for_students temp;
				temp=student_processes[j];
				student_processes[j]=student_processes[j+1];
				student_processes[j+1]=temp;
			}
		}
	}
}
void check(int time,int quanta,int n,struct jobs_for_students student_processes[],int ready_queue[])
{
	for(int i=0;i<n;i++)
	{
		if(student_processes[i].arrival_time>time-quanta && student_processes[i].arrival_time<=time)
		{
			for(int j=0;j<n;j++)
			{
				if(ready_queue[j]==0)
				{
					ready_queue[j]=i+1;
					break;
				}
			}
		}
	}
}
void push(int n,int index,int ready_queue[])
{
	for(int i=0;i<n;i++)
	{
		if(ready_queue[i]==0)
		{
			ready_queue[i]=index+1;
			break;
		}
	}
}
int pop(int n,int ready_queue[])
{
	int item=ready_queue[0];
	for(int i=0;i<n-1;i++)
	{
		ready_queue[i]=ready_queue[i+1];
	}
	ready_queue[n-1]=0;
	return item-1;
}
void execute_students(int n,struct jobs_for_students student_processes[])
{
	int quanta,loop_var=0;
	int time=student_processes[0].arrival_time;
	int total_time=0;
	int ready_queue[n];
	for(int i=0;i<n;i++)
	{
		ready_queue[i]=0;
	}
	printf("\n Please enter time Quanta(between range 1 to 20 ):");
	scanf("%d",&quanta);
	ready_queue[0]=1;
	for(int i=0;i<n;i++)
	{
		loop_var+=student_processes[i].burst_time;
	}
	printf("\n it is loop var%d",loop_var);
	int next_process=pop(n,ready_queue);
	while(time<=120 && total_time!=loop_var)
	{
		if(student_processes[next_process].remaining_time==student_processes[next_process].burst_time)
		{
			student_processes[next_process].response_time=time-student_processes[next_process].arrival_time;
		}

		 if(student_processes[next_process].remaining_time>quanta)
		 {
			student_processes[next_process].remaining_time-=quanta;
			time+=quanta;
			total_time+=quanta;
			check(time,quanta,n,student_processes,ready_queue);
			push(n,next_process,ready_queue);
			next_process=pop(n,ready_queue);
		 }
		else if(student_processes[next_process].remaining_time<=quanta)
		{
			time=time+student_processes[next_process].remaining_time;
			total_time=total_time+student_processes[next_process].remaining_time;
			student_processes[next_process].completed=1;
			student_processes[next_process].exit_time=time;
			student_processes[next_process].remaining_time=0;
			check(time,quanta,n,student_processes,ready_queue);
			next_process=pop(n,ready_queue);
		}


	}

}

void sorting_students_by_exit_time(int n,struct jobs_for_students student_processes[])
{
	for(int i=0;i<n;i++)
	{

		for(int j=0;j<n-1;j++)
		{
			 if(student_processes[j].exit_time>student_processes[j+1].exit_time)
			{
				struct jobs_for_students temp;
				temp=student_processes[j];
				student_processes[j]=student_processes[j+1];
				student_processes[j+1]=temp;

			}
		}
	}
}
//=========================================================================================================================================================================================================
int main()
{	
	int choice;
	printf("\n\t\t\twelcome...");
	printf("\n\tPress 1 for faculty processes\n\t and press 2 for student processes");
	scanf("%d",&choice);
	switch(choice)
	{
	  case 1: {
			printf("\nENTER NUMBER OF FACULTY PROCESSES");
			int n;
			scanf("%d",&n);
			struct jobs_for_faculty faculty_processes[n];
			faculty_job_process(n,faculty_processes);
			//printf("\nbefore sorting");
			//print(n,faculty_processes);
			sorting_by_arrival(n,faculty_processes);
			//print(n,faculty_processes);
			execute_faculty(n,faculty_processes);
			sorting_by_exit_time(n,faculty_processes);
			print(n,faculty_processes);
			break;	
		  }
		
	  case 2: 
		{	
			printf("\nENTER NUMBER OF STUDNET PROCESSES:");
			int n;
			scanf("%d",&n);
			struct jobs_for_students student_processes[n];
			student_job_process(n,student_processes);
//			printf("\nbefore sorting...");
//			print_students(n,student_processes);
//			printf("\n After sorting on the basis of their arrival time...");
			sorting_students_by_arrival(n,student_processes);
//			print_students(n,student_processes);
			execute_students(n,student_processes);
			sorting_students_by_exit_time(n,student_processes);
			print_students(n,student_processes);
			break;
		}
	  default:
		{
		printf("You Entered wrong key...Try Again..");
		main();
		}
	}
}
