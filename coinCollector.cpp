#include <iostream>
#include <vector>

using namespace std;

//for storing points along path
vector<pair<int, int>> points;

bool isGreater(int a, int b) {
  if (a > b) 
    return true;
  else return false;
}

int main()
{
  int i, j, rows, cols;
  cin >> rows >> cols;
  
  //example one
  //rows = 5, cols = 6;

  // //example two
  // rows = 4, cols = 5;

  int initArr[rows][cols];

  //insert user values
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      cin >> initArr[i][j];
    }
  }

  //examples from homework used for initial testing
  //example one
  // int initArr[5][6] = { 
  //                       {0, 0, 0, 0, 1, 0},
  //                       {0, 1, 0, 1, 0, 0},
  //                       {0, 0, 0, 1, 0, 1},
  //                       {0, 0, 1, 0, 0, 1},
  //                       {1, 0, 0, 0, 1, 0}
  //                                           };

  //example two
  // int initArr[4][5] = { 
  //                       {0, 0, 0, 1, 0},
  //                       {0, 1, 1, 1, 0},
  //                       {1, 1, 1, 0, 1},
  //                       {0, 0, 0, 0, 0}
  //                                           };

  
  // cout << "printing initial array: " << endl;
  // for (int i = 0; i < rows; i++) {
  //   for (int j = 0; j < cols; j++) {
  //     cout << initArr[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;


  //generating modified array with cumulative values
  int modArr[rows][cols];
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      modArr[i][j] = 0;
    }
  }

  int total = 0;
  for (i = 0; i < rows; i++) {
    int rowTally = 0;
    for (j = 0; j < cols; j++) {
      if (i == 0) {
        if (initArr[i][j] == 1){
          rowTally++;
        }
        modArr[i][j] = rowTally;
      } else {
        if (j == 0) {
          int colTally = 0;
          if (initArr[i][j] == 1) {
            colTally++;
          }
          modArr[i][j] = colTally + modArr[i-1][j];
        } else {
          if (initArr[i][j] == 0) {
            modArr[i][j] = max(modArr[i-1][j], modArr[i][j-1]);
          } else {
            modArr[i][j] = max(modArr[i-1][j], modArr[i][j-1]) + 
              initArr[i][j];
          }
        }
      }
    }
  }

  // cout << "printing modified array: " << endl;
  // for (int i = 0; i < rows; i++) {
  //   for (int j = 0; j < cols; j++) {
  //     cout << modArr[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  //backtracking proces
  i = rows - 1;
  j = cols - 1;
  
  pair<int, int> start;
  start.first = i;
  start.second = j;
  points.push_back(start);

  while (i >= 0 && j >= 0) {
    pair<int, int> point;
    if (i > 0 && j > 0) {
      if (isGreater(modArr[i-1][j], modArr[i][j-1])){
        point.first = i - 1;
        point.second = j;
        points.push_back(point);
        i--;
      } 
      if (isGreater(modArr[i][j-1], modArr[i-1][j]) || modArr[i-1][j] == modArr[i][j-1]) {
        point.first = i;
        point.second = j - 1;
        points.push_back(point);
        j--;
      }
    } else if (i == 0 && j > 0) {
        point.first = i;
        point.second = j - 1;
        points.push_back(point);
        j--;
    } else if (j == 0 && i > 0) {
        point.first = i - 1;
        point.second = j;
        points.push_back(point);
        i--;
      }
    else {
      break;
    }
  }


  //final print
  cout << "Max coins:" << modArr[rows - 1][cols - 1] << "\n";
  cout << "Path:";

  //moving backwards through backtracking vector
  for (i = points.size() - 1; i >= 0; i--) {
    if (i != 0) {
      cout << "(" << points[i].first + 1 << "," << points[i].second + 1 << ")->";
    } else {
      cout << "(" << points[i].first + 1<< "," << points[i].second + 1<< ")";
    }
  }

  cout << "\n";
  return 0;
}

