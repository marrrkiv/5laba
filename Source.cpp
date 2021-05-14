#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <string>

using namespace std;

//Створити базовий клас ЕКСКУРСІЯ(задаються назва, дата, тривалість, вартість).
//Створити похідні класи ПІШОХІДНА ЕКСКУРСІЯ(задаються дані про гіда та частка
//заробітку гіда у вартості) та ЗМІШАНА ЕКСКУРСІЯ(задаються номер автобуса,
//дані про водія та частка заробітку водія у вартості, дані про гіда та
//частка заробітку гіда у вартості, тривалість пішохідної частини, 
//тривалість автобусної частини).Для введених даних про екскурсії
//(один гід може провести декілька екскурсій) обчислити сумарний заробіток для кожного 
//гіда і відсортувати заробітки гідів за спаданням.Для перевірки використати масив 
//вказівників на об’єкти базового класу, яким присвоїти адреси об’єктів похідних класів.

struct Excursion {
	string name;
	string date;

	int dur_days;
	int price_usd;

	double guide_salary_usd;
};

struct HikingExcursion : public Excursion {
	string guide_name;
	double chastka;
};


struct MixedExcursion : public Excursion {
	string guide_name;
	int hike_length_km;

	string bus_number;

	string driver_name;
	double driver_salary_usd;
	int ride_length_km;

};

void Sort(Excursion* excursions, int len)
{
	int i, j;
	Excursion temp;
	for (int gap = len; gap > 0; gap /= 2)
	{
		for (i = gap; i < len; i++)
		{
			temp = excursions[i];
			for (j = i; (j >= gap) && (excursions[j - gap].price_usd > temp.price_usd); j -= gap)
			{
				excursions[j] = excursions[j - gap];
			}
			excursions[j] = temp;
		}
	}
}

int main() {
	Excursion* excursions;
	int excursion_count = 0;

	cout << "Enter the number of excursions: ";
	cin >> excursion_count;

	excursions = new Excursion[excursion_count];

	cout << '\n';

	for (int i = 0; i < excursion_count; i++) {
		int excursion_type = 0;
		Excursion* excursion_to_add = nullptr;

		cout << "Excursion " << i + 1 << ":\n";

		cout << "What is the type of excursion?\n";
		cout << "1. Hiking Excursion;\n";
		cout << "2. Mixed Excursion;\n";

		cin >> excursion_type;

		switch (excursion_type) {
		case 1: {
			cout << "You chose a hiking excursion.\n";
			excursion_to_add = new HikingExcursion;
			//переведення вказівника  базового класу на об'єкт похідного 
			cout << "Excursion name: ";
			cin >> static_cast<HikingExcursion*>(excursion_to_add)->name;

			cout << "Excursion date: ";
			cin >> static_cast<HikingExcursion*>(excursion_to_add)->date;

			cout << "Excursion duration in days: ";
			cin >> static_cast<HikingExcursion*>(excursion_to_add)->dur_days;

			cout << "Excursion price in dollars: ";
			cin >> static_cast<HikingExcursion*>(excursion_to_add)->price_usd;

			cout << "Excursion guide name: ";
			cin >> static_cast<HikingExcursion*>(excursion_to_add)->guide_name;

			cout << "Excursion guide salary: ";
			cin >> static_cast<HikingExcursion*>(excursion_to_add)->guide_salary_usd;


			break;
		}

		case 2: {
			cout << "You chose a mixed excursion.\n";
			excursion_to_add = new MixedExcursion;


			cout << "Excursion name: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->name;

			cout << "Excursion date: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->date;

			cout << "Excursion duration in days: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->dur_days;

			cout << "Excursion price in dollars: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->price_usd;

			cout << "Excursion guide name: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->guide_name;

			int price_usd;
			cout << "Excursion guide salary: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->guide_salary_usd;

			cout << "Excursion hiking length in km: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->hike_length_km;

			cout << "Excursion bus number: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->bus_number;

			
			cout << "Excursion driver_name: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->driver_name;

			cout << "Excursion driver salary: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->driver_salary_usd;

			cout << "Excursion ride length in km: ";
			cin >> static_cast<MixedExcursion*>(excursion_to_add)->ride_length_km;


			break;
		}

		default:
			cout << "Invalid input.\n";
		}

		excursions[i] = *excursion_to_add;
	}

	//    Для введених даних про екскурсії(один гід може провести декілька екскурсій) 
	//    обчислити сумарний заробіток для кожного 
	//    гіда і відсортувати заробітки гідів за спаданням. Для перевірки використати 
	//    масив вказівників на об’єкти базового класу, 
	//    яким присвоїти адреси об’єктів похідних класів.
	double guide_salary_sum = 0;

	for (Excursion* pex = excursions; pex < excursions + excursion_count; pex++) {
		guide_salary_sum += pex->guide_salary_usd;
	}

	cout << "Summary salary is " << guide_salary_sum << endl;


	Sort(excursions, excursion_count);
	cout << endl;
	for (Excursion* pex = excursions; pex < excursions + excursion_count; pex++) {
		cout << pex->guide_salary_usd << endl;
	}


	delete[] excursions;
	return 0;
}