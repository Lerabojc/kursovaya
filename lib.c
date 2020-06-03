#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct LNode
{
    int   id; /* unique value */
    char *name;
    char gender; /* 'm' or 'f' */
    int year_of_birth;
    char *spec;
    int year;
    char *group;
    float balls;
    float average;
    int exame[2];
    struct LNode *prev; /* link to previous node */
    struct LNode *next; /* link to next node */
};

struct LHead {
    int cnt;
    struct LNode *first;
    struct LNode *last;
};

typedef struct LHead Head;
typedef struct LNode Node;


Head *make_head()//создание заголовка
{
    Head *ph=NULL;

    ph=(Head*)malloc(sizeof(Head));
    if(ph)
    {
        ph->cnt=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}



void ClearStructure(Node *str0)//очищение памяти из-под структуры
{
    free(str0->name);
    free(str0->group);
    free(str0->spec);
    str0->name=NULL;
    str0->group=NULL;
    str0->spec=NULL;
    free(str0);
    str0=NULL;
}
void ClearStringArray(char **str, int n)//очищение массива строк
{
    int i;

    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;

}

Node *create_node2(char **str) /* node initialization */
{
   Node *new_node=NULL; /* pointer to new node */


    new_node = (Node*)malloc(sizeof(Node));
    if(new_node)
    {
        new_node->id = 1;
        new_node->name=str[0];
        new_node->gender=*str[1];
        new_node->year_of_birth=atoi(str[2]);
        new_node->spec=str[3];
        new_node->year=atoi(str[4]);
        new_node->group=str[5];
        new_node->balls=atoi(str[6]);
        new_node->average=atof(str[7]);
        new_node->exame[0]=atoi(str[8]);
        new_node->exame[1]=atoi(str[9]);
        new_node->next = NULL;
    }
    return new_node;  /* return of node address */
}

void add_first2(Head *my_head, Node *new_node) /* link head to first node */
{
    my_head->first = new_node;
    my_head->last = new_node;
    my_head->cnt++;
}





void insert_before2(Head *my_head, Node *new_node, Node *current_node)//создание узла и запись в заголовок
{
    Node *q=NULL;
    int n;

    if(my_head&&new_node&&current_node)
    {
        new_node->prev=current_node;
        current_node->next=new_node;
        n=my_head->cnt+1;
        new_node->id=n;
        my_head->cnt=n;
    }
}

Node *select_by_id(Head *my_head, int n)//нахождение элемента
{
    Node *q;
    int k;

    q=my_head->first;
    k=my_head->cnt; /* last node id */
    if((n>0)&&(n<=k))
    {
        while((q->id)!=n) q=q->next;
    }
    else q=NULL;
    return q;
}

void delete_selected(Head *my_head, Node *current_node)//удаление элемента
{
    Node *q, *q1;

    q=my_head->first;
    q1=my_head->last;
    my_head->cnt--;
    if(current_node==q)//если удаляемый элемент заголовок
    {
        q=q->next;
        while(q!=NULL){
                q->id=q->id-1;

                q=q->next;
            }
        my_head->first=current_node->next;
        current_node->next=NULL;
        free(current_node);


    }
    else
    {

        while(q!=NULL)//перебор элементов
        {

            if(q->next==current_node)//пока не равен
            {
                if(current_node==q1) my_head->last=q;
                q->next=current_node->next;
                q->prev=current_node->prev;
                current_node->next=NULL;
                current_node->prev=NULL;
                free(current_node);
                while(q->next!=NULL){
                    q=q->next;
                    q->id=q->id-1;
                }

            }
            else q=q->next;
        }
    }
}
int safe_scanf()
{
    int chooce = -1;
    char str[100];

    scanf("%s", str);

    while(sscanf(str, "%d", &chooce) != 1) {
        printf("Incorrect input! Try again use only numbers!\n");
        scanf("%s" , str);
    }

    return chooce;
}
char **simple_split(char *str, int length, char sep)//разделение полученной строки на элементы
{
    char **str_array=NULL;
    int i,j,k,m;
    m=0;
    int key,count;
    for(j=0;j<length;j++)//подсчет элементов
    {
        if(str[j]==sep) m++;
    }

    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));//массив строк элементов
    if(str_array!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));//создание массива элементов
            if(str_array[i]!=NULL) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) str_array[m][j-k]=str[j];//запись в массив
                else
                {
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
        }
        else
        {
            ClearStringArray(str_array,count);//очистка
        }
     }
     return str_array;
}
void print_header()//вывод оглавления
{
    printf("|%6s|%20s |%6s|%6s |%10s |%6s |%6s |%5s|%5s|%6s|\n","id", "fullname","gender","year","code","course","group","ball","average", "exame");
    printf("+------+---------------------+------+-------+-----------+-------+-------+-----+-----+--------+\n");
}

