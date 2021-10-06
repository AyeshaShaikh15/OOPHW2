#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;

//Structure to keep track of various locations
struct Point
{
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y)
    {
    }
};
//Structure for the Player object
struct Player
{
    int food;
    int health;
    bool alive;
    int x;
    int y;
    Player()
    {
        food = 64;
        health = 10;
        alive = true;
    }
    void loseHealth()
    {
        if (health > 0)
            health--;
        if (health == 0)
            alive = false;
    }
    void gainHealth()
    {
        if (health < 10)
            health++;
    }
};

typedef const int cint; //Google typedef to see what this means
typedef const Point cPoint;

char *CreateDungeon(int, int, Point &, Point &);       //Creates the dungeon
void Traversal(char *, Point &, cPoint &, cint, cint); //Used for moving inside dungeon
void Combat(Player &, int);                            //Used for simulating combat
void TrapStatements();                                 //3 statements that show at random when the player activates a trap
void FoodStatements();                                 //3 statements that show at random when the player finds food
void HitStatements();                                  //3 statements that show at random when the player hits enemy
void GetHitStatements();                               //3 statements that show at random when the player gets hit
void display(char *, int, int);
//void move_left(char direction, char *dungeon, int width, int height, int enemies);
//void move_right(char direction, char *dungeon, int width, int height, int enemies);
//void move_down(char direction, char *dungeon, int width, int height, int enemies);
//void move_up(char direction, char *dungeon, int width, int height, int enemies);

