/*************************************************
Aufgabe Nr./Task No.:                   H4
Nachname/Last,Family Name:              Elsayed
Vorname/First,Given Name:               Mohamed Ahmed Hamed Mohamed
Matrikelnummer/Matriculation number:    3056145
Uni-Email:                              mohamed.ahmed-hamed-mohamed-elsayed@stud.uni-due.de
Studiengang/Course of Studies:          ISE software CE
*************************************************/


#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Time
{
private:
    int minuteOfDay;
public:
    Time(unsigned int a = 0)
    {
        if(a < 1440)
        minuteOfDay = a;
    }

    Time(int hour , int minute)
    {
        set_time(hour, minute);
    }

    void set_time(int h , int m)
    {
        if (h < 24 && m < 60)
        {
            minuteOfDay = (h*60)+m;
        }else{
            minuteOfDay = 0;
        cout<<"Error message"<<endl;
        }
    }

    int get_hour()
    {
       return minuteOfDay/60;
    }

    int get_minute()
    {
        return minuteOfDay%60;
    }

    int get_minuteOfDay()
    {
        return minuteOfDay;
    }

    Time operator + (unsigned int a)
    {
        Time n;
        n.minuteOfDay = minuteOfDay + a;
        if(n.minuteOfDay > 1439)
            n.minuteOfDay = n.minuteOfDay - 1440;
            return n;
    }
};

class Train
{
private:
    string no,to,over;
public:
    Train(string, string, string);
    ~Train();
    string get_no();
    string get_to();
    string get_over();
};
istream &operator >> (istream &input,Time &p)
{
    char c;
    int h,m;
input>>h>>c>>m;
p.set_time(h,m);
}

ostream &operator << (ostream &output,Time &p)
{
output<< setw(2) <<right<< setfill('0') <<p.get_hour()<<':'<< setw(2) <<right<< setfill('0') <<p.get_minute();
        return output;
}


class Station
{
private:
    const string station;
    static const unsigned int platforms = 15;
    Train *schedule[1440][platforms];
public:
    Station(string a) : station(a)
    {
        for (unsigned int k = 0; k < 1440; k++)
        {
            for (unsigned int f = 0; f < platforms; f++)
            schedule[k][f] = nullptr;
        }
    }

    ~Station()
    {
        Time j;
        for (int x = 0; x < 1440; x++)
        {
            for (unsigned int f = 0; f < platforms; f++)
            {
                if(schedule[x][f] != nullptr )
                {
                    j = x+1;
                cout<<j<<"  "<<"platform "<<f+1<<":"<<" Train "<<schedule[x][f]->get_no()<<" to "<<schedule[x][f]->get_to()<<" deleted"<<endl;
                delete schedule;
                }
            }
        }
        cout<<"schedule for DUISBURG MAIN TRAIN STATION completely deleted"<<endl;
    }

    void addDeparture(int t ,int p,Train *train)
    {
        schedule[t-1][p-1] = train;
    }

    void showDepartures(Time time, unsigned int m)
    {
        Time q = time+m;
        Time k = (time.get_minuteOfDay()) - 1;
        Time y = k + m;
        int x = k.get_minuteOfDay();
        int z = y.get_minuteOfDay();
        cout<<"DUISBURG MAIN TRAIN STATION"<<endl;
        cout<<"DEPARTURES "<<time<<'-'<<q<<endl;
        cout<<"================="<<endl;
        cout<<"Time"<<setw(10)<<setfill(' ')<<"Train"<<setw(15)<<setfill(' ')<<"Over"<<setw(52)<<setfill(' ')<<"To"<<setw(27)<<setfill(' ')<<"Platform"<<endl;
        if(x<z){
            for (x; x <= z; x++)
            {
                for (unsigned int f = 0; f < platforms; f++)
                {
                    if(schedule[x][f] != nullptr )
                    {
                        q = x+1;
                    cout<<q<<"    ";
                    cout<<setw(16)<<left<<setfill(' ')<<schedule[x][f]->get_no()<<setw(54)<<setfill(' ')<<schedule[x][f]->get_over()<<setw(21)<<setfill(' ')<<schedule[x][f]->get_to()<<setw(10)<<setfill(' ')<<f+1<<endl;
                    }
                }
            }
        }else{
            for (x; x <= 1439; x++)
            {
                for (unsigned int f = 0; f < platforms; f++)
                {
                    if(schedule[x][f] != nullptr )
                    {
                        q = x+1;
                    cout<<q<<"    ";
                    cout<<setw(16)<<left<<setfill(' ')<<schedule[x][f]->get_no()<<setw(54)<<setfill(' ')<<schedule[x][f]->get_over()<<setw(21)<<setfill(' ')<<schedule[x][f]->get_to()<<setw(10)<<setfill(' ')<<f+1<<endl;
                    }
                }
            }
            for (x = 0; x <= z; x++)
            {
                for (unsigned int f = 0; f < platforms; f++)
                {
                    if(schedule[x][f] != nullptr )
                    {
                        q = x+1;
                    cout<<q<<"    ";
                    cout<<setw(16)<<left<<setfill(' ')<<schedule[x][f]->get_no()<<setw(54)<<setfill(' ')<<schedule[x][f]->get_over()<<setw(21)<<setfill(' ')<<schedule[x][f]->get_to()<<setw(10)<<setfill(' ')<<f+1<<endl;
                    }
                }
            }
        }
    }
};

