#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file
bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  EXP1=0;
  EXP2=0;
  T1=0;
  T2=0;
  E=0;
  string line[100];
  int dem=0;
  ifstream read;
  read.open(filename);
  if(!read.is_open()){
   return false;
  }
  for(int i=0;i<5;i++){
      getline(read,line[i]);
      dem++;
  }
  if(dem!=5){
      return false;
  }
  read.close();
 // for(int i=0;i<5;i++){
 //   cout<<line[i]<<endl;
 //}
 for(int i=0;i<17;i++){
  LF1[i]=0;
  LF2[i]=0;
 }
  int seen=1;// bien danh giau da het cac chu so lien ke
  //int* temp= new int[target.length()];//mang chua cac so cuoi cung
  //temp=LF1 va LF2
  string strnum[39];//mang chua cac so dang string
  //strnum=line
  int chuso[39];//mang chua cac chu so cua so dang string
  int strnumx=0;
  int chusox;
  for(int i=0;i<39;++i){//set toan bo phan tu chuso=0
      chuso[i]=0;
  }
  for(int i=0;i<line[0].length();++i){
    if(line[0][i]>='0'&&line[0][i]<='9'){
      seen=0;
      chusox=1;
      if((i-1)>=0&&line[0][i-1]=='-'){
        strnum[strnumx]+='-';
      }
      strnum[strnumx]+=line[0][i];
      chuso[strnumx]=chusox;
      while(seen==0){
        i++;
        if(i<line[0].length()){
          if((line[0][i]<'0'||line[0][i]>'9')){
             seen=1;
          }
          else{
            strnum[strnumx]+=line[0][i];
            chuso[strnumx]++;
          continue;
          }
        }
        else{
          break;
        }
      }
      strnumx++;
    }
  }
if(strnumx!=17){
  //cout<<"ne"<<endl;
  while(strnumx!=17){
    strnum[strnumx]='0';
    chuso[strnumx]=1;
    strnumx++;
  }
}


for(int i=0;i<line[1].length();++i){
  if(line[1][i]>='0'&&line[1][i]<='9'){
    seen=0;
    chusox=1;
    if((i-1)>=0&&line[1][i-1]=='-'){
      strnum[strnumx]+='-';
    }
    strnum[strnumx]+=line[1][i];
    chuso[strnumx]=chusox;
    while(seen==0){
      i++;
      if(i<line[1].length()){
        if((line[1][i]<'0'||line[1][i]>'9')){
           seen=1;
        }
        else{
          strnum[strnumx]+=line[1][i];
          chuso[strnumx]++;
        continue;
        }
      }
      else{
        break;
      }
    }
    strnumx++;
  }
}
if(strnumx!=34){
while(strnumx!=34){
  strnum[strnumx]='0';
  chuso[strnumx]=1;
  strnumx++;
}
}


for(int i=0;i<line[2].length();++i){
if(line[2][i]>='0'&&line[2][i]<='9'){
  seen=0;
  chusox=1;
  if((i-1)>=0&&line[2][i-1]=='-'){
    strnum[strnumx]+='-';
  }
  strnum[strnumx]+=line[2][i];
  chuso[strnumx]=chusox;
  while(seen==0){
    i++;
    if(i<line[2].length()){
      if((line[2][i]<'0'||line[2][i]>'9')){
         seen=1;
      }
      else{
        strnum[strnumx]+=line[2][i];
        chuso[strnumx]++;
      continue;
      }
    }
    else{
      break;
    }
  }
  strnumx++;
}
}
if(strnumx!=36){
while(strnumx!=36){
strnum[strnumx]='0';
chuso[strnumx]=1;
strnumx++;
}
}


for(int i=0;i<line[3].length();++i){
if(line[3][i]>='0'&&line[3][i]<='9'){
  seen=0;
  chusox=1;
  if((i-1)>=0&&line[3][i-1]=='-'){
    strnum[strnumx]+='-';
  }
  strnum[strnumx]+=line[3][i];
  chuso[strnumx]=chusox;
  while(seen==0){
    i++;
    if(i<line[3].length()){
      if((line[3][i]<'0'||line[3][i]>'9')){
         seen=1;
      }
      else{
        strnum[strnumx]+=line[3][i];
        chuso[strnumx]++;
      continue;
      }
    }
    else{
      break;
    }
  }
  strnumx++;
}
}
if(strnumx!=38){
while(strnumx!=38){
strnum[strnumx]='0';
chuso[strnumx]=1;
strnumx++;
}
}

