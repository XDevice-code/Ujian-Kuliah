#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int papan[10] = {2,2,2,2,2,2,2,2,2,2};
int giliran = 1,bendera = 0;
int pemain,comp;

void menu();
void go(int n);
void mulai_game();
void cek_seri();
void gambar_papan();
void pemain_pertama();
void put_X_O(char ch,int pos);
COORD coord= {0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
    system("cls");
    menu();
    getch();

}

void menu()
{
    int choice;
    system("cls");
    printf("\n-------- MENU --------");
    printf("\n1 : Bermain jadi X");
    printf("\n2 : Bermain jadi O");
    printf("\n3 : Exit");
    printf("\n");
    printf("\nMasukkan pilihanmu:>");
    scanf("%d",&choice);
    giliran = 1;
    switch (choice)
    {
    case 1:
        pemain = 1;
        comp = 0;
        pemain_pertama();
        break;
    case 2:
        pemain = 0;
        comp = 1;
        mulai_game();
        break;
    case 3:
        exit(1);
    default:
        menu();
    }
}

int make2()
{
    if(papan[5] == 2)
        return 5;
    if(papan[2] == 2)
        return 2;
    if(papan[4] == 2)
        return 4;
    if(papan[6] == 2)
        return 6;
    if(papan[8] == 2)
        return 8;
    return 0;
}

int make4()
{
    if(papan[1] == 2)
        return 1;
    if(papan[3] == 2)
        return 3;
    if(papan[7] == 2)
        return 7;
    if(papan[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{
    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;
    else
        check_val = 50;

    i = 1;
    while(i<=9)
    {
        if(papan[i] * papan[i+1] * papan[i+2] == check_val)
        {
            if(papan[i] == 2)
                return i;
            if(papan[i+1] == 2)
                return i+1;
            if(papan[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)
    {
        if(papan[i] * papan[i+3] * papan[i+6] == check_val)
        {
            if(papan[i] == 2)
                return i;
            if(papan[i+3] == 2)
                return i+3;
            if(papan[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(papan[1] * papan[5] * papan[9] == check_val)
    {
        if(papan[1] == 2)
            return 1;
        if(papan[5] == 2)
            return 5;
        if(papan[9] == 2)
            return 9;
    }

    if(papan[3] * papan[5] * papan[7] == check_val)
    {
        if(papan[3] == 2)
            return 3;
        if(papan[5] == 2)
            return 5;
        if(papan[7] == 2)
            return 7;
    }
    return 0;
}

void go(int n)
{
    if(giliran % 2)
        papan[n] = 3;
    else
        papan[n] = 5;
    giliran++;
}

void pemain_pertama()
{
    int pos;

    cek_seri();
    gambar_papan();
    gotoxy(30,18);
    printf("Giliranmu :> ");
    scanf("%d",&pos);

    if(papan[pos] != 2)
        pemain_pertama();

    if(pos == posswin(pemain))
    {
        go(pos);
        gambar_papan();
        gotoxy(30,20);
        printf("Pemain Menang");
        getch();
        exit(0);
    }

    go(pos);
    gambar_papan();
    mulai_game();
}

void mulai_game()
{
    if(posswin(comp))
    {
        go(posswin(comp));
        bendera = 1;
    }
    else if(posswin(pemain))
        go(posswin(pemain));
    else if(make2())
        go(make2());
    else
        go(make4());
    gambar_papan();

    if(bendera)
    {
        gotoxy(30,20);
        printf("Computer Menang");
        getch();
    }
    else
        pemain_pertama();
}

void cek_seri()
{
    if(giliran > 9)
    {
        gotoxy(30,20);
        printf("Game Seri");
        getch();
        exit(0);
    }
}

void gambar_papan()
{
    int j;

    for(j=9; j<17; j++)
    {
        gotoxy(35,j);
        printf("|       |");
    }
    gotoxy(28,11);
    printf("-----------------------");
    gotoxy(28,14);
    printf("-----------------------");

    for(j=1; j<10; j++)
    {
        if(papan[j] == 3)
            put_X_O('X',j);
        else if(papan[j] == 5)
            put_X_O('O',j);
    }
}

void put_X_O(char ch,int pos)
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
}
