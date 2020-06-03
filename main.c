#include <stdio.h>
#include <stdlib.h>
#include "lib.c"
#include <string.h>




int main()
{
    Head *p0, *p1;
    Node *p,*my_node = NULL;
    enum {maxlen = 256};//максимум символов
    int slen, i, n;
    char **s2 = NULL;
    char s1[maxlen];
    char sep;//разделитель
    printf("Hello! press  to start ");
    sep=';';

    FILE *df;
    p0 = make_head();

    df = fopen("4.csv","r");//открываем файл
    if(df != NULL)
    {
        n = 0;
        while((fgets(s1,maxlen,df)) != NULL) n++;//считываем тсроки
        rewind(df);

        for(i = 0; i < n; i++)//записываем элементы в структуры
            {
                fgets(s1,maxlen,df);
                slen = strlen(s1);
                s1[slen-1] = '\0';
                slen = strlen(s1);
                s2 = simple_split(s1,slen,sep);//разделяем на элементы
                if(s2 != NULL)
                {
                    if(i == 0){//если первый элемент - создаем заголовок
                        p = create_node2(s2);
                        add_first2(p0,p);
                        p = p0->first;
                    }
                    else{
                        my_node = create_node2(s2);//создание элемента
                        insert_before2(p0, my_node, p);// реверс списка
                        p = my_node;
                    }
                }
                else puts("Error at data reading!");
            }

        fclose(df);
        getchar();
        p = p0->first;
        printf("\n----------------------------------------------\n");
        print_header();//вывод списка
        while(p != NULL)
        {
            struct_out(p);
            p = p->next;//переход
        }
        printf("\n----------------------------------------------\n");

        vibor(p0, sep, s2);
        df = fopen("itog.csv","a");
        p = p0->first;
        while(p != NULL)
        {
            zapis(p, df);
            p = p->next;//переход
        }



    }
    else puts("File not found!");
    p=p0->first;//очищение памяти
    while(p!=NULL)
    {
        p1=p->next;
        ClearStructure(p);

        p=p1;
    }
    free(p0);

    return 0;
}

