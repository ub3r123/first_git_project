//Алгоритм Уилсона

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


typedef struct Node
{
    int i;
    int j;
    int fl;
    struct Node* curr;
} Node;

typedef unsigned long long ull;




//left 1
//right 2
//up 4
//down 8
int delete_4(ull** mas,int a,int b)
{
    for (int i=0;i<a;i++)
    {
        free(*(mas+i));
    }
    free(mas);
}
int delete_curr(Node** node)
{
    Node*curr=*node;
    while(curr->curr!=NULL)
    {
        Node*remove=curr;
        curr=curr->curr;
        free(remove);
    }
    free(curr);
    *node=NULL;
}
ull** initialization_4(int a,int b,int num)
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

int flag_4(ull**size,ull**fl,int a,int b)
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

int print_4(ull**size,int a,int b)
{
    FILE *fp;
    fp= fopen("D:\\generation of labirint\\file.txt","w");
    ull** fl= initialization_4(a,b,0);
    flag_4(size,fl,a,b);

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

    //delete_4(fl,a,b);

}

int delete_walls(int a,int b,ull** size,int move,int i,int j)
{
    if (move==0)
    {
        size[i][j]-=2;
        size[i][j+1]-=1;
    }
    else if (move==1)
    {
        size[i][j]-=8;
        size[i+1][j]-=4;
    }
    else if (move==2)
    {
        size[i][j]-=1;
        size[i][j-1]-=2;
    }
    else if (move==3)
    {
        size[i][j]-=4;
        size[i-1][j]-=8;
    }

}


int snake(int sum,int* cur_cnt,ull cur_flag, ull **size,ull **flag,int i,int j,int move_last,int a,int b,int* fl,ull start,Node**node,int *cnt_p)
{
    ull end =clock();
    if ((double)(end-start)/(double)CLOCKS_PER_SEC > 1.0) return 3;
    if (flag[i][j]==-1)
    {
        if (*fl==1){
            *fl=0;
            Node*curr=*node;
            while(curr!=NULL)
            {
                if (i!=curr->i || j!=curr->j)
                {
                    flag[curr->i][curr->j]=0;
                }
                curr=curr->curr;

            }
            delete_curr(node);
        }
        delete_walls(a,b,size,move_last,i,j);
        return 1;
    }
    else if (flag[i][j]==cur_flag)
    {
        return 0;
    }
    else
    {
        flag[i][j]=cur_flag;
        int flag_move=1;
        int moves[4]={1,1,1,1};
        int cnt=4;

        int random_moves=rand()%2;

        do{
            int move;
            int t;
            if (cnt!=1)
                t=rand()%(cnt-1)+1;
            else
                t=1;

            if (random_moves==0) {
                int t_u = 0;

                for (int k = 0; k < 4; k++) {
                    if (moves[3 - k] == 1) {
                        t_u++;
                        if (t_u == t) {
                            move = 3 - k;
                            break;
                        }
                    }
                }
            }
            else if (random_moves==1 ){
                int t_u = 0;
                for (int k = 0; k < 4; k++) {
                    if (moves[k] == 1) {
                        t_u++;
                        if (t_u == t) {
                            move = k;
                            break;
                        }
                    }
                }
            }

            cnt-=1;
            if (move==0 && j!=0)
            {
                int p=snake(sum,cur_cnt,cur_flag,size,flag,i,j-1,0,a,b,fl,start,node,cnt_p);
                if (p==1)
                {
                    flag[i][j]=-1;
                    *cur_cnt+=1;
                    delete_walls(a,b,size,move_last,i,j);
                    return 1;
                }
                else if (p==3){
                    return 3;
                }
                else
                {
                    moves[0]=0;
                }
            }
            if (move==1 && i!=0)
            {
                int p=snake(sum,cur_cnt,cur_flag,size,flag,i-1,j,1,a,b,fl,start,node,cnt_p);
                if (p==1)
                {
                    flag[i][j]=-1;
                    *cur_cnt+=1;

                    delete_walls(a,b,size,move_last,i,j);
                    return 1;
                }
                else if (p==3){
                    return 3;
                }
                else
                {
                    moves[1]=0;
                }
            }
            if (move==2 && j!=b-1)
            {
                int p=snake(sum,cur_cnt,cur_flag,size,flag,i,j+1,2,a,b,fl,start,node,cnt_p);
                if (p==1)
                {
                    flag[i][j]=-1;
                    *cur_cnt+=1;

                    delete_walls(a,b,size,move_last,i,j);
                    return 1;
                }
                else if (p==3){
                    return 3;
                }
                else
                {

                    moves[2]=0;
                }
            }
            if (move==3 && i!=a-1)
            {
                int p=snake(sum,cur_cnt,cur_flag,size,flag,i+1,j,3,a,b,fl,start,node,cnt_p);
                if (p==1)
                {
                    flag[i][j]=-1;

                    delete_walls(a,b,size,move_last,i,j);
                    *cur_cnt+=1;
                    return 1;
                }
                else if (p==3){
                    return 3;
                }
                else
                {
                    moves[3]=0;
                }
            }
            else
            {
                moves[move]=0;
            }
        }while((moves[0] || moves[1] || moves[2] || moves[3]) && cnt>0);

        flag[i][j]=0;
        return 0;
    }
}

