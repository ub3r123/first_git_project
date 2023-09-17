//Алгоритм «Sidewinder»

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

//left 1
//right 2
//up 4
//down 8
int delete_2(int** mas,int a,int b)
{
    for (int i=0;i<a;i++)
    {
        free(*(mas+i));
    }
    free(mas);
}

int** initialization_2(int a,int b,int num)
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

int flag_2(int**size,int**fl,int a,int b)
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

int print_2(int**size,int a,int b)
{
    FILE *fp;
    fp= fopen("D:\\generation of labirint\\file.txt","w");
    int** fl= initialization_2(a,b,0);
    flag_2(size,fl,a,b);

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


        int flag=0;
        for(int j=0;j<b && i!=a-1;j++)
        {
            if (size[i][j] == 8 || size[i][j] == 9 || size[i][j] == 12 || size[i][j] == 10 || size[i][j] == 11 || size[i][j] == 13 || size[i][j] == 14 || size[i][j] == 15)
            {
                flag=1;
                fprintf(fp," # # #");
            }
            else
            {
                flag=0;
                if (j!=b-1)
                    fprintf(fp,"     ");//5 пробелов
                else
                    fprintf(fp,"    ");

                if (j<=b-1 && i<=a-1 && (fl[i][j+1]==1 || fl[i+1][j+1]==1 || (j<b-1 && (size[i][j] == 8 || size[i][j] == 9 || size[i][j] == 12 || size[i][j] == 10 || size[i][j] == 11 || size[i][j] == 13 || size[i][j] == 14 || size[i][j] == 15))))
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

        if (fl==0 && flag==0)
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

    delete_2(fl,a,b);

}

int initialization_mas(int b,int num,int* mas)
{
    for (int i=0;i<b;i++)
    {
        mas[i]=num;
    }
}

int labirint_2(int a,int b)
{
    int** size= initialization_2(a,b,15);
    srand(time(NULL));

    for (int j=0;j<b-1;j++)//1 строка
    {
        size[0][j] -= 2;
        size[0][j+1]-=1;
    }


    for (int i=1;i<a;i++)//остальные
    {
        for (int j=0;j<b;j++)
        {

            int fl=rand()%2;

            int t=j;
            for (int k=j+1;k<b && fl==1;k++)
            {
                fl=rand()%2;
                t=k;
            }


            for(int k=j;k<t;k++)
            {
                size[i][k]-=2;
                size[i][k+1]-=1;
            }

            int cnt=t-j+1;
            cnt=rand()%cnt;
            size[i][j+cnt]-=4;
            size[i-1][j+cnt]-=8;

            j=t;
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


    print_2(size,a,b);

    printf("\n");
    printf("\n");
    //printf("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112");

    for (int i=0;i<100;i++)
        printf("# # # ");





}