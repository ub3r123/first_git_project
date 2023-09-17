//Алгоритм Олдоса-Бродера

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

//left 1
//right 2
//up 4
//down 8
int delete_3(int** mas,int a,int b)
{
    for (int i=0;i<a;i++)
    {
        free(*(mas+i));
    }
    free(mas);
}

int** initialization_3(int a,int b,int num)
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

int flag_3(int**size,int**fl,int a,int b)
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

int print_3(int**size,int a,int b)
{
    FILE *fp;
    fp= fopen("D:\\generation of labirint\\file.txt","w");
    int** fl= initialization_3(a,b,0);
    flag_3(size,fl,a,b);

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

    delete_3(fl,a,b);

}

//int initialization_mas_(int b,int num,int* mas)
//{
//    for (int i=0;i<b;i++)
//    {
//        mas[i]=num;
//    }
//}

int labirint_3(int a,int b)
{
    int** size= initialization_3(a,b,15);
    int** flag= initialization_3(a,b,0);

    srand(time(NULL));

    int i1=rand()%a, j1=rand()%b, sum=a*b, cnt=0, move;
    flag[i1][j1]=1;
    cnt+=1;

    while (sum!=cnt)
    {
        move=rand()%4;
        if (move==0)
        {
            if (j1!=0) {
                j1 -= 1;
                if (flag[i1][j1] == 0) {
                    flag[i1][j1] = 1;
                    size[i1][j1] -= 2;
                    size[i1][j1 + 1] -= 1;
                    cnt+=1;
                }
            }
        }
        else if (move==1)
        {
            if (i1!=0){
                i1-=1;
                if (flag[i1][j1]==0){
                    flag[i1][j1]=1;
                    size[i1][j1]-=8;
                    size[i1+1][j1]-=4;
                    cnt+=1;
                }
            }
        }
        else if (move==2)
        {
            if (j1!=b-1) {
                j1 += 1;
                if (flag[i1][j1] == 0) {
                    flag[i1][j1] = 1;
                    size[i1][j1] -= 1;
                    size[i1][j1 - 1] -= 2;
                    cnt+=1;
                }
            }
        }
        else if (move==3)
        {
            if (i1!=a-1){
                i1+=1;
                if (flag[i1][j1]==0){
                    flag[i1][j1]=1;
                    size[i1][j1]-=4;
                    size[i1-1][j1]-=8;
                    cnt+=1;
                }
            }
        }
    }

    print_3(size,a,b);


}
