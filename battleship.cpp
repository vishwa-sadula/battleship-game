#include <bits/stdc++.h>
using namespace std;

// for windows
#define clear_terminal system("cls");

// for linux
//#define clear_terminal system("clear");

string red = "\033[38;5;209m";
string blue = "\033[38;5;039m";
string yellow = "\033[38;5;227m";
string nc = "\033[0m";
string emptyy;

char grid[2][10][10];
int turn = 1;
vector<pair<int, int>> shots[2][5]; // hit positions
int sinks[2] = {0, 0};

void display_grid(int);
void planning_phase();
void guessing_phase();
void display_blocked_grid(int);

void guessing_phase()
{
    clear_terminal
        turn %= 2;
    string color = turn ? blue : yellow;
    cout << color << "\tMy grid\n"
         << nc;
    display_grid(turn ^ 1);
    cout << color << "\tOpponent's grid\n"
         << nc;
    display_blocked_grid(turn);
    cout << color << "Attack on co-ordinate:";
    int x;
    char yy;
    cin >> yy >> x;
    yy = toupper(yy);
    cout << nc;
    int y = yy - 'A';
    x--;
    if (x < 0 or x > 9 or y < 0 or y > 9)
    {
        cout << red << "Enter a valid co-ordinate!!\n\nPress ENTER to continue.\n"
             << nc;
        getline(cin, emptyy);
        getline(cin, emptyy);
        turn++;
    }
    else if (grid[turn][x][y] == '*' or grid[turn][x][y] == 'H' or grid[turn][x][y] == 'S')
    {
        cout << red << "This co-ordinate has already been attacked.\n\nPress ENTER to continue.\n"
             << nc;
        getline(cin, emptyy);
        getline(cin, emptyy);
        turn++;
    }
    else
    {
        char current_pos = grid[turn][x][y];
        if (current_pos == '.')
        {
            grid[turn][x][y] = '*';

            clear_terminal
                    cout
                << color << "\tMy grid\n"
                << nc;
            display_grid(turn ^ 1);
            cout << color << "\tOpponent's grid\n"
                 << nc;
            display_blocked_grid(turn);
            cout << color << "Oops!! It is a MISS..\n\nPress ENTER to continue.\n"
                 << nc;
            getline(cin, emptyy);
            getline(cin, emptyy);
        }
        else
        {
            shots[turn]['E' - current_pos].push_back({x, y});
            grid[turn][x][y] = 'H';
            if (shots[turn]['E' - current_pos].size() == 'E' - current_pos + 1)
            {
                for (auto points : shots[turn]['E' - current_pos])
                {
                    int i = points.first, j = points.second;
                    grid[turn][i][j] = 'S';
                }
                sinks[turn]++;
                if (sinks[turn] != 5)
                {
                    clear_terminal
                            cout
                        << color << "\tMy grid\n"
                        << nc;
                    display_grid(turn ^ 1);
                    cout << color << "\tOpponent's grid\n"
                         << nc;
                    display_blocked_grid(turn);
                    cout << color << "Hurray!! HIT AND SUNK ..\nYou get another turn...\n\nPress ENTER to continue.\n"
                         << nc;
                    getline(cin, emptyy);
                    getline(cin, emptyy);
                }
            }
            else
            {
                clear_terminal
                        cout
                    << color << "\tMy grid\n"
                    << nc;
                display_grid(turn ^ 1);
                cout << color << "\tOpponent's grid\n"
                     << nc;
                display_blocked_grid(turn);
                cout << color << "Hurray!! It is a HIT..\nYou get another turn...\n\nPress ENTER to continue.\n"
                     << nc;
                getline(cin, emptyy);
                getline(cin, emptyy);
            }
            turn++;
            turn %= 2;
        }
    }
    if (sinks[turn ^ 1] == 5)
    {
        clear_terminal
            display_blocked_grid(turn ^ 1);
        cout << "\033[38;5;046m"
             << "Player " << turn + 1 << " wins!!\n\n"
             << nc;
        return;
    }

    turn++;
    guessing_phase();
}

