#include "grid.h"
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

bool hasCorrectForm(string plan)
{
  int i = 0;
  //executes code within brackets while counter is less than the length of parameter
  while(i<plan.length())
  {//tests if first character of current plan portion is a valid direction letter
    if(tolower(plan[i])=='l' || tolower(plan[i])=='r')
    {
      i++;
    }
    //tests if second charcter of current plan portion is a valid direction when first charcter of current plan portion is not a valid direction letter
    else if((tolower(plan[i+1])=='l' || tolower(plan[i+1])=='r') && i<plan.length()-1)
    {
      if(isdigit(plan[i]))
      {
        i+=2;
      }
      else
      {
        return false;
      }
    }
    //tests if second charcter of current plan portion is a valid direction when first and second charcter of current plan portion is not a valid direction letter
    else if((tolower(plan[i+2])=='l' || tolower(plan[i+2])=='r') && i<plan.length()-2)
    {
    if(isdigit(plan[i]) && isdigit(plan[i+1]))
      {
        i+=3;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  //if nothing is returned after while loop, then the plan string contains only valid plan portions
  return true;
}

//determines how far north you can travel
int determineSafeDistanceNorth(int r, int c)
{
  int wallPos;
  if (r > getRows() || c > getCols() || r < 1 || c < 1)
  {
    return -1;
  }
  if (isWall(r, c) == true)
  {
    return -1;
  }
  for (int i = r; i > 0; i--)
  {
    if (isWall(i, c) == true)
    {
      return r-i-1;
    }
  }
  return r-1;
}

//determines how far the car can travel to the east
int determineSafeDistanceEast(int r, int c)
{
  int wallPosition;
  if (r > getRows() || c > getCols() || r < 1 || c < 1)
  {
      return -1;
  }
  if (isWall(r, c) == true)
  {
    return -1;
  }
  for (int i = c; i <= getCols(); i++)
  {
    if (isWall(r, i) == true)
    {
      return i-c-1;
    }
  }
  return getCols() - c;
}

//determines how far you can travel to the south
int determineSafeDistanceSouth(int r, int c)
{
    int wallPos;
    if (r > getRows() || c > getCols()|| r < 1 || c < 1)
    {
        return -1;
    }
    if (isWall(r, c) == true){
        return -1;
    }
    
    for (int i = r; i <= getRows(); i++){
        if (isWall(i, c) == true)
        {
          return i - r - 1;
        }
    }
    return getRows() - r;
}

//determines how far you can travel to the west
int determineSafeDistanceWest(int r, int c)
{
  int wallPos;
  if (r > getRows() || c > getCols()|| r < 1 || c < 1)
  {
    return -1;
  }

  if (isWall(r, c) == true)
  {
    return -1;
  }

  for (int i = c; i > 0; i--)
  {
    if (isWall(r, i) == true)
    {
      return c - i - 1;
    }
  }
  return c - 1;
}

//the final function that combines all of the aforementioned functions
int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
  //return -1 if maxSteps is negative, (r, c) is not a valid position on the grid, or dir is not a valid direction letter
  if (maxSteps < 0)
  {
    return -1;
  }

  if (r > getRows() || c > getCols()|| r < 1 || c < 1)
  {
    return -1;
  }

  if (isWall(r, c) == true)
  {
    return -1;
  }
  if (tolower(dir) != 'w' && tolower(dir) != 'n' && tolower(dir) != 's' && tolower(dir) != 'e')
  {
    return -1;
  }
  //calls on helper function depending on dir and returns either steps or maxSteps
  if (tolower(dir) == 'n')
  {
    int steps = determineSafeDistanceNorth(r, c);
    if (steps > maxSteps)
    {
      return maxSteps;
    }
    return steps;
  }
    
  if (tolower(dir)=='e')
  {
    int steps = determineSafeDistanceEast(r, c);
    if (steps > maxSteps)
    {
      return maxSteps;
    }
    return steps;
  }
    
  if (tolower(dir) == 's')
  {
    int steps = determineSafeDistanceSouth(r, c);
    if (steps > maxSteps)
    {
      return maxSteps;
    }
    return steps;
  }

  if (tolower(dir) == 'w')
  {
    int steps = determineSafeDistanceWest(r, c);
    if (steps > maxSteps)
    {
      return maxSteps;
    }
    return steps;
  }
    //if none of the above scenarios apply, it can be assumed that the given input is invalid
  return -1;
}


int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{
  string directions = "NESW";
  int directionInteger = 0;
  for (int a = 0; a < directions.size(); a++)
  {
    if (directions.at(a) == dir)
    {
      directionInteger = a;
    }
  }
  //return 2 if (sr,sc) or (er,ec) are not valid empty grid positions or if dir is not a direction letter or if the plan string is not a plan
  if (sr > getRows() || sc > getCols() || er > getRows() || ec > getCols() || sr < 1 || sc < 1 || er <1 || ec< 1|| !hasCorrectForm(plan)|| isWall(sr, sc)|| isWall(er, ec))
  {

    return 2;
  }
  else if (tolower(dir) != 'n' && tolower(dir) != 'e' && tolower(dir) != 's' && tolower(dir) != 'w')
  {
    return 2;
  }
  else
  {
    nsteps = 0;
    //change dir depending on current character of plan string if current character is a valid direction letter
    for (int i = 0; i < plan.size(); i++)
    {
      if (tolower(plan.at(i)) == 'l') 
      {
          if(tolower(dir)=='n')
          {
            dir = 'w';
          }

          else if(tolower(dir)=='e')
          {
            dir = 'n';
          }
 
          else if(tolower(dir)=='s')
          {
            dir = 'e';
          }
          else
          {
            dir = 's';
          }
        }

      else if (tolower(plan.at(i)) == 'r') 
      {
        if(tolower(dir)=='n')
        {
          dir = 'e';
        }
        else if(tolower(dir)=='e')
        {
          dir = 's';
        }
        else if(tolower(dir)=='s')
        {
        dir = 'w';
        }
        else
        {
          dir = 'n';
        }
      }

      else
      {
        //calculating how (sr, sc) will be affected by current plan character
        int maxsteps = 0;
        if (isdigit(plan.at(i + 1)))
        {
          maxsteps = plan.at(i) - '0';
          maxsteps = maxsteps * 10 + (plan.at(i + 1) - '0');
          i++;
        }
        else
        {
          maxsteps = plan.at(i) - '0';
        }
        int steps = determineSafeDistance(sr, sc, dir, maxsteps);
        if (steps != maxsteps)
        {
          nsteps += steps;
          return 3;
        }     
        else
        {
          nsteps += steps;
          if (tolower(dir) == 'n')
          {
            sr -= steps;
          }
          else if (tolower(dir) == 'e')
          {
            sc += steps;
          }
          else if (tolower(dir) == 's')
          {
            sr += steps;
          }
          else
          {
            sc -= steps;
          }
        }
      }
    }
  }
  //return 0 if car ends up at desired destination but 1 if otherwise
  if (sr == er && sc == ec)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int main()
{
  int steps;
  setSize(3,4);
  setWall(3,2);
  setWall(1,4);
  setWall(2,2);
	assert(hasCorrectForm("5rL00L0R09R7L") == true);
  assert(hasCorrectForm("RRRRRRRRRRRRR00l00r0L0R9RLLLLLL29l75r") == true);
  assert(hasCorrectForm("42l") == true);
  assert(hasCorrectForm("R") == true);
  assert(hasCorrectForm("3r") == true);
  assert(hasCorrectForm("L2") == false);
  assert(hasCorrectForm("w2+n3") == false);
  assert(hasCorrectForm("2R1N") == false);
  assert(hasCorrectForm("") == true);
  assert(determineSafeDistance(5, 5, 's', 1) == -1);
  assert(determineSafeDistance(1, 1, 3, 2) == -1);
  assert(determineSafeDistance(2, 1, 'R', -1) == -1);
  assert(determineSafeDistance(1, 1, 'e', 2) == 2);
  assert(determineSafeDistance(2, 3, 'w', 1) == 0);
  assert(determineSafeDistance(1, 3, 'w', 2)==2);
  assert(determineSafeDistance(2, 1, 'n', 1)==1);
  assert(determineSafeDistance(1, 1, 'e', 3)==2);
  steps = -999;
  assert(obeyPlan(1, 1, 1, 2, 'e', "1R", steps) == 0 && steps==1);
  assert(obeyPlan(1, 1, 1, 3, 'e', "1R", steps) == 1 && steps==1);
  assert(obeyPlan(1, 1, 1, 2, 'n', "1R1R1", steps)==2);
  assert(obeyPlan(5, 5, 1, 2, 's',"1R", steps) == 2);
  assert(obeyPlan(1, 1, 4, 5, 'n', "1R", steps) ==2);
  assert(obeyPlan(1, 1, 4, 5, 'x', "123R", steps) == 2);
  assert(obeyPlan(3, 1, 3, 4, 's', "LL2R3r", steps) == 3 && steps == 4);
}
