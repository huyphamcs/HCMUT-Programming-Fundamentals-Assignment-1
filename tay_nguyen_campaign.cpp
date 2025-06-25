#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file

int get_EXP_T(string c, int index){
  int number,i=0;
  stringstream ss(c);int EXP[2];string str;
  while (getline(ss,str,' '))
  {
      EXP[i] = stoi(str);i++;
  }
  number = EXP[index];
  return number;
}

bool string_array(string c, int arr[]){
  // string c = "[200,150,100,80,50,30,20,10,5,2,1,1,1,1,0,0,0]";
  char d[c.size()-2];
  for (int i = 0; i < c.size()-2; i++){
      d[i] = c[i+1];
  }
  // cout << d;

  stringstream ss(d);string str; 
  int i=0;
  while (getline(ss,str,',')){
      arr[i] = stoi(str); i++;
  }
  return true;
}

bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
    numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
    return false;
  }

  // TODO: Extract values from the `data` array and store them in respective variables
  
  string str;
  int i = 0;
  
  while (getline(ifs,str)){
      
      cout << str.length() << endl;
      for (int j = 0; j < str.length(); j++){
          data[i][j] = str[j];
      }
      i++;
      // if (str.length()==0) break;
      if (i == MAX_LINES) break;
  }
  i=0;
  string_array(data[0],LF1);
  string_array(data[1],LF2);
  EXP1 = get_EXP_T(data[2],0);
  EXP2 = get_EXP_T(data[2],1);
  T1 = get_EXP_T(data[3],0);
  T2 = get_EXP_T(data[3],1);
  E = get_EXP_T(data[4],0);

  for (int i = 0; i < 17; i++){
    if (LF1[i]>1000) LF1[i]=1000;
    else if (LF1[i]<0) LF1[i] = 0;
  }
  for (int i = 0; i < 17; i++){
    if (LF2[i]>1000) LF2[i]=1000;
    else if (LF2[i]<0) LF2[i] = 0;
  }

  if (EXP1>600) EXP1 = 600;
  else if (EXP1<0) EXP1 = 0;
  if (EXP2>600) EXP2 = 600;
  else if (EXP2<0) EXP2 = 0;

  if (T1>3000) T1=3000;
  else if (T1<0) T1=0;
  if (T2>3000) T2=3000;
  else if (T2<0) T2=0;

  if (E>99)E=99;
  else if (E<0)E=0;

  return true;
}

// Task 1
int powerCalculate(int LF[]){
  int power = 0, k = 0;
  for (int i = 0; i <17;i++){
    switch (i)
    {
    case 0:case 1:case 2: case 3: case 4:k=i+1;break;
    case 5: case 6: case 7: case 8:k = i+2;break;
    case 9: k = 12;break;
    case 10:k=15;break;
    case 11:k=18;break;
    case 12:k=20;break;
    case 13:k=30;break;
    case 14:k=40;break;
    case 15:k=50;break;
    case 16:k=70;break;
    default:break;
    }

    power += LF[i]*k;
  }
  return power;
}



int gatherForces(int LF1[], int LF2[])
{
  // TODO: Implement this function

  return powerCalculate(LF1) + powerCalculate(LF2);;
}

// Task 2
int findMax(int a,int b, int c){
  int max = a;
  if (max < b) max = b;
  if (max < c) max = c;
  return max;
}
bool isNumber(char c){
  if (c>=48&&c<=57) return 1;
  return 0;
}

bool isLowerLetter(char c){
  if (c>=97&&c<=122)return 1;
  return 0;
}
bool isUpperLetter(char c){
  if (c>=65&&c<=90)return 1;
  return 0;
}
string stringStandadization(string c){
  string tempString = "";
  c += " ";
  int j = 0, count = 0;
  for (int i = 0; i < c.size(); i++){
      if (c[i]!=32) tempString+=c[i];
      else if (tempString.size()>0){
          tempString="";
          count ++;
      }
  }
  if (count == 0) return c;
  tempString = "";
  string stringArray[count]; 
  for (int i = 0; i < c.size(); i++){
      if (c[i]!=32) tempString+=c[i];
      else if (tempString.size()>0){
          stringArray[j]=tempString;j++;
          tempString="";
      }
  }
  tempString = "";
  
  for (int i = 0; i < count; i++){
      if (i!=count-1) tempString += (stringArray[i]+ " ");
      else tempString+=stringArray[i]; 
  }
  return tempString;
}

string reWrite(string c){
  if (isLowerLetter(c[0])) c[0] = (char)(c[0]-32);
    for (int i = 1; i < c.size(); i++){
        if (isUpperLetter(c[i])&&c[i-1]!=32) c[i] = (char)(c[i]+32);
        if (isLowerLetter(c[i])&&c[i-1]==32) c[i] = (char)(c[i]-32);
    }
  return c;
}

