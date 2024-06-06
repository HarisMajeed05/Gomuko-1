#include<windows.h>
#include<conio.h>
#include<iostream>
#include<math.h>

using namespace std;

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}


void init(char a[][19], int d, string namep[], int nop, char sym[], int& tu)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            a[r][c] = '-';
        }
    }
    for (int r = 0; r < nop; r++)
    {
        cout << "Player " << r + 1 << " name :";
        string a;
        cin >> a;
        namep[r] = a;
        cout << "Player " << r + 1 << " symbol :";
        char b;
        cin >> b;
        sym[r] = b;
    }
    //tu = rand.radiant(0, nop);

}
void printboard(char a[][19], int d)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            cout << a[r][c];
        }cout << "\n";
    }
}
void turnmsg(string a)
{
    cout << a << "'s TURN! \n";
}
void selectposition(int pr, int pc, int d)
{

}
void placemove(char a[][19], int pr, int pc, char sym)
{
    a[pr][pc] = sym;
}
void turnch(int& tu, int nop)
{
    tu = (tu + 1) % nop;
}
bool isvalid(char a[][19], int d, int r, int c)
{
    return (r >= 0 && r < d) && (c >= 0 && c < d) && (a[r][c] == '-');
}
bool winhori(char a[][19], int d, int r, int c, char sym, int win)
{
    if (c + win > d)
        return false;
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r][c + i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winver(char a[][19], int d, int r, int c, char sym, int win)
{
    if (r + win > d)
        return false;
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r + i][c] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winLtoR(char a[][19], int d, int r, int c, char sym, int win)
{
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r + i][c + i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winRtoL(char a[][19], int d, int r, int c, char sym, int win)
{
    int count = 0;
    for (int i = 0; i < win; i++)
        if (a[r + i][c - i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool win(char a[][19], int d, char smb[], int win, int t)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (winhori(a, d, r, c, smb[t], win))
                return true;
            if (winver(a, d, r, c, smb[t], win))
                return true;
            if (winLtoR(a, d, r, c, smb[t], win))
                return true;
            if (winRtoL(a, d, r, c, smb[t], win))
                return true;
        }
    }
    return false;
}
bool draw(char a[][19], int d)
{
    int count = 0;
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (a[r][c] == '-')
                count++;
        }
    }
    if (count == 0)
        return true;
    else
        return false;
}


int main()
{
    char B[19][19];
    int dim, nop, turn = 0, row = 0, col = 0, winl = 0, gm = 0;
    cout << "Enter Dimension ";
    cin >> dim;
    if (dim == 3)
    {
        winl = 3;
    }
    else
    {
        cout << "Enter win Lenght  " << dim << "\n";
        cin >> winl;
    }
    cout << "Enter Number of Players: ";
    cin >> nop;
    const int l = 5;
    string PN[l];
    char Sym[l];
    init(B, dim, PN, nop, Sym, turn);
    while (gm == 0)
    {
        system("Cls");
        printboard(B, dim); cout << "\n";
        turnmsg(PN[turn]);
        do
        {
            getRowColbyLeftClick(row, col);
        } while (!isvalid(B, dim, row, col));
        placemove(B, row, col, Sym[turn]);
        if (win(B, dim, Sym, winl, turn))
        {
            system("Cls");
            printboard(B, dim);
            cout << "\n\nPlayer " << turn + 1 << " " << PN[turn] << " WINS!\n\n";
            gm = 1;
        }
        if (draw(B, dim))
        {
            system("Cls");
            printboard(B, dim);
            cout << "\n\nGame Draw \n\n";
            gm = 1;
        }
        turnch(turn, nop);

    }
}