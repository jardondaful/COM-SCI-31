#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

const int maxCribLength = 90;
const int maxMessageCount = 70;
const int maxCipherLength = 6371;

//helper function reformats crib so it has no unecessary whitespaces, removes punctuation and numbers, and lowercases all letters
void reformat(char ciphertext[], const char reference[])
{
  int i = 0;
  int j = 0;
  //checks to see if the iterator is on a word in crib. reformat cannot get rid of \n
  bool on_word = false;
  while(reference[i]!= '\0')
  {
    if (isalpha(reference[i]) || reference[i] == '\n')
    {
      if(reference[i]=='\n')
      {
        on_word = false;
      } 
      else 
      {
       on_word = true;
      }
      ciphertext[j] = tolower(reference[i]);
      j++;
    }
    else
    {
      if (on_word)
      {
        on_word = false;
        ciphertext[j] = ' ';
        j++;
      }
    }
    i++;
  }
  if ((strlen(ciphertext) > 1) && (isspace(ciphertext[j - 1]))) 
  {
    ciphertext[j - 1] = '\0';
  }
}

//helper function returns true if two characters are wither both spaces or both letters
bool sameType(char a, char b) 
{
	return (isalpha(a) && isalpha(b)) || (isspace(a) && isspace(b));
}


bool decrypt(const char ciphertext[], const char crib[])
{
  //returns false if crib if crib is longer than the maximum allowed crib length, is empty, or longer than ciphertext
  if(strlen(crib)<1||strlen(crib) > maxCribLength)
  {
    return false;
  }
  char ciphertext_copy[maxCipherLength];
  char reformatted_crib[maxCribLength];
  char crib_copy[maxCribLength];
  char reformatted_ciphertext[maxCipherLength];

  //stores characters of ciphertext
  strcpy(ciphertext_copy, ciphertext);
  
  for (int i = 0; i < maxCribLength; i++) {
    reformatted_crib[i] = '\0';
  }

  for (int i = 0; i < maxCipherLength; i++) {
    reformatted_ciphertext[i] = '\0';
  }
  strcpy(crib_copy, crib);
  int i = 0;
  while (crib_copy[i] != '\0') {
    if (crib_copy[i]=='\n')
    {
      int j = i;
      for(; j < (strlen(crib_copy) - 1); j++)
      {
        crib_copy[j]=crib_copy[j + 1];
      }
      crib_copy[j] = '\0';
    } else {
      i++;
    }
  }
  //reformats crib
  reformat(reformatted_crib, crib_copy);
  for(int i = 0; reformatted_crib[i]!='\0'; i++)
  {
    if(reformatted_crib[i]=='\n')
    {
      reformatted_crib[i] = ' ';
    }
  }
  //reformat ciphertext
  reformat(reformatted_ciphertext, ciphertext);

  if (strlen(reformatted_crib) < 1 || strlen(reformatted_crib) > strlen(ciphertext)) {
    return false;
  }

  //iterator that loops through ciphertext
  int substr_index = 0;
  bool advance = false;
	while(substr_index < strlen(reformatted_ciphertext))
  {
    if (advance) 
    {
      //increases the iterator by 1 if current character of ciphertext is a space
      if (reformatted_ciphertext[substr_index] != ' ') 
      {
        substr_index++;
        continue;
      }
      else
      {
        substr_index++;
        advance = false;
      }
    }
    char cipher_to_crib[26];
    char crib_to_cipher[26];
    //fills up cipher_to_crib and crib_to_cipher with empty character values
    for(int i = 0; i < 26; i++)
    {
      cipher_to_crib[i] = '\0';
      crib_to_cipher[i]= '\0';
    }
    //declare iterator outside of for loop so it can be set equal to substr_index
    int i = substr_index;
    for(; i < substr_index + strlen(crib); i++)
    {
      int cribIndex = i - substr_index;
      if(i > strlen(reformatted_ciphertext) - 1)
      {
        return false;
      }
      else if (reformatted_ciphertext[i] == '\n') {
        
      }
      else if (!sameType(reformatted_crib[cribIndex], reformatted_ciphertext[i]))
      {
        break;
      }
      else if (reformatted_ciphertext[i] == ' ' && reformatted_crib[cribIndex] == ' ')
      {
        continue;
      }
      //else condition code block fills in cipher_to_crib and crib_to_cipher with their corresponding letters
      else
      {
        int current_index_of_crib_letter = reformatted_crib[cribIndex] - 'a';
        int current_index_of_cipher_letter = reformatted_ciphertext[i] - 'a';

        if(crib_to_cipher[current_index_of_cipher_letter] == '\0')
        {
          cipher_to_crib[current_index_of_crib_letter] = reformatted_ciphertext[i];
          crib_to_cipher[current_index_of_cipher_letter] = reformatted_crib[cribIndex];
        }
        else if(cipher_to_crib[current_index_of_crib_letter] != reformatted_ciphertext[i] || crib_to_cipher[current_index_of_cipher_letter] != reformatted_crib[cribIndex])
        {
          break;
        }

      }
      //if condition code block executes code within if either cribIndex reaches the end of crib and one of the other two conditions: either if i reaches the end of reformatted_ciphertext or if the end of reformatted_ciphertext is a space character
      if (cribIndex == strlen(reformatted_crib) - 1 && (i + 1 == strlen(reformatted_ciphertext) || (reformatted_ciphertext[i + 1] == ' '))) 
      {
        for (int j = 0; ciphertext_copy[j] != '\0'; j++) 
        {
          if (!isalpha(ciphertext_copy[j])) 
          {
            continue;
          }
          char cribLetter = crib_to_cipher[tolower(ciphertext_copy[j]) - 'a'];
          if (cribLetter != '\0') 
          {
            ciphertext_copy[j] = toupper(cribLetter);
          } else 
          {
            ciphertext_copy[j] = tolower(ciphertext_copy[j]);
          }
        }
        for (int k = 0; ciphertext_copy[k] != '\0'; k++)
        {
          cout << ciphertext_copy[k];
        }
        return true;
      }

      if (reformatted_ciphertext[i] == '\n') 
      {
        break;
      }
    }
    advance = true;
  }
  return false;
}
  
	void runtest(const char ciphertext[], const char crib[])
	{
	    cout << "====== " << crib << endl;
	    bool result = decrypt(ciphertext, crib);
	    cout << "Return value: " << result << endl;
	}

