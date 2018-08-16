// Javier Gomez Serrano

// Randomized solution for genetics
// At each step, does any simplification (if possible) or
// if there isn't any, cuts and pastes randomly

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

string transform(string& s, int & arms, int& legs){
       // Rule 1
       for (int i=0;i<s.size()-1;i++){
           if (s[i] == s[i+1]+'A'-'a' or s[i] == s[i+1]+'a'-'A'){
              string t1 = s.substr(0,i);
              string t2 = s.substr(i+2,s.size()-i-2);
              return t1 + t2;
           }
       }
       if (s[0] == s[s.size()-1] + 'A' - 'a' or s[0] == s[s.size()-1]+'a'-'A'){
          string t1 = s.substr(1,s.size()-2);
          return t1;
       }
       // Rule 2
       for (int i=0;i<s.size()-1;i++){
           if (s[i] == s[i+1]){
              string t1 = s.substr(0,i);
              string t2 = s.substr(i+2,s.size()-i-2);
              arms++;
              return t1 + t2;
           }
       }
       if (s[0] == s[s.size()-1]){
          string t1 = s.substr(1,s.size()-2);
          arms++;
          return t1;
       }
       // Rule 3
       for (int i=0;i<s.size()-3;i++){
           if (s[i] == s[i+2]+'A'-'a' or s[i] == s[i+2]+'a'-'A'){
              if (s[i+1] == s[i+3]+'A'-'a' or s[i+1] == s[i+3]+'a'-'A'){
                 string t1 = s.substr(0,i);
                 string t2 = s.substr(i+4,s.size()-i-4);
                 legs++;
                 return t1 + t2;
              }
           }
       }
       if (s[s.size()-3] == s[s.size()-1]+'A'-'a' or s[s.size()-3] == s[s.size()-1]+'a'-'A'){
          if (s[s.size()-2] == s[0]+'A'-'a' or s[s.size()-2] == s[0]+'a'-'A'){
             string t1 = s.substr(1,s.size()-4);
             legs++;
             return t1;
          }
       }
       if (s[s.size()-2] == s[0]+'A'-'a' or s[s.size()-2] == s[0]+'a'-'A'){
          if (s[s.size()-1] == s[1]+'A'-'a' or s[s.size()-1] == s[1]+'a'-'A'){
             string t1 = s.substr(2,s.size()-4);
             legs++;
             return t1;
          }
       }
       if (s[s.size()-1] == s[1]+'A'-'a' or s[s.size()-1] == s[1]+'a'-'A'){
          if (s[0] == s[2]+'A'-'a' or s[0] == s[2]+'a'-'A'){
             string t1 = s.substr(3,s.size()-4);
             legs++;
             return t1;
          }
       }
       // Rule 4
       // Select nucleotid
       char randchar = s[rand()%s.size()];
       if (randchar >= 'A' && randchar <= 'Z') randchar+='a' - 'A';
       // Cut
       int pos1,pos2;
       pos1 = -1;
       pos2 = -1;
       for (int i=0;i<s.size();i++){
           if (s[i] == randchar or s[i] == randchar + 'A' - 'a'){
              if (pos1 == -1) pos1 = i;
              else pos2 = i;
           }
       }
       //cout << "pos1 = " << pos1 << " pos2 = " << pos2 << endl;
       int cut = pos1+1+rand()%(pos2-pos1-1);
       //cout << "cut = " << cut << endl;
       string t1 = s.substr(0,cut);
       string t2 = s.substr(cut,s.size()-cut);
       pos2 = pos2 - cut;
       bool dif = true;
       if (s[pos1] == s[pos2+cut]){
          dif = false;
          string t3 = "";
          for (int i=t2.size()-1;i>=0; i--){
              if (t2[i] >= 'a' && t2[i] <='z'){
                 t3 = t3 + (char)(t2[i]+'A'-'a');
              }
              else t3 = t3 + (char)(t2[i]+'a'-'A');
          }
          t2 = t3;
          pos2 = t3.size() - pos2 - 1;
       }
       //cout << "t1 = " << t1 << " t2 = " << t2 << endl;
       string p1,p2,p3,p4;
       p1 = t1.substr(0,pos1);
       p2 = t1.substr(pos1+1,t1.size() - pos1);
       p3 = t2.substr(0,pos2);
       p4 = t2.substr(pos2+1,t2.size() - pos2);
       //cout << "p1 = " << p1 << " p2 = " << p2 << " p3 = " << p3 << " p4 = " << p4 << endl;
       string t5,t6;
       t5 = p1 + p4;
       t6 = p3 + p2;
       //cout << "t5 = " << t5 << " t6 = " << t6 << endl;
       string tot = t5 + (char)randchar + t6;
       if (dif) tot += (char)(randchar + 'A'-'a');
       else tot+=(char)randchar;
       //cout << "tot = " << tot << endl;
       return tot;
}

int main(){
    srand(time(0));
    string s;
    while (cin >> s, s != "END"){
          int arms, legs;
          legs = 0;
          arms = 0;
          while (1){
                //cout << "s antes = " << s << endl;
                s = transform(s,arms,legs);
                //cout << "s despues = " << s << endl;
                if (legs > 0 && arms > 0){
                   arms+=2*legs;
                   legs = 0;
                }
                if (s == "") break;
          }
          if (arms == 0 && legs != 0){
             cout << legs << " leg";
             if (legs > 1) cout << "s";
             cout << endl;
          }
          else if (arms != 0 && legs == 0){
             cout << arms << " arm";
             if (arms > 1) cout << "s";
             cout << endl;
          }
          else cout << "none" << endl;
    }
    return 0;
}
