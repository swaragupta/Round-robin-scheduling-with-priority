
//
//  main.c
//  Round robin scheduling with priority
//
//  Created by SWARA GUPTA on 18/03/18.
//  Copyright © 2018 SWARA GUPTA. All rights reserved.
//

/*
 Ques. 5. CPU schedules N processes which arrive at different time intervals and each process is
 allocated the CPU for a specific user input time unit, processes are scheduled using a preemptive
 round robin scheduling algorithm. Each process must be assigned a numerical priority, with a
 higher number indicating a higher relative priority. In addition to the processes one task has
 priority 0. The length of a time quantum is T units, where T is the custom time considered as
 time quantum for processing. If a process is preempted by a higher-priority process, the
 preempted process is placed at the end of the queue. Design a scheduler so that the task with
 priority 0 does not starve for resources and gets the CPU at some time unit to execute. Also
 compute waiting time, turn around.
 */

#include <iostream>

struct process{
    int arr,burst,prior,firstt,i,status,rect,burl,compt,waitingt,turnaroundt;
}*run=NULL;
int n,tq,tburst=0;
struct node{
    struct process *q;
    struct node *next;
}*start=NULL,*last,*cn;
int main()
{
    printf("\nEnter total number of the processes you want to execute :");
    scanf("%d",&n);
    int pl=n; //process left
    printf("Enter the value of time quantum :");
    scanf("%d",&tq);
    struct process p[n];
    for(int i=0;i<n;i++)
    {
        printf("\nEnter the details of process %d ",i+1);
        printf("\n\tArrival Time : ");
        scanf("%d",&p[i].arr);
        printf("\tBurst Time : ");
        scanf("%d",&p[i].burst);
        p[i].burl=p[i].burst;
        printf("\tPriority : ");
        scanf("%d",&p[i].prior);
        p[i].i=i+1;
        p[i].status=0;
    }
    printf("\n\n Details entered are following:");;
    printf("\n ___________________________________________________________________");
    printf("\n|\tPROCESS\t\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tPRIORITY\t|");
    printf("\n|_______________|___________________|_______________|_______________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\t\tP%d\t\t|\t\t%d\t\t\t|\t\t%d\t\t|\t\t%d\t\t|",p[i].i,p[i].arr,p[i].burst,p[i].prior);
        printf("\n|_______________|___________________|_______________|_______________|");
    }
    for(int time=0;pl!=0;time++)
    {
        for(int i=0;i<n;i++)
        {
            if(p[i].arr==time && p[i].status==0)
            {
                if(start==NULL)
                {
                    p[i].status=1;
                    cn=new node;
                    cn->q=&p[i];
                    cn->next=NULL;
                    last=cn;
                    start=cn;
                }
                else{
                    p[i].status=1;
                    cn=new node;
                    cn->q=&p[i];
                    last->next=cn;
                    last=last->next;
                }
            }
        }
        if(run==NULL)
        {
            if(start!=NULL)
            {
                run=start->q;
                start=start->next;
                if(run->firstt<0 || run->firstt>200)
                {
                    run->firstt=time;
                }
                run->rect=time;
            }
        }
        if(run!=NULL && (time)<((run->rect)+tq) && run->status!=2)
        {
            run->burl--;
            if(run->burl==0)
            {
                run->status=2;
                pl--;
                run->compt=(time+1);
                run->turnaroundt=((run->compt)-(run->arr));
                run->waitingt=((run->turnaroundt)-(run->burst));
                run=NULL;
            }
            else if((time+1)==((run->rect)+tq))
            {
                cn=new node;
                cn->q=run;
                cn->next=NULL;
                if(start==NULL)
                {
                    last=cn;
                    start=cn;
                }
                else{
                    last->next=cn;
                    last=last->next;
                }
                run=NULL;
            }
        }
        
    }
    printf("\nDetails after scheduling are :");
    printf("\n\n Details entered are following:");;
    printf("\n _______________________________________________________________________________________________________________");
    printf("\n|\tPROCESS\t\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tPRIORITY\t|\tWAITING TIME  \t|\tTURN AROUND TIME  \t|");
    printf("\n|_______________|___________________|_______________|_______________|___________________|_______________________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\t\tP%d\t\t|\t\t%d\t\t\t|\t\t%d\t\t|\t\t%d\t\t|\t\t\t%d\t\t|\t\t\t%d\t\t\t|",p[i].i,p[i].arr,p[i].burst,p[i].prior,p[i].waitingt,p[i].turnaroundt);
        printf("\n|_______________|___________________|_______________|_______________|___________________|_______________________|");
    }
    int awt=0,att=0;
    for(int i=0;i<n;i++)
    {
        awt=awt+p[i].waitingt;
        att=att+p[i].turnaroundt;
    }
    awt=awt/n;
    att=att/n;
    printf("\nAverage  waiting time = %d ",awt);
    printf("\nAverage Turn Around Time = %d \n",att);
}
