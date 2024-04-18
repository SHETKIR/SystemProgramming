#include<iostream>
using namespace std;

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
		cout << "Введите объём топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();

	} while (fuel > 0);
#endif

	Engine engine(10);
	engine.info();
}