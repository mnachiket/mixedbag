#include<stdio.h>
#define MAX 30
//Authour : M. Nachiket
struct pro tasks[MAX],newtasks[MAX],queue[MAX];
typedef struct pro
{
        int prid,prior;
        float arrt,burstt,compt,waitt,strtt,rt,tat;
        int flag;
        int rel;
        int inQ;
}pro;
int gant[MAX],no,proatT[MAX],newno=0,tslice=0,f=0,r=-1;
float awt=0,atat=0;

void sortarrt()
{
     int i,j;
     pro temp_job;
    for(i=0;i<no-1;i++)
     {    
         for(j=0;j<no-i-1;j++)
         {
            if((float)tasks[j].arrt > (float)tasks[j+1].arrt)
            {
                temp_job=tasks[j];
                tasks[j]=tasks[j+1];
                tasks[j+1]=temp_job;
            }
           
         }
     }
     
     printf("\nSorted Order (By Arrival Time)\n");
     for(i=0;i<no;i++)
        printf("%d %G\n",tasks[i].prid,tasks[i].arrt);
        
 }

void addtoQ()
{
  int i;
  for(i=0;i<newno;i++)
  {
     
     queue[++r]=newtasks[i];
     
  }
 } 
 
float smallestremaining()
{
      int stall=0;
      for(;stall<no;stall++)
        {
           if(tasks[stall].flag!=1 && tasks[stall].rel!=0)
              return(tasks[stall].arrt);
        }
        return 0;
}
 
void roundr()
{
     int pro_over=0,i,cnt=0,q;
     float temp=0;
     int stallflag=0;
     if((float)temp <(float)tasks[0].arrt)
          temp=tasks[0].arrt;
          pro localtop;
     while(pro_over<no)
     {
           newno=0;
           stallflag=0;
           for(i=0;i<no;i++)
           {
                if((float)tasks[i].arrt <= (float)temp && tasks[i].flag!=1 && tasks[i].rel==1 )
                {
              if(tasks[i].inQ!=1)
              { 
                   tasks[i].inQ=1;
                   newtasks[newno]=tasks[i];
                   newno++;
               }
               stallflag=1;
                }            
            }  
           
        if(stallflag!=1)
        {
            temp=smallestremaining();        
        }  
        if(newno!=0)
           addtoQ();
        if(f<=r)
           localtop=queue[f++];
        else
           localtop.flag=1;  
        if(localtop.flag!=1) 
        {
           localtop.inQ=0;
           gant[cnt]=localtop.prid;
           if(localtop.rt<=tslice && localtop.rt>0)
           {
             
             localtop.flag=1;
             if(localtop.strtt<=0)
                {
                    localtop.strtt=temp;
                }
             temp=temp+localtop.rt;
             localtop.rt=0;
             localtop.compt=temp;
             
             cnt++;
             pro_over++;

           }
           else
           {
               localtop.rt=localtop.rt-tslice;
               gant[cnt]=localtop.prid;
               cnt++;
               if(localtop.strtt<=0)
                {
                    localtop.strtt=temp;
                }
               temp=temp+tslice;
               
           }
           
           
           for(q=0;q<no;q++)
            {
               if(localtop.prid == tasks[q].prid)
               {
                 /*               
                  if(tasks[q].strtt>0)
                  {
                      localtop.strtt=tasks[q].strtt;
                  } */             
                  tasks[q]=localtop;
                  break;
               }
             }
        }    
     }
     printf("\nRound Robin Gant\n");
      for(i=0;i<cnt;i++)
      {
         printf("\n P%d ",gant[i]);
      }
      //Tasks
      printf("\nTask Details");
      for(i=0;i<no;i++)
      {
         printf("\n P%d CT%G",tasks[i].prid,tasks[i].compt);
      }
      printf("\n Proid\tArrT\tstrT\tBurstT\tCompT\tWaitT\tTAT\t");
      for(i=0;i<no;i++)
      {
//         tasks[i].waitt=tasks[i].strtt-tasks[i].arrt;   
         tasks[i].tat=tasks[i].compt-tasks[i].arrt;
         tasks[i].waitt=tasks[i].tat-tasks[i].burstt;
         awt=awt+tasks[i].waitt;
         atat=atat+tasks[i].tat; 
         printf("\n P%d\t%G\t%G\t%G\t%G\t%G\t%G",tasks[i].prid,tasks[i].arrt,tasks[i].strtt,tasks[i].burstt,tasks[i].compt,tasks[i].waitt,tasks[i].tat);
      } 
      printf("\nAverage Wait: %f\nAverage TAT: %f",awt/no,atat/no);
 }

int rdtsc()    
{    
    __asm__ __volatile__("rdtsc");    
}     
int main()
{
    int i,t;
    
    printf("\nEnter Number Of processes\n");
    scanf("%d",&no);
    for(i=0;i<no;i++)
    {
    
      srand(rdtsc()); 
      tasks[i].prid=i;
      tasks[i].arrt=(rand()%10);
      t=rand()%10;
      if(t==0)
        {
              t=5;
        }
        tasks[i].burstt=t;
      tasks[i].rt=tasks[i].burstt;
      tasks[i].prior=(rand()%10);
      tasks[i].flag=0;
      tasks[i].rel=1;
      tasks[i].inQ=0;
    }
    printf("\n This is our Input");
    printf("\n Proid\tArrival\tBurst\tPriority\tFlag\tReal");
    for(i=0;i<no;i++)
    {
      printf("\n%d\t%G\t%G    \t%d\t\t%d\t%d",tasks[i].prid,tasks[i].arrt,tasks[i].burstt,tasks[i].prior,tasks[i].flag,tasks[i].rel);
     }    
    printf("\nEnter Time Slice : ");
    scanf("%d",&tslice);
    
    
    printf("\nRound Robin nkt\n");
     sortarrt();
     roundr();
               
      
    getch();
    return 0;
}
   
