/*************************************************
Aufgabe Nr./Task No.: H1
Nachname/Last,Family Name: Elsayed
Vorname/First,Given Name: Mohamed Ahmed Hamed Mohamed
Matrikelnummer/Matriculation number: 3056145
Uni-Email: mohamed.ahmed-hamed-mohamed-elsayed@stud.uni-due.de
Studiengang/Course of Studies: ISE software CE
*************************************************/
#include <iostream>
#include <iomanip>

using namespace std;


const int m = 8;
int act = 0;

enum typePhoneNumber{home , work, fax, mobile, other};

struct contacts
{
    string phoneNumber;
    string name;
    typePhoneNumber type;
};
contacts contact[m];

bool myfunction()
{
    char s;
    cout<< "pleas enter the number: " ;
    cin>> contact[act].phoneNumber;
    cout<< "pleas enter the name: ";
    cin.sync();
    getline(cin, contact[act].name);
    cout<< "type of number(h for home,  w for work, f for fax, m for mobile, o for other):" ;
    cin>>s;
 switch (s)
        {
            case 'f': contact[act].type=fax;
                      break;
            case 'h': contact[act].type=home;
                      break;
            case 'm': contact[act].type=mobile;
                      break;
            case 'w': contact[act].type=work;
                      break;
            case 'o': contact[act].type=other;
                      break;

            default:  cout << "sorry wrong choice" << endl;
        }
    act ++;
    cout<<"contact stored"<<endl;
    return (act != m);
    }

bool deleted()
{
    string x;
    int d=act;
    cout<< "pleas enter the name: ";
    cin.sync();
    getline(cin, x);
    for(int i=0 ; i<m ; i++)
    {
        if(contact[i].name==x)
        {
            for(int s=i ; s<m; s++)
            {
        contact[s] = contact[s+1];
            }
        act--;
        cout<<"contact was deleted"<<endl;
        }
    }if(d==act)
    {
        cout << "sorry contact not found" << endl;
    }
}

void printall()
{

    for(int i=0; i< act; i++)
    {
            string x;
        int s = contact[i].type;
        if(s==0)
            x="(home)";
        if(s==1)
            x="(work)";
        if(s==2)
            x="(fax)";
        if(s==3)
            x="(mobile)";
        if(s==4)
            x="(other)";

        cout<< setw(20) <<left<<contact[i].name<< setw(20) << left<< contact[i].phoneNumber<< setw(20) << left<< x<<endl;
    }
}


int main(void)
{
	char choice;

	do
    {
        cout <<"*** "<<act<<" contact entries ***" << endl
             << "0  end" << endl
             << "1  new contact" << endl
             << "2  delete contact" << endl
             << "3  show all contacts" << endl
             << "9  empty contact memory" << endl;
        cin >> choice;
        switch (choice)
        {
            case '0': break;
            case '1': myfunction();
                      break;
            case '2': deleted();
                      break;
            case '3': printall();
                      break;
            case '9': act=0;
                      cout << "all contacts deleted" << endl;
                      break;
            default:  cout << "sorry wrong choice" << endl;
        }
    } while(choice != '0');

    return 0;
}