void struct_out(Node *str0)//вывод узла
{
    printf("|%6d|%20s |   %c  |%6d |%10s |%6d |%6s |%5.3f|%5.3f|%6d %d|\n",
        str0->id,str0->name,str0->gender,str0->year_of_birth,str0->spec,str0->year,str0->group,str0->balls,str0->average,str0->exame[0],str0->exame[1]);
}
void zapis(Node *str0, FILE *df)//создание итогового файла по окончании работы
{
    fprintf(df, "%6d;%20s;%c;%6d;%10s;%6d;%6s;%5.3f;%5.3f;%6d;%d;\n",
        str0->id,str0->name,str0->gender,str0->year_of_birth,str0->spec,str0->year,str0->group,str0->balls,str0->average,str0->exame[0],str0->exame[1]);
}
void menu(){//основное меню

    printf("\n  1- delete element\n 2- add element\n 3- print spisok\n 4- Found\n 5- redaction\n 6- sortirovka\n 7- exit\n Your choice: ");
}

void menu2(){//меню поиска
    printf("\n  1- find name\n 2- find course \n 3- find year of birth\n 4- exit\n Your choice: ");
}

void delete(Head *p0){//удаление элемента
    int n;
    Node *p;
        printf("%s: ","\nPlease enter your number");//поиск элемента для удаления
        n=safe_scanf();
        p=select_by_id(p0, n);
        if(p!=NULL)
        {
            printf("\nYour choice\n");//вывод выбранного
            print_header();
            struct_out(p);
            printf("\n----------------------------------------------\n");
            delete_selected(p0,p);//удаление
            p=p0->first;
        }
        else printf("ERROR! Element not exists!\n");//если не введен или отсутствует
        p=p0->first;//вывод нового списка
        print_header();
        while(p!=NULL)
        {
            struct_out(p);
            p=p->next;
        }
}

char *gets(char *s)
{

fflush(stdin);

    int i, k = getchar();

    /* Возвращаем NULL если ничего не введено */
    if (k == EOF)
        s= NULL;

    /* Считываем и копируем в буфер символы пока не достигнем конца строки или файла */
    for (i = 0; k != EOF && k != '\n'; ++i) {
        s[i] = k;
        k = getchar();


        if (k == EOF && !feof(stdin))
            s=NULL;
    }

    s[i]='\0';


    return s;
}
void perestanovka(Node *tmp, Node *a, Node *l){//перестановка данных узлов при сортировке
    int t;
                t=tmp->id;
                tmp->id=a->id;
                a->id=t;



                t=tmp->year;
                tmp->year=a->year;
                a->year=t;

                t=tmp->year_of_birth;
                tmp->year_of_birth=a->year_of_birth;
                a->year_of_birth=t;

                t=tmp->average;
                tmp->average=a->average;
                a->average=t;

                t=tmp->balls;
                tmp->balls=a->balls;
                a->balls=t;

                t=tmp->exame[0];
                tmp->exame[0]=a->exame[0];
                a->exame[0]=t;

                t=tmp->exame[1];
                tmp->exame[1]=a->exame[1];
                a->exame[1]=t;

                l->group=tmp->group;
                tmp->group=a->group;
                a->group=l->group;

                l->name=tmp->name;
                tmp->name=a->name;
                a->name=l->name;

                l->spec=tmp->spec;
                tmp->spec=a->spec;
                a->spec=l->spec;

                l->gender=tmp->gender;
                tmp->gender=a->gender;
                a->spec=l->spec;



}

