#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define EXIT 27
#define CONFIRM 13
#define YA 121
#define TIDAK 110
using namespace std;
int cursor[10][5]={0};
int bomb[10][5]={0};
int visible [10][5]={0};
int banyakpemain=0,win=0,ad=0;
struct game{
    int score=0;
    game *next;
}*head=NULL, *tail=NULL, *cur=NULL, *newNode=NULL;
void createUser(){
    if(banyakpemain>0){
        newNode = new game();
        newNode->next=NULL;
        tail->next=newNode;
        tail=newNode;
    }else{
        head=new game();
        head->next = NULL;
        tail=head; 
    }
    banyakpemain++;
}
void cursor_up(){
    for (int i = 0; i < 10; i++)
    {
        if (i-1>=0)
        {
            for (int j = 0; j < 5; j++)
            {
                if (cursor[i][j]>=1)
                {
                    cursor[i-1][j]=1;
                    cursor[i][j]=0;
                    return;
                }
            }
        }  
    }
}
void cursor_down(){
    for (int i = 0; i < 10; i++)
    {
        if ((i+1)<=9)
        {
            for (int j = 0; j < 5; j++)
            {
                if (cursor[i][j]>=1)
                {
                    cursor[i][j]=0;
                    cursor[i+1][j]=1;
                    return;
                }
            }
        }  
    }
}
void cursor_left(){
    for (int i = 0; i < 10; i++)
    {
        
        for (int j = 0; j < 5; j++)
        {
            if (j-1>=0)
            {
                if (cursor[i][j]>=1)
                {
                    cursor[i][j]=0;
                    cursor[i][j-1]=1;
                    return;
                }  
            }
            
        }
    
    }
}
void cursor_right(){
    for (int i = 0; i < 10; i++)
    {
        
        for (int j = 0; j < 5; j++)
        {
            if (j+1<=4)
            {
                if (cursor[i][j]>=1)
                {
                    cursor[i][j]=0;
                    cursor[i][j+1]=1;
                    return;
                }  
            }
            
        }
    }
}
void cursor_open(){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (cursor[i][j]==1)
            {
                cursor[i][j]=2;
                if(visible[i][j]==0){
                    visible[i][j]=1;
                    if (bomb[i][j]==0)
                    {
                        win-=1000;
                    }else if (visible[i][j]==1)
                    {
                        tail->score+=bomb[i][j];
                        win+=1;
                        visible[i][j]=2;
                    }
                }
            }
            
            
        }
        
    }
    
}
void resetValue(){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bomb[i][j]=0;
            visible[i][j]=0;
            cursor[i][j]=0;
        }
        
    }
    
}
void cekScore(){
    cur=head;
        cout<<"\nSkor Anda!!!\n";
    if (cur==NULL)
    {
        cout<<"Tidak Ada Data Pemain!!!\n";
    }else{ 
        for (int i=1; cur!=NULL; i++){
            cout<<i<<".\t: "<<cur->score<<endl;
            cur=cur->next;
        }
    }
    cout<<endl;
}
void welcome(){
    short counter = 30;
    Sleep(1000);
    while (counter >=1){
        cout<<"//////// Selamat Datang di GAME INGATAN ////////\n\n\n";
        cout<<"- Disini ingatan kamu akan diuji, Bersiaplah\n";
        cout<<"- Sebelum Mulai Bermain Program Akan Memberikan Anda Waktu 10 Detik Untuk Mengingat Lokasi BOMB\n";
        cout<<"- Kumpulkan Score sebanyak banyak nya\n";
        cout<<"- Hati-Hati Terdapat 8 Bomb [ * ], Jika Kamu Mendapat 1 Maka Game Berakhir\n";
        cout<<"- Selamat Bermain dan Semoga Beruntung <3 :)\n";
        cout << "\r\n\n- Permainan Akan Dimulai Dalam " << counter <<" Detik"<< flush;
        Sleep(1000);
        counter--;
        system("cls");
    }
}
int main(){
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(0));
    SetConsoleTextAttribute(h,7);
    welcome();
    ulang:
    cursor[0+rand()%10][0+rand()%6]=1;
    int input;
    int a=0,b=0,c=0;
    do
    {
        a:
        a=0+rand()%10;
        b=0+rand()%6;
        if (bomb[a][b]>0)
        {
            goto a;
        }else{
            bomb[a][b]=1+rand()%4;
        }
        c++;
    } while (c<43);
    short counter = 10; //amount of seconds
    Sleep(1000);
    while (counter >= 1)
    {
        if (ad>=1)
        {
            cekScore();
        }
        
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (bomb[i][j]==0)
                {
                    cout<<"[ * ] ";                    
                }else{
                    cout<<"[ "<<bomb[i][j]<<" ] ";
                }
            }
            cout<<endl<<endl;
        }
        cout << "\rAnda Akan Mulai Bermain Dalam " << counter <<" Detik"<< flush;
        Sleep(1000);
        counter--;
        system("cls");
    }
    createUser();
    
    awal:
    cout<<"          Skor Anda : "<<tail->score<<endl<<endl;
    cout<<"          ";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (cursor[i][j]==0)
            {
                if (visible[i][j]>=1)
                {
                    if (bomb[i][j]==0)
                    {
                        SetConsoleTextAttribute(h,12);
                        cout<<"[ * ]";
                    }else{
                        SetConsoleTextAttribute(h,14);
                        cout<<"[ "<<bomb[i][j]<<" ]";
                    }
                    
                    SetConsoleTextAttribute(h,7);
                    cout<<" ";
                }else{
                    SetConsoleTextAttribute(h,255);
                    cout<<"     ";
                    SetConsoleTextAttribute(h,7);
                    cout<<" ";
                }
            }else if (cursor[i][j]==1||cursor[i][j]==2)
            {
                if (cursor[i][j]==2)
                {
                    if (bomb[i][j]==0)
                    {
                        SetConsoleTextAttribute(h,12);
                        cout<<"[ * ]";
                        SetConsoleTextAttribute(h,7);
                        cout<<" ";
                    }else if(bomb[i][j]>0){
                        SetConsoleTextAttribute(h,14);
                        cout<<"[ "<<bomb[i][j]<<" ]";
                        SetConsoleTextAttribute(h,7);
                        cout<<" ";

                    }
                    
                }
                if(cursor[i][j]==1){
                    SetConsoleTextAttribute(h,99);
                    cout<<"     ";
                    SetConsoleTextAttribute(h,7);
                    cout<<" ";

                }
                
            }
        }
        cout<<endl<<endl<<"          ";
    }
    if (win==42)
    {
        cout<<"\n            //////// YOU WIN ////////\n";
        goto opsi;
    }else if(win<0){
        cout<<"\n            //////// YOU LOSE ////////\n";
        goto opsi;
    }
    SetConsoleTextAttribute(h,99);
    cout<<"\n ";
    SetConsoleTextAttribute(h,7);
    cout<<" Gunakan Arah Panah Untuk Memindahkan Cursor.....";
    SetConsoleTextAttribute(h,99);
    cout<<" \n ";
    SetConsoleTextAttribute(h,7);
    cout<<" Tekan ENTER Untuk Membuka Kotak.................";
    SetConsoleTextAttribute(h,99);
    cout<<" \n ";
    SetConsoleTextAttribute(h,7);
    cout<<" Tekan ESC Untuk Berhenti Bermain................";
    SetConsoleTextAttribute(h,99);
    cout<<" ";
    SetConsoleTextAttribute(h,7);
    attemp:
    input=getch();
    if(input==0||input==0xE0){
        input=getch();
    }
    switch (input)
    {
    case KEY_UP:
        cursor_up();
        system("cls");
        goto awal;
        break;
    case KEY_DOWN:
        cursor_down();
        system("cls");
        goto awal;
        break;
    case KEY_LEFT:
        cursor_left();
        system("cls");
        goto awal;
        break;
    case KEY_RIGHT:
        cursor_right();
        system("cls");
        goto awal;
        break;
    case CONFIRM:
        cursor_open();
        system("cls");
        goto awal;
        break;
    case EXIT:
        system("cls");
        cekScore();
        return 0;
        break;
    default:
        SetConsoleTextAttribute(h,12);
        cout<<"\n   !!!!!Sundel Salah Input!!!!, Ulang Ulang :^\n";
        SetConsoleTextAttribute(h,7);
        goto attemp;
        break;
    }
    opsi:
    cout<<"        Ingin Mengulang Permainan ???...\n";
    cout<<"        Tekan Enter Untuk YA............\n";
    cout<<"        Tekan Esc Untuk Tidak...........\n";
    z:
    input = getch();
    switch (input)
    {
    case CONFIRM:
        system("cls");
        resetValue();
        win=0;
        ad+=1;
        goto ulang;
        break;
    case EXIT:
        system("cls");
        cekScore();
        return 0;
    default:
        SetConsoleTextAttribute(h,12);
        cout<<"Sundel Dibilangin Input ENTER atau Esc doang\nPacuan Coba Jadi User :(\n";
        SetConsoleTextAttribute(h,7);
        goto z;
        break;
    }
    return 0;
}