#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int reduplicate(string a[], int n)
{
  if (n < 0)
  {
    return -1;
  }
  //loops through given array and concatenates a copy of itself to itself for every element
  for (int i = 0; i < n; i++)
  {
    string temp = a[i];
    a[i] += temp;
  }
  return n;
}

int locate(const string a[], int n, string target)
{
  if (n < 0)
  {
    return -1;
  }
  //loops through each element of given array and returns the current value of the iterator i if it is equal to the given target string
  for (int i = 0; i < n; i++)
  {
    if (a[i] == target)
    {
      return i;
    }
  }
  return -1;
}

int locationOfMax(const string a[], int n)
{
  if (n < 1)
  {
    return -1;
  }
  string max;
  int maxIndex = 0;
  //loops through each element of the given array and relabels the index of the array's element that has the highest value as the current index of the iterator and the element itself as the highest value element if the element has a greater value than the previously highest marked element       
  for (int i = 0; i < n; i++)
  {
    if (a[i] > max)
    {
      maxIndex = i;
      max = a[i];
    }
  }
  return maxIndex;
}
//n=0?
int circleLeft(string a[], int n, int pos)
{
  if (pos >= n || pos < 0 || n <= 0)
  {
    return -1;
  }
  string moving_string = a[pos];
  //loops through array starting at second element and ending at the second to last element of the given array. For each iteration, it swaps the current element of the array that the iterator is on with the element in front of itself               
  for (int i = pos; i < n - 1; i++)
  {
    a[i] = a[i + 1];
  }
  a[n - 1] = moving_string;
  return pos;
}

int enumerateRuns(const string a[], int n)
{
  if (n < 0)
  {
    return -1;
  }
  else if (n == 0)
  {
    return 0;
  }
  int count = 1;
  string repeat = a[0];
  //loops through array starting at second element and ending at the last element of the given array. For each iteration, if the element of the array the iterator is on is not equal to the first element of the array, it increments count by 1 and sets repeat to that element              
  for (int i = 1; i < n; i++)
  {
    if (repeat != a[i])
    {
      count++;
      repeat = a[i];
    }
  }
  return count;
}

int flip(string a[], int n)
{
  if (n < 0)
  {
    return -1;
  }
  string temp;
  //loops through array and ends when iterator reaches half of the array's length. For each iteration, the current element of the array is swapped with the (n-i-1)th element of the array                    
  for (int i = 0; i < n / 2; i++)
  {
    temp = a[i];
    a[i] = a[n - i - 1];
    a[n - i - 1] = temp;
  }
  return n;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
  if (n1 < 0 || n2 < 0)
  {
    return -1;
  }
  int reps;
  if (n1 <= n2)
  {
    reps = n1;
  }
  else
  {
    reps = n2;
  }
  //loops through array reps times. The function returns the current iterator's value if that index's element of a1 if it is not equal to that of a2
  for (int i = 0; i < reps; i++)
  {
    if (a1[i] != a2[i])
    {
      return i;
    }
  }
  return reps;
}
//*
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
  if (n1 < 0 || n2 < 0 || n1 < n2)
  {
    return -1;
  }
  if (n2 == 0 || (n1 == 0 && n2 == 0))
  {
    return 0;
  }
  int matches = 0;
  //loops through each element of a1                     
  for (int i = 0; i < n1; i++)
  {
    //loops through each element of a2 and increments matches by 1 if the current element of a2 the loop is on is equal to the current element of a1 the above for loop is on. If the number of matching elements is equal to n2, then the fucntion returns (current value of the iterator) +1 - (number of matcheing elements)           
    for (int y = 0; y < n2; y++)
    {
      if (a1[i] == a2[y])
      {
        matches++;
        if (matches == n2)
        {
          return i + 1 - matches;
        }
        i++;
      }
      else
      {
        matches = 0;
      }
    }
  }
  return -1;
}

int locateAny(const string a1[], int n1, const string a2[], int n2)
{
  if (n2 < 0 || n1 < 0)
  {
    return -1;
  }
  //loops through each elment of a1 and returns the current value of the iterator if the a string in a2 matches the element of a1 the loop is currently on 
  for (int i = 0; i < n1; i++)
  {
    if (locate(a2, n2, a1[i]) != -1)
    {
      return i;
    }
  }
  return -1;
}

int separate(string a[], int n, string separator)
{
  if (n < 0)
  {
    return -1;
  }
  int index = 0;
  //loops through a backwards and calls on circleLeft if the element of a the iterator is currently on has a greater value than separator          
  for (int i = n - 1; i >= 0; i--)
  {
    if (a[i] >= separator)
    {
      circleLeft(a, n, i);
    }
    else
    {
      index++;
    }
  }       
  for (int i = 0; i < n; i++)
  {
    if (a[i] == separator)
    {
      string temp = a[i];
      a[i] = a[index];
      a[index] = temp;
      index++;
    }
  }
  //loops through a and returns current value of iterator if it has a greater value than separator
  for (int i = 0; i < n; i++)
  {
    if (a[i] >= separator)
    {
      return i;
    }
    }
  return n;
}

