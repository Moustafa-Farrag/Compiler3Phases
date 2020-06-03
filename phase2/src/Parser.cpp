#include "../include/Parser.h"
#include <bits/stdc++.h>


using namespace std;

Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}

void Parser::readGrammer(string path)
{
   std::ifstream infile(path);
   std::string line;

   vector<string> allForT ; 
   string Tname ;  
   while (getline(infile, line))
   {
      int i = 0;
      while (line[i] == ' ')
         i++;
      if (line[i] == '#')
      {
         if (Tname != "" ) 
            nonTerminal[Tname] = allForT ; 
            //cout << Tname << "fffff0" << endl ; 
         int index = 0;
         Tname = "";
         allForT.clear(); 
         for (++i; i < line.size(); i++)
         {
            if (line[i] == ' ')
            {
               continue;
            }
            if (line[i] == '=')
            {
               index = i;
               break;
            }
            Tname = Tname + line[i];
         }

        string s = line.substr(index + 1, line.size() - index + 1);
        // s = vectorToString(stringToVector(s));
        string ss = "" ;
        i = 0 ; 
        while (i < s.size() && s[i] == ' ')
         i++;
        
         while ( i < s.size() ) {
            if (s[i] == '|') {
               if (ss != "" ) {
                  allForT.push_back(ss) ;
                  ss= "" ;
               }
               i++ ;  
               while (i < s.size() &&  s[i] == ' ')
                i++;
               continue ;
            }

            ss += s[i] ;
            i++ ;              
        }
        if (ss != "") {
           allForT.push_back(ss) ; 
        } 
      }
      else if (line[i] == '|')
      {

        string s = line ; 
        string ss = "" ;
        i = 1 ; 
        while (s[i] == ' ')
         i++; 
        //vector<string> allForT ;  
        for ( i ; i < s.size() ; i++ ) {
            
            if (s[i] == '|') {
               if (ss != "" ) {
                  allForT.push_back(ss) ;
                  ss= "" ;
               }
               continue ;
            }

            ss += s[i] ;             
        }
        if (ss != "") {
           allForT.push_back(ss) ; 
        }
      }
      else
      {
         cout << "eeeee In file" << endl ; 
      }
      if ( Tname != "" ) 
   {
      nonTerminal[Tname] = allForT ;
      nTerOrder.push_back(Tname);
   }
   }

   
     
}

vector<string> Parser::stringToVector(string s)
{
   std::stringstream ss(s);
   std::istream_iterator<std::string> begin(ss);
   std::istream_iterator<std::string> end;
   std::vector<std::string> vstrings(begin, end);
   //std::copy(vstrings.begin(), vstrings.end());
   return vstrings;
}

string Parser::vectorToString(vector<string> vec)
{
   std::ostringstream vts;
   if (!vec.empty())
   {
      std::copy(vec.begin(), vec.end(),
      std::ostream_iterator<string>(vts, " "));
   }
   return vts.str();
}

void Parser::immediateLeftRecursion(string a, vector<string> ex)
{
   std::vector<std::string> aString;
   std::vector<std::string> bString;
   string a_ = a;
   a_.push_back('\'');
   for (string s : ex)
   {
      std::vector<std::string> temp = stringToVector(s);
      string sbegin = *temp.begin();
      if (a == sbegin)
      {
         temp.erase(temp.begin());
         temp.push_back(a_);
         string tempString = vectorToString(temp);
         bString.push_back(tempString);
      }
      else
      {
         temp.push_back(a_);
         string tempString = vectorToString(temp);
         aString.push_back(tempString);
      }
   }
   if (!bString.empty())
   {
      string e = "eeee";
      bString.push_back(e);
      nonTerminal[a] = aString;
      nonTerminal[a_] = bString;
      nTerOrder.push_back(a_);
   }
}

