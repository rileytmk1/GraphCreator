#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;


int getVertexIndex(string label, string vertices[20], int &numVertices);
void addVertex(string label, string vertices[20], int &numVertices);
void addEdge(string from, string to, int matrix[20][20], string vertices[20], int weight, int &numVertices);
void rmEdge(string from, string to, int matrix[20][20], string vertices[20], int &numVertices);
void rmVertex(string label, int matrix[20][20], string vertices[20], int &numVertices);
void printMatrix(int matrix[20][20], string vertices[20], int &numVertices);
void dijkstra(string start, string end, int matrix[20][20], string vertices[20], int &numVertices);
int main()
{
  int matrix[20][20];
  string vertices [20];
  int numVertices = 0;
  for (int i = 0; i < 20; i++){
    for (int j = 0; j < 20; j++){
      matrix[i][j] = -1;
    }
  }
  char input[20];
  while (strcmp(input, "QUIT") != 0){
    cout << "ADD, REMOVE, PRINT, PATH, or QUIT" << endl;
    cin.get(input, 20);
    cin.get();
    if (strcmp(input, "ADD") == 0){
      cout << "vertex or edge? ";
      char input2[10];
      cin.get(input2, 10);
      cin.get();
      if(strcmp(input2, "vertex") == 0){
	cout << "Name of Vertex: ";
	string v;
	cin >> v;
	cin.ignore();
	addVertex(v, vertices, numVertices);
      }
      if (strcmp(input2, "edge") == 0){
	cout << "Vertex 1: ";
	string v1;
	cin >> v1;
	cin.ignore();
	cout << "Vertex 2: ";
	string v2;
	cin >> v2;
	cin.ignore();
	cout << "Weight: ";
	int w;
	cin >> w;
	cin.ignore();
	addEdge(v1, v2, matrix, vertices, w, numVertices);
      }
      
    }
    else if (strcmp(input, "REMOVE") == 0){
      cout << "vertex or edge? ";
      char input2[10];
      cin.get(input2, 10);
      cin.get();
      if (strcmp(input2, "vertex") == 0){
	cout << "Vertex Name: ";
	string l;
	cin >> l;
	cin.ignore();
	rmVertex(l, matrix, vertices, numVertices);
      }
      if (strcmp(input2, "edge") == 0){
	cout << "Vertex 1: ";
	string v1;
	cin >> v1;
	cin.ignore();
	cout << "Vertex 2: ";
	string v2;
	cin >> v2;
	cin.ignore();
	rmEdge(v1, v2, matrix, vertices, numVertices);
      }
    }
    else if (strcmp(input, "PRINT") == 0){
      printMatrix(matrix, vertices, numVertices); 
    }
    else if (strcmp(input, "PATH") == 0){
      cout << "Vertex 1: ";
      string v1;
      cin >> v1;
      cin.ignore();
      cout << "Vertex 2: ";
      string v2;
      cin >> v2;
      cin.ignore();
      dijkstra(v1, v2, matrix, vertices, numVertices);
    }
  }

}

int getVertexIndex(string label, string vertices[20], int &numVertices)
{
  for(int i = 0; i < numVertices; i++){
    if (vertices[i] == label){
      return i;
    }
  }
  return -1;
}

void addVertex(string label, string vertices[20], int &numVertices)
{
  vertices[numVertices++] = label;
}

void addEdge(string from, string to, int matrix[20][20], string vertices[20], int weight, int &numVertices)
{
  int i = getVertexIndex(from, vertices, numVertices);
  int j = getVertexIndex(to, vertices, numVertices);
  if (i == -1 || j == -1){
    return;
  }
  matrix[i][j] = weight;
  
}

void rmEdge(string from, string to, int matrix[20][20], string vertices[20], int &numVertices)
{
  int i = getVertexIndex(from, vertices, numVertices);
  int j = getVertexIndex(to, vertices, numVertices);
  if (i == -1 || j == -1){
    cout << "Edge does not exist." << endl;
    return;
  }
  matrix[i][j] = -1;
}

void rmVertex(string label, int matrix[20][20], string vertices[20], int &numVertices)
{
  int v = getVertexIndex(label, vertices, numVertices);
  if (v == -1){
    cout << "Vertex doesn't exist." << endl;
    return;
  }
  for (int i = 0; i < numVertices; i++){
    matrix[i][v] = -1;
    matrix[v][i] = -1;
  }
  for (int i = v; i < numVertices - 1; i++) {
      vertices[i] = vertices[i + 1];
  }
  for (int i = v; i < numVertices - 1; i++) {
      for (int j = 0; j < 20; j++) {
          matrix[i][j] = matrix[i + 1][j];
          matrix[j][i] = matrix[j][i + 1];
      }
  }
  numVertices--;

  
}

void printMatrix(int matrix[20][20], string vertices[20], int &numVertices) {
    cout << "   ";
    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i] << "  ";
        for (int j = 0; j < numVertices; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


void dijkstra(string startV, string endV, int matrix[20][20], string vertices[20], int &numVertices)
{
  // Get indexes of vertex labels
  int start = getVertexIndex(startV, vertices, numVertices);
  int end = getVertexIndex(endV, vertices, numVertices);

  // check validity
  if (start == -1 || end == -1){
    cout << "Invalid vertex." << endl;
    return;
  }

  //dist[i] holds current shortest distance from start to vertex i
  int dist[20];
  // marks if a vertex's shortest path is fixed
  bool visited[20];
  // holds previous vertexes on shortest path.
  int prev[20];

  // set unknow distances to infinity, mark all unvisited 
  for (int i = 0; i < 20; i++){
    dist[i] = 99999;
    visited[i] = false;
    prev[i] = -1;
  }

  //distance from start to itself is 0
  dist[start] = 0;

  
  for(int i = 0; i < numVertices; i++){
    int a = -1;
    for (int j = 0; j < numVertices; j++){
      if ( (visited[j] == false) && (a == -1 || dist[j] < dist[a])){
	a = j;
      }
    }

    if (a == -1 || dist[a] == 99999){
      break;
    }
    visited[a] = true;
    //check if going through a leads to a shorter path to j
    for (int j = 0; j < numVertices; j++){
      if (matrix[a][j] != -1){
	if (dist[a] + matrix[a][j] < dist[j]){
	  dist[j] = dist[a] + matrix[a][j];
	  prev[j] = a; //keep track shortest path to j
	}
      }
    }
  }

  // there is no path
  if (dist[end] == 99999){
    cout << "No path found." << endl;
    return;
  }
  //reverse prev to get path
  vector<string> path;
  int current = end;
  while(current != -1){
    path.push_back(vertices[current]);
    current = prev[current];
  }
  for (int i = path.size() -1; i>= 0; i--){
    cout << path[i] << " ";
  }
  cout << endl;
  cout << "Total: " << dist[end] << endl;
}
