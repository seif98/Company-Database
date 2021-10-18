#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct employee{
    char name[50];
    char phone[12];
    char mail[50];
    char bd[12];
    char job_title[50];
    struct employee *next;
};
struct titles{
    char title[50];
    struct titles *tnext;
};
typedef struct titles t_n;
typedef struct employee emp;
t_n *headt=NULL;
emp* head=NULL;
int count=0;

emp* create();  void ADD();   void LOAD();  void del(emp *ptr,emp *prev);
void DELETE();  void SAVE();    emp* SEARCH();  void MODIFY();  void QUIT();
void SORT();    void pr(emp *ptr);  void print();   void display(); void check();
void cn(char *s,emp *prev); emp *cp(emp*,emp*); t_n *create_t(); void readtitles();
emp *cm(emp *temp,emp *prev);   emp *cb(emp *temp,emp *prev);   int isLeabYear(emp* temp);

void main()
{
    char x='1';
    while(x){
        display();
        scanf(" %c",&x);
        switch(x){
            case '1': ADD();    break;
            case '2': LOAD();   break;
            case '3': DELETE(); break;
            case '4': SAVE();   break;
            case '5': SEARCH(); break;
            case '6': MODIFY(); break;
            case '7': QUIT();   break;
            case '8': SORT();   break;
            case '9': check();  break;
            case '0': print();  break;
            default : printf("please choose a number from 1 to 7\n");
        }
        if(x=='7') break;
        //print();
    }
}
emp* create(){
    emp* temp=malloc(sizeof(emp));
    emp* prev=malloc(sizeof(emp));
    emp* t=malloc(sizeof(emp));
    count++;
    if (head==NULL){
        head=temp;
        head->next=NULL;
        return head;
    }
    else{
        temp=head->next;
        prev=head;
        while(temp!=NULL){
            temp=temp->next;
            prev=prev->next;
        }
        temp=t;
        prev->next=temp;
        temp->next=NULL;
        return temp;
    }
}
t_n *create_t(){
    t_n* temp=malloc(sizeof(emp));
    t_n* prev=malloc(sizeof(emp));
    t_n* t=malloc(sizeof(emp));
    count++;
    if (headt==NULL){
        headt=temp;
        headt->tnext=NULL;
        return headt;
    }
    else{
        temp=headt->tnext;
        prev=headt;
        while(temp!=NULL){
            temp=temp->tnext;
            prev=prev->tnext;
        }
        temp=t;
        prev->tnext=temp;
        temp->tnext=NULL;
        return temp;
    }
}


//  1


void ADD(){
    emp* current=create();
        fflush(stdin);
        printf("enter the name\n");
        gets(current->name);
        printf("enter the phone number\n");
        gets(current->phone);
        printf("enter the mail\n");
        gets(current->mail);
        printf("enter the date of birth\n");
        gets(current->bd);
        printf("enter job title\n");
        gets(current->job_title);
        SORT();
}


//  2


void LOAD(){
    char input[150];
    FILE* fptr;
    fptr=fopen("LOAD.txt","r");
    int i=0;
    if(fptr==NULL){
        printf("unable to open file\n");
    }
    else{
        while(!feof(fptr)){
            emp* current=create();
            fgets(input,150,fptr);
            char* rest=input;
            for(int i=0;i<10;i++){
                if(rest[i]=='"'){
                    rest=rest+i;
                    break;
                }
            }
            int len=strlen(rest)-1;
            int j = 0;
            for (int i = 0; i < len; i ++) {
                if (rest[i] != '"' && rest[i] != '\\') { 
                    rest[j++] = rest[i];
                }
                else if (rest[i+1] == '"' && rest[i] == '\\') { 
                 rest[j++] = '"';
                }
                else if (rest[i+1] != '"' && rest[i] == '\\') { 
                 rest[j++] = '\\';
                }
            }
            if(j>0) rest[j]='\0';
            char *token=strtok_r(rest,",",&rest);
            strcpy(current->name,token);
            token=strtok_r(rest,",",&rest);
            len=strlen(token)-1;
            for(int i=0; i<len; i++)
	        {
		        if(token[i]==' '){
			        for(int j=i; j<strlen(token); j++)
			        {
				        token[j]=token[j+1];
			        }
		            len--;
		        }
	        }
            strcpy(current->phone,token);
            token=strtok_r(rest,",",&rest);
            len=strlen(token)-1;
            for(int i=0; i<len; i++)
	        {
		        if(token[i]==' '){
			        for(int j=i; j<strlen(token); j++)
			        {
				        token[j]=token[j+1];
			        }
		            len--;
		        }
	        }
            strcpy(current->mail,token);
            token=strtok_r(rest,",",&rest);
            len=strlen(token)-1;
            for(int i=0; i<len; i++)
	        {
		        if(token[i]==' '){
			        for(int j=i; j<strlen(token); j++)
			        {
				        token[j]=token[j+1];
			        }
		            len--;
		        }
	        }
            strcpy(current->bd,token);
            token=strtok_r(rest,"\n",&rest);
            strcpy(current->job_title,token);
        }
        SORT();
        printf("\n\n");
        fclose(fptr);
    }

}