Train::Train(string n, string t, string o) : no(n), to(t), over(o) {}

Train::~Train(){
cout<<no<<" "<<to<<" "<<over<<" Deleted"<<endl;
}

string Train::get_no(){
    return no;
}

string Train::get_to(){
    return to;
}

string Train::get_over(){
    return over;
}





int main()
{
  Station duisburg("DUISBURG MAIN TRAIN STATION");
  Train *s1 = new Train("S1","Dortmund Hbf","Muelheim(Ruhr)Styrum - Muelheim(Ruhr) - Essen");
  Train *s_1 = new Train("S1","Solingen Hbf","Duisburg-Schlenk - Duesseldorf Flughafen");
  Train *s2 = new Train("S2","Dortmund Hbf","Oberhausen - Gelsenkirchen - Wanne-Eickel");
  Train *re1 = new Train("RE1","Aachen Hbf","Duesseldorf Flughafen - Duesseldorf - Koeln");
  Train *re2 = new Train("RE2","Muenster Hbf","Muelheim(Ruhr) - Essen - Gelsenkirchen");

     for(int i = 7; i<1440 ; i+=20)
        {
            duisburg.addDeparture(i, 9, s1 );
        }
     for(int i = 15; i<1440 ; i+=20)
        {
            duisburg.addDeparture(i, 5, s_1 );
        }

     for(int i = 35; i<1440 ; i+=60)
        {
            duisburg.addDeparture(i, 2, s2 );
        }

     for(int i = 22; i<1440 ; i+=60)
        {
            duisburg.addDeparture(i, 4, re1 );
        }

     for(int i = 24; i<1440 ; i+=60)
        {
            duisburg.addDeparture(i, 10, re2 );
        }
//Time x(1,30);
//duisburg.showDepartures(x, 30);

Time a1,a2;
int m1,m2,x;
string a,b,d;
char c;
do{
    cout<<"0 end"<<endl
        <<"1 schedule train"<<endl
        <<"2 show schedule"<<endl
        <<">> ";
    cin>>c;
    switch (c)
    {
        case '0': {break;}

        case '1': {cout<<"time of departure? ";
                  cin>>a2;
                  cout<<"platform? ";
                  cin>>m2;
                  cout<<"train? ";
                  cin>>a;
                  cout<<"to? ";
                  cin>>b;
                  cout<<"over? ";
                  cin.sync();
                  getline(cin,d);
                  Train *n = new Train(a,b,d);
                  x = a2.get_minuteOfDay();
                  duisburg.addDeparture(x, m2, n);
                  break;}

        case '2': {cout<<"show departures starting at? ";
                  cin>>a1;
                  cout<<"for how many next minutes? ";
                  cin>>m1;
                  duisburg.showDepartures(a1,m1);
                  break;}
        default:  {cout << "sorry wrong choice" << endl;}
    }
}while(c != '0');















   /* Time x(2, 30);
    cout<<x;
    Time y;
    y = x + 15;
    cout<<y;
     Time z;
    cout<<"enter the time"<<endl;
    cin>>z;
    cout<<z;
    Train a("s1","bochum","essen");
    cout<<a.get_no()<<" "<<a.get_to()<<" "<<a.get_over()<<endl;
    Train *a = new Train("s1","bochum","essen");
    Train *b = new Train("re11","koln","dortmund");
    Station w("Bochum HBF");
    w.addDeparture(95,1,a);
    w.addDeparture(95,2,b);
    w.addDeparture(95,3,a);
    w.addDeparture(95,4,b);
    w.addDeparture(95,14,b);
    //w.print();
    Time x(1, 30);
    w.showDepartures(x,15);
    */
    return 0;
}