int main()
{
  //test cases at end of spec
    string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
    assert(locate(h, 7, "belle") == 5);
    assert(locate(h, 7, "ariel") == 2);
    assert(locate(h, 2, "ariel") == -1);
    assert(locationOfMax(h, 7) == 3);

    string g[4] = { "moana", "mulan", "belle", "raya" };
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");

    string c[4] = { "ma", "can", "tu", "do" };
    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

    string e[4] = { "ariel", "tiana", "", "belle" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
    assert(enumerateRuns(d, 5) == 2);

    string f[3] = { "tiana", "ariel", "raya" };
    assert(locateAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana");

    assert(separate(h, 7, "elsa") == 3);

    cout << "All tests succeeded" << endl;



//test cases from functions in spec
    string stuff[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
    assert(reduplicate(stuff, 6)==6);

    string cast[6] = { "elsa", "ariel", "mulan", "tiana", "belle", "moana" };
    assert(locationOfMax(cast, 6)==3);

    string folks[5] = { "moana", "elsa", "ariel", "raya", "mulan" };
    assert(circleLeft(folks, 5, 1)==1);

    string ddd[9] = {"belle", "merida", "raya", "raya", "tiana", "tiana", "tiana", "raya", "raya"};
    assert(enumerateRuns(ddd, 9)==5);

    string roles[6] = { "merida", "raya", "", "belle", "moana", "elsa" };
    string group[5] = { "merida", "raya", "elsa", "", "belle" };
    assert(locateDifference(roles, 2, group, 1)==1);
    assert(locateDifference(roles, 6, group, 5)==2);

    string names[10] = { "moana", "mulan", "raya", "tiana", "merida" };
    string names1[10] = { "mulan", "raya", "tiana" };
    assert(subsequence(names, 5, names1, 3)==1);
    string names2[10] = { "moana", "tiana" };
    assert(subsequence(names, 4, names2, 2)==-1);

    string set1[10] = { "elsa", "merida", "tiana", "mulan" };
    assert(locateAny(names, 6, set1, 4)==1);  
    string set2[10] = { "belle", "ariel" };
    assert(locateAny(names, 6, set2, 2)==-1);  

    string cast2[4] = { "mulan", "tiana", "ariel", "raya" };
    assert(separate(cast, 6, "merida")==3);
    assert(separate(cast2, 4, "raya")==2);

    cout<<"spec cases in middle passed"<<endl;

//my own test cases
    string aa[3] = { "apple", "banana", "orange" };
    string aa0[3] = { "apple", "banana", "orange" };
    string aa00[3] = { "apple", "banana", "orange" };
    string aa000[3] = { "apple", "banana", "orange" };
    string aa1[3] = { "apple", "banana", "orange" };
    string aa2[3] = { "apple", "banana", "orange" };
    string bb[4] = { "apple", "orange", "banana", "kiwi" };
    string cc[3] = { "apple", "banana", "banana" };
    string dd[5] = { "apple", "banana", "banana", "orange", "orange" };
    string ee[1] = {""};
    string ff[1] = { "apple" };
    string gg[5] = { "apple", "banana", "orange", "kiwi", "grape" };
    string hh[4] = { "apple", "banana", "orange", "kiwi" };
    string ii[4] = { "apple", "", "banana", "kiwi" };
    string jj[5] = { "apple", "banana", "banana", "banana", "orange" };
    string hhh[2] = { "apple", "banana" };
    string kk[2] = { "kiwi", "apple" };
    string ll[3] = { "kiwi", "apple", "tangerine" };
    string mm[3] = { "orange", "kiwi", "grape" };
    string nn[3] = { "kiwi", "tangerine", "grape" };
    string oo[2] = { "banana", "orange" };
    string pp[3] = { "kiwi", "apple", "apple" };


    assert(reduplicate(aa, -3) == -1);
     assert(reduplicate(bb, 4)==4 && 
      bb[0]=="appleapple" && bb[1]=="orangeorange" && bb[2]=="bananabanana" && bb[3]=="kiwikiwi");
    assert(reduplicate(ii, 4) == 4 && ii[0]=="appleapple" && ii[1]==""&&ii[2]=="bananabanana" && ii[3] == "kiwikiwi");

    assert(locate(aa, 4, "kiwi") == -1);
    assert(locate(aa, 3, "banana") == 1);


    assert(locationOfMax(cc, 3) == 1);
    assert(locationOfMax(ee, 0) == -1);
    assert(locationOfMax(ff, -3) == -1);

    assert(circleLeft(aa, 3, 1)==1 && aa[0]=="apple" && aa[1]=="orange" && aa[2] == "banana"); 
    assert(circleLeft(aa, -1, 1) == -1);
    assert(circleLeft(aa, 3, 4) == -1);

    assert(enumerateRuns(jj, 5) == 3);
    assert(enumerateRuns(dd, 5) == 3);
    assert(enumerateRuns(ee, 0) == 0);
    assert(enumerateRuns(ff, -2) == -1);

    assert(flip(aa, -3) == -1);
    assert(flip(aa0, 3)==3 && aa0[0]=="orange" && aa0[1]=="banana" && aa0[2]=="apple");

    assert(locateDifference(aa, -1, hh, -2) == -1);
    assert(locateDifference(aa000, 3, mm, 3) == 0);
    assert(locateDifference(aa000, 3, nn, 3) == 0);

    assert(subsequence(aa00, -4, ll, -3) == -1);
    assert(subsequence(ff, 1, hhh, 2) == -1);
    assert(subsequence(aa00, 3, oo, 2) == 1);

    assert(locateAny(aa000, -4, ll, -3) == -1);
    assert(locateAny(kk, 2, aa000, 3) == 1);
    assert(locateAny(ll, 3, aa000, 3)==1);
    assert(locateAny(pp, 3, aa000, 3) == 1);

    assert(separate(h, -1, "orange") == -1);
    assert(separate(gg, 5, "grape") == 2 && gg[0] == "apple" && gg[1] == "banana" && gg[2] == "grape" && gg[3] == "kiwi" && gg[4] == "orange");
    assert(separate(aa1, 3, "aa") == 0 && aa1[0] == "orange" && aa1[1] == "banana" && aa1[2] == "apple");
    assert(separate(aa2, 3, "zebra") == 3 && aa2[0]=="apple" && aa2[1]=="banana" && aa2[2]=="orange");

    cout << "Your own test cases succeeded";
}
