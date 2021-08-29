/*************************************************
Aufgabe Nr./Task No.:                   H3
Nachname/Last,Family Name:              Elsayed
Vorname/First,Given Name:               Mohamed Ahmed Hamed Mohamed
Matrikelnummer/Matriculation number:    3056145
Uni-Email:                              mohamed.ahmed-hamed-mohamed-elsayed@stud.uni-due.de
Studiengang/Course of Studies:          ISE software CE
*************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct icd{
string code , diagnosis;
icd *next;
};

icd *head = nullptr;

void readCSVfile()
{
   string code,diagnosis;

   string fileName = "E:\\OOP\\Section111ValidICD10-2018.csv";
   char c,separator = ';';
   ifstream inFile;
   inFile.open(fileName);
   if (!inFile.is_open())
      cerr << "error opening file \"" << fileName << '\"' << endl;
   else
   {
      cout << "input file \"" << fileName << "\" opened..." << endl;
      while ((c = inFile.get()) != EOF)
      {
         code = "";
         while (c != separator)
         {
            code = code + c;
            c = inFile.get();
         }
         c = inFile.get();
         diagnosis = "";
         while ((c != EOF) && (c != '\n') && (c != separator))
         {
            diagnosis = diagnosis + c;
            c = inFile.get();
         }
         c = inFile.get();
         if(code == "CODE")
         {
             continue;
         }else{
         icd *newIcd = new icd;
        newIcd->code = code;
        newIcd->diagnosis = diagnosis;
        newIcd->next = head;
        head = newIcd;
         }
      }
      inFile.close();
      cout << "input file closed" << endl;
   }
}

void toUpper(basic_string<char>& s) {
   for (basic_string<char>::iterator p = s.begin();
        p != s.end(); ++p) {
      *p = toupper(*p);
   }
}

void printall(icd *x,string y, int z){ // z = 1 for code & 2 for diagnosis
    icd *iterator = x;
    string a,b;
    b = y;
    int i = 0;
    toUpper(y);
    if(z == 1){
        while (iterator != nullptr)
        {
	    a = iterator->code;
	    if(a.find(y) != std::string::npos){
		cout << iterator->code << "\t" << iterator->diagnosis <<endl;
		i++;
	    }
		iterator = iterator->next;
        }
}
    if(z == 2){
        while (iterator != nullptr)
        {
            a = iterator->diagnosis;
            toUpper(a);
            if(a.find(y) != std::string::npos){
            cout << iterator->code << "\t" << iterator->diagnosis <<endl;
            i++;
            }
            iterator = iterator->next;
        }
    }
    if(i == 1){
        cout<<"One entry found"<<endl<<endl;
        }else if(i == 0){
        cout<<"\""<<b<<"\""<<" not found"<<endl<<endl;
        }else{
        cout<<i<<" entries found"<<endl<<endl;
        }
}


int main()
{
    readCSVfile();
    char c;
    string c1;
    cout<<"World Health Institution (WHO)"<<endl;
    cout<<"International Classification of Diseases (ICD)"<<endl;
    do{
    cout<<"0 end"<<endl
        <<"1 search for ICD code(s) (e.g G4453)"<<endl
        <<"2 search for diagnosis(s (e.g angina, Ebola, horse, Malaria, Wheelchair)"<<endl
        <<">> ";
    cin>>c;
    switch (c)
    {
        case '0': break;
        case '1': cout<<"to search for ICD code: ";
                  cin>>c1;
                  printall(head, c1, 1);
                  break;
        case '2': cout<<"to search for diagnosis: ";
                  cin>>c1;
                  printall(head, c1, 2);
                  break;
        }
    }while(c != '0');
    return 0;
}
