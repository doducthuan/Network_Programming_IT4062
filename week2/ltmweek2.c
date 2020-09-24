#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct imformation{
	char course_code[10];
	char course_name[20];
	char day_of_the_week[10];
	char status[20];
	char period[10];
    char week[20];
    char room[10];
    int start;
    int end;
}IMFORMATION;
typedef struct node{
	IMFORMATION imfor;
	struct node *next;
}NODE;
typedef struct list{
	NODE *head;
	NODE *tail;
}LIST;

void initialization(LIST *l){
	l->head=l->tail=NULL;
}
NODE * create_node(IMFORMATION imfor){
	NODE* new_node;
	new_node=(NODE*)malloc(sizeof(NODE));
	if(new_node==NULL){
		printf("Fail\n");
	}
	else{
		new_node->imfor = imfor;
		new_node->next = NULL;
	}
	return new_node;
}
void add_node_tail(LIST* l, NODE* new_node){
	if(l->head==NULL){
		l->head = l->tail = new_node;
	}
	else{
		l->tail->next = new_node;
		l->tail = new_node;
	}
}
void print_list(LIST l){
	for(NODE* k = l.head; k!=NULL; k=k->next){
		printf("%10s%20s%10s%20s%10s%20s%10s\n", k->imfor.course_code, k->imfor.course_name, k->imfor.day_of_the_week,k->imfor.status,k->imfor.period,k->imfor.week,k->imfor.room);
	}
}
void remove_list(LIST* l){
	for(NODE* k = l->head; k!= NULL; k=k->next){
		l->head=l->head->next;
		free(k);
	}
}
void day_in_week(int index_day,char day[]){
	switch(index_day){
		case 2:
		   strcpy(day,"Monday");
		   break;
		case 3:
		   strcpy(day,"Tuesday");
		   break;
		case 4:
		   strcpy(day,"Wednesday");
		   break;
		case 5:
		   strcpy(day,"Thursday");
		   break;
		case 6:
		   strcpy(day,"Friday");
		   break;
	}
}

void am_pm(int x, char status1[]){

	switch(x){
		case 1:
		   strcpy(status1,"Morning");
		   break;
		case 2:
		   strcpy(status1,"Afternoon");
		   break;
	}
}
void time_class(char day_of_the_week[], char status[], char period[], int imfor_start, int imfor_end){
		int time_end     =   imfor_end % 10;
		
		int time_start   =   imfor_start % 10;
		
		int index_status =   ((imfor_start - time_start)/10) % 10;
		int index_day    =   (imfor_start - (index_status*10) - time_start)/100;
		char day[20];  
		day_in_week(index_day,day);
		strcpy(day_of_the_week,day);
		char status1[20] ;
		am_pm(index_status,status1);
		strcpy(status,status1);
		for(int i=0;i<3;i++){
			if(i==0){
				period[i]=(int)time_start +48;
			}
			else if(i==1){
				period[i]='-';
			}
			else if(i==2){
				period[i]=(int)time_end +48;
			}
		}
}

