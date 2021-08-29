/*************************************************
Aufgabe Nr./Task No.: H2
Nachname/Last,Family Name: Elsayed
Vorname/First,Given Name: Mohamed Ahmed Hamed Mohamed
Matrikelnummer/Matriculation number: 3056145
Uni-Email: mohamed.ahmed-hamed-mohamed-elsayed@stud.uni-due.de
Studiengang/Course of Studies: ISE software CE
*************************************************/
#include <iostream>
#include <iomanip>

using namespace std;

struct Cof {
	int f;
	Cof *next = nullptr;
};

void extend(Cof *&head, int y) {
	Cof *newnum = new Cof;
	newnum->f = y;
	newnum->next = nullptr;

	if (head == nullptr) {
		head = newnum;
	}
	else {
		Cof *temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newnum;
	}
}

Cof *re() {
	Cof *head = new Cof;
	cout << "Continued fraction, enter first value f_0: ";
	cin >> head->f;
	int i = 1;

	int x;
	do {
		cout << "Enter next part denominator f_" << i++ << "(<= 0 for end): ";
		cin >> x;
		if (x == 0) break;
		extend(head, x);
	} while (x != 0);


	return head;
}

double fun(Cof *head) {
	if (head->next != nullptr) {
		return (head->f + (1 / fun(head->next)));
	}
	else {
		return (head->f);
	}
}


void deleteAll(Cof* &head)
{
	Cof *toDelete;
	cout << "Delete: " ;
	while (head != nullptr)
	{
		toDelete = head;
		head = head->next;
		cout << toDelete->f<<" ";
		delete toDelete;
	}
	cout<<endl;
}

int main() {
    Cof *x = nullptr;
	int arr1[] = {1, 4, 2, 1, 7};
	for (int i = 0; i < 5; ++i)
		extend(x, arr1[i]);

    Cof *y = nullptr;
    int arr2[] = {1, 1, 2, 3};
	for (int i = 0; i < 4; ++i)
		extend(y, arr2[i]);

    cout<< "cf1 = 123/100 = "<<fixed << setprecision(2) << fun(x) << endl;
	deleteAll(x);
	cout<< "cf2 = 17/10 = "<<fixed << setprecision(1) << fun(y) << endl;
	deleteAll(y);

	Cof *z=new Cof;
	for(;;)
    {
	z = re();
	cout<<"value inputted continued fraction cf3 = "<<fixed << setprecision(15) <<fun(z)<<endl;
	deleteAll(z);
	cout<<endl;
    }
}
