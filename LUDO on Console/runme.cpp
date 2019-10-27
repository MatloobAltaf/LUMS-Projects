#include<iostream>
#include <ctime>
#include<stdlib.h>
#include<string>
#include<windows.h>

using namespace std ;

int dice_roll();
void turn_player();
int check_movables1(int aa);
void board();
int array_contains(string aaa[]);
void move_gote(string En,int q);
int first_empty(string ab[]);
void jota_maar();
int check_end();


int mari,pugi,bp,player=1;
string name1,name2;

string movables[4];
string a[52];
string b[7]={"X_","X_","X_","X_","X_","X_","  "};
string c[7]={"X_","X_","X_","X_","X_","X_","  "};
string A[5]={"AA","A1","A2","A3","A4"};
string B[5]={"BB","B1","B2","B3","B4"};
string S1[8];string S2[8];string S3[8];string S4[8];string S11[8];string S12[8];string S13[8];string S14[8];







//******************************************* MAIN FUNCTION
                                           // Returns 0
int main ()
{


for(int n=0;n<52;n++){a[n]="__";}
a[0]=a[8]=a[13]=a[21]=a[26]=a[34]=a[39]=a[47]="MM";   //Filling board circular array with appropriate symbols

for (int i=0;i<8;i++)
   {S1[i]="  ";S2[i]="  ";S3[i]="  ";S4[i]="  ";S11[i]="  ";S12[i]="  ";S13[i]="  ";S14[i]="  ";}   //Filling Arrays for pair



cout<<"\n\nEnter Name of Player-1\t";getline(cin,name1);           //Input Names of players
cout<<"\nEnter Name of Player-2\t";getline(cin,name2);


while(1)
{
    if (player==3){player=1;}
turn_player();
int x = check_end() ;
if (x==1) break;

}


    return 0 ;
}





//*************************************** Function to Display the Ludo Board

void board()
{
    system("cls");

    cout<<"\t\t\t\t"<<"*************************************************\n\n"
        <<"\t\t\t\t"<<"           TWO PLAYERS LITTLE HORSES\n\n"
        <<"\t\t\t\t"<<"*************************************************\n";


   cout                        <<"______________________________________________";
 cout<<endl<<"|"                <<" P1              |"                                                  <<a[10]<<"|"<<a[11]<<"|" <<a[12]<<"|                 "                                                           <<"|";
 cout<<endl<<"|"                <<"    "<<A[1]<<"   "<<A[2]<<"      |"                                  <<a[9]      <<"|X_|"     <<a[13]<<"|--               "                                                           <<"|";                     if (array_contains(S1)>0) cout<<"  "<<"*1"<<" = "<<S1[0]<<"," <<S1[1]<<"," <<S1[2]<<"," <<S1[3]<<"," <<S1[4] <<","<<S1[5] <<","<<S1[6] <<","<<S1[7];
 cout<<endl<<"|"                <<"               --|"                                                  <<a[8]      <<"|X_|"     <<a[14]<<"|                 "                                                           <<"|";                     if (array_contains(S2)>0) cout<<"  "<<"*2"<<" = "<<S2[0]<<"," <<S2[1]<<"," <<S2[2]<<"," <<S2[3]<<"," <<S2[4] <<","<<S2[5] <<","<<S2[6] <<","<<S2[7];
 cout<<endl<<"|"                <<"    "<<A[3]<<"   "<<A[4]<<"      |"                                  <<a[07]     <<"|X_|"     <<a[15]<<"|                 "                                                           <<"|";                     if (array_contains(S3)>0) cout<<"  "<<"*3"<<" = "<<S3[0]<<"," <<S3[1]<<"," <<S3[2]<<"," <<S3[3]<<"," <<S3[4] <<","<<S3[5] <<","<<S3[6] <<","<<S3[7];
 cout<<endl<<"|"                <<"                 |"                                                  <<a[06]     <<"|X_|"     <<a[16]<<"|                 "                                                           <<"|";                     if (array_contains(S4)>0) cout<<"  "<<"*4"<<" = "<<S4[0]<<"," <<S4[1]<<"," <<S4[2]<<"," <<S4[3]<<"," <<S4[4] <<","<<S4[5] <<","<<S4[6] <<","<<S4[7];
 cout<<endl<<"|"                <<"___|_____________|"                                                  <<a[05]     <<"|X_|"     <<a[17]<<"|_________|_______"                                                           <<"|";                     if (array_contains(S11)>0)cout<<"  "<<"*5"<<" = "<<S11[0]<<","<<S11[1]<<","<<S11[2]<<","<<S11[3]<<","<<S11[4]<<","<<S11[5]<<","<<S11[6]<<","<<S11[7];
 cout<<endl<<"|"                <<a[51]<<"|"<<a[00]<<"|"<<a[01]<<"|"<<a[02]<<"|"<<a[03]<<"|"<<a[04]     <<"|   "    <<"  "       <<"   |"    <<a[18]<<"|"<<a[19]<<"|"<<a[20]<<"|"<<a[21]<<"|"<<a[22]<<"|"<<a[23]         <<"|";                     if (array_contains(S12)>0)cout<<"  "<<"*6"<<" = "<<S12[0]<<","<<S12[1]<<","<<S12[2]<<","<<S12[3]<<","<<S12[4]<<","<<S12[5]<<","<<S12[6]<<","<<S12[7];
 cout<<endl<<"|"                <<a[50]<<"|"<<b[01]<<"|"<<b[02]<<"|"<<b[03]<<"|"<<b[04]<<"|"<<b[05]<<"|"<<b[06]     <<"LUDO"     <<c[06]<<"|"<<c[05]<<"|"<<c[04]<<"|"<<c[03]<<"|"<<c[02]<<"|"<<c[01]<<"|"<<a[24]         <<"|";                     if (array_contains(S13)>0)cout<<"  "<<"*7"<<" = "<<S13[0]<<","<<S13[1]<<","<<S13[2]<<","<<S13[3]<<","<<S13[4]<<","<<S13[5]<<","<<S13[6]<<","<<S13[7];
 cout<<endl<<"|"                <<a[49]<<"|"<<a[48]<<"|"<<a[47]<<"|"<<a[46]<<"|"<<a[45]<<"|"<<a[44]     <<"|___"    <<"__"       <<"___|"    <<a[30]<<"|"<<a[29]<<"|"<<a[28]<<"|"<<a[27]<<"|"<<a[26]<<"|"<<a[25]         <<"|";                     if (array_contains(S14)>0)cout<<"  "<<"*8"<<" = "<<S14[0]<<","<<S14[1]<<","<<S14[2]<<","<<S14[3]<<","<<S14[4]<<","<<S14[5]<<","<<S14[6]<<","<<S14[7];
 cout<<endl<<"|"                <<"      |          |"                                                  <<a[43]     <<"|X_|"     <<a[31]<<"|            |    "                                                           <<"|";
 cout<<endl<<"|"                <<"                 |"                                                  <<a[42]     <<"|X_|"     <<a[32]<<"|                 "                                                           <<"|";
 cout<<endl<<"|"                <<"                 |"                                                  <<a[41]     <<"|X_|"     <<a[33]<<"|      "<<B[1]<<"   "<<B[2]<<"    "                                           <<"|";
 cout<<endl<<"|"                <<"                 |"                                                  <<a[40]     <<"|X_|"     <<a[34]<<"|--               "                                                           <<"|";
 cout<<endl<<"|"                <<"               --|"                                                  <<a[39]     <<"|X_|"     <<a[35]<<"|      "<<B[3]<<"   "<<B[4]<<"    "                                           <<"|";
 cout<<endl<<"|"                <<"_________________|"                                                  <<a[38]<<"|"<<a[37]<<"|"<<a[36] <<"|______________P2_"                                                           <<"|";
       cout<<endl                //<<"-------------------------------"
 <<endl ;


}





