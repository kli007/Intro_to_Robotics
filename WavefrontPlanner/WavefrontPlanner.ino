#define X_OF_GRID 24
#define Y_OF_GRID 12
#define X_OF_GOAL 23
#define Y_OF_GOAL 11
#define X_OF_START 0
#define Y_OF_START 0



int grid[X_OF_GRID][Y_OF_GRID];
int pointOfInterest[2][288];
int placeholder=0;



void setup(){
  Serial.begin(9600);
  delay(2000);
  initializeGrid();
  createPOI();
  createObject();
  wavefront();
  displayGrid();
}

void loop(){

}

void createPOI(){
  //goal 0=x, 1=y
  pointOfInterest[0][0]=X_OF_GOAL;
  pointOfInterest[1][0]=Y_OF_GOAL;
  grid[pointOfInterest[0][0]][pointOfInterest[1][0]]=1;
  grid[X_OF_START][Y_OF_START]=50;
}

void createObject(){
  //Obstacle 1
  grid[22][8] = 0;
  grid[22][9] = 0;
  grid[21][8] = 0;

  //Obstacle 2
  grid[12][5] = 0;
  grid[12][6] = 0;
  grid[12][7] = 0;
  grid[12][8] = 0;


  //Obstacle 3
  grid[3][2] = 0;
  grid[3][3] = 0;
  grid[4][3] = 0;
  grid[4][4] = 0;
  grid[5][4] = 0;
  grid[5][5] = 0;
}

void initializeGrid (){
  for (int i = 0; i<X_OF_GRID; i++){
    for (int j = 0; j<Y_OF_GRID; j++){
      grid[i][j]=-1;
    }
  }
}

void displayGrid(){
  int i,j;
  for (j=0;j<Y_OF_GRID;j++){
    for (i=0; i<(X_OF_GRID-1); i++) {
      Serial.print(grid[i][j]);
      Serial.print("\t");
    }
    Serial.println(grid[i][j]);
  }
}

void wavefront(){
  int first = 0;
  int newValue;
  for (int i = 0; i<=placeholder; i++) {
    int x = pointOfInterest[0][i];
    int y = pointOfInterest[1][i];
    int POIValue = grid[x][y];
    newValue = POIValue+1;
    if (y >0){
      if (grid[x][y-1] == -1) {  //above
        grid[x][y-1] = newValue;
        placeholder = placeholder+1;
        pointOfInterest[0][placeholder]=x;
        pointOfInterest[1][placeholder]=y-1;
      }
    }
    if (y<11){
      if (grid[x][y+1] == -1) {  //below
        grid[x][y+1] = newValue;
        placeholder = placeholder+1;
        pointOfInterest[0][placeholder]=x;
        pointOfInterest[1][placeholder]=y+1;
      }
    }
    if (x>0) {
      if (grid[x-1][y] == -1) {  //left
        grid[x-1][y] = newValue;
        placeholder = placeholder+1;
        pointOfInterest[0][placeholder]=x-1;
        pointOfInterest[1][placeholder]=y;
      }
    }
    if (x<23) {
      if (grid[x+1][y] == -1) {  //above
        grid[x+1][y] = newValue;
        placeholder = placeholder+1;
        pointOfInterest[0][placeholder]=x+1;
        pointOfInterest[1][placeholder]=y;
      }
    }
  }
}