int main()
{
  cout.setf(ios::boolalpha); // output bools as "true"/"false"
  //hiESS ejsT MY SECRET oS o M foSCREET.
  runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
  assert(decrypt("Hirdd ejsy zu \ndrvtry od.\nO'z fodvtrry.\n", "my secret") == false);
  runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
  runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "   hush???hUSh---     --- until    NovemBER !!  ");
  runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "hush-hush until November 25, 2021");
  runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "hush hush until november");
  runtest("Rswjo qgx Tmeuo sgjsy jds vqgf vo jds vqzf xbby.\nUdbyjo iqcju cg wybgj cg jds esjqiqo zqy\nXbg'j rsj jds jsrrsy jycn jds ucrsgj qrqyt.\nZU 31 cu zdqrrsgecge!",
      "silent alarm");
  runtest("Kpio't dmpbl-boe-ebhhfs opwfm", "s cloak and");

  cout<<"passed smallberg tests"<<endl;
  char text1[maxCipherLength] = "      hello there how are you";
  char reference1[maxCipherLength];
  reformat(reference1, text1);
  assert(strcmp(reference1, "hello there how are you")==0);

  char text2[maxCipherLength] = "hello there                how are you";
  char reference2[maxCipherLength];
  reformat(reference2, text2);
  assert(strcmp(reference2, "hello there how are you")==0);

  char text3[maxCipherLength] = "hello there how are you                    ";
  char reference3[maxCipherLength];
  reformat(reference3, text3);
  assert(strcmp(reference3, "hello there how are you")==0);

  char text4[maxCipherLength] = "!@#!@$@#@!he@@llo there. *&^%$how are you&^%&*?";
  char reference4[maxCipherLength];
  reformat(reference4, text4);
  assert(strcmp(reference4, "he llo there how are you")==0);

  char text5[maxCipherLength] = "HeLlO tHeRe HoW ArE YoU";
  char reference5[maxCipherLength];
  reformat(reference5, text5);
  assert(strcmp(reference5, "hello there how are you")==0);

  assert(sameType(' ', ' ')==true);

  assert(sameType('a', 'a')==true);

  assert(sameType('A', 'A')==true);

  assert(sameType('a', 'A')==true);

  assert(sameType('a', ' ')==false);

  assert(sameType('a','\0')==false);

  assert(decrypt("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret")==true);

  assert(decrypt("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow")==false);

  char c[1];
  c[0] = '\0';
  assert(decrypt("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", c)==false);

  assert(decrypt("Hirdd ejsy zu drvtry od.", "supercalifragilisticexpialidocious")==false);

  assert(decrypt("abcd efg hijk ilm nppq rst dccb cba uwwx wyz", "good one")==true);

  assert(decrypt("Hirdd ejsy zu drvtry od Hirdd ejsy zu drvtry od Hirdd ejsy zu drvtry od Hirdd ejsy zu drvtry od Hirdd ejsy zu drvtry od.", "Hello Alexander how have you been? I just wanted to let you know that the money is located somewhere in UCLA at Rieber Hall on the north side of the fifth floor within the lounge. Good luck on finding it!")==false);

  cout<<endl;
  assert(decrypt("Gsc JfrxP YiDlM UlC qfnkh Levi GSRigvvM ozab Wlth", "    \n73%*&^#%9837QuIcK$%^&8545     ")==true);

  assert(decrypt("Gsc JfrxP YiDlM UlC qfnkh Levi GSRigvvM ozab Wlth", " QuIcK")==true);

  int counter = 0;
  char aa[6371];
  while(counter<6371)
  {
    if(counter % 90 == 0 && counter != 0)
      {
        aa[counter]='\n';
      } 
    else 
      {
        aa[counter] = 'a';
      }
    counter++;
  }
  aa[6370] = '\0';
  assert(decrypt(aa, "a")==false);

  int counter2 = 0;
  char aaa[141];
  while(counter2 < 140)
  {
    if((counter2) % 2 == 0 && counter2 != 0)
    {
      aaa[counter2] = '\n';
    }
    else
    {
      aaa[counter2]='a';
    }
    counter2++;
  }
  aaa[140] = '\0';
  assert(decrypt(aaa, "a")==false); 

  char b[1];
  b[0] = '\0';
  assert(decrypt("Gsc JfrxP YiDlM UlC qfnkh Levi GSRigvvM ozab Wlth", b)==false);

  assert(decrypt("bwra wmwt\nqeirtk spst\n", "alan turing") == false);
  assert(decrypt("bwra wmwt qeirtk spst\n", "alan turing") == true);

  assert(decrypt("$%^&*()*&^%$%^&*(*&^%$%^&)   @!(#^!$($&%!*))         ", "a")==false);
  assert(decrypt("           ", "a")==false);
  assert(decrypt("\n\n\n\n\n\n\n\n", "a")==false);
  cout<<endl<<endl<<"IT WORKS"<<endl<<endl;
	}

