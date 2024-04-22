#include<iostream>
#include <conio.h>
#include <thread>
#include<Windows.h>
using namespace std;

#define ENTER 13
#define ESCAPE 27	
#define min_tank_volume 20
#define max_tank_volume 120


class Tank
{
	const int VOLUME;
	double fuel_level;
public:
	const int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double amount)
	{
		if (amount < 0)return;
		if (fuel_level + amount < VOLUME)fuel_level += amount;
		else fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		if (amount < 0)return fuel_level;
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	Tank(int volume) : VOLUME(volume < min_tank_volume ? min_tank_volume :
		volume>max_tank_volume ? max_tank_volume : volume)
	{
		/*if (volume < min_tank_volume)volume = min_tank_volume;
		if (volume > max_tank_volume)volume = max_tank_volume;
		this->VOLUME - volume;*/

		this->fuel_level = 0;
		cout << "Tank is ready" << this << endl;
	}
	~Tank()
	{
		cout << "Tank is over: " << this << endl;
	}
	void info()const
	{
		cout << "Tank volume: " << VOLUME << "liters.\n";
		cout << "Fuel level: " << fuel_level << "liters.\n";
	}
};

#define min_engine_consumption 3
#define max_engine_consumption 30
class Engine
{
	double consumption;
	double consumption_per_second;
	bool is_started;
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	Engine(double consumption) : consumption
	(
		consumption < min_engine_consumption ? min_engine_consumption :
		consumption> max_engine_consumption ? max_engine_consumption : consumption
	), consumption_per_second(consumption * 3e-5),
		is_started(false)
		
	{
		consumption_per_second = consumption * 3e-5;
		cout << "Engine is ready: " << this << endl;

	}

	~Engine()
	{
		cout << "Engine is over: " << this << endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}
	void info() const
	{
		cout << "consumption: " << consumption << " liters/100km" << endl;
		cout << "consumption: " << consumption_per_second << " liters/100km" << endl;
		cout << "Engine is: " << (is_started ? "started" : "stopped") << endl;
	}
};

class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	struct Threads
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
	}threads;
public:
	Car(int consumption = 10, int volume = 60) : engine(consumption), tank(volume), driver_inside(false)
	{
		cout << "Your car is ready to go" << endl;
	}
	~Car()
	{
		cout << "Your car is over" << endl;
	}
	void info()const 
	{
		engine.info();
		tank.info();
	}
	void get_in() {
		driver_inside = true;
		threads.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out() {

		driver_inside = false;
		if(threads.panel_thread.joinable())threads.panel_thread.join();
		system("CLS");
		cout << "Out of the car" << endl;
		panel();
	}



	void control() {
		char key;
		do {
			key = _getch();
			switch (key) {
			case 'F':
			case 'f': 

				if (driver_inside) {
				
					cout << "Get out of the car\a" << endl;
				}

			else{
			
				double fuel;
				cout << "¬ведите уровень топлива: "; cin >> fuel;
				tank.fill(fuel);
				}break;
			case ENTER: driver_inside ? get_out() : get_in(); break;
			case 'I':
			case 'i': engine.started() ? stop() : start(); break;
			case ESCAPE: stop(); get_out(); break;
			}
		} while (key != 27);
	}

	void engine_idle() {
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))this_thread::sleep_for(1s);
	}
	void panel() const {
		while (driver_inside) {
			system("CLS");
			if (tank.get_fuel_level() < 5) {
			
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " low fuel ";
				SetConsoleTextAttribute(hConsole, 0xC07);
			}
			cout<<endl;
			cout << "Fuel level: \t" << tank.get_fuel_level() << "liters.\n";
			cout << "Engine is: " << (engine.started() ? "started" : "stopped") << endl;
			std::this_thread::sleep_for(100ms);
		}
	}
	void start() {
		if (tank.get_fuel_level()) {
			engine.start();
			threads.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
		}
	void stop() {
		engine.stop();
		if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();
	}
};

//#define TANK_CHECK
#define ENGINE

void main()
{
	setlocale(LC_ALL, "");

#ifdef TANK_CHECK
	Tank tank(-50);
	int fuel;
	do
	{
		cout << "¬ведите объЄм топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();

	} while (fuel > 0);
#endif

#ifdef ENGINE
	Engine engine(10);
	engine.info();
#endif

	Car bmw;
	bmw.info();
	bmw.control();
	bmw.panel();
	int g;
	
	cin >> g;
}