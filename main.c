#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

typedef unsigned long long ull;
ull** initialization_5(int a,int b,int num)
{
    ull**size=(ull**)malloc(a*sizeof(ull*));

    for (int i=0;i<a;i+=1)
    {
        *(size+i)=(ull *) malloc(b * sizeof(ull));

        for(int j=0;j<b;j+=1)
        {
            size[i][j]=num;
        }
    }

    return size;
}
int initialization_num(ull** size,int a,int b,int num)
{

    for (int i=0;i<a;i+=1)
    {
        for(int j=0;j<b;j+=1)
        {
            size[i][j]=num;
        }
    }

}


int labirint_1(int a,int b);
int labirint_2(int a,int b);
int labirint_3(int a,int b);
int labirint_4(int a,int b,ull start,ull** size,ull**flag,int cnt_currs);

int main() {
//    FILE *fp;
//
//    fp= fopen("file.txt","w");
    int x,y,z;
    ull owowowow;
    int a, b;
    printf("Enter size\n");
    printf("Height:");
    scanf("%d", &a);
    printf("Width:");
    scanf("%d", &b);
    ull **size = initialization_5(a, b, 15);
    ull **flag = initialization_5(a, b, 0);
    int p=1;

    //labirint_3(a,b);
    FILE *fp;
    fp= fopen("D:\\generation of labirint\\results.txt","w");
    int s=clock();

//    for (int i=0;i<100;i++) {
//        ull start = clock();
//        p = labirint_4(a, b, start,size,flag,300);
//        initialization_num(size,a,b,15);
//        initialization_num(flag,a,b,0);
//        ull end=clock();
//        if (p==1){
//            fprintf(fp,"30\n");
//        }
//        else
//            fprintf(fp,"%f\n",(end-start)/(double)CLOCKS_PER_SEC);
//
//        printf("%d %f\n",i,(end-start)/(double)CLOCKS_PER_SEC);
//    }
    while (p==1) {
        ull start = clock();
        int si = a*b*0.01;
        p = labirint_4(a, b, start, size, flag, si);
        initialization_num(size,a,b,15);
        initialization_num(flag,a,b,0);
    }
    int e=clock();
    printf("%d",(e-s)/CLOCKS_PER_SEC);
    //_getch();
    return 0;
}