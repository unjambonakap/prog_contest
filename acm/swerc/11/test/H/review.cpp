// Solution to 'Peer review'
// Manuel Freire
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

// set to true for verbose mode
#define dcout if (false) cout

using namespace std;

struct paper {
  int place;
  vector<int> in;
};
vector<paper> papers;
map<string,int> places;

int main() {

  int k, n;
  while (cin >> k >> n && k && n) {
    places.clear();
    papers.clear();
    papers.resize(n);
    for (int i=0; i<n; i++) {
      string place;
      cin >> place;
      if (places.find(place) == places.end()) {
        places[place] = places.size();
      }
      papers[i].place = places[place];
      dcout << "reading paper " << i << " from " << places[place] << "\n";
      for (int j=0; j<k; j++) {
        int other;
        cin >> other;
        other --; // 1-to-n --> 0-to-(n-1)
        papers[other].in.push_back(i);
        dcout << "reviews paper " << other << "\n";
      }
    }
    // now, let us find problems
    int problems = 0;
    for (int i=0; i<n; i++) {
      if ((int)papers[i].in.size() != k) {
        // too many or too little        
        problems ++;
        dcout << "paper " << i << " has "
             << papers[i].in.size() << " revs!\n";
      } else {
        // check 'by the wrong people'
        sort(papers[i].in.begin(), papers[i].in.end());
        for (int j=0; j<k; j++) {
          int reviewer = papers[i].in[j];
          dcout << i << " reviewed by " << reviewer << "\n";          
          if (papers[reviewer].place == papers[i].place) {
            problems ++;
            dcout << "paper " << i << " from " << papers[i].place
                 << " conflicts with " << reviewer << " from "
                 << papers[reviewer].place << "!\n";
            break;
          } else if (j>0 && papers[i].in[j-1] == papers[i].in[j]) {
            problems ++;
            dcout << "paper " << i << " is reviewed more than once by "
                  << papers[i].in[j] << "!\n";
            break;
          }
        }
      }
    }
    // print output
    switch (problems) {
      case 0: cout << "NO PROBLEMS FOUND\n"; break;
      case 1: cout << "1 PROBLEM FOUND\n"; break;
      default: cout << problems << " PROBLEMS FOUND\n"; break;
    }
  }
  
  return 0;
}