for(int i=0;i<line[4].length();++i){
if(line[4][i]>='0'&&line[4][i]<='9'){
  chusox=1;
  if((i-1)>=0&&line[4][i-1]=='-'){
    strnum[strnumx]+='-';
  }
  strnum[strnumx]+=line[4][i];
  chuso[strnumx]=chusox;
  while((++i)<line[4].length()){
      if((line[4][i]<'0'||line[4][i]>'9')){
      }
      else{
        strnum[strnumx]+=line[4][i];
        chuso[strnumx]++;
      continue;
      }
    }
  strnumx++;
}
}

if(strnumx!=39){
while(strnumx!=39){
strnum[strnumx]='0';
chuso[strnumx]=1;
strnumx++;
}
}
/*for(int i=0;i<39;i++){
  cout<<strnum[i]<<endl;
}
for(int i=0;i<39;i++){
  cout<<chuso[i]<<endl;
}*/
for(int j=0;j<17;j++){
  int power=chuso[j];
  if(strnum[j][0]=='-'){
    for(int i=chuso[j]-1;i>=0;i--){
      LF1[j]+=((int)(strnum[j][i+1]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
   LF1[j]=-LF1[j];
  }
  else{
    for(int i=chuso[j]-1;i>=0;i--){
    LF1[j]+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
    power--;
    }
  }
  
}
// for(int j=0;j<17;j++){cout<<LF1[j]<<",";
// }

for(int j=0;j<17;j++){
  int power=chuso[j+17];
  if(strnum[j+17][0]=='-'){
    for(int i=chuso[j+17]-1;i>=0;i--){
      LF2[j]+=((int)(strnum[j+17][i+1]-'0'))*pow(10,chuso[j+17]-power);
      power--;
   }
   LF2[j]=-LF2[j];
  }
  else{
  for( int i=chuso[j+17]-1;i>=0;i--){
    LF2[j]+=((int)(strnum[j+17][i]-'0'))*pow(10,chuso[j+17]-power);
    power--;
 }
}
}
// for(int j=0;j<17;j++){cout<<LF2[j]<<",";
// }

for(int j=34;j<35;j++){
  int power=chuso[j];
  if(strnum[j][0]=='-'){
    for(int i=chuso[j]-1;i>=0;i--){
      EXP1+=((int)(strnum[j][i+1]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
   EXP1=-EXP1;
  }
  else{
  for( int i=chuso[j]-1;i>=0;i--){
    EXP1+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
    power--;
 }
}}
//cout<<EXP1<<",";
//for(int i=0;i<5;i++){
//  cout<<chuso[i]<<",";
//}
for(int j=35;j<36;j++){
  //cout<<strnum[35]<<","<<chuso[35];
  int power=chuso[j];
  if(strnum[j][0]=='-'){
    for(int i=chuso[j]-1;i>=0;i--){
      EXP2+=((int)(strnum[j][i+1]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
   EXP2=-EXP2;
  }
  else{
  for( int i=chuso[j]-1;i>=0;i--){
    EXP2+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
    //cout<<EXP2<<",";
    power--;
 }
}}

for(int j=36;j<37;j++){
  int power=chuso[j];
  if(strnum[j][0]=='-'){
    for(int i=chuso[j]-1;i>=0;i--){
      T1+=((int)(strnum[j][i+1]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
   T1=-T1;
  }
  else{
  for( int i=chuso[j]-1;i>=0;i--){
    T1+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
    power--;
 }
}}
for(int j=37;j<38;j++){
  int power=chuso[j];
  if(strnum[j][0]=='-'){
    for(int i=chuso[j]-1;i>=0;i--){
      T2+=((int)(strnum[j][i+1]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
   T2=-T2;
  }
  else{
  for( int i=chuso[j]-1;i>=0;i--){
    T2+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
    power--;
 }
}}
for(int j=38;j<39;j++){
  int power=chuso[j];
  if(strnum[j][0]=='-'){
    for(int i=chuso[j]-1;i>=0;i--){
      E+=((int)(strnum[j][i+1]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
   E=-E;
  }
  else{
  for( int i=chuso[j]-1;i>=0;i--){
    E+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
    power--;
 }
}
}

for(int i=0;i<17;i++){
  LF1[i]=max(0,min(LF1[i],1000));
  LF2[i]=max(0,min(LF2[i],1000));
}
EXP1=max(0,min(EXP1,600));
EXP2=max(0,min(EXP2,600));
T1=max(0,min(T1,3000));
T2=max(0,min(T2,3000));
E=max(0,min(E,99));
return true;
}

// Task 1
int gatherForces(int LF1[], int LF2[])
{
  int L1=0,L2=0;
  int sucmanh[17]={1,2,3,4,5,7,8,9,10,12,15,18,20,30,40,50,70};
  for(int i=0;i<17;++i){
    if(LF1[i]<0) {LF1[i]=0;}
    else if(LF1[i]>1000) {LF1[i]=1000;}
    if(LF2[i]<0) {LF2[i]=0;}
    else if(LF2[i]>1000) {LF2[i]=1000;}
    L1+=sucmanh[i]*LF1[i];
    L2+=sucmanh[i]*LF2[i];
  }
  return L1 + L2;
}

// Task 2
string determineRightTarget(const string &target)
{
  int num=0,ID=0;//num: bien dem co bao nhieu so trong target
    int seen=1;// bien danh giau da het cac chu so lien ke
    int* temp= new int[target.length()];//mang chua cac so cuoi cung
    string* strnum=new string[target.length()];//mang chua cac so dang string
    int* chuso=new int[target.length()];//mang chua cac chu so cua so dang string
    int strnumx=0;
    int chusox;
    for(int i=0;i<target.length();++i){//set toan bo phan tu temp va chuso=0
        temp[i]=0;
        chuso[i]=0;
    }
    for(int i=0;i<target.length();++i){
      if(target[i]>='0'&&target[i]<='9'){
        seen=0;
        chusox=1;
        strnum[strnumx]=target[i];
        chuso[strnumx]=chusox;
        while(seen==0){
          i++;
          if(i<target.length()){
            if((target[i]<'0'||target[i]>'9')){
               seen=1;
            }
            else{
              strnum[strnumx]+=target[i];
              chuso[strnumx]++;
            continue;
            }
          }
          else{
            break;
          }
        }
        strnumx++;
      }
    }
  if(strnumx==0||strnumx>3){
    return "INVALID";
  }
  for(int j=0;j<strnumx;j++){
    int power=chuso[j];
    for( int i=chuso[j]-1;i>=0;i--){
      temp[j]+=((int)(strnum[j][i]-'0'))*pow(10,chuso[j]-power);
      power--;
   }
  }
  for(int i=0;i<strnumx;i++){
    if(temp[i]<0||temp[i]>100){
      return "INVALID";
    }
  }
    if(strnumx==1){
        ID=temp[0];
    }
    else if(strnumx==2){
        ID=(temp[0]+temp[1])%5+3;
    }
    else if(strnumx==3){
        ID=max(max(temp[0],temp[1]),temp[2])%5+3;
    }
    else {return "INVALID";}
    switch(ID){
        case 0:
        case 1:
        case 2:return "DECOY";
        case 3:
          return "Buon Ma Thuot";
        case 4:
          return "Duc Lap";
        case 5:
          return "Dak Lak";
        case 6:
          return "National Route 21";
        case 7:
          return "National Route 14";
        default: return "INVALID";
    } 
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
  // TODO: Implement this function
  EXP1=max(0,min(EXP1,600));
  EXP2=max(0,min(EXP2,600));
  int method=0;
  string sample[8]={"Kon Tum","Pleiku","Gia Lai","Buon Ma Thuot","Duc Lap","Dak Lak",
  "National Route 21","National Route 14"};
  string finalmes;
  if(EXP1>=300&&EXP2>=300){method=1;}
  else{method=2;}
  switch(method){
    case 1:
      int shift;
      shift=(EXP1+EXP2)%26;
      for(int i=0;i<message.length();i++){
        if((message[i]>='a')&&(message[i]<='z')){
          finalmes+=(char)((message[i]-'a'+shift)%26+'a');
        }
        else if((message[i]>='A')&&(message[i]<='Z')){
          finalmes+=(char)((message[i]-'A'+shift)%26+'A');
        }
        else if((message[i]==' ')||((message[i]<='9'&&message[i]>='0'))){
          finalmes+=message[i];
        }
        else {
          return "INVALID";
        }
      }
      break;
    case 2:
      for(int i=0;i<message.length();i++){
        finalmes+=message[message.length()-i-1];
      }
      break;
    }
  for(int i=0; i< finalmes.length();i++){
    if(((finalmes[i]>='A')&&(finalmes[i]<='Z'))){
      finalmes[i]=char(finalmes[i]+32);
    }    
  }
  for(int i=0; i< finalmes.length();i++){
    if(i==0||(finalmes[i-1]==' ')&&((finalmes[i]>='a')&&(finalmes[i]<='z'))){
      finalmes[i]=char(finalmes[i]-32);
    }
  }
  int found=0;
  for(int i=0;i<8;++i){
    if(finalmes==sample[i]){
      found=1;
      return sample[i];
    }
  }
  return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
  LF1=max(0,min(LF1,304000));
  LF2=max(0,min(LF2,304000));
    EXP1=max(0,min(EXP1,600));
    EXP2=max(0,min(EXP2,600));
    T1=max(0,min(T1,3000));
    T2=max(0,min(T2,3000));
    E=max(0,min(E,99));
    float T1tem=T1,T2tem=T2, delT1=0,delT2=0;
    if (E==0){
        delT1=((LF1/(float)(LF1+LF2))*(T1+T2)*(1+(EXP1-EXP2)/(float)100));
        delT2=((T1+T2)-delT1);
    }
    else if(E>=1 && E<=9){
        T1tem=T1-T1*E*1/(float)100;
        T2tem=T2-T2*E*0.5/(float)100;
    }
    else if(E>=10 && E<=29){
        T1tem=T1+E*50;
        T2tem=T2+E*50;
    }
    else if(E>=30 && E<=59){
        T1tem=T1+T1*E*0.5/(float)100;
        T2tem=T2+T2*E*0.2/(float)100;
    }
    T1tem+=delT1;
    T2tem+=delT2;
    T1=T1tem;
    T2=T2tem;
    if((T1tem)>((int)T1tem)){T1=((int)T1tem)+1;}
    if(T2tem>((int)T2tem)){T2=((int)T2tem)+1;}
    T1=max(0,min(T1,3000));
    T2=max(0,min(T2,3000));
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  LF1=max(0,min(LF1,304000));
  LF2=max(0,min(LF2,304000));
  EXP1=max(0,min(EXP1,600));
  EXP2=max(0,min(EXP2,600));
  T1=max(0,min(T1,3000));
  T2=max(0,min(T2,3000));
  double S=0;
  S=(LF1+LF2)+(EXP1+EXP2)*5+(T1+T2)*2;
  for(int i=0;i<10;++i){
    for(int j=0;j<10;++j){
      if(i%2!=0){
        S=S-(battleField[i][j]*3/(double)2);
      }
      else{
        S=S-(battleField[i][j]*2/(double)3);
      }
    }
  }
  double epsilon=0.0000001;
  if((S<0)&&(abs(S-floor(S))<epsilon)){S=floor(S);}
  else if((S>0)&&(abs(S-ceil(S))<epsilon)){S=ceil(S);}
  else{
    if((S>0)&&((S)>((int)S))){S=((int)S)+1;}
    if((S<0)&&((S)<((int)S))){S=((int)S);}
  }
  return S;
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  int temp[25];
  int temp1=0,sum=0,min=0;
  for(int j=0;j<5;++j){
      for(int k=0;k<5;++k){
          min+=supply[j][k];
          temp[temp1]=supply[j][k];
          temp1++;
      }
  }
  for(int a=0;a<21;++a){
      for(int b=a+1;b<22;++b){
        for(int c=b+1;c<23;++c){
          for(int d=c+1;d<24;++d){
            for(int e=d+1;e<25;++e){
              sum=temp[a]+ temp[b]+ temp[c]+ temp[d]+ temp[e];
              if(sum>=shortfall&&sum<min){
                min=sum;
              }
            }
          }
        }
      }
    }
  return min;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