void planning_phase()
{
    bool ok = true;
    string color;
    string ships[5] = {"Aircraft carrier (A)", "Battleship (B)", "Destroyer (C)", "Corvette (D)", "Frigate (E)"};

    for (int player = 0; player <= 1; player++)
    {
        color = player ? yellow : blue;

        for (int type = 5; type > 0; type--)
        {
            clear_terminal if (!ok)
                    cout
                << red << "\n\nEnter valid position !!\n\n"
                << nc;

            ok = true;
            display_grid(player);
            cout << color;
            cout << "The starting co-ordinate for " << ships[5 - type] << " :";
            int x;
            char yy, z;
            cin >> yy >> x;
            yy = toupper(yy);
            cout << "Choose orientation Vertical(V) or Horizontal(H):";
            cin >> z;
            z = toupper(z);
            cout << nc;
            int y = yy - 'A';
            x--;

            if (z == 'H')
            {
                if (x < 10 and y < 10 and x >= 0 and y >= 0 and y + type - 1 < 10)
                {
                    for (int i = x, j = y; j < y + type; j++)
                    {
                        if (grid[player][i][j] != '.')
                            ok = false;
                    }
                }
                else
                    ok = false;
            }
            else if (z == 'V')
            {
                if (x < 10 and y < 10 and x >= 0 and y >= 0 and x + type - 1 < 10)
                {
                    for (int i = x, j = y; i < x + type; i++)
                    {
                        if (grid[player][i][j] != '.')
                            ok = false;
                    }
                }
                else
                    ok = false;
            }
            else
                ok = false;

            if (!ok)
            {
                type++;
                continue;
            }

            if (z == 'H')
            {
                for (int i = x, j = y; j < y + type; j++)
                {
                    grid[player][i][j] = 'A' + 5 - type;
                }
            }
            else if (z == 'V')
            {

                for (int i = x, j = y; i < x + type; i++)
                {
                    grid[player][i][j] = 'A' + 5 - type;
                }
            }
        }

        clear_terminal
                cout
            << color << "\tFinal grid\n"
            << nc;
        display_grid(player);
        cout << color << "\nPress ENTER to continue..\n\n"
             << nc;
        getline(cin, emptyy);
        getline(cin, emptyy);
    }
}

void display_grid(int t)
{
    int i, j;
    string color = t == 0 ? blue : yellow;
    cout << "\n"
         << color;
    cout << "   ";
    for (i = 0; i < 10; i++)
    {
        cout << setw(3) << char('A' + i);
    }
    for (i = 0; i < 10; i++)
    {
        cout << "\n";
        cout << setw(3) << i + 1;
        for (j = 0; j < 10; j++)
        {
            cout << setw(3) << grid[t][i][j];
        }
    }
    cout << "\n\n\n"
         << nc;
}

void display_blocked_grid(int t)
{
    int i, j;
    string color = t == 1 ? blue : yellow;
    cout << "\n"
         << color;
    cout << "   ";
    for (i = 0; i < 10; i++)
    {
        cout << setw(3) << char('A' + i);
    }
    for (i = 0; i < 10; i++)
    {
        cout << "\n";
        cout << setw(3) << i + 1;
        for (j = 0; j < 10; j++)
        {
            char x = (grid[t][i][j] >= 'A' and grid[t][i][j] <= 'E') ? '.' : grid[t][i][j];
            cout << setw(3) << x;
        }
    }
    cout << "\n\n\n"
         << nc;
}

int main()
{
    clear_terminal int i, j;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            grid[0][i][j] = '.'; // grid[0][i][j] for player 1
            grid[1][i][j] = '.'; // grid[1][i][j] for player 2
        }
    }

    cout << "\n";
    cout << blue << "Blue " << nc << " stands for player 1\n";
    cout << yellow << "Yellow " << nc << " stands for player 2\n";
    cout << "Enter every co-ordinate as LETTER-NUMBER for its COLUMN-ROW (Such as F6)\n";
    cout << "\n\n";

    cout << "Press ENTER to start planning..\n\n";
    getline(cin, emptyy);
    planning_phase();
    clear_terminal
            cout
        << "Planning phase completed!!\n\nPress ENTER to start Guessing..\n\n";
    getline(cin, emptyy);
    guessing_phase();

    return 0;
}