void Parser::replaceAwithB(string a, string b)
{
   std::vector<std::string> aString = nonTerminal[a];
   std::vector<std::string> bString = nonTerminal[b];
   std::vector<std::string> pre;
   std::vector<std::string> result;
   for (string s : aString)
   {

      std::vector<std::string> temp = stringToVector(s);
      string sbegin = *temp.begin();
      if (sbegin == b)
      {
         temp.erase(temp.begin());
         string tempString = vectorToString(temp);
         pre.push_back(tempString);
      }
      else
      {
         result.push_back(s);
      }
   }
   for (string s : pre)
   {
      for (string sb : bString)
      {
         std::vector<std::string> temp = stringToVector(sb);
         temp.push_back(s);
         string tempString = vectorToString(temp);
         result.push_back(tempString);
      }
   }
   if (!pre.empty())
   {
      nonTerminal[a] = result;
   }
}

void Parser::leftRecursion()
{
   std::vector<string> fin;
   for (auto a : nTerOrder)
   {
      for (string s : fin)
      {
         replaceAwithB(a, s);
      }
      immediateLeftRecursion(a, nonTerminal[a]);
      fin.push_back(a);
   }
}

void Parser::leftFactoring()
{
   for (auto a : nonTerminal)
   {

      vector<string> v = a.second;

      sort(v.begin(), v.end());

      vector<string> newVector;

      int times = 0;
      for (int i = 0; i < v.size(); i++)
      {

         int j = i + 1;

         vector<string> s = stringToVector(v[i]);

         while (j < v.size())
         {

            vector<string> spliting = stringToVector(v[j]);
            if (spliting[0] == s[0])
            {

               j++;
            }
            else
            {
               break;
            }
         }

         if (j == i + 1)
         {
            newVector.push_back(v[i]);

            continue;
         }

         int counter = 1;
         int indexOfebslon = -1;
         string newOne = s[0] + " ";

         while (true)
         {
            int start;
            for (start = i + 1; start < j; start++)
            {
               if (counter < s.size())
               {
                  vector<string> ss = stringToVector(v[start]);
                  if (counter >= ss.size()) // will make problem
                     break;
                  if (s[counter] != ss[counter])
                     break;

                  /*cout << s[counter] << " "  << i <<  " "  << start  <<  " " << ss[counter] << endl ;
                  cout << v[i] << endl ; 
                  cout << v[start] << endl ;  */
               }
               else
               {
                  break;
               }
            }
            if (start == j)
            {
               newOne += s[counter] + " ";
               counter++;
            }
            break;
         }

         string newNonTerminal = a.first + to_string(times);

         newOne += newNonTerminal;

         newVector.push_back(newOne);

         vector<string> nonTerVec;

         for (int start = i; start < j; start++)
         {
            vector<string> ss = stringToVector(v[start]);
            string f = "eeee";
            if (counter == ss.size())
            {
               nonTerVec.push_back(f); // eeeeee
               continue;
            }
            f = ss[counter];
            for (int k = counter + 1; k < ss.size(); k++)
            {
               f += " " + ss[k];
               // cout << "fffffffffffffff" << endl ;
            }
            nonTerVec.push_back(f);
            //cout << newNonTerminal << " " << f << endl  ;
         }

         nonTerminal[newNonTerminal] = nonTerVec;
         //  cout << i << " " << j -1  << " "  << counter - 1   << endl ;
         //cout << newOne << endl ;

         i = j - 1;
         times++;
      }

      nonTerminal[a.first] = newVector;
   }
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

unordered_map<string , set<string>> Parser::print()
{
  unordered_map <string , set<string>> newMap ; 
  
  for (auto a : nonTerminal){
     set <string> newSet ; 
      for (auto b : a.second){
         newSet.insert(rtrim(b)) ;
         cout << a.first << " -> " << b << endl;
      }
      newMap[a.first] = newSet ;
     // cout  << "----------------------------" << endl ; 
   }
   cout  << "----------------------------" << endl ; 
   
   newMap.erase(""); 

   for (auto a : newMap){
      cout << ":" << endl ; 
      for (auto b : a.second){
         cout << a.first << " " << b << endl;
      } 
   }

    cout  << "----------------------------" << endl ; 


   return newMap ; 
}