string determineRightTarget(const string &target)
{
  // TODO: Implement this function
  string target2 = target + "a";
  
  string tempNumber;
  int j = 0, count = 0,ID;
  for(int i = 0; i < target2.size();i++){
    if (isNumber(target2[i])) tempNumber+=target2[i];
    else if (tempNumber.size()>0) {
      count++;
      tempNumber="";
    }
  }
  
  string stringNumber[count];
  for(int i = 0; i < target2.size();i++){
    if (isNumber(target2[i])) tempNumber+=target2[i];
    else {
        if (tempNumber.size()>0){
          stringNumber[j]=tempNumber;
          j++;
          tempNumber="";
          
        }
    }
  }
  j-=j;
  int number[count];
  if (count == 0 || count > 3) return "INVALID";
  for (int i = 0; i < count; i++) number[i] = stoi(stringNumber[i]);
  
  if (count == 1){
    if (number[0]>=3&&number[0]<=7) ID = number[0];
    else if (number[0]<=2) return "DECOY";
    else return "INVALID";
  }
  else if (count == 2) ID = ((number[0]+number[1])%5)+3;
  else if (count == 3) ID = (findMax(number[0],number[1],number[2])%5)+3;
  
  switch (ID)
  {
  case 3: return "Buon Ma Thuot";break;
  case 4: return "Duc Lap";break;
  case 5: return "Dak Lak";break;
  case 6: return "National Route 21";break;
  case 7: return "National Route 14";break;
  }
  return "INVALID";
}




string decodeTarget(const string &message, int EXP1, int EXP2)
{
  string newMessage = stringStandadization(message);
  // TODO: Implement this function
  if (EXP1>=300 and EXP2>=300){
    int shift = (EXP1+EXP2)%26;
    for (int i = 0; i < newMessage.size();i++){
      if (!(isNumber(newMessage[i])||isLowerLetter(newMessage[i])||isUpperLetter(newMessage[i])||newMessage[i]==32)) return "INVALID";
      else if (isLowerLetter(newMessage[i])) newMessage[i] = (newMessage[i]-'a'+shift)%26+'a';
      else if (isUpperLetter(newMessage[i])) newMessage[i] = (newMessage[i]-'A'+shift)%26+'A';
      // else if (messgae[i]==32||isNumber(newMessage[i])) 
    }
  }
  else{
    string tempMessage = newMessage;
    for (int i = 0; i < newMessage.size(); i++) tempMessage[i] = newMessage[newMessage.size()-i-1];
    newMessage = tempMessage;
  }
  newMessage=reWrite(newMessage);
  if (newMessage == "Buon Ma Thuot" || newMessage == "Duc Lap" || newMessage == "Dak Lak" || newMessage == "National Route 21" || newMessage == "National Route 14") return newMessage;
  return "INVALID";
  // return newMessage;
  
}

// Task 3
int findMin(int a, int b){
  if (a>b) return b;
  return a;
}
int findMax(int a, int b){
  if (a>b) return a;
  return b;
}

void manageLogistics(int LF1_power, int LF2_power, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
  float newT1, newT2, deltaT1, deltaT2;
  newT1 = (float)T1; newT2 = (float)T2;
  if (E==0){
    deltaT1 = ((float)LF1_power*(newT1+newT2)/(LF1_power+LF2_power))*(1+(float)(EXP1-EXP2)/100);
    deltaT2 = (newT1+newT2)-deltaT1;
    // if ((int)deltaT1-deltaT1!=0) deltaT1 = (int)deltaT1+1;
    // else deltaT1 = (int)deltaT1;

    // if ((int)deltaT2-deltaT2!=0) deltaT2 = (int)deltaT2+1;
    // else deltaT2 = (int)deltaT2;
    newT1+=deltaT1;
    newT2+=deltaT2;
  }
  else if (E>=1&&E<=9){
    deltaT1 = newT1*((float)E/100);
    deltaT2 = newT2*((float)E/200);
    newT1 -= deltaT1;
    newT2 -= deltaT2;
  }
  else if (E>=10 && E <= 29){
    newT1 += E*50;
    newT2 += E*50;
  }
  else if (E>=30 && E <= 59){
    newT1 += newT1*E/200;
    newT2 += newT2*E/500;
  }
  // cout << newT1 << newT2;
  if ((int)newT1-newT1!=0) newT1 = (int)newT1+1;
  if ((int)newT2-newT2!=0) newT2 = (int)newT2+1;
  // T1 = (int)newT1;
  // T2 = (int)newT2;
  T1 = findMin(newT1,3000);
  T2 = findMin(newT2,3000);

  T1 = findMax(T1,0);
  T2 = findMax(T2,0);

  
}

// Task 4
int planAttack(int LF1_power, int LF2_power, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  int S = LF1_power+LF2_power+ (T1+T2)*2 + (EXP1+EXP2)*5;
  float newS = S;
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++) {
      if (i%2==0)newS -= (float)battleField[i][j]*2/3;
      else newS -= (float)battleField[i][j]*3/2;
    }
  }
  if ((int)newS-newS!=0) {
    if (newS>=0)newS = (int)newS+1;
    else newS = (int)newS;
  }
  

  S = newS;
  return S;
}

// Task 5
void sort(int arr[], int size){
  int count  = 0;
  for (int i = 0; i < size-1;i++){
      if (arr[i] > arr[i+1]) {
          swap(arr[i], arr[i+1]);
          count ++;
      }
  }
  if (count > 0) {
      count -= count;
      sort(arr,size);
  }
  else;
}

int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  int position[25], k = 0;
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++){
      position[k] = supply[i][j];k++;
    }
  }
  int n = 25, sum = 1000000;
  sort(position,25);
  for (int i = 0; i < n-4; i++){
    for (int j = i+1; j < n-3; j++){
        for (int k = j+1; k < n-2; k++){
            for (int l = k+1; l < n-1; l++){
                for (int m = l+1; m < n; m++){
                    if (position[i]+position[j]+position[k]+position[l]+position[m]>=shortfall && position[i]+position[j]+position[k]+position[l]+position[m]<sum)sum = position[i]+position[j]+position[k]+position[l]+position[m];
                }
            }
        }
    }
}
  if (sum == 1000000) return -1;
  return sum;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