void  time_location(char day_of_the_week[], char status[], char period[], char week[], char room[], char neu[]){
	char **time=(char**)malloc(50*sizeof(char));
	char *p;
	int index_time=0;
	int index_time_start, index_time_end;
	int index_week=0, index_room=0;
	char s1[20],s2[20],s3[20];
	p = strtok(neu,",");
	while(p != NULL){
		time[index_time]=p;
		index_time++;
		p = strtok(NULL,",");
	}
	switch(index_time){
		case 5:
			for(int i=0;i<index_time;i++){
				if(i==0)
					index_time_start=atoi(time[0]);
				else if(i==1)
					index_time_end=atoi(time[1]);
				else if(i==2){
					strcpy(s1,time[2]);
					strcat(s1,",");
				}
				else if(i==3)
					strcpy(s2,time[3]);
				else if(i==4)
					strcpy(room,time[4]);
			}
			strcpy(week,s1);
			strcat(week,s2);
			time_class(day_of_the_week,status,period,index_time_start,index_time_end);
			break;
		case 6:
			for(int i=0;i<index_time;i++){
				if(i==0)
					index_time_start=atoi(time[0]);
				else if(i==1)
					index_time_end=atoi(time[1]);
				else if(i==2){
					strcpy(s1,time[2]);
					strcat(s1,",");
				}
				else if(i==3){
					strcpy(s2,time[3]);
					strcat(s2,",");
				}
				else if(i==4)
					strcpy(s3,time[4]);
				else if(i==5)
					strcpy(room,time[5]);
			}
			strcpy(week,s1);
			strcat(week,s2);
			strcat(week,s3);
			time_class(day_of_the_week,status,period,index_time_start,index_time_end);
			break;
	}
	free(time);
}
int main(){
	LIST l;
	initialization(&l);
	FILE *read_file;
	read_file=fopen("thongtin.txt","r");
	printf("%10s|%20s|%10s|%20s|%10s|%20s|%10s\n","Code","Course","Week Day","AM/PM","Period","Week","Room");
	while(!feof(read_file)){
		char read_line[100];
		fgets(read_line,100,read_file);
		if(!feof(read_file)){
			IMFORMATION imfor;
			int *x, *y;
			char neu[50];
		    char **draft=(char**)malloc(50*sizeof(char));
		    int index=0;
			read_line[strlen(read_line)-1]='\0';
			char *hust;
			hust = strtok(read_line," ");
			while(hust!=NULL){
				draft[index]=hust;
				index++;
				hust=strtok(NULL," ");
			}
			switch(index){
				case 3:{
					for(int i=0;i<index;i++){
						if(i==0){
							strcpy(imfor.course_code,draft[i]);
						}
						else if(i==1){
							strcpy(imfor.course_name,draft[i]);
						}
						else if(i==2){
							strcpy(neu,draft[2]);
						}
					}
					time_location(imfor.day_of_the_week,imfor.status,imfor.period,imfor.week,imfor.room,neu);
					//imfor.start= *x;
					//imfor.end = *y;
					for(int i=0;i<strlen(imfor.period);i++){
						//imfor.start=atoi()
						if(i==0){
							imfor.start=atoi(&imfor.period[i]);
						}
						else if(i==2){
							imfor.end=atoi(&imfor.period[i]);
						}
					}
					break;
				}
				case 4:{
					int j=0;
					for(int i=0;i<index;i++){
						if(i==0){
						    strcpy(imfor.course_code,draft[0]);
						}
						else if(i==1){
							for(int h=0;h<strlen(draft[i]);h++){
								imfor.course_name[j]=draft[i][h];
								j++;
							}
							imfor.course_name[j]=' ';
							j++;
						}
						else if(i==2){
							for(int h=0;h<strlen(draft[i]);h++){
								imfor.course_name[j]=draft[i][h];
								j++;
							}
							imfor.course_name[j]='\0';
						}
						else if(i==3){
							strcpy(neu,draft[3]);
						}
					}
					time_location(imfor.day_of_the_week,imfor.status,imfor.period,imfor.week,imfor.room,neu);
					for(int i=0;i<strlen(imfor.period);i++){
						if(i==0){
							imfor.start=atoi(&imfor.period[i]);
						}
						else if(i==2){
							imfor.end=atoi(&imfor.period[i]);
						}
					}
					break;
				}
				default:{
					break;
				}
			}
			printf("%10s|%20s|%10s|%20s|%10s|%20s|%10s|\n",imfor.course_code,imfor.course_name,imfor.day_of_the_week,imfor.status,imfor.period,imfor.week,imfor.room);
			NODE *new_node=create_node(imfor);
			add_node_tail(&l,new_node);
			free(draft);
		}	
	}
	printf("\n=========================================================================================================================================\n");
	printf("%30s|%20s|%20s|%20s|%20s|\n","Monday","Tuesday","Wednesday","Thursday","Friday");
	for(int i=1;i<13;i++){
		char s2[10]="",s3[10]="",s4[10]="",s5[10]="",s6[10]="";
		for(NODE *k=l.head;k!=NULL;k=k->next){
			if((i>=k->imfor.start) && (i<=k->imfor.end)){
				if(strcmp(k->imfor.day_of_the_week,"Monday")==0)
					strcpy(s2,k->imfor.room);
				else if(strcmp(k->imfor.day_of_the_week,"Tuesday")==0)
					strcpy(s3,k->imfor.room);
				else if(strcmp(k->imfor.day_of_the_week,"Wednesday")==0)
					strcpy(s4,k->imfor.room);
				else if(strcmp(k->imfor.day_of_the_week,"Thursday")==0)
					strcpy(s5,k->imfor.room);
				else if(strcmp(k->imfor.day_of_the_week,"Friday")==0)
					strcpy(s6,k->imfor.room);
			}
		}
		printf("%10d|%20s|%20s|%20s|%20s|%20s|\n",i,s2,s3,s4,s5,s6);
	}
	fclose(read_file);
	remove_list(&l);
	return 0;
}