void move_left(char direction, char *dungeon, int width, int height, int enemies)
{
    Player p;
    for (int i = 0; i < (width - 1) * (height - 1); i++)
    {
        if (dungeon[i] == 'P' && dungeon[i + 1] == ' ')
        {
            dungeon[i] = ' ';
            dungeon[i - 1] = 'P';
            printf("There is nothing here. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - 1] == 'w')
        {
            printf("You are at the edge of the tunnel, you cannot move left. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - 1] == 'H')
        {
            dungeon[i] = ' ';
            dungeon[i - 1] = 'P';
            p.gainHealth();
            printf ("You found some health. \n");
            printf("Current health: %d ", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - 1] == 'E')
        {
            Combat(p, enemies);
            dungeon[i] = ' ';
            dungeon[i - 1] = 'P';
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - 1] == 'T')
        {
            TrapStatements();
            dungeon[i] = ' ';
            dungeon[i - 1] = 'P';
            p.loseHealth();
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - 1] == 'F')
        {
            FoodStatements();
            dungeon[i] = ' ';
            dungeon[i - width] = 'P';
            p.gainHealth();
            printf("Current health: %d", p.health);
            break;
        }
    }
}

void move_right(char direction, char *dungeon, int width, int height, int enemies)
{
    Player p;
    for (int i = 0; i < (width - 1) * (height - 1); i++)
    {
        if (dungeon[i] == 'P' && dungeon[i + 1] == ' ')
        {
            dungeon[i] = ' ';
            dungeon[i + 1] = 'P';
            printf ("There is nothing here. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + 1] == 'w')
        {
            printf ("You are at the edge of the tunnel, you cannot move right. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + 1] == 'H')
        {
            dungeon[i] = ' ';
            dungeon[i + 1] = 'P';
            p.gainHealth();
            printf ("You found some health. \n");
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + 1] == 'E')
        {
            Combat(p, enemies);
            dungeon[i] = ' ';
            dungeon[i + 1] = 'P';
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + 1] == 'T')
        {
            TrapStatements();
            dungeon[i] = ' ';
            dungeon[i + 1] = 'P';
            p.loseHealth();
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + 1] == 'F')
        {
            FoodStatements();
            dungeon[i] = ' ';
            dungeon[i + 1] = 'P';
            p.gainHealth();
            printf("Current health: %d", p.health);
            break;
        }
    }
}

void move_down(char direction, char *dungeon, int width, int height, int enemies)
{
    Player p;
    for (int i = 0; i < (width - 1) * (height - 1); i++)
    {
        if (dungeon[i] == 'P' && dungeon[i + width] == ' ')
        {
            dungeon[i] = ' ';
            dungeon[i + width] = 'P';
            printf ("There is nothing here. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + width] == 'w')
        {
            printf ("You are at the edge of the tunnel, you cannot move down. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + width] == 'H')
        {
            dungeon[i] = ' ';
            dungeon[i + width] = 'P';
            p.gainHealth();
            printf ("You found some health. \n");
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + width] == 'E')
        {
            Combat(p, enemies);
            dungeon[i] = ' ';
            dungeon[i + width] = 'P';
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + width] == 'T')
        {
            TrapStatements();
            dungeon[i] = ' ';
            dungeon[i + width] = 'P';
            p.loseHealth();
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i + width] == 'F')
        {
            FoodStatements();
            dungeon[i] = ' ';
            dungeon[i + width] = 'P';
            p.gainHealth();
            printf("Current health: %d", p.health);
            break;
        }
    }
}

void move_up(char direction, char *dungeon, int width, int height, int enemies)
{
    Player p;
    for (int i = 0; i < (width - 1) * (height - 1); i++)
    {
        if (dungeon[i] == 'P' && dungeon[i - width] == ' ')
        {
            dungeon[i] = ' ';
            dungeon[i - width] = 'P';
            printf ("There is nothing here. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - width] == 'w')
        {
            printf ("You are at the edge of the tunnel, you cannot move up. \n");
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - width] == 'H')
        {
            dungeon[i] = ' ';
            dungeon[i - width] = 'P';
            p.gainHealth();
            printf ("You found some health. \n");
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - width] == 'E')
        {
            Combat(p, enemies);
            dungeon[i] = ' ';
            dungeon[i - width] = 'P';
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - width] == 'T')
        {
            TrapStatements();
            dungeon[i] = ' ';
            dungeon[i - width] = 'P';
            p.loseHealth();
            printf("Current health: %d", p.health);
            break;
        }
        else if (dungeon[i] == 'P' && dungeon[i - width] == 'F')
        {
            FoodStatements();
            dungeon[i] = ' ';
            dungeon[i - width] = 'P';
            p.gainHealth();
            printf("Current health: %d", p.health);
            break;
        }
    }
}

int main()
{
    srand(time(0));

    int width;
    int height;
    printf ("Enter width: \n");
    while (true)
    {
        cin >> width;
        if (width >= 8)
        {
            break;
        }
        else
        {
            printf ("Width should be great than or equal to 8 \n");
        }
    }

    printf("Enter height: \n");
    while (true)
    {
        cin >> height;
        if (height >= 8)
        {
            break;
        }
        else
        {
            printf ("Height should be great than or equal to 8\n");
        }
    }

    /*
    *   ADD YOUR CODE HERE IF REQUIRED
    */

    Point startPoint(0, 0);
    Point exitPoint(0, 0);

    char *dungeon = nullptr;

    dungeon = CreateDungeon(width, height, startPoint, exitPoint);
    //cout << dungeon;
    Traversal(dungeon, startPoint, exitPoint, width, height);
    //display(dungeon, width, height);

    /*
        *   ADD YOUR CODE HERE IF REQUIRED
        */

    return 0;
}

void TrapStatements()
{
    int randomnumber;
    randomnumber = rand() % 50;
    if (randomnumber >= 20 && randomnumber <= 30)
    {
        printf("You stepped into a bear trap and got yourself injured. \n");
    }
    else if (randomnumber >= 30 && randomnumber <= 40)
    {
        printf("You walked into some spikes that sprung out of the floor. \n");
    }
    else
    {
        printf("An arrow flew out of a nearby wall and hit you in your posterior. That will leave a scar! \n");
    }
}

void FoodStatements()
{
    int randomnumber;
    randomnumber = rand() % 50;
    if (randomnumber >= 20 && randomnumber <= 30)
    {
        printf("It is a bread roll in this dungeon? Maybe there is a secret bakery around here. \n");
    }
    else if (randomnumber >= 30 && randomnumber <= 40)
    {
        printf("You looked at the food and it was a well cooked chicken ... well at least it looked like one. \n");
    }
    else
    {
        printf("It is a rat as big as a rabbit. It will go down well with a bit of wasp juice. \n");
    }
}

void HitStatements()
{
    int randomnumber;
    randomnumber = rand() % 50;
    if (randomnumber >= 20 && randomnumber <= 30)
    {
        printf("Your speed is unmatched and delivered a Stone Cold Stunner. One enemy dead! \n");
    }
    else if (randomnumber >= 30 && randomnumber <= 40)
    {
        printf("Your roundhouse kick sent your enemy flying right into a gutter. One enemy dead! \n");
    }
    else
    {
        printf("You made an excellent jab that knocked the lights out of your enemy. One enemy dead! \n");
    }
}

void GetHitStatements()
{
    Player p;
    int randomnumber;
    randomnumber = rand() % 50;
    if (randomnumber >= 20 && randomnumber <= 30)
    {
        printf("The enemy threw a rock that hit you on the temple and shook you bad. \n");
        p.loseHealth();
    }
    else if (randomnumber >= 30 && randomnumber <= 40)
    {
        printf("The enemy avoided your attack and gave you a nasty scratch. \n");
        p.loseHealth();
    }
    else
    {
        printf("You were not prepared for a sudden lunging attack that hit you hard. \n");
        p.loseHealth();
    }
}

void Traversal(char *dungeon, Point &startPoint, cPoint &exitPoint, cint width, cint height)
{
    //char U, D, L, R;
    int enemies;
    //Player player;

    Player p;
    char direction;
    int foodremaining;
    display(dungeon, width, height);
    while (p.alive == true && p.food != 0 && p.health != 0)
    {
        printf("\n Enter the direction you wish to move in: \n");
        cin >> direction;
        if (direction == 'L')
        {
            move_left(direction, dungeon, width, height, enemies);
            p.food -= 1;
            printf("you have food for %d remaining turns", p.food);
        }
        else if (direction == 'R')
        {
            move_right(direction, dungeon, width, height, enemies);
            p.food -= 1;
            printf("you have food for %d remaining turns", p.food);
        }
        else if (direction == 'D')
        {
            move_down(direction, dungeon, width, height, enemies);
            p.food -= 1;
            printf("you have food for %d remaining turns", p.food);
        }
        else if (direction == 'U')
        {
            move_up(direction, dungeon, width, height, enemies);
            p.food -= 1;
            printf("you have food for %d remaining turns", p.food);
        }
        else if (direction == 'X')
        {
            break;
        }
        display(dungeon, width, height);
        cout << endl;
    }
}

void Combat(Player &player, int enemies)
{
    Player p;
    int randomnumber;
    while (enemies != 0 && p.health != 0)
    {
        randomnumber = rand() % 50;
        if (randomnumber <= 30 && randomnumber > 10)
        {
            HitStatements();
            enemies--;
        }
        else if (randomnumber <= 10)
        {
            GetHitStatements();
            p.loseHealth();
        }
    }
}

char *CreateDungeon(int width, int height, Point &ref_startPoint, Point &ref_exitPoint)
{
    char *dungeon = new char[width * height];
    for (int i = 0; i <= (width * height) - 1; i++)
    {
        dungeon[i] = ' ';
    }
    for (int i = 0; i <= width - 1; i++)
    {
        dungeon[i] = 'w';
    }
    cout << "\n";
    for (int i = width; i <= ((width - 1) * height) - 1; i += width)
    {
        dungeon[i] = 'w';
        dungeon[i - 1] = 'w';
    }
    dungeon[((width - 1) * height) - 1] = 'w';
    for (int i = ((width - 1) * height); i <= (width * height) + 1; i++)
    {
        dungeon[i] = 'w';
    }
    for (int i = 0; i <= (width * height) - 1; i++)
    {
        if (dungeon[i] != 'w')
        {
            int number;
            number = (rand() % 100) + 1;
            if (number <= 20)
            {
                int number2;
                number2 = (rand() % 100) + 1;
                if (number2 >= 0 && number2 <= 15)
                {
                    dungeon[i] = 'E';
                }
                else if (number2 >= 15 && number2 <= 30)
                {
                    dungeon[i] = 'H';
                }
                else if (number2 >= 30 && number2 <= 45)
                {
                    dungeon[i] = 'T';
                }
                else if (number2 >= 45 && number2 <= 60)
                {
                    dungeon[i] = 'F';
                }
                else if (number2 > 60)
                {
                    dungeon[i] = 'w';
                }
            }
        }
    }
    for (int i = 1; i < (width * height); i += width)
    {
        int randomnumber;
        randomnumber = (rand() % 100) + 1;
        if (randomnumber <= 20)
        {
            dungeon[i] = 'P';
            break;
        }
    }
    for (int i = width - 2; i < (width * height); i += width)
    {
        int randomnumber;
        randomnumber = (rand() % 100) + 1;
        if (randomnumber <= 30)
        {
            dungeon[i] = 'X';
            break;
        }
    }
    return dungeon;
}
/*
    *   ADD YOUR CODE HERE AS REQUIRED. DEFINE NEW FUNCTIONS IF IT GETS LONG.
    */

void display(char *dungeon, int width, int height)
{
    for (int i = 0; i <= (width * height) - 1; i++)
    {
        if (i % width == 0)
        {
            cout << "\n";
        }
        cout << dungeon[i];
    }
}

//void randomnumber()
//{
//    int number;
//    number = (rand() % 100) + 1;
//    return number;
//}