//*************************************** FUNCTION TO FIND THE INDEX OF FIRST EMPTY ELEMENT OF ARRAY
                                        //Argument is for Pair Array
                                        //Returns the index of First empty element of pair array WHICH IS CALLED i.e. "  "
int first_empty(string ab[])
{int i;
    for ( i=0;i<8;i++)
    {
        if (ab[i]=="  ")break;
    }
return i;
}







//**************************************  Function to CHECK NUMBER OF ELEMENETS IN PAIR ARRAY
                                        //Argument is for Pair array
                                        // Returns the number of Gotes stored in Pair ARRAY
int array_contains(string aaa[])
{int n=0;
    for (int i=0;i<8;i++)
    {if (aaa[i]!="  ") {n++;}}
    return n;
}









//***************************************  Function to get random dice output
                                          // Returns the random dice number from 1-6

int dice_roll()
{
srand(time(0));
string ab;
    cout<<"Enter any key to roll the DICE\t";
    cin>>ab;

int x;

    x= rand()%6 +1 ;
if (ab=="<") x=6;
if (ab==">") x=2;
if (x==6) cout<<"\n\t\t\t YaaHoo U got\t"<<x<<endl;
else     cout<<"\n\t\t\tU got\t"<<x<<endl;

return x;

}











//***************************************  Function to proceed the turn of Player 1

void turn_player()
{
     int y=0,z=0,n=0,x,tpugi=0;
mari=0;string entered;

do
{pugi=0;bp=0;
board();
cout<<"\t\t\t TURN PLAYER---"<<player<<"\t"; if (player==1) cout<<name1; if (player==2) cout<<name2;
cout<<endl<<endl;


if (n==1)
   {x=y;y=0;}
   else if (n==2) {x=y;y=z;z=0;}
   else
   {x= dice_roll() ;
   if (x==6) {n++;y=dice_roll(); if (y==6) {n++;z=dice_roll();} if (z==6){n++;} }}

   if (n==3){cout<<"\n\t U got THREE 6  So \t TURN CANCELLED\n\n";system("pause");break; }


   cout<<"\n\t\t\t\tYour Remaining Dice\t"; if (x==0) cout<<"__"; else cout<<x; cout<<" "; if (y==0) cout<<"__"; else cout<<y; cout<<" "; if (z==0)cout<<"__"; else cout<<z;


int num_moveables=check_movables1(x);
     if (num_moveables==0)
     {
    system("pause");
     break;}

     cout<<"\n\n\t\t\t\tMOVE\t"<<x<<endl;
     N:
cout<<"\nEnter any of the movable gote\t";
cin>>entered;

int i=0;
for (int j=0;j<4;j++)
if (movables[j]==entered)
    i++;
    if (i==0) goto N;

move_gote(entered,x);

//fOR BEEP TO SOUND
if (bp==1 || pugi==1)
    { if (bp==1){cout<<"\n\t\t\t GOTE KILLED\n";} else if (pugi==1){tpugi=1;cout<<"\n\t\t\t GOTE REACHED\n";}Beep(2000,1000);}

board();


}
while(x==6);
bp=0;
jota_maar();
if (bp==1){cout<<"\n\t\t\t Gote Killed\n";Beep(2000,1000);}
player++;

if (tpugi==1 || mari==1) player--;

}











//****************************************  Functions to Check Movable Gotes
                                         //Argument is the dice number to move
                                         //Returns the number of movable Gotes

int check_movables1(int aa)
{
    for (int i=0;i<4;i++)
movables[i]= " ";

int n=0;

if (player==1)
{


if (aa==6)            // Checking in home
 {
        for (int i=1;i<5;i++)
        { if (A[i][0]=='A') {movables[n]=A[i];n++;} }
}

                      // On board


for (int i=0;i<52;i++)
{
    if (a[i][0]=='A') {movables[n]=a[i];n++;}
}
//On Ending
for (int i =1;i<6;i++)
{
    if (b[i][0]=='A' && i+aa<=6) {movables[n]=b[i];n++;}
}
//In Pair Arrays
for (int i=0;i<8;i++)
{
    if (S1[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*1") {movables[n]=S1[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*1" && ii +aa<=6) {movables[n]=S1[i];n++;}}}

    if (S2[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*2") {movables[n]=S2[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*2" && ii +aa<=6) {movables[n]=S2[i];n++;}}}

    if (S3[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*3") {movables[n]=S3[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*3" && ii +aa<=6) {movables[n]=S3[i];n++;}}}

    if (S4[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*4") {movables[n]=S4[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*4" && ii +aa<=6) {movables[n]=S4[i];n++;}}}

    if (S11[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*5") {movables[n]=S11[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*5" && ii+aa<=6) {movables[n]=S11[i];n++;}}}

    if (S12[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*6") {movables[n]=S12[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*6" && ii +aa<=6) {movables[n]=S12[i];n++;}}}

    if (S13[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*7") {movables[n]=S13[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*7" && ii +aa<=6) {movables[n]=S13[i];n++;}}}

    if (S14[i][0]=='A') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*8") {movables[n]=S14[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (b[ii]=="*8" && ii +aa<=6) {movables[n]=S14[i];n++;}}}

}

}


if (player==2)
{


if (aa==6)            // Checking in home
 {
        for (int i=1;i<5;i++)
        { if (B[i][0]=='B') {movables[n]=B[i];n++;} }
}

                      // On board


for (int i=0;i<52;i++)
{
    if (a[i][0]=='B') {movables[n]=a[i];n++;}
}
//On Ending
for (int i =1;i<6;i++)
{
    if (c[i][0]=='B' && i+aa<=6) {movables[n]=c[i];n++;}
}
//In Pair Arrays
for (int i=0;i<8;i++)
{
    if (S1[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*1") {movables[n]=S1[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*1" && ii +aa<=6) {movables[n]=S1[i];n++;}}}

    if (S2[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*2") {movables[n]=S2[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*2" && ii +aa<=6) {movables[n]=S2[i];n++;}}}

    if (S3[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*3") {movables[n]=S3[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*3" && ii +aa<=6) {movables[n]=S3[i];n++;}}}

    if (S4[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*4") {movables[n]=S4[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*4" && ii +aa<=6) {movables[n]=S4[i];n++;}}}

    if (S11[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*5") {movables[n]=S11[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*5" && ii+aa<=6) {movables[n]=S11[i];n++;}}}

    if (S12[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*6") {movables[n]=S12[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*6" && ii +aa<=6) {movables[n]=S12[i];n++;}}}

    if (S13[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*7") {movables[n]=S13[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*7" && ii +aa<=6) {movables[n]=S13[i];n++;}}}

    if (S14[i][0]=='B') {for (int ii=0;ii<52;ii++) {if (a[ii]=="*8") {movables[n]=S14[i];n++;}}
                       for (int ii=1;ii<6;ii++) {if (c[ii]=="*8" && ii +aa<=6) {movables[n]=S14[i];n++;}}}

}

}

