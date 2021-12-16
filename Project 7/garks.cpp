// garks.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Mesa::display going.  That gives
// you more flexibility in the or der you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the mesa
const int MAXCOLS = 25;             // max number of columns in the mesa
const int MAXGARKS = 150;           // max number of garks allowed
const int INITIAL_GARK_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Mesa;  // This is needed to let the compiler know that Mesa is a
             // type name, since it's mentioned in the Gark declaration.

class Gark
{
  public:
        // Constructor
    Gark(Mesa* mp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool getAttacked(int dir);

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_hits_taken; //TODO completed: added int data member m_hits_taken keeps track of humber of hits taken
};

class Player
{
  public:
     // Constructor
    Player(Mesa *mp, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

    // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();

  private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Mesa
{
  public:
     // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

    // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark*   m_garks[MAXGARKS];
    int     m_nGarks;
};

class Game
{
  public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Gark implementation
///////////////////////////////////////////////////////////////////////////

Gark::Gark(Mesa* mp, int r, int c)
{
    if (mp == nullptr)
    {
        cout << "***** A gark must be created in some Mesa!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > mp->rows()  ||  c < 1  ||  c > mp->cols())
    {
        cout << "***** Gark created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_mesa = mp;
    m_row = r;
    m_col = c;
    m_hits_taken = 0;
}

int Gark::row() const
{
    return m_row;
}

int Gark::col() const 
{
    return m_col;  // TODO completed: made Gark::col() return private data member m_col
}

void Gark::move()
{
      // Attempt to move in a random direction; if it can't move, don't move
  int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
  switch(dir)//TODO completed: called on determineNewPosition() function to attempt to move in direction dir
  {
    case UP:
      if(m_row>1)
      {
        m_row--;
      }
      break;
    
    case DOWN:
      if(m_row < m_mesa->rows())
      {
        m_row++;
      }
      break;

    case LEFT:
      if(m_col > 1)
      {
        m_col--;
      }
      break;

    case RIGHT:
      if(m_col < m_mesa->cols())
      {
        m_col++;
      }
      break;

    default:
      break;
  }
}

bool Gark::getAttacked(int dir)  // TODO completed: return true if either you were attacked or if you fell off the grid. Otherwise, move the gark one step in direction dir
{
  if (m_hits_taken == 1) 
  {
    return true;
  }
   
  switch (dir)
  {
    case UP:
      if (m_row > 1)
      {
        m_row--;
        m_hits_taken++;
        return false;
      }
      break;

    case DOWN:
      if (m_row < m_mesa->rows()) 
      {
        m_col++;
        m_hits_taken++;
        return false;
      }
      break;

    case LEFT:
      if (m_col > 1) 
      {
        m_col--;
        m_hits_taken++;
        return false;
      }
      break;

    case RIGHT:
      if (m_col < m_mesa->cols()) 
      {
        m_col++;
        m_hits_taken++;
        return false;
      }
      break;

    default:
      return false; 
  }
  return true; 
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Mesa* mp, int r, int c)
{
    if (mp == nullptr)
    {
        cout << "***** The player must be created in some Mesa!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > mp->rows()  ||  c < 1  ||  c > mp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_mesa = mp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
  return m_row;  //TODO completed: makes row() funciton of player class return the private data member m_row (which is the row number the player is on)
}

int Player::col() const
{
  return m_col;  //TODO completed: makes col() funciton of player class return the private data member m_col (which is column number the player is on)
}

int Player::age() const
{
  return m_age;  //TODO completed: makes age() function of player class return the private data memnber m_age (which is the age of the player)
}

void Player::stand()
{
  m_age++;
}

void Player::moveOrAttack(int dir)
{
  m_age++;
  //TODO completed moveOrAttack() funciton of Player classes calls on attackGarkAt() to attack the gark if it is adjacent to the player.  Otherwise, the function calls on determineNewPositon() to move the player to that position.
  int adjacent_row = m_row;
  int adjacent_column = m_col;
  m_mesa -> determineNewPosition(adjacent_row, adjacent_column, dir);
  if(m_mesa -> numGarksAt(adjacent_row, adjacent_column) > 0)
  {
    m_mesa -> attackGarkAt(adjacent_row, adjacent_column, dir);
    return;
  }
  m_mesa -> determineNewPosition(m_row, m_col, dir);
}

bool Player::isDead() const
{
  return m_dead;  // TODO completed: makes isDead() function of the Player class return private data member m_dead (which determines whether or not the player is dead)
}

void Player::setDead()
{
  m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Mesa implementations
///////////////////////////////////////////////////////////////////////////

Mesa::Mesa(int nRows, int nCols)
{
  if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
  {
    cout << "***** Mesa created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
    exit(1);
  }
  m_rows = nRows;
  m_cols = nCols;
  m_player = nullptr;
  m_nGarks = 0;
}

Mesa::~Mesa()
{
  //TODO completed: deleted value of private data member m_player and deleted elements in m_garks with a for-loop.
  delete m_player;
  m_player = nullptr;
  for(int i = 0; i < m_nGarks; i++)
  {
    delete m_garks[i];
    m_garks[i] = nullptr;
  }
  m_nGarks = 0;
}

int Mesa::rows() const
{
  return m_rows;  //TODO completed: made rows() funciton of Mesa class return private data member m_rows
}

int Mesa::cols() const
{
  return m_cols;  //TODO completed: made cols() function of Mesa class return private data member m_cols
}

Player* Mesa::player() const
{
  return m_player; 
}

int Mesa::garkCount() const
{
  return m_nGarks;
}

int Mesa::numGarksAt(int r, int c) const
{
  //TODO completed: increments garks every time the row and column values associated with m_garks[i] matches r and c
  int garks = 0;
  for(int i = 0; i < m_nGarks; i++)
  {
    if(m_garks[i]-> row() == r && m_garks[i]->col() == c)
    {
      garks++;
    }
  }
  return garks; 
}

bool Mesa::determineNewPosition(int& r, int& c, int dir) const
{
    //TODO completed:  returned false if next move taken will go off bounds.
  if(r==1 && dir == UP)
  {
    return false;
  }
  if(r == rows() && dir == DOWN)
  {
    return false;
  }
  if(c == 1 && dir == LEFT)
  {
    return false;
  }
  if(c == cols() && dir == RIGHT)
  {
    return false;
  }
  switch (dir)
  {
    //TODO done:  subtracted row coordinate by 1 if dir is 'UP'
    case UP:
      r--;
      break;
    case DOWN:
      r++;
      break;
    case LEFT:
      c--;
      break;
    case RIGHT:
      c++;
    // TODO DONE: incremented row cooridnate by 1 if dir is 'DOWN', decremented column coordinate by 1 if dir is 'LEFT', and incremented column coordinate by 1 if dir is 'RIGHT'
      break;
    default:
      return false;
  }
  return true;
}

void Mesa::display() const
{
  // Position (row,col) in the mesa coordinate system is represented in
  // the array element grid[row-1][col-1]
  char grid[MAXROWS][MAXCOLS];
  int r, c;
    
  // Fill the grid with dots
  for (r = 0; r < rows(); r++)
    for (c = 0; c < cols(); c++)
      grid[r][c] = '.';

  // Indicate each gark's position
  //TODO edited: each element of grid is iterated through by a  for-loop. If there is only one gark at that position, the grid position at that coordinate will be filled with a 'G'. Otherwise, if there is two to eight garks at that position, the grid position at that coordinate will be filled with the number of garks that are there. Otherwise, the grid position at that coordinate will be filled the number 9.
  for(int i = 0; i < m_nGarks; i++)
  {
    char &gridChar = grid[m_garks[i]->row()-1][m_garks[i]->col()-1];
    if(gridChar=='.')
    {
      gridChar = 'G';
    }
    else if(gridChar =='G')
    {
      gridChar = '2';
    }
    else if(gridChar=='9')
    {

    }
    else 
    {
      gridChar++;
    }
  }
        // Indicate player's position
  if (m_player != nullptr)
  {
    // Set the char to '@', unless there's also a gark there,
    // in which case set it to '*'.
    char& gridChar = grid[m_player->row()-1][m_player->col()-1];
    if (gridChar == '.')
      gridChar = '@';
    else
      gridChar = '*';
  }

  // Draw the grid
  clearScreen();
  for (r = 0; r < rows(); r++)
  {
    for (c = 0; c < cols(); c++)
      cout << grid[r][c];
    cout << endl;
  }
  cout << endl;

  // Write message, gark, and player info
  cout << endl;
  cout << "There are " << garkCount() << " garks remaining." << endl;
  if (m_player == nullptr)
    cout << "There is no player." << endl;
  else
  {
    if (m_player->age() > 0)
      cout << "The player has lasted " << m_player->age() << " steps." << endl;
    if (m_player->isDead())
      cout << "The player is dead." << endl;
  }
}

bool Mesa::addGark(int r, int c)
{

  // TODO completed: create new gark at row coordinate 'r' and column coordinate 'c' and increment private data member m_nGarks by 1 if m_nGarks did not exceed the maximum gark count
  if(m_nGarks>=MAXGARKS)
  {
    return false;  
  }
  m_garks[m_nGarks] = new Gark(this, r, c);
  m_nGarks++;
  return true;
}

bool Mesa::addPlayer(int r, int c)
{
  // Don't add a player if one already exists
  if (m_player != nullptr)
    return false;

  // Dynamically allocate a new Player and add it to the mesa
  m_player = new Player(this, r, c);
  return true;
}

bool Mesa::attackGarkAt(int r, int c, int dir)
{
    // TODO completed: Attacks one gark at row r, column c if there is at least one gark in that position.  If the gark does not survive the attack, the gark object is deleted, removed it from the mesa, and the function returns true.  Otherwise, the function returns false 
    for(int i = 0; i < m_nGarks; i++)
    {
      Gark* &g = m_garks[i];
      if(g->row() == r && g->col() == c)
      {
        if(g->getAttacked(dir))
        {
          delete g;
          m_nGarks--;
          g = m_garks[m_nGarks];
          return true;
        }
        return false;
      }
    }
  return false;  
}

bool Mesa::moveGarks()
{
  for (int k = 0; k < m_nGarks; k++)
  {
    //TODO completed: The k-th gark on the mesa make one move and if that move results in that gark being in the same position as the player, m_player is set to be dead from setDead() function.
    m_garks[k]->move();
    if(m_player->row()==m_garks[k]->row() && m_player->col()==m_garks[k]->col())
    {
      m_player->setDead();
    }
  }
  // returns true if the player is still alive but false if otherwise
  return !m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nGarks)
{
    if (nGarks < 0)
    {
        cout << "***** Cannot create Game with negative number of garks!" << endl;
        exit(1);
    }
    if (nGarks > MAXGARKS)
    {
        cout << "***** Trying to create Game with " << nGarks
             << " garks; only " << MAXGARKS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nGarks > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the garks!" << endl;
        exit(1);
    }

        // Create mesa
    m_mesa = new Mesa(rows, cols);

        // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_mesa->addPlayer(rPlayer, cPlayer);

      // Populate with garks
    while (nGarks > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
          // Don't put a gark where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_mesa->addGark(r, c);
        nGarks--;
    }
}

Game::~Game()
{
    delete m_mesa;
}

void Game::play()
{
    m_mesa->display();
    Player* player = m_mesa->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_mesa->garkCount() > 0)
    {
        cout << endl;
        cout << "Move (u/d/l/r/q or nothing): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player stands
            player->stand();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                player->moveOrAttack(decodeDirection(action[0]));
                break;
            }
        }
        m_mesa->moveGarks();
        m_mesa->display();
    }
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

  // Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
