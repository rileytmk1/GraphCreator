#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int adjacency_table[20][20];
  char vertexes [20];

  char input[20];
  while (strcmp(input, "QUIT") != 0){
    cout << "ADD, REMOVE, SEARCH, or QUIT" << endl;
    cin.get(input, 20);
    cin.get();
    if (strcmp(input, "ADD") == 0){
      cout << "vertex or edge? ";
      char input2[10];
      cin.get(input2, 10);
      cin.get();
      if(strcmp(input2, "vertex") == 0){

      }
    }
  }

}
