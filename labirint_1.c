//Алгоритм двоичного дерева

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

//left 1
//right 2
//up 4
//down 8

int** initialization(int a,int b,int num)
{
    int**size=(int**)malloc(a*sizeof(int*));

    for (int i=0;i<a;i+=1)
    {
        *(size+i)=(int *) malloc(b * sizeof(int));

        for(int j=0;j<b;j+=1)
        {
            size[i][j]=num;
        }
    }

    return size;
}

int flag(int**size,int**fl,int a,int b)
{
    for (int i=0;i<a;i++)
    {
        for (int j=0;j<b;j++)
        {
            if (size[i][j] == 1 || size[i][j] == 3 || size[i][j] == 5 || size[i][j] == 9 || size[i][j] == 7 || size[i][j] == 13 || size[i][j] == 11 || size[i][j] == 15)
            {
                fl[i][j] = 1;
            }

        }
    }
}

int delete(int** mas,int a,int b)
{
    for (int i=0;i<a;i++)
    {
        free(*(mas+i));
    }
    free(mas);
}

int print(int**size,int a,int b)
{
    FILE *fp;
    fp= fopen("D:\\generation of labirint\\file.txt","w");
    int** fl= initialization(a,b,0);
    flag(size,fl,a,b);

    srand(time(NULL));
    int entr=rand()%b,exit=rand()%b;


    for(int j=0;j<b;j+=1)
    {
        if (entr==j)
            fprintf(fp,"#     ");
        else
            fprintf(fp,"# # # ");
    }
    fprintf(fp,"#\n");

    for (int i=0;i<a;i+=1)
    {

        for(int j=0;j<b;j+=1)
        {
            if (fl[i][j] == 1)
            {

                fprintf(fp,"#     ");
            }
            else
            {
                fprintf(fp,"      ");
            }
        }
        fprintf(fp,"#\n");

        for(int j=0;j<b;j++)
        {
            if (fl[i][j] == 1)
                fprintf(fp,"#     ");
            else
                fprintf(fp,"      ");
        }
        fprintf(fp,"#\n");
//--------------------------------------дальше пол
        fprintf(fp,"#" );

        for(int j=0;j<b && i!=a-1;j++)
        {
            if (size[i][j] == 8 || size[i][j] == 9 || size[i][j] == 12 || size[i][j] == 10 || size[i][j] == 11 || size[i][j] == 13 || size[i][j] == 14 || size[i][j] == 15)
            {
                fprintf(fp," # # #");
            }
            else
            {
                if (j!=b-1)
                    fprintf(fp,"     ");//5 пробелов
                else
                    fprintf(fp,"    ");

                if (j<=b-1 && i<=a-1 && (fl[i][j+1]==1 || fl[i+1][j+1]==1))
                {
                    fprintf(fp,"#");
                }
                else
                {
                    fprintf(fp," ");
                }
            }
            //fl[i][j]=0;
        }

        int fl=0;
        if (i==a-1)
        {
            for(int j=0;j<b;j+=1)
            {
                if (exit==j)
                    fprintf(fp,"     #");
                else
                    fprintf(fp," # # #");
            }
            fl=1;
        }

        if (fl==0)
            fprintf(fp,"#\n" );
        else
            fprintf(fp,"\n");

    }

//    for (int i=0;i<a;i+=1)
//    {
//        for (int j=0;j<b;j+=1)
//        {
//            printf("%d ",fl[i][j]);
//        }
//        printf("\n");
//    }

    delete(fl,a,b);

}


int labirint_1(int a,int b)
{
    int**size= initialization(a,b,15);
    srand(time(NULL));

    for (int i=0;i<a;i+=1)
    {
        for(int j=0;j<b;j+=1)
        {
            if (i==0 && j!=b-1)
            {
                size[i][j]-=2;
                size[i][j+1]-=1;
            }
            else
            {
                int random_num=rand()%2;

                if (j!=b-1) {
                    if (random_num == 0) {
                        size[i][j] -= 2;
                        size[i][j + 1] -= 1;
                    } else {
                        size[i][j] -= 4;
                        size[i - 1][j] -= 8;
                    }
                }
                else if (i!=0) {
                    size[i][j] -= 4;
                    size[i - 1][j] -= 8;
                }
            }
        }

    }

    for (int i=0;i<a;i+=1)
    {
        for (int j=0;j<b;j+=1)
        {
            printf("%d ",size[i][j]);
        }
        printf("\n");
    }

    print(size,a,b);

    delete(size,a,b);
}