void sort(Head *p0, int vibor)//сортировка
{
    Node *tmp;
    Node *a;
    Node *l;
    l=p0->first;
    int t=0;
    int flag=1;
    while(flag==1)//сортируем пока при прохождении круга не будет изменений
    {
        tmp=p0->first;
        a=tmp->next;
        flag=0;
        while(a)
        {
            if(vibor==1){
                if((tmp->year)>(a->year))
                {
                    perestanovka( tmp, a, l);

                }
                tmp=tmp->next;
                a=a->next;
            }
            if(vibor==2){
                if((tmp->year_of_birth)>(a->year_of_birth))
                {
                    perestanovka( tmp, a, l);

                }
                tmp=tmp->next;
                a=a->next;
            }

            if(vibor==3){
                if((tmp->average)>(a->average))
                {
                    perestanovka( tmp, a, l);

                }
                tmp=tmp->next;
                a=a->next;
            }


        }
    }
}

void Found2(Head *p0, int kol, char s[21], int vibor2){//в зависимости от выбора по списку ищется нужное поле
    int k=0;
    Node *p;
    p=p0->first;
    while(p!=NULL){
            if(vibor2==1){
                if(strncmp(p->name, s, kol)==0){//если символы совпадают, вывод узла
                    k++;
                    printf("\n found name:\n");
                    print_header();
                    struct_out(p);
                }
            }
            if(vibor2==2){
                if(p->year==atoi(s)){//если символы совпадают, вывод строки массива
                    k++;
                    printf("\n found course:\n");
                    print_header();
                    struct_out(p);
                }
            }
            if(vibor2==3){
                if(p->year_of_birth==atoi(s)){//если символы совпадают, вывод строки массива
                    k++;
                    printf("\n found year of birth:\n");
                    print_header();
                    struct_out(p);
                }
            }

        p=p->next;
    }
    if ((k==0)){
            printf("\nNo this pole\n");
                }
    }

void Found(Head *p0, int vibor2){//функция поиска, вводится нужное поле
        char s[21];
        int kol;
            printf("\nEnter :");
            scanf("%20s", &s);
            kol=strlen(s);
            Found2(p0, kol, s, vibor2);
}


Node *create_node_enter()//ввод с консоли
{
    int MAXLEN=128;
    Node *new_node=NULL;

    new_node = (Node*)malloc(sizeof(Node));
    if(new_node)
    {
        new_node = (Node*)malloc(sizeof(Node));
    	new_node->name=(char*)malloc(MAXLEN*sizeof(char));

   		new_node->group=(char*)malloc(MAXLEN*sizeof(char));
   		new_node->spec=(char*)malloc(MAXLEN*sizeof(char));

   		printf("Enter name:");
        fflush(stdin);
    	fgets((*new_node).name,MAXLEN,stdin);
    	fflush(stdin);
    	printf("Enter gender:");
    	scanf("%c", &(*new_node).gender);
    	fflush(stdin);
    	printf("Enter year of birth:");
    	(*new_node).year_of_birth=safe_scanf();
    	printf("Enter code:");
    	fflush(stdin);
    	fgets((*new_node).spec,MAXLEN,stdin);
    	printf("Enter course:");
    	(*new_node).year=safe_scanf();
    	fflush(stdin);
    	printf("Enter group:");
    	fgets((*new_node).group,MAXLEN,stdin);
    	fflush(stdin);
    	printf("Enter balls:");
    	(*new_node).balls=safe_scanf();
    	printf("Enter average:");
    	(*new_node).average=safe_scanf();
    	printf("Enter exame1:");
    	(*new_node).exame[0]=safe_scanf();
    	printf("Enter exame2:");
    	(*new_node).exame[1]=safe_scanf();

        new_node->name[strlen(new_node->name)-1]='\0';

    	new_node->group[strlen(new_node->group)-1]='\0';
    	new_node->spec[strlen(new_node->spec)-1]='\0';
    	new_node->prev = NULL;
    	new_node->next = NULL;
    }
    return new_node;
}



