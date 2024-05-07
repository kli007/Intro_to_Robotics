int grid[24][12];
int pointsOfInterest [2][288];  //x,y for a point of interest
int placeholder=0;

void setObstacles () {
  //Obstacle 1
  grid[22][8] = 0;
  pointsOfInterest[0][0] = 22;
  pointsOfInterest[1][0] = 8;
  grid[22][9] = 0;
  pointsOfInterest[0][1] = 22;
  pointsOfInterest[1][1] = 9;
  grid[21][8] = 0;
  pointsOfInterest[0][2] = 21;
  pointsOfInterest[1][2] = 8;


  //Obstacle 2
  grid[12][5] = 0;
  pointsOfInterest[0][3] = 12;
  pointsOfInterest[1][3] = 5;
  grid[12][6] = 0;
  pointsOfInterest[0][4] = 12;
  pointsOfInterest[1][4] = 6;
  grid[12][7] = 0;
  pointsOfInterest[0][5] = 12;
  pointsOfInterest[1][5] = 7;
  grid[12][8] = 0;
  pointsOfInterest[0][6] = 12;
  pointsOfInterest[1][6] = 8;


  //Obstacle 3
  grid[3][2] = 0;
  pointsOfInterest[0][7] = 3;
  pointsOfInterest[1][7] = 2;
  grid[3][3] = 0;
  pointsOfInterest[0][8] = 3;
  pointsOfInterest[1][8] = 3;
  grid[4][3] = 0;
  pointsOfInterest[0][9] = 4;
  pointsOfInterest[1][9] = 3;
  grid[4][4] = 0;
  pointsOfInterest[00][10] = 4;
  pointsOfInterest[1][10] = 4;
  grid[5][4] = 0;
  pointsOfInterest[0][11] = 5;
  pointsOfInterest[1][11] = 4;
  grid[5][5] = 0;
  pointsOfInterest[0][12] = 5;
  pointsOfInterest[1][12] = 5;
  placeholder = 12;
}

void initializeGrid (){
  for (int i = 0; i<24; i++){
    for (int j = 0; j<12; j++){
      grid[i][j]=-1;
    }
  }
}

void displayGrid() {
  int i,j;
  for (j=0;j<12;j++){
    for (i=0; i<23; i++) {
      Serial.print(grid[i][j]);
      Serial.print("\t");
    }
    Serial.println(grid[i][j]);
  }
}

void brushFire() {
  for (int i = 0; i<=placeholder; i++) {
    int x = pointsOfInterest[0][i];
    int y = pointsOfInterest[1][i]; //retrieve x, y coordinate of a point of interest
    int POIValue = grid[x][y];
    int newValue = POIValue+1;
    if (y >0){
      if (grid[x][y-1] == -1) {  //above
        grid[x][y-1] = newValue;
        placeholder = placeholder+1;
        pointsOfInterest[0][placeholder]=x;
        pointsOfInterest[1][placeholder]=y-1;
      }
    }
    if (y<11){
      if (grid[x][y+1] == -1) {  //below
        grid[x][y+1] = newValue;
        placeholder = placeholder+1;
        pointsOfInterest[0][placeholder]=x;
        pointsOfInterest[1][placeholder]=y+1;
      }
    }
    if (x>0) {
      if (grid[x-1][y] == -1) {  //left
        grid[x-1][y] = newValue;
        placeholder = placeholder+1;
        pointsOfInterest[0][placeholder]=x-1;
        pointsOfInterest[1][placeholder]=y;
      }
    }
    if (x<23) {
      if (grid[x+1][y] == -1) {  //above
        grid[x+1][y] = newValue;
        placeholder = placeholder+1;
        pointsOfInterest[0][placeholder]=x+1;
        pointsOfInterest[1][placeholder]=y;
      }
    }
    Serial.print(i);
    Serial.print(" " );
    Serial.print(x);
    Serial.print(" " );
    Serial.println(y);
    displayGrid();
    Serial.println();
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  initializeGrid();
  setObstacles();
  displayGrid();
  Serial.println();
  brushFire();
  displayGrid();
}

void loop() {
  // put your main code here, to run repeatedly:

}