cout<<"\n\nMOVABLE GOTES :\n";
n=0;
for(int i = 0;i<4;i++)
{cout<<movables[i]<<"\t";
    if (movables[i]!=" ")
        { n++;}
}



if (n==0) cout<<"NONE\n";

return n ;

}







//***************************************** FUNCTION TO KILL GOTES IN PAIR ARRAYS

void jota_maar()
{
                                  // FOR SINGLE GOTE IN PAIR

for (int i=0;i<52;i++)
{                                 //FOR A KILLS B
    if (a[i]=="*1" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S1[0][0]=='B' && S1[1][0]=='A')
{ bp=1;
         if (S1[0]=="B1"){B[1]="B1";}
    else if (S1[0]=="B2"){B[2]="B2";}
    else if (S1[0]=="B3"){B[3]="B3";}
    else if (S1[0]=="B4"){B[4]="B4";}
S1[0]=="  ";
for (int ii=0;ii<8;ii++){S1[ii]=S1[ii+1]; } S1[7]=="  ";
}

if (a[i]=="*2" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S2[0][0]=='B' && S2[1][0]=='A')
{ bp=1;
         if (S2[0]=="B1"){B[1]="B1";}
    else if (S2[0]=="B2"){B[2]="B2";}
    else if (S2[0]=="B3"){B[3]="B3";}
    else if (S2[0]=="B4"){B[4]="B4";}
S2[0]=="  ";
for (int ii=0;ii<8;ii++){S2[ii]=S2[ii+1]; } S2[7]=="  ";
}

if (a[i]=="*3" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S3[0][0]=='B' && S3[1][0]=='A')
{ bp=1;
         if (S3[0]=="B1"){B[1]="B1";}
    else if (S3[0]=="B2"){B[2]="B2";}
    else if (S3[0]=="B3"){B[3]="B3";}
    else if (S3[0]=="B4"){B[4]="B4";}
S3[0]=="  ";
for (int ii=0;ii<8;ii++){S3[ii]=S3[ii+1]; } S3[7]=="  ";
}

if (a[i]=="*4" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S4[0][0]=='B' && S4[1][0]=='A')
{ bp=1;
         if (S4[0]=="B1"){B[1]="B1";}
    else if (S4[0]=="B2"){B[2]="B2";}
    else if (S4[0]=="B3"){B[3]="B3";}
    else if (S4[0]=="B4"){B[4]="B4";}
S4[0]=="  ";
for (int ii=0;ii<8;ii++){S4[ii]=S4[ii+1]; } S4[7]=="  ";
}

if (a[i]=="*5" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S11[0][0]=='B' && S11[1][0]=='A')
{ bp=1;
         if (S11[0]=="B1"){B[1]="B1";}
    else if (S11[0]=="B2"){B[2]="B2";}
    else if (S11[0]=="B3"){B[3]="B3";}
    else if (S11[0]=="B4"){B[4]="B4";}
S11[0]=="  ";
for (int ii=0;ii<8;ii++){S11[ii]=S11[ii+1]; } S11[7]=="  ";
}

if (a[i]=="*6" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S12[0][0]=='B' && S12[1][0]=='A')
{ bp=1;
         if (S12[0]=="B1"){B[1]="B1";}
    else if (S12[0]=="B2"){B[2]="B2";}
    else if (S12[0]=="B3"){B[3]="B3";}
    else if (S12[0]=="B4"){B[4]="B4";}
S12[0]=="  ";
for (int ii=0;ii<8;ii++){S12[ii]=S12[ii+1]; } S12[7]=="  ";
}

if (a[i]=="*7" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S13[0][0]=='B' && S13[1][0]=='A')
{ bp=1;
         if (S13[0]=="B1"){B[1]="B1";}
    else if (S13[0]=="B2"){B[2]="B2";}
    else if (S13[0]=="B3"){B[3]="B3";}
    else if (S13[0]=="B4"){B[4]="B4";}
S13[0]=="  ";
for (int ii=0;ii<8;ii++){S13[ii]=S13[ii+1]; } S13[7]=="  ";
}

if (a[i]=="*8" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S14[0][0]=='B' && S14[1][0]=='A')
{ bp=1;
         if (S14[0]=="B1"){B[1]="B1";}
    else if (S14[0]=="B2"){B[2]="B2";}
    else if (S14[0]=="B3"){B[3]="B3";}
    else if (S14[0]=="B4"){B[4]="B4";}
S14[0]=="  ";
for (int ii=0;ii<8;ii++){S14[ii]=S14[ii+1]; } S14[7]=="  ";
}

                                        // FOR B KILLS A

if (a[i]=="*1" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S1[0][0]=='A' && S1[1][0]=='B')
{ bp=1;
         if (S1[0]=="A1"){A[1]="A1";}
    else if (S1[0]=="A2"){A[2]="A2";}
    else if (S1[0]=="A3"){A[3]="A3";}
    else if (S1[0]=="A4"){A[4]="A4";}
S1[0]=="  ";
for (int ii=0;ii<8;ii++){S1[ii]=S1[ii+1]; } S1[7]=="  ";
}

if (a[i]=="*2" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S2[0][0]=='A' && S2[1][0]=='B')
{ bp=1;
         if (S2[0]=="A1"){A[1]="A1";}
    else if (S2[0]=="A2"){A[2]="A2";}
    else if (S2[0]=="A3"){A[3]="A3";}
    else if (S2[0]=="A4"){A[4]="A4";}
S2[0]=="  ";
for (int ii=0;ii<8;ii++){S2[ii]=S2[ii+1]; } S2[7]=="  ";
}

if (a[i]=="*3" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S3[0][0]=='A' && S3[1][0]=='B')
{ bp=1;
         if (S3[0]=="A1"){A[1]="A1";}
    else if (S3[0]=="A2"){A[2]="A2";}
    else if (S3[0]=="A3"){A[3]="A3";}
    else if (S3[0]=="A4"){A[4]="A4";}
S3[0]=="  ";
for (int ii=0;ii<8;ii++){S3[ii]=S3[ii+1]; } S3[7]=="  ";
}

if (a[i]=="*4" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S4[0][0]=='A' && S4[1][0]=='B')
{ bp=1;
         if (S4[0]=="A1"){A[1]="A1";}
    else if (S4[0]=="A2"){A[2]="A2";}
    else if (S4[0]=="A3"){A[3]="A3";}
    else if (S4[0]=="A4"){A[4]="A4";}
S4[0]=="  ";
for (int ii=0;ii<8;ii++){S4[ii]=S4[ii+1]; } S4[7]=="  ";
}

if (a[i]=="*5" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S11[0][0]=='A' && S11[1][0]=='B')
{ bp=1;
         if (S11[0]=="A1"){A[1]="A1";}
    else if (S11[0]=="A2"){A[2]="A2";}
    else if (S11[0]=="A3"){A[3]="A3";}
    else if (S11[0]=="A4"){A[4]="A4";}
S11[0]=="  ";
for (int ii=0;ii<8;ii++){S11[ii]=S11[ii+1]; } S11[7]=="  ";
}

if (a[i]=="*6" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S12[0][0]=='A' && S12[1][0]=='B')
{ bp=1;
         if (S12[0]=="A1"){A[1]="A1";}
    else if (S12[0]=="A2"){A[2]="A2";}
    else if (S12[0]=="A3"){A[3]="A3";}
    else if (S12[0]=="A4"){A[4]="A4";}
S12[0]=="  ";
for (int ii=0;ii<8;ii++){S12[ii]=S12[ii+1]; } S12[7]=="  ";
}

if (a[i]=="*7" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S13[0][0]=='A' && S13[1][0]=='B')
{ bp=1;
         if (S13[0]=="A1"){A[1]="A1";}
    else if (S13[0]=="A2"){A[2]="A2";}
    else if (S13[0]=="A3"){A[3]="A3";}
    else if (S13[0]=="A4"){A[4]="A4";}
S13[0]=="  ";
for (int ii=0;ii<8;ii++){S13[ii]=S13[ii+1]; } S13[7]=="  ";
}

if (a[i]=="*8" && i!=0 && i!=8 && i!=13 && i!=21 && i!=26 && i!=34 && i!=39 && i!=47 && S14[0][0]=='A' && S14[1][0]=='B')
{ bp=1;
         if (S14[0]=="A1"){A[1]="A1";}
    else if (S14[0]=="A2"){A[2]="A2";}
    else if (S14[0]=="A3"){A[3]="A3";}
    else if (S14[0]=="A4"){A[4]="A4";}
S14[0]=="  ";
for (int ii=0;ii<8;ii++){S14[ii]=S14[ii+1]; } S14[7]=="  ";
}

}





                                 // TO REPLACE *n BY SINGLE ELEMENT OF THE PAIR ARRAY

if (array_contains(S1)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*1") {a[ii]=S1[0];S1[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*1"){b[ii]=S1[0];S1[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*1"){c[ii]=S1[0];S1[0]="  ";}}}
if (array_contains(S2)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*2") {a[ii]=S2[0];S2[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*2"){b[ii]=S2[0];S2[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*2"){c[ii]=S2[0];S2[0]="  ";}}}
if (array_contains(S3)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*3") {a[ii]=S3[0];S3[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*3"){b[ii]=S3[0];S3[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*3"){c[ii]=S3[0];S3[0]="  ";}}}
if (array_contains(S4)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*4") {a[ii]=S4[0];S4[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*4"){b[ii]=S4[0];S4[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*4"){c[ii]=S4[0];S4[0]="  ";}}}
if (array_contains(S11)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*5") {a[ii]=S11[0];S11[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*5"){b[ii]=S11[0];S11[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*5"){c[ii]=S11[0];S11[0]="  ";}}}
if (array_contains(S12)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*6") {a[ii]=S12[0];S12[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*6"){b[ii]=S12[0];S12[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*6"){c[ii]=S12[0];S12[0]="  ";}}}
if (array_contains(S13)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*7") {a[ii]=S13[0];S13[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*7"){b[ii]=S13[0];S13[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*7"){c[ii]=S13[0];S13[0]="  ";}}}
if (array_contains(S14)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*8") {a[ii]=S14[0];S14[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*8"){b[ii]=S14[0];S14[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*8"){c[ii]=S14[0];S14[0]="  ";}}}

}





//**********************************  FUNCTION TO CHECK THE END OF THE GAME  **********************
                                   //Returns 1 if game is ended else 0

int check_end()
{

string *p; string jota="  ";
p = &b[6];int gend=0;
jota=*p;
if (jota=="*1" && array_contains(S1)==4) {gend=1;}
else if (jota=="*2" && array_contains(S2)==4) {gend=1;}
else if (jota=="*3" && array_contains(S3)==4) {gend=1;}
else if (jota=="*4" && array_contains(S4)==4) {gend=1;}
else if (jota=="*5" && array_contains(S11)==4) {gend=1;}
else if (jota=="*6" && array_contains(S12)==4) {gend=1;}
else if (jota=="*7" && array_contains(S13)==4) {gend=1;}
else if (jota=="*8" && array_contains(S14)==4) {gend=1;}

if (gend==1) { cout<<"\n\n \t\t\t YAAHOOOOOOOO\n\t\t\t PLAYER-1   WINS\n\n\n"; goto AA;}


jota="  ";
p = &c[6];
jota = *p;
if (jota=="*1" && array_contains(S1)==4) {gend=1;}
else if (jota=="*2" && array_contains(S2)==4) {gend=1;}
else if (jota=="*3" && array_contains(S3)==4) {gend=1;}
else if (jota=="*4" && array_contains(S4)==4) {gend=1;}
else if (jota=="*5" && array_contains(S11)==4) {gend=1;}
else if (jota=="*6" && array_contains(S12)==4) {gend=1;}
else if (jota=="*7" && array_contains(S13)==4) {gend=1;}
else if (jota=="*8" && array_contains(S14)==4) {gend=1;}

if (gend==1) { cout<<"\n\n \t\t\t YAAHOOOOOOOO\n\t\t\t PLAYER-2   WINS\n\n\n";}

AA:
    if (gend==1) return 1;
    else return 0;
}




//****************************************  FUNCTION TO MOVE GOTE
                                         // Argument-- [string En] is the Gote entered by the player to move --
                                         //[int q] is the dice number the Gote is to be moved

void move_gote(string En,int q)
{
    string k,jota="  ";
string *p;


                                        //*********  FOR GOTE IN PAIRS
if (player==1)
{

 for (int ii=0;ii<8;ii++)
 {
if (S1[ii]==En)
                                 { jota ="*1"; p=&S1[ii];break;}
else  if (En==S2[ii])
                                 { jota ="*2"; p=&S2[ii];break;}
else if (En==S3[ii])
                            { jota ="*3"; p=&S3[ii];break;}
else if (En==S4[ii])
                             { jota ="*4"; p=&S4[ii];break;}
else if (En==S11[ii])
                                    { jota ="*5"; p=&S11[ii];break;}
else if (En==S12[ii])
                                     { jota ="*6"; p=&S12[ii];break;}
else if (En==S13[ii])
                         { jota ="*7"; p=&S13[ii];break;}
else if (En==S14[ii])
                             { jota ="*8"; p=&S14[ii];break;}


 }

 if (jota=="  ") goto YY;         // If nothing to move in pair jump to move gotes on board , home or end





                                  // FOR PAIR ON END
for (int i=1;i<6;i++)
{if (b[i]==jota)
      {if (i+q==6){pugi=1;}

    if (b[i+q]=="X_" || b[i+q]=="  ")
        {b[i+q]=En;
*p="  ";  break;}// jota arrange krna rehta hai

    else if (b[i+q][0]=='A')
    {    if (array_contains(S1)==0) {S1[0]=b[i+q];S1[1]=En;b[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=b[i+q];S2[1]=En;b[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=b[i+q];S3[1]=En;b[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=b[i+q];S4[1]=En;b[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=b[i+q];S11[1]=En;b[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=b[i+q];S12[1]=En;b[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=b[i+q];S13[1]=En;b[i+q]="*7";}
        else                             {S14[0]=b[i+q];S1[1]=En;b[i+q]="*8";}
*p="  ";
break;

    }
    else if (b[i+q][0]=='*')
        { k=b[i+q];


if      (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else              {S14[first_empty(S14)]=En; }
*p="  ";
break;
        }



}
}



for (int i=0;i<52;i++)         // FOR PAIR ON BOARD
{if (a[i]==jota)
{

    if (i+q>50 && b[i+q-50][0]!='A' && b[i+q-50][0]!='*')  //From board to end
        {if (i+q-50 == 6){pugi=1;} b[i+q-50]=En;
*p="  "; }

       else if (i+q>50 && b[i+q-50][0]=='A') // from board to end if there already a gote
       {if (i+q-50 == 6){pugi=1;}
           if (array_contains(S1)==0) {S1[0]=b[i+q-50];S1[1]=En;b[i+q-50]="*1";}
        else if (array_contains(S2)==0) {S2[0]=b[i+q-50];S2[1]=En;b[i+q-50]="*2";}
        else if (array_contains(S3)==0) {S3[0]=b[i+q-50];S3[1]=En;b[i+q-50]="*3";}
        else if (array_contains(S4)==0) {S4[0]=b[i+q-50];S4[1]=En;b[i+q-50]="*4";}
        else if (array_contains(S11)==0) {S11[0]=b[i+q-50];S11[1]=En;b[i+q-50]="*5";}
        else if (array_contains(S12)==0) {S12[0]=b[i+q-50];S12[1]=En;b[i+q-50]="*6";}
        else if (array_contains(S13)==0) {S13[0]=b[i+q-50];S13[1]=En;b[i+q-50]="*7";}
        else {S1[0]=b[i+q-50];S14[1]=En;b[i+q-50]="*8";}
*p="  ";
break;

       }

        else if (i+q>50 && b[i+q-50][0]=='*')//From board to end if there is a jota
    {if (i+q-50 == 6){pugi=1;}
        k = b[i+q-50];
    if      (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else                   {S14[first_empty(S14)]=En; }
*p="  ";
break;}


     else if (a[i+q]=="__" || a[i+q]=="MM")   //agr dabba khali hai ya cheeta khali hai
        {a[i+q]=En;
*p="  ";break; }




    else if (a[i+q][0]=='A' || i+q==0 || i+q==8 || i+q==13 || i+q==21 || i+q==26 || i+q==34 || i+q==39 || i+q==47)   // agr apni geeti pdi hai ya cheeta  hai to pair me store
{
            if (array_contains(S1)==0) {S1[0]=a[i+q];S1[1]=En;a[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=a[i+q];S2[1]=En;a[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[i+q];S3[1]=En;a[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[i+q];S4[1]=En;a[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[i+q];S11[1]=En;a[i+q]="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[i+q];S12[1]=En;a[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[i+q];S13[1]=En;a[i+q]="*7";}
        else                             {S14[0]=a[i+q];S1[1]=En;a[i+q]="*8";}
*p="  ";
break;}
else if (a[i+q][0]=='*')
{k= a[i+q];

if      (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else                   {S14[first_empty(S14)]=En; }
*p="  ";
break;}

else if (a[i+q][0]=='B')       //singe gote marnay k lye
{ mari=1;bp=1;
         if (a[i+q]=="B1"){B[1]="B1";a[i+q]=En;}
    else if (a[i+q]=="B2"){B[2]="B2";a[i+q]=En;}
    else if (a[i+q]=="B3"){B[3]="B3";a[i+q]=En;}
    else if (a[i+q]=="B4"){B[4]="B4";a[i+q]=En;}
    // jota marna rehta hai abi
*p="  ";
break;}


break;}

}

YY:

    if (jota!="  ") goto ZZ;    // If gote moved in pair so jump to end bcoz nothing more to move




                                       //************* For Gote on End


for (int i=1;i<6;i++)
{if (b[i]==En){if (i+q==6){pugi=1;}

    if (b[i+q]=="X_" || b[i+q]=="  ")
        { b[i+q]=b[i];b[i]="X_";break;}

    else if (b[i+q][0]=='A')
    {
      if (array_contains(S1)==0) {S1[0]=b[i+q];S1[1]=b[i];b[i]="X_";b[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=b[i+q];S2[1]=b[i];b[i]="X_";b[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=b[i+q];S3[1]=b[i];b[i]="X_";b[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=b[i+q];S4[1]=b[i];b[i]="X_";b[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=b[i+q];S11[1]=b[i];b[i]="X_";b[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=b[i+q];S12[1]=b[i];b[i]="X_";b[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=b[i+q];S13[1]=b[i];b[i]="X_";b[i+q]="*7";}
        else                             {S14[0]=b[i+q];S1[1]=b[i];b[i]="X_";b[i+q]="*8";}
break;

    }
    else if (b[i+q][0]=='*')
        {k=b[i+q];


if      (k=="*1") {S1[first_empty(S1)]=b[i];b[i]="X_"; }
else if (k=="*2") {S2[first_empty(S2)]=b[i];b[i]="X_"; }
else if (k=="*3") {S3[first_empty(S3)]=b[i];b[i]="X_"; }
else if (k=="*4") {S4[first_empty(S4)]=b[i];b[i]="X_"; }
else if (k=="*5") {S11[first_empty(S11)]=b[i];b[i]="X_"; }
else if (k=="*6") {S12[first_empty(S12)]=b[i];b[i]="X_"; }
else if (k=="*7") {S13[first_empty(S13)]=b[i];b[i]="X_"; }
else              {S14[first_empty(S14)]=b[i];b[i]="X_"; }
break;
        }



}
}



                                        //**************** For gote on Board

for (int i=0;i<52;i++)
{if (a[i]==En){

    if (i+q>50 && b[i+q-50][0]!='A' && b[i+q-50][0]!='*')  // From board to end
        {if (i+q-50 == 6){pugi=1;}     b[i+q-50]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }

        else if (i+q>50 && b[i+q-50][0]=='*')
    {if (i+q-50 == 6){pugi=1;} k = b[i+q-50];goto NN;}//From board to end if there is a jota

        else if (i+q>50 && b[i+q-50][0]=='A') // from board to end if there is already a gote
        { if (i+q-50 == 6){pugi=1;}
            if (array_contains(S1)==0) {S1[0]=b[i+q-50];S1[1]=En;b[i+q-50]="*1"; if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S2)==0) {S2[0]=b[i+q-50];S2[1]=En;b[i+q-50]="*2";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S3)==0) {S3[0]=b[i+q-50];S3[1]=En;b[i+q-50]="*3";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S4)==0) {S4[0]=b[i+q-50];S4[1]=En;b[i+q-50]="*4";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S11)==0) {S11[0]=b[i+q-50];S11[1]=En;b[i+q-50]="*5";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S12)==0) {S12[0]=b[i+q-50];S12[1]=En;b[i+q-50]="*6";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S13)==0) {S13[0]=b[i+q-50];S13[1]=En;b[i+q-50]="*7";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else {S1[0]=b[i+q-50];S14[1]=En;b[i+q-50]="*8";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}


break;        }

     else if (a[i+q]=="__" || a[i+q]=="MM")   //agr dabba khali hai ya cheeta khali hai
        {a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";break; }




    else if (a[i+q][0]=='A' || i+q==0 || i+q==8 || i+q==13 || i+q==21 || i+q==26 || i+q==34 || i+q==39 || i+q==47)   // agr apni geeti pdi hai ya cheeta  hai to pair me store
{
            if (array_contains(S1)==0) {S1[0]=a[i+q];S1[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=a[i+q];S2[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[i+q];S3[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[i+q];S4[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[i+q];S11[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[i+q];S12[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[i+q];S13[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*7";}
        else                             {S14[0]=a[i+q];S1[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*8";}
break;}
else if (a[i+q][0]=='*')
{k= a[i+q];
NN:
if      (k=="*1") {S1[first_empty(S1)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*2") {S2[first_empty(S2)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*3") {S3[first_empty(S3)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*4") {S4[first_empty(S4)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*5") {S11[first_empty(S11)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*6") {S12[first_empty(S12)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*7") {S13[first_empty(S13)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else                   {S14[first_empty(S14)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
break;}

else if (a[i+q][0]=='B')       //single gote marnay k lye
{ mari=1;bp=1;
         if (a[i+q]=="B1"){B[1]="B1";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[i+q]=="B2"){B[2]="B2";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[i+q]=="B3"){B[3]="B3";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[i+q]=="B4"){B[4]="B4";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    // jota marna rehta hai abi
break;}


}

}




                                      //*****************For Gote in Home



for (int i=1;i<5;i++)
{
    if (A[i]==En && a[0]=="MM") {a[0]=A[i];A[i]="__";break;}      // agr cheeta khali
    else if (A[i]==En && a[0][0]!='*')                      // agr cheetay pe koi geeti hai
        {
            if (array_contains(S1)==0) {S1[0]=a[0];S1[1]=A[i];A[i]="__";a[0]="*1";}  // check here
        else if (array_contains(S2)==0) {S2[0]=a[0];S2[1]=A[i];A[i]="__";a[0]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[0];S3[1]=A[i];A[i]="__";a[0]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[0];S4[1]=A[i];A[i]="__";a[0]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[0];S11[1]=A[i];A[i]="__";a[0]="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[0];S12[1]=A[i];A[i]="__";a[0]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[0];S13[1]=A[i];A[i]="__";a[0]="*7";}
        else                             {S14[0]=a[0];S14[1]=A[i];A[i]="__";a[0]="*8";}
break;}
else if (A[i]==En && a[0][0]=='*')                         // Agr pair hai
{
if (a[0]=="*1") {S1[first_empty(S1)]=A[i];A[i]="__"; }
else if (a[0]=="*2") {S2[first_empty(S2)]=A[i];A[i]="__"; }
else if (a[0]=="*3") {S3[first_empty(S3)]=A[i];A[i]="__"; }
else if (a[0]=="*4") {S4[first_empty(S4)]=A[i];A[i]="__"; }
else if (a[0]=="*5") {S11[first_empty(S11)]=A[i];A[i]="__"; }
else if (a[0]=="*6") {S12[first_empty(S12)]=A[i];A[i]="__"; }
else if (a[0]=="*7") {S13[first_empty(S13)]=A[i];A[i]="__"; }
else {S14[first_empty(S14)]=A[i];A[i]="__"; }
break;}
}


}

if (player==2)
{


                                        //*********  FOR GOTE IN PAIRS


 for (int ii=0;ii<8;ii++)
 {
if (S1[ii]==En)
                                 { jota ="*1"; p=&S1[ii];break;}
else  if (En==S2[ii])
                                 { jota ="*2"; p=&S2[ii];break;}
else if (En==S3[ii])
                            { jota ="*3"; p=&S3[ii];break;}
else if (En==S4[ii])
                             { jota ="*4"; p=&S4[ii];break;}
else if (En==S11[ii])
                                    { jota ="*5"; p=&S11[ii];break;}
else if (En==S12[ii])
                                     { jota ="*6"; p=&S12[ii];break;}
else if (En==S13[ii])
                         { jota ="*7"; p=&S13[ii];break;}
else if (En==S14[ii])
                             { jota ="*8"; p=&S14[ii];break;}


 }

 if (jota=="  ") goto WW;         // If nothing to move in pair jump to move gotes on board , home or end





                                  // FOR PAIR ON END
for (int i=1;i<6;i++)
{if (c[i]==jota)
      {if (i+q==6){pugi=1;}

    if (c[i+q]=="X_" || c[i+q]=="  ")
        {c[i+q]=En;
*p="  ";  break;}

    else if (c[i+q][0]=='B')
    {        if (array_contains(S1)==0) {S1[0]=c[i+q];S1[1]=En;c[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=c[i+q];S2[1]=En;c[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=c[i+q];S3[1]=En;c[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=c[i+q];S4[1]=En;c[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=c[i+q];S11[1]=En;c[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=c[i+q];S12[1]=En;c[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=c[i+q];S13[1]=En;c[i+q]="*7";}
        else                             {S14[0]=c[i+q];S14[1]=En;c[i+q]="*8";}
*p="  ";
break;

    }
    else if (c[i+q][0]=='*')
        { k=c[i+q];


if      (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else              {S14[first_empty(S14)]=En; }
*p="  ";
break;
        }



}
}



for (int i=0;i<52;i++)         // FOR PAIR ON BOARD
{if (a[i]==jota)
{

    if (i+q>24 && i<=24 && c[i+q-24][0]!='B' && c[i+q-24][0]!='*')  //From board to end
        {if (i+q-24 == 6){pugi=1;} c[i+q-24]=En;
*p="  "; }

       else if (i+q>24&& i<=24 && c[i+q-24][0]=='B') // from board to end if there already a gote
       {if (i+q-24 == 6){pugi=1;}
           if (array_contains(S1)==0)   {S1[0]=c[i+q-24];S1[1]=En;c[i+q-24]="*1";}
        else if (array_contains(S2)==0) {S2[0]=c[i+q-24];S2[1]=En;c[i+q-24]="*2";}
        else if (array_contains(S3)==0) {S3[0]=c[i+q-24];S3[1]=En;c[i+q-24]="*3";}
        else if (array_contains(S4)==0) {S4[0]=c[i+q-24];S4[1]=En;c[i+q-24]="*4";}
        else if (array_contains(S11)==0) {S11[0]=c[i+q-24];S11[1]=En;c[i+q-24]="*5";}
        else if (array_contains(S12)==0) {S12[0]=c[i+q-24];S12[1]=En;c[i+q-24]="*6";}
        else if (array_contains(S13)==0) {S13[0]=c[i+q-24];S13[1]=En;c[i+q-24]="*7";}
        else                             {S14[0]=c[i+q-24];S14[1]=En;c[i+q-24]="*8";}
*p="  ";
break;

       }

        else if (i+q>24 && i<=24 && c[i+q-24][0]=='*')//From board to end if there is a jota
    {if (i+q-24 == 6){pugi=1;}
        k = c[i+q-24];
    if   (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else                   {S14[first_empty(S14)]=En; }
*p="  ";
break;}


      else if (i+q>51)             // if array ends
      { int x=i+q-52;
          if (a[x]=="__" || a[x]=="MM")   //agr dabba khali hai ya cheeta khali hai
        {a[x]=En;
*p="  ";break; }




    else if (a[x][0]=='B' || x==0 || x==8 || x==13 || x==21 || x==26 || x==34 || x==39 || x==47)   // agr apni geeti pdi hai ya cheeta  hai to pair me store
{
             if (array_contains(S1)==0) {S1[0]=a[x];S1[1]=En;a[x]="*1";}
        else if (array_contains(S2)==0) {S2[0]=a[x];S2[1]=En;a[x]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[x];S3[1]=En;a[x]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[x];S4[1]=En;a[x]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[x];S11[1]=En;a[x]="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[x];S12[1]=En;a[x]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[x];S13[1]=En;a[x]="*7";}
        else                             {S14[0]=a[x];S1[1]=En;a[x]="*8";}
*p="  ";
break;}
else if (a[x][0]=='*')  // agr jota pda hai
{k= a[x];

if      (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else                   {S14[first_empty(S14)]=En; }
*p="  ";
break;}

else if (a[x][0]=='A')       //singe gote marnay k lye
{ mari=1;bp=1;
         if (a[x]=="A1"){A[1]="A1";a[x]=En;}
    else if (a[x]=="A2"){A[2]="A2";a[x]=En;}
    else if (a[x]=="A3"){A[3]="A3";a[x]=En;}
    else if (a[x]=="A4"){A[4]="A4";a[x]=En;}

*p="  ";
break;}
      }


           else if (i+q<=51){       // if array does not end
      if (a[i+q]=="__" || a[i+q]=="MM")   //agr dabba khali hai ya cheeta khali hai
        {a[i+q]=En;
*p="  ";break; }




    else if (a[i+q][0]=='B' || i+q==0 || i+q==8 || i+q==13 || i+q==21 || i+q==26 || i+q==34 || i+q==39 || i+q==47)   // agr apni geeti pdi hai ya cheeta  hai to pair me store
{
             if (array_contains(S1)==0) {S1[0]=a[i+q];S1[1]=En;a[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=a[i+q];S2[1]=En;a[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[i+q];S3[1]=En;a[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[i+q];S4[1]=En;a[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[i+q];S11[1]=En;a[i+q]="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[i+q];S12[1]=En;a[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[i+q];S13[1]=En;a[i+q]="*7";}
        else                             {S14[0]=a[i+q];S1[1]=En;a[i+q]="*8";}
*p="  ";
break;}
else if (a[i+q][0]=='*')  // agr jota pda hai
{k= a[i+q];

if      (k=="*1") {S1[first_empty(S1)]=En; }
else if (k=="*2") {S2[first_empty(S2)]=En; }
else if (k=="*3") {S3[first_empty(S3)]=En; }
else if (k=="*4") {S4[first_empty(S4)]=En; }
else if (k=="*5") {S11[first_empty(S11)]=En; }
else if (k=="*6") {S12[first_empty(S12)]=En; }
else if (k=="*7") {S13[first_empty(S13)]=En; }
else                   {S14[first_empty(S14)]=En; }
*p="  ";
break;}

else if (a[i+q][0]=='A')       //singe gote marnay k lye
{ mari=1;bp=1;
         if (a[i+q]=="A1"){A[1]="A1";a[i+q]=En;}
    else if (a[i+q]=="A2"){A[2]="A2";a[i+q]=En;}
    else if (a[i+q]=="A3"){A[3]="A3";a[i+q]=En;}
    else if (a[i+q]=="A4"){A[4]="A4";a[i+q]=En;}

*p="  ";
break;}
           }

break;}

}

WW:

    if (jota!="  ") goto ZZ;    // If gote moved in pair so jump to end bcoz nothing more to move









                                       //************* For Gote on End


for (int i=1;i<6;i++)
{if (c[i]==En){if (i+q==6){pugi=1;}

    if (c[i+q]=="X_" || c[i+q]=="  ")
        {c[i+q]=c[i];c[i]="X_";break;}

    else if (c[i+q][0]=='B')
    {
             if (array_contains(S1)==0) {S1[0]=c[i+q];S1[1]=c[i];c[i]="X_";c[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=c[i+q];S2[1]=c[i];c[i]="X_";c[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=c[i+q];S3[1]=c[i];c[i]="X_";c[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=c[i+q];S4[1]=c[i];c[i]="X_";c[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=c[i+q];S11[1]=c[i];c[i]="X_";c[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=c[i+q];S12[1]=c[i];c[i]="X_";c[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=c[i+q];S13[1]=c[i];c[i]="X_";c[i+q]="*7";}
        else                             {S14[0]=c[i+q];S14[1]=c[i];c[i]="X_";c[i+q]="*8";}
break;

    }
    else if (c[i+q][0]=='*')
        {  k=c[i+q];


if      (k=="*1") {S1[first_empty(S1)]=c[i];c[i]="X_"; }
else if (k=="*2") {S2[first_empty(S2)]=c[i];c[i]="X_"; }
else if (k=="*3") {S3[first_empty(S3)]=c[i];c[i]="X_"; }
else if (k=="*4") {S4[first_empty(S4)]=c[i];c[i]="X_"; }
else if (k=="*5") {S11[first_empty(S11)]=c[i];c[i]="X_"; }
else if (k=="*6") {S12[first_empty(S12)]=c[i];c[i]="X_"; }
else if (k=="*7") {S13[first_empty(S13)]=c[i];c[i]="X_"; }
else              {S14[first_empty(S14)]=c[i];c[i]="X_"; }
break;
        }



}
}



                                        //**************** For gote on Board

for (int i=0;i<52;i++)
{if (a[i]==En){

    if (i+q>24 && i<=24 && c[i+q-24][0]!='B' && c[i+q-24][0]!='*')  // From board to end if there is no gote and pair
        {if (i+q-24 == 6){pugi=1;}     c[i+q-24]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }

        else if (i+q>24 && i<=24 && c[i+q-24][0]=='*')    //From board to end if there is a jota                                           //ye rehta hai  NN chk kro
    {if (i+q-24 == 6){pugi=1;} k = c[i+q-50];if      (k=="*1") {S1[first_empty(S1)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*2") {S2[first_empty(S2)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*3") {S3[first_empty(S3)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*4") {S4[first_empty(S4)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*5") {S11[first_empty(S11)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*6") {S12[first_empty(S12)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*7") {S13[first_empty(S13)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else                   {S14[first_empty(S14)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
break;}

        else if (i+q>24 && i<=24 && c[i+q-24][0]=='B') // from board to end if there is already a gote
        { if (i+q-24 == 6){pugi=1;}
            if (array_contains(S1)==0)    {S1[0]=c[i+q-24];S1[1]=En;c[i+q-24]="*1"; if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S2)==0)   {S2[0]=c[i+q-24];S2[1]=En;c[i+q-24]="*2";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S3)==0)   {S3[0]=c[i+q-24];S3[1]=En;c[i+q-24]="*3";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S4)==0)   {S4[0]=c[i+q-24];S4[1]=En;c[i+q-24]="*4";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S11)==0) {S11[0]=c[i+q-24];S11[1]=En;c[i+q-24]="*5";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S12)==0) {S12[0]=c[i+q-24];S12[1]=En;c[i+q-24]="*6";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else if (array_contains(S13)==0) {S13[0]=c[i+q-24];S13[1]=En;c[i+q-24]="*7";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
        else                             {S14[0]=c[i+q-24];S14[1]=En;c[i+q-24]="*8";if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}


break;        }

       else if (i+q>51)
        { int x=i+q-52;
        if (a[x]=="__" || a[x]=="MM")                     //agr dabba khali hai ya cheeta khali hai
        {a[x]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";break; }




    else if (a[x][0]=='B' || x==0 || x==8 || x==13 || x==21 || x==26 || x==34 || x==39 || x==47)   // agr apni geeti pdi hai ya cheeta  hai to pair me store
{
            if (array_contains(S1)==0) {S1[0]=a[x];S1[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=a[x];S2[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[x];S3[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[x];S4[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[x];S11[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[x];S12[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[x];S13[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*7";}
        else                             {S14[0]=a[x];S1[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*8";}
break;}
else if (a[x][0]=='*')
{k= a[i+q];
MM:
if      (k=="*1") {S1[first_empty(S1)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*2") {S2[first_empty(S2)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*3") {S3[first_empty(S3)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*4") {S4[first_empty(S4)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*5") {S11[first_empty(S11)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*6") {S12[first_empty(S12)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*7") {S13[first_empty(S13)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else                   {S14[first_empty(S14)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
break;}

else if (a[x][0]=='A')       //single gote marnay k lye
{ mari=1;bp=1;
         if (a[x]=="A1"){A[1]="A1";a[x]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[x]=="A2"){A[2]="A2";a[x]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[x]=="A3"){A[3]="A3";a[x]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[x]=="A4"){A[4]="A4";a[x]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    // jota marna rehta hai abi
break;}


}  // yaha tak change kernay hain uus k bad else if me agla sara code daalna hai

    else if (i+q<=51)
{


     if (a[i+q]=="__" || a[i+q]=="MM")                     //agr dabba khali hai ya cheeta khali hai
        {a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";break; }




    else if (a[i+q][0]=='B' || i+q==0 || i+q==8 || i+q==13 || i+q==21 || i+q==26 || i+q==34 || i+q==39 || i+q==47)   // agr apni geeti pdi hai ya cheeta  hai to pair me store
{
            if (array_contains(S1)==0) {S1[0]=a[i+q];S1[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*1";}
        else if (array_contains(S2)==0) {S2[0]=a[i+q];S2[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[i+q];S3[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[i+q];S4[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[i+q];S11[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]=="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[i+q];S12[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[i+q];S13[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*7";}
        else                             {S14[0]=a[i+q];S1[1]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";a[i+q]="*8";}
break;}
else if (a[i+q][0]=='*')
{k= a[i+q];
//MM:
if      (k=="*1") {S1[first_empty(S1)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*2") {S2[first_empty(S2)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*3") {S3[first_empty(S3)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*4") {S4[first_empty(S4)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*5") {S11[first_empty(S11)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*6") {S12[first_empty(S12)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else if (k=="*7") {S13[first_empty(S13)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
else                   {S14[first_empty(S14)]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__"; }
break;}

else if (a[i+q][0]=='A')       //single gote marnay k lye
{ mari=1;bp=1;
         if (a[i+q]=="A1"){A[1]="A1";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[i+q]=="A2"){A[2]="A2";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[i+q]=="A3"){A[3]="A3";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    else if (a[i+q]=="A4"){A[4]="A4";a[i+q]=a[i];if (i==0 || i==8 || i==13 || i==21 || i==26 || i==34 || i==39 || i==47) a[i]="MM"; else a[i]="__";}
    // jota marna rehta hai abi
break;}
}

}

}

                                      //*****************For Gote in Home



for (int i=1;i<5;i++)
{
    if (B[i]==En && a[26]=="MM") {a[26]=B[i];B[i]="__";break;}      // agr cheeta khali

    else if (B[i]==En && a[26][0]!='*')                      // agr cheetay pe koi geeti hai
        {
            if (array_contains(S1)==0) {S1[0]=a[26];S1[1]=B[i];B[i]="__";a[26]="*1";}  // check here   yahaaan
        else if (array_contains(S2)==0) {S2[0]=a[26];S2[1]=B[i];B[i]="__";a[26]="*2";}
        else if (array_contains(S3)==0) {S3[0]=a[26];S3[1]=B[i];B[i]="__";a[26]="*3";}
        else if (array_contains(S4)==0) {S4[0]=a[26];S4[1]=B[i];B[i]="__";a[26]="*4";}
        else if (array_contains(S11)==0) {S11[0]=a[26];S11[1]=B[i];B[i]="__";a[26]="*5";}
        else if (array_contains(S12)==0) {S12[0]=a[26];S12[1]=B[i];B[i]="__";a[26]="*6";}
        else if (array_contains(S13)==0) {S13[0]=a[26];S13[1]=B[i];B[i]="__";a[26]="*7";}
        else                             {S14[0]=a[26];S14[1]=B[i];B[i]="__";a[26]="*8";}
break;}
else if (B[i]==En && a[26][0]=='*')                         // Agr pair hai
{
if      (a[26]=="*1")  {S1[first_empty(S1)]=B[i];B[i]="__"; }
else if (a[26]=="*2")  {S2[first_empty(S2)]=B[i];B[i]="__"; }
else if (a[26]=="*3")  {S3[first_empty(S3)]=B[i];B[i]="__"; }
else if (a[26]=="*4")  {S4[first_empty(S4)]=B[i];B[i]="__"; }
else if (a[26]=="*5") {S11[first_empty(S11)]=B[i];B[i]="__"; }
else if (a[26]=="*6") {S12[first_empty(S12)]=B[i];B[i]="__"; }
else if (a[26]=="*7") {S13[first_empty(S13)]=B[i];B[i]="__"; }
else                  {S14[first_empty(S14)]=B[i];B[i]="__"; }
break;}
}






}

ZZ:



                                  //******************** PAIR ARRAYS UPDATE

if (jota!="  ")
    {// agr 3 thay or 2 reh gaye
    int nn=1;string aa = *(p+nn);
    while ( aa[0]=='A' || aa[0]=='B')
    {
        nn++;aa = *(p+nn);}

for (int i =0;i<=nn;i++)
{
    *(p+i)=*(p+i+1);
}
*(p+nn)="  ";
    }



                                                   // replacing the pair with only element of pair array

if (array_contains(S1)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*1") {a[ii]=S1[0];S1[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*1"){b[ii]=S1[0];S1[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*1"){c[ii]=S1[0];S1[0]="  ";}}}
if (array_contains(S2)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*2") {a[ii]=S2[0];S2[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*2"){b[ii]=S2[0];S2[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*2"){c[ii]=S2[0];S2[0]="  ";}}}
if (array_contains(S3)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*3") {a[ii]=S3[0];S3[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*3"){b[ii]=S3[0];S3[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*3"){c[ii]=S3[0];S3[0]="  ";}}}
if (array_contains(S4)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*4") {a[ii]=S4[0];S4[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*4"){b[ii]=S4[0];S4[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*4"){c[ii]=S4[0];S4[0]="  ";}}}
if (array_contains(S11)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*5") {a[ii]=S11[0];S11[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*5"){b[ii]=S11[0];S11[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*5"){c[ii]=S11[0];S11[0]="  ";}}}
if (array_contains(S12)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*6") {a[ii]=S12[0];S12[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*6"){b[ii]=S12[0];S12[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*6"){c[ii]=S12[0];S12[0]="  ";}}}
if (array_contains(S13)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*7") {a[ii]=S13[0];S13[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*7"){b[ii]=S13[0];S13[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*7"){c[ii]=S13[0];S13[0]="  ";}}}
if (array_contains(S14)==1)
    {for (int ii=0;ii<52;ii++){if (a[ii]=="*8") {a[ii]=S14[0];S14[0]="  ";}} for (int ii=1;ii<7;ii++){if (b[ii]=="*8"){b[ii]=S14[0];S14[0]="  ";}}for (int ii=1;ii<7;ii++){if (c[ii]=="*8"){c[ii]=S14[0];S14[0]="  ";}}}


}

