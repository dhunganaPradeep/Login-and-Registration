#include<iostream>
// #include<windows.h>
using namespace std;

class UserInterface{
  public:
    void borderBox(string text,int paddingRL = 0, int paddingTB = 0, int coolBorder = false){
      int strlen = text.size();
      paddingRL += 1;
      int border = coolBorder == true?186:179;
      int row = (strlen + 2*paddingRL);
      cout << endl;

      // Top Border
      cout << char(218);      
      for(int i=0; i<row; i++){cout << char(196);}      
      cout << char(191) << endl;

      // Middle Sections
      for(int i=0; i<paddingTB; i++) { 
        cout << char(border);
        for(int j=0; j<row; j++){
          cout<<" ";
        }
        cout << char(border) << endl;
      }

      // Text Parts
      cout << char(border) ;
      for(int i=0; i<=row; i++){
        cout << " ";
        if(i == paddingRL - 1){ // Left Padding
          cout<<text;
          i = row - paddingRL;
        }
      }cout << char(border) << endl;

      // Middle Sections
      for(int i=0; i<paddingTB; i++) {
       cout << char(border);
        for(int j=0; j<row; j++){
          cout<<" ";
        }
        cout << char(border) << endl;
      }

      // Bottom Border
      cout << char(192);  // Left Corner    
      for(int i=0; i<row; i++){cout << char(196);}      
      cout << char(217) << endl;
    }      
};