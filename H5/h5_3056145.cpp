/*************************************************
Aufgabe Nr./Task No.:                   H5
Nachname/Last,Family Name:              Elsayed
Vorname/First,Given Name:               Mohamed Ahmed Hamed Mohamed
Matrikelnummer/Matriculation number:    3056145
Uni-Email:                              mohamed.ahmed-hamed-mohamed-elsayed@stud.uni-due.de
Studiengang/Course of Studies:          ISE software CE
*************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

class Date {
private:
    short unsigned int day, month, year;
public:
    Date(int a = 0, int b = 0, int c = 0) : day(a), month(b), year(c){}
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    Date operator + (int n)
    {
        day += n;
        while(day > daysInMonth[month-1])
            {
              day -= (daysInMonth[month-1]);
              if(month < 12)
                  {
                    month ++;
                  }
                else
                    {
                     month = 1;
                     year++;
                    }
            }
            Date e(day,month,year);
            return e;
    }

friend istream &operator >> (istream &input,Date &p)
    {
        char c,d;
        int q,w,e;
        input>>q>>c>>w>>d>>e;
        p.day=q;
        p.month=w;
        p.year=e;
        return input;
    }

friend ostream &operator << (ostream &output,Date &p)
    {
        output << setw(2) << setfill('0')<<  p.day << '.' << setw(2) << setfill('0')<< p.month << '.' << p.year;
        return output;
    }

};

enum Board { allInclusive = 'a', breakfast = 'b', halfBoard = 'h', noMeals = 'w'};
inline std::ostream & operator<<(std::ostream & Str, Board V) {
  switch (V) {
  case noMeals: return Str << "no meals";
  case breakfast: return Str << "with breakfast";
  case halfBoard: return Str << "half board";
  case allInclusive: return Str << "all inclusive";
  default: return Str << (int) V;
    }
}

class Hotel{
private:
    string name;
    Date arrival;
    int nights, singles, doubles;
    Board board;
    double priceNightSingle, priceNightDouble;
    bool parking;

public:
    Hotel(string name, Date date, int nights, int singles, int doubles, Board board, double priceNightSingle, double priceNightDouble, bool parking) : name(name), arrival(date), nights(nights),
           singles(singles), doubles(doubles), board(board), priceNightSingle(priceNightSingle), priceNightDouble(priceNightDouble), parking(parking) {}

    ~Hotel(){
        cout<<"destructor hotel "<<name<<" at "<<arrival<<" for "<<get_guests()<<" guests done"<<endl;
    }

    double get_price(){
        double total;
        total = (nights*singles*priceNightSingle) + (nights*doubles*priceNightDouble);
        if(parking == true)
        {
            total += (10*nights);
        }
        return total;
    }

    Date get_arrival(){
        return arrival;
    }

    Date get_checkout(){
        Date g = arrival;
        g = g+nights;
        return g;
    }

    int get_guests(){
        return (singles*1)+(doubles*2);
    }

    void print(){
        cout<<"check-in:            hotel "<<arrival<<" "<<name<<" for "<<nights<<" night(s) ";
        if(doubles > 0)
            cout<< doubles << " double bed room(s) ";
        if(singles > 0)
            cout<<singles<<" single bed room(s) ";
        cout <<endl;
        cout<<"                     "<<board;
        if(parking == true)
            cout<<", Parking included"<<endl;
        else
            cout<<endl;
    }
};

class Transport{
public:
    virtual ~Transport(){
        cout<<"destructor Transport done"<<endl;
    };
    virtual bool withTransfer()=0;
    virtual double get_price()=0;
    virtual void print()=0;
};

class SelfOrganised : public Transport {
public:
    SelfOrganised(){}
    virtual ~SelfOrganised(){
        cout<<"destructor SelfOrganised done"<<endl;
    }
    virtual bool withTransfer(){
        return false;
    }
    virtual double get_price(){
        return 0.00;
    }
    virtual void print(){
        cout<<"self organised transport"<<endl;
    }
};

class PublicTransport : public Transport {
private:
    Date departure;
    string code, from, to;
    double priceOneSeat;
    bool firstClass;
    friend class Flight;
    friend class Train;
public:
    PublicTransport(Date departure, string code, string from, string to, double priceOneSeat, bool firstClass = false) : departure(departure), code(code), from(from), to(to)
                    , priceOneSeat(priceOneSeat), firstClass(firstClass){}
    virtual ~PublicTransport(){
        cout<<"destructor PublicTransport "<<code<<" at "<<departure<<" done"<<endl;
    }
    virtual void print(){
        cout<<departure<<" "<<code<<" from "<<from<<" to "<<to;
        if(firstClass == true)
            cout<<" first class"<<endl;
        else
            cout<<endl;
    }
};

class Flight : public PublicTransport{
private:
    bool transfer;

public:
    Flight(Date departure, string code, string from, string to, double priceOneSeat, bool f = false, bool g = true) : PublicTransport(departure,code,from,to,priceOneSeat,firstClass),
    transfer(g) {}
    virtual ~Flight(){
        cout<<"destructor Flight done"<<endl;
    }
    virtual bool withTransfer(){
        return transfer;
    }
    virtual double get_price(){
        if(firstClass == true)
            return priceOneSeat*2;
        else
            return priceOneSeat;
    }
    virtual void print(){
        cout<<"flight ";
        PublicTransport::print();
    }
};

class Train : public PublicTransport{
public:
    Train(Date departure, string code, string from, string to, double priceOneSeat, bool f = false) : PublicTransport(departure,code,from,to,priceOneSeat,firstClass){}
    virtual ~Train(){
        cout<<"destructor Train done"<<endl;
    }
    virtual bool withTransfer(){
        return false;
    }
    virtual double get_price(){
        if(firstClass == true)
            return priceOneSeat*1.5;
        else
            return priceOneSeat;
    }
    virtual void print(){
        cout<<"train ";
        PublicTransport::print();
    }
};

class Trip{
private:
    const unsigned int no ;
    static unsigned int lastNo;
    unsigned int travellers;
    Hotel *hotel;
    Transport *transportOutward;
    Transport *transportBack;
    Trip *next;

public:
    Trip(int travellers, Hotel *hotel, Transport *transportOutward, Transport *transportBack, Trip *next = nullptr) : travellers(travellers), hotel(hotel), transportOutward(transportOutward),
         transportBack(transportBack), next(next),no((lastNo++)){}
    virtual ~Trip(){
    delete hotel;
    delete transportOutward;
    delete transportBack;
    cout<<"destructor Trip done"<<endl;
    }
    int get_no(){
        return no;
    }
    Trip* get_next(){
        return next;
    }
    Trip* set_next(Trip *a){
        next = a;
    }
    double get_price(){
       return (hotel->get_price())+(transportOutward->get_price()*hotel->get_guests())+(transportBack->get_price()*hotel->get_guests());
    }
    void print(){
        cout<<"trip inquiry "<<no+1<<" for "<<travellers<<" person(s)"<<endl;
        hotel->print();
        cout <<"outward journey:     ";
        transportOutward->print();
        cout<<"journey back:        ";
        transportBack->print();

        if(transportOutward->withTransfer() == true || transportBack->withTransfer() == true)
            cout<<"with transfer"<<endl;
            else
            cout<<"no transfer"<<endl;
        cout<<"         price: "<<get_price()<<" EUR"<<endl;
    }
};


class TravelAgency{
private:
    Trip *trips;

public:
    TravelAgency(){trips = nullptr ;};
    void add(Trip *a){
        if ( trips == nullptr)
        {
            trips = a;
            trips->set_next(nullptr);
        }
        else{
        Trip *newtrip = a;
        newtrip->set_next(trips);
        trips = newtrip;
        }
    }
    void remove(Trip* a){
    if (trips != nullptr)
	{
        if (trips == a)
        {
            Trip *toDelete = trips;
            trips = trips->get_next();
            delete toDelete;
        }
        else
        {
            Trip *iterator = trips->get_next(), *previous = trips;
            while (iterator != nullptr)
            {
                if (iterator == a)
                {
                    previous->set_next(iterator->get_next());
                    delete iterator;
                }
                previous = iterator;
                iterator = iterator->get_next();

            }
        }
	}
    }
    Trip *search(int a){
        Trip *c = trips;
        if (c->get_no() == a)
            {
                return c;
            }
        else if(c->get_next() != nullptr)
        {
            Trip *iterator = c->get_next(), *previous = c;
            while (iterator != nullptr)
            {
                if (iterator->get_no() == a)
                {
                    return iterator;
                }
                previous = iterator;
                iterator = iterator->get_next();
            }
        }
        Trip *iterator = trips;
        bool notfound;
            while (iterator != nullptr)
            {
                if(iterator->get_no() == a)
                    notfound = false;
                iterator = iterator->get_next();
            }
            if(notfound == true)
        {
            return nullptr;
        }
	}

    void printAllTrips(){
        Trip *iterator = trips;
            while (iterator != nullptr)
            {
                iterator->print();
                iterator = iterator->get_next();
            }
    }
};
unsigned int Trip::lastNo = 0;
int main()
{
    char choice, food, parking, deletetrip, transporttypeo, transporttypeb;
	string hotelname, traincode, mainstationdeparture, mainstationarrival, flightcode, airportdeparture, airportarrival;
	Date arrivaldate;
	int nonights, nosingleroom, nodoubleroom, notrip;
	double pricenightsingleroom, pricenightdoubleroom, pricepassengertrain, pricepassengerflight;
	Board foodenum;
	bool parkingbool;
	Train *td;
	Flight *fd;
	SelfOrganised *so, *sb;
	Transport *out, *backw;
    TravelAgency travela;
	do
    {
        cout << "HOTLINE TRAVEL AGENCY" << endl
             << "0 end" << endl
             << "1 new trip" << endl
             << "2 search trip" << endl
             << "3 show all trip offers" << endl
             <<"your choice: ";
        cin >> choice;
        switch (choice)
        {
            case '0':   break;
            case '1':  { cout <<"name of hotel: ";
                        cin.sync();
                        getline(cin,hotelname);
                        cout << "arrival on : ";
                        cin >> arrivaldate;
                        cout << "how many nights: ";
                        cin >> nonights;
                        cout << "how many single bed rooms: ";
                        cin >>nosingleroom;
                        cout << "how many double bed rooms: ";
                        cin >> nodoubleroom;
                        cout << "a all inclusive"<<endl
                             << "b breakfast"<<endl
                             << "h halfboard"<<endl
                             << "w without meals"<<endl;
                        cin >> food;
                        foodenum = (Board) food;
                        cout << "price one night in single bed room: ";
                        cin >> pricenightsingleroom;
                        cout << "price one night in double bed room: ";
                        cin >> pricenightdoubleroom;
                        cout << "with parking((y)es or (n)o): ";
                        cin >> parking;
                        if(parking == 'y' || parking == 'Y')
                            parkingbool = true;
                        else if(parking == 'n' || parking == 'N')
                            parkingbool = false;

                        Hotel *h = new Hotel(hotelname, arrivaldate, nonights, nosingleroom, nodoubleroom, foodenum, pricenightsingleroom, pricenightdoubleroom, parkingbool);
                        cout << "please choose transport for outward journey"<<endl
                             << "0 self organised"<<endl
                             << "1 by flight"<<endl
                             << "2 by train"<<endl
                             << "your choice: ";
                        cin >> transporttypeo;
                        switch(transporttypeo){
                            case '0' : {SelfOrganised *so = new SelfOrganised;
                                        out = so;
                                        break;
                                        }
                            case '2' :
                                        {
                                        cout << "code of train: ";
                                        cin.sync();
                                        getline(cin,traincode);
                                        cout << "main train station of departure: ";
                                        cin.sync();
                                        getline(cin,mainstationdeparture);
                                        cout << "main train station of arrival: ";
                                        cin.sync();
                                        getline(cin,mainstationarrival);
                                        cout << "price for one passenger: ";
                                        cin >> pricepassengertrain;
                                        Train *td= new Train(arrivaldate,traincode,mainstationdeparture,mainstationarrival,pricepassengertrain);
                                        out = td;
                                        break;
                                        }
                           case '1' :
                                        {
                                        cout << "code of flight: ";
                                        cin.sync();
                                        getline(cin,flightcode);
                                        cout << "airport of departure: ";
                                        cin.sync();
                                        getline(cin,airportdeparture);
                                        cout << "airport of arrival: ";
                                        cin.sync();
                                        getline(cin,airportarrival);
                                        cout << "price for one passenger: ";
                                        cin >> pricepassengerflight;
                                        Flight *fd= new Flight(arrivaldate, flightcode, airportdeparture, airportarrival, pricepassengerflight);
                                        out = fd;
                                        break;
                                        }

                        }
                             cout<<endl;
                             cout << "please choose transport for journey back"<<endl
                             << "0 self organised"<<endl
                             << "1 by flight"<<endl
                             << "2 by train"<<endl
                             << "your choice: ";
                             cin >> transporttypeb;
                        switch(transporttypeb)
                        {
                            case '0' : {SelfOrganised *sb = new SelfOrganised;
                                        backw = sb;
                                        break;
                                        }
                            case '2' :{
                                        cout << "code of train: ";
                                        cin.sync();
                                        getline(cin,traincode);
                                        cout << "main train station of departure: ";
                                        cin.sync();
                                        getline(cin,mainstationdeparture);
                                        cout << "main train station of arrival: ";
                                        cin.sync();
                                        getline(cin,mainstationarrival);
                                        cout << "price for one passenger: ";
                                        cin >> pricepassengertrain;
                                        Train *ta = new Train((h->get_checkout()),traincode,mainstationdeparture, mainstationarrival,pricepassengertrain);
                                        backw = ta;
                                                  break;
                            }
                           case '1' :{
                                        cout << "code of flight: ";
                                        cin.sync();
                                        getline(cin,flightcode);
                                        cout << "airport of departure: ";
                                        cin.sync();
                                        getline(cin,airportdeparture);
                                        cout << "airport of arrival: ";
                                        cin.sync();
                                        getline(cin,airportarrival);
                                        cout << "price for one passenger: ";
                                        cin >> pricepassengerflight;
                                        Flight *fa = new Flight(h->get_checkout(), flightcode, airportdeparture, airportarrival, pricepassengerflight);
                                        backw = fa;
                                      break;
                           }
                        }
                            Trip *t = new Trip(h->get_guests(), h, out, backw);
                            travela.add(t);
                             cout<<endl<<endl;
                        break;
        }
            case '2':   {cout << "number of trip: ";
                        cin >> notrip;
                        notrip--;
                        Trip *tofind = travela.search(notrip);
                        if(tofind !=nullptr){
                            tofind->print();
                        cout << "(d)elete or (n)ot: ";
                        cin >> deletetrip;
                        if(deletetrip == 'd' || deletetrip == 'D')
                            travela.remove(tofind);}
                            else{
                                cout<<"trip not found"<<endl;
                            }
                        break;}
            case '3':   travela.printAllTrips();
                        break;
            default:    cout << "sorry wrong choice" << endl;
        }
    } while(choice != '0');
    return 0;
}