int labirint_4(int a,int b,ull start,ull**size,ull** flag,int cnt_currs) {
    //ull **size = initialization_4(a, b, 15);
    //ull **flag = initialization_4(a, b, 0);

    srand(time(NULL));

    int i, j, sum = a * b, cnt = 0, move, cur_cnt = 0;
    int i1 = rand() % a, j1 = rand() % b;
    flag[i1][j1] = -1;
    Node* node=malloc(sizeof(Node));
    node->i=i1;
    node->j=j1;
    node->fl=0;

    Node*curr=node;
    if (a*b>1000) {
        for (int i=0;i<cnt_currs;i++) {
            i1 = rand() % a;
            j1 = rand() % b;
            flag[i1][j1] = -1;
            curr->curr=malloc(sizeof(Node));
            curr=curr->curr;
            curr->i=i1;
            curr->j=j1;
            curr->fl=0;
            curr->curr=NULL;
        }
        cnt+=1;
    }
    else
        cnt += 1;
    i=i1;
    j=j1;
    int fl;
    if (a*b>1000){
        fl=1;
    }
    else
        fl=0;
    ull cur_flag = 2;
    if (fl==1) {
        while (flag[i][j]!=-1) {
            i = rand() % a;
            j = rand() % b;
        }
    }
    else{
        while (i == i1 ) i = rand() % a;
        while (j == j1 ) j = rand() % b;
    }
    flag[i][j]=cur_flag;
    int hhh = 1;

    int attention=0;
    while (sum > cnt) {
        int t = sum - cnt;
        t = rand() % t + 1;
        int t_cur = 0;
        for (int i2 = 0; i2 < a; i2++) {
            int flag2 = 0;
            for (int j2 = 0; j2 < b; j2++) {
                if (flag[i2][j2] != -1) {
                    t_cur++;
                    if (t == t_cur || t==1 || t==0) {
                        i = i2;
                        j = j2;
                        flag2 = 1;
                        break;
                    }
                }
            }
            if (flag2 == 1) break;
        }

        int p=snake(sum, &cur_cnt, cur_flag, size, flag, i, j, -1, a, b, &fl,start,&node,&cnt);
        if (p==3){
            attention=1;
            break;
        }
        cnt += cur_cnt;
        cur_cnt = 0;
        cur_flag++;
    }

    if (attention==0) {
        if (node!=NULL)
        {
            //delete_curr(&node);
        }
        print_4(size, a, b);
//        delete_4(size, a, b);
//        delete_4(flag, a, b);
//        for (int i=0;i<a;i++){
//            for(int j=0;j<b;j++){
//                printf("%d ",size[i][j]);
//            }
//            printf("\n");
//        }
        return 0;
    }
    else{
        if (node!=NULL)
        {
            delete_curr(&node);
            node=NULL;
        }
        //delete_4(size, a, b);
        //delete_4(flag, a, b);
        return 1;
    }



}