//  3


void del(emp *ptr,emp *prev){
    if(prev==NULL){
        if(head==NULL) return;
        head=head->next;
        free(ptr);
    }
    else {
        prev->next=ptr->next;
        free(ptr);
    }
    count--;
}
void DELETE(){
    emp* temp=head->next;
    emp* prev=head;
    char s[50];
    printf("enter the name of the employee: ");
    fflush(stdin);
    gets(s);
    printf("\n\n");
    if((strcmp(head->name,s))==0){
        printf("employee found \n");
        pr(head);
        del(head,NULL);
        //head=head->next;
        return;
    }
    while(temp!=NULL){
        if((strcmp(s,temp->name))==0){
            printf("employee found \n");
            pr(temp);
            del(temp,prev);
            return;
        }
        else{
            prev=temp;
            temp=temp->next;
        }
    }
    printf("employee not found\n");
}


//  4


void SAVE(){
    FILE *fptr;
    fptr=fopen("Database.txt","w");
    if(fptr==NULL){
        printf("unable to open file\n");
        return;
    }
    else{
        SORT();
        emp* current=malloc(sizeof(emp));
        current=head;
        while(current!=NULL){
            fprintf(fptr,"%s,",current->name);
            fprintf(fptr,"%s,",current->phone);
            fprintf(fptr,"%s,",current->mail);
            fprintf(fptr,"%s,",current->bd);
            fprintf(fptr,"%s\n",current->job_title);
            current=current->next;
        }
    }
    fclose(fptr);
}


//  5


emp* SEARCH(){
    //SORT();
    emp *temp=head;
    char s[50];
    printf("enter the name: ");
    scanf("%s",s);
    printf("\n");
    while(temp!=NULL){
        if((strcmp(s,temp->name))==0) {
            printf("employee name found\n\n");
            pr(temp);
            return temp;
        }
        else{
            temp=temp->next;
        }
    }
    printf("employee name not found\n\n");
    return NULL;
}


//  6


void MODIFY(){
    emp* current;
    char s[50];
    short int x;
    current=SEARCH();
    if (current==NULL){
        return;
    }
    printf("if you want to modify the phone press\"1\"\nif you want to modify mail press \"2\"\nif you want to modify job title\"3\": ");
    scanf(" %d",&x);
    printf("enter the new one: ");
    fflush(stdin);
    while(1){
        switch(x){
            case 1: fgets(current->phone,12,stdin); strtok(current->phone,"\n"); printf("\n\n");   return;
            case 2: fgets(current->mail,50,stdin);  strtok(current->mail,"\n"); printf("\n\n");  return;
            case 3: fgets(current->job_title,50,stdin); strtok(current->job_title,"\n"); printf("\n\n");  return;
            default: printf("enter \"1\" or \"2\" or \"3\" only please"); continue;
        }
        break;
    }
}


//  7


void QUIT(){
    printf("if you want to save before exit click \"y\": ");
    char s;
    scanf(" %c",&s);
    if(s=='y') SAVE();
}


//  8


void SORT(){
    check();
    emp *current=malloc(sizeof(emp));
    emp *prev=malloc(sizeof(emp));
    emp *temp=malloc(sizeof(emp));
    for(int i=0;i<count;i++){
        current=head;
        prev=NULL;
        temp=head->next;
        for(int j=0;j<count-1;j++){
            if(current==head){
                if((strcmp(current->name,temp->name))>0){
                    head=head->next;
                    current->next=head->next;
                    head->next=current;
                }
                current=head->next;
                temp=current->next;
                prev=head;
            }
            else{
                if((strcmp(current->name,temp->name))>0){
                    prev->next=temp;
                    current->next=temp->next;
                    temp->next=current;
                }
                prev=temp;
                temp=current->next;
            }
        }
    }
}


void pr(emp *ptr){
    printf("name:   ");     puts(ptr->name);
    printf("phone:   ");    puts(ptr->phone);
    printf("mail:   ");     puts(ptr->mail);
    printf("bd:   ");        puts(ptr->bd);
    printf("job title:   ");  puts(ptr->job_title);
}
void print(){
    emp* current;
    current=head;
    while(current!=NULL){
        pr(current);
        current=current->next;
        printf("\n");
    }
    printf("\n");
}