void vibor(Head *p0, char sep, char **s2){//выбор пользователя
        Node *my_node=NULL;
        int vibor=0;
        Node *p;
        p=p0->first;
        while (vibor != 7){// 7 - выход
            system("CLS");

                menu();// вывод меню и считывание
                vibor=safe_scanf();
                if (vibor==1){//удаление
                    p=p0->first;
                    delete(p0);
                    system("CLS");

                }
                if (vibor==2){//добавление
                    p=p0->first;
                    while(p->next!=NULL)
                    {
                        p=p->next;
                    }
                    my_node=create_node_enter();//создание элемента
                    insert_before2(p0, my_node, p);
                    p=my_node;
                    system("CLS");

                }
                if (vibor==3){//вывод списка
                    p=p0->first;
                    print_header();
                    while(p!=NULL)
                    {
                        struct_out(p);
                        p=p->next;
                    }
                }
                if(vibor==4){//поиск по полю

                    int vibor2=0;
                    menu2();
                    vibor2=safe_scanf();
                    while (vibor2!=4){
                        char s[21];
                        int kol;
                        printf("\nEnter dannie:");
                        scanf("%20s", &s);
                        kol=strlen(s);
                        Found2(p0, kol, s, vibor2);
                        menu2();
                        scanf("%d", &vibor2);
                    }


                }
                if(vibor==5){//редактирование
                    printf("\nEnter nomer cartochki:");
                    int nomer;
                    nomer=safe_scanf();
                    p=select_by_id(p0, nomer);
                    if(p!=NULL)
                        {
                        printf("\nYour choice\n");//вывод выбранного
                        print_header();
                        struct_out(p);
                        printf("\n----------------------------------------------\n");
                        printf("\nWhat you want to redact? \n 1- fullname\n 2- gender\n 3- year\n 4- code\n 5- course\n 6- group\n 7- ball\n 8- average\n 9- exame1 \n 10- exame2 \n 11- exit \n Your choice: ");
                        int vib;
                        vib=safe_scanf();
                        char s[10][21];
                        int l=0;
                        int newpole;
                        if(vib==1){

                            printf("\nEnter new pole: ");
                            gets(s[l]);
                            strcpy(p->name, s[l]);
                            l++;
                        }
                        if(vib==2){

                            printf("\nEnter new pole: ");
                            scanf("%s", &p->gender);

                        }
                        if(vib==3){

                            printf("\nEnter new pole: ");
                            p->year_of_birth=safe_scanf();

                        }
                        if(vib==4){

                            printf("\nEnter new pole: ");
                            gets(s[l]);
                            strcpy(p->spec, s[l]);
                            l++;
                        }
                        if(vib==5){

                            printf("\nEnter new pole: ");

                            p->year=safe_scanf();
                        }
                        if(vib==6){

                            printf("\nEnter new pole: ");
                            gets(s[l]);
                            strcpy(p->group, s[l]);
                            l++;
                        }
                        if(vib==7){

                            printf("\nEnter new pole: ");

                            p->balls=safe_scanf();
                        }
                        if(vib==8){

                            printf("\nEnter new pole: ");

                            p->average=safe_scanf();
                        }
                        if(vib==9){

                            printf("\nEnter new pole: ");

                            p->exame[0]=safe_scanf();
                        }
                        if(vib==10){

                            printf("\nEnter new pole: ");

                            p->exame[1]=safe_scanf();
                        }


                        p=p0->first;
                    }
                    else printf("ERROR! Element not exists!\n");//если не введен или отсутствует
                    p=p0->first;//вывод нового списка
                    print_header();
                    while(p!=NULL)
                    {
                        struct_out(p);
                        p=p->next;
                    }
                    system("CLS");

                }
                if(vibor==6){
                    int vibor3;
                    printf("\n Enter kind of sort\n 1- by course\n 2- by year_of_birth\n 3- by average\n 4- exit\n Your choice:");
                    vibor3=safe_scanf();
                    if(vibor3!=4){

                        p=p0->first;
                        sort(p0, vibor3);

                    }
                    print_header();//вывод списка
                    p=p0->first;
                    while(p!=NULL)
                        {
                            struct_out(p);
                            p=p->next;//переход
                        }
                        system("CLS");


                }
                if((vibor<1)||(vibor>7)){
                    printf("Error! Please enter number from 1 to 7");
                }




        }
}


void Clear(Head *p0){
    Node *p, *p1;
    p=p0->first;//очищение памяти
    while(p!=NULL)
    {
        p1=p->next;
        ClearStructure(p);
        free(p);
        p=p1;
    }
    free(p0);
}