void display(){
    printf("press any of the numbers next to the option you want to use\n");
    printf("1-ADD\n");
    printf("2-LOAD\n");
    printf("3-DELETE\n");
    printf("4-SAVE\n");
    printf("5-SEARCH\n");
    printf("6-MODIFY\n");
    printf("7-QUIT\n");
    printf("8-SORT\n\n\n");
}
void check(){
    emp *current=head;
    emp *prev=NULL;
    while(current!=NULL){
        int a=0;
        printf("\n%s\n",current->name);
        cn(current->name,current);
        for (int i = 0; i < strlen(current->name) ; i++){
                if ((current->name[i] >= 'a' && current->name[i] <= 'z') || (current->name[i] >= 'A' && current->name[i] <= 'Z') || (current->name[i] == ' ')) continue;
                else{
                    printf("\n%s is not all letters\n",current->name);
                    del(current,prev);
                    a=1;
                    break;
                }
        }
        if (a==1) {
             prev=current;
            current=current->next;
            continue;
        }
        if(cp(current,prev)==prev){
            if(prev==NULL) current=head;
            else    current=prev->next;
            continue;
        }
        if(cm(current,prev)==prev){
            if(prev==NULL) current=head;
            else    current=prev->next;
            continue;
        }
        /*if(cb(current,prev)==prev){
            if(prev==NULL) current=head;
            else    current=prev->next;
            continue;
        }*/
        prev=current;
        current=current->next;
    }
}
void cn(char *s,emp *current){
    emp *prev=current;
    emp *temp=current->next;
    while(temp!=NULL){
        if((strcmp(s,temp->name))==0){
            del(temp,prev);
            printf("\n%s is repeated\n",current->name);
        }
        prev=prev->next;
        temp=prev->next;
    }
}
emp *cp(emp *current,emp *prev){
    for(int i=0;i<11;i++){
        if((current->phone[i]>='0') && (current->phone[i]<='9')) continue;
        else{
            printf("\n%s phone number incorrect\n",current->name);
            del(current,prev);
            return prev;
        }
    }
    return current;
}
emp *cm(emp *temp,emp *prev){
    int i;
    char rest[50];
    strcpy(rest,temp->mail);
    for(i=0;i<strlen(rest);i++){
        if(rest[i]=='@') break;
    }
    char *token=rest+i+1;
    token=strtok(token,".");
    if( ((strcmp(token,"gmail")!=0) && ((strcmp(token,"yahoo"))!=0))){
        del(temp,prev);
        printf("\n%s mail is not yahoo or gmail\n",temp->name);
        return prev;
    }
    if( (temp->mail[0]>='0') && (temp->mail[0]<='9') ){
        printf("\n%s mail starts with number\n",temp->name);
        del(temp,prev);
        return prev;
    }
    return temp;
}
emp* cb(emp *temp,emp *prev){
    char *s=temp->bd;
    int i=0;
    if((isLeabYear(temp))==1) i=1;
    else i=0;
    if( !( (temp->bd[2]=='/') && (temp->bd[5]=='/') ) ){
        printf("\n%s wrong date formate\n",temp->name);
        del(temp,prev);
        return prev;
    }
    else if( !(((s[3]=='0') && ((s[4]>'0') && (s[4]<='9'))) || ((s[3]=='1') && ((s[4]>='0') && (s[4]<='2')))) ){
        printf("\n%s wrong date formate\n",temp->name);
        del(temp,prev);
        return prev;
    }
    if( ((s[3]=='0') && ( (s[4]=='1') || (s[4]=='3') || (s[4]=='5') || (s[4]=='7') || (s[4]=='8') )) || ( (s[3]=='1') && ((s[4]=='2') || (s[4]=='0') ))){
        if( !( (((s[0]>='0') && (s[0]<'3')) && ((s[1]>'0') && (s[1]<='9'))) && ( (s[0]=='3') && ((s[1]=='1') || (s[1]=='0'))  ) && (((s[0]=='1') || (s[0]=='2')) && (s[1]=='0')))){
            printf("\n%s wrong date formate\n",temp->name);
            del(temp,prev);
            return prev;
        }
    }
    else if( ((s[3]=='0') && ( (s[4]=='4') || (s[4]=='6') || (s[4]=='9'))) || ( (s[3]=='1') && (s[4]=='1') )){
        if( !( (((s[0]>='0') && (s[0]<'3')) && ((s[1]>'0') && (s[1]<='9'))) && ( (s[0]=='3') && (s[1]=='0')) && (((s[0]=='1') || (s[0]=='2')) && (s[1]=='0')))){
            printf("\n%s wrong date formate\n",temp->name);
            del(temp,prev);
            return prev;
        }
    }
    else if(  ((s[3]=='0') && (s[4]=='2')) ){
        if( !(  ((s[0]=='0') && ((s[1]>'0') && (s[1]<='9')))  || (((s[0]=='1') && (s[0]=='2')) && ((s[1]>='0') && (s[1]<='9') )) && (i) )){
            printf("\n%s wrong date formate\n",temp->name);
            del(temp,prev);
            return prev;
        }
    }
    if( !((strcmp((s+6),"1959")>0) && (strcmp((s+6),"1996")<0 ))  ) {
        printf("\n%s wrong date formate\n",temp->name);
        del(temp,prev);
        return prev;
    }
    return temp;
}
int isLeabYear(emp* temp){
    char *s=temp->bd;
    int i;
    i=(s[6]-48)*1000+(s[7]-48)*100+(s[8]-48)*10+(s[9]-48);
    if(i%4==0)  return 1;
    else return 0;
}
void readtitles(){
    FILE *fptr=fopen("titles.txt","r");
    if (fptr==NULL) printf("file couldn't be opened");
    else {
        while(!feof(fptr)){
            char *s;
            fgets(s,50,fptr);
            t_n *temp=create_t();
            strtok(s,"\n");
            strcpy(temp->title,s);
        }

    }
}


