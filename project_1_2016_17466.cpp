#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;

class  vehicle {
public:
	virtual int getSpeed() { return speed; }
	virtual void setSpeed(int _speed) { speed = _speed; }

	virtual int getEnergy() { return energy; }
	virtual void setEnergy(int _energy) { energy = _energy; }

	virtual int getTemperature() { return temperature; }
	virtual void setTemperature(int _temperature) { temperature = _temperature; }

private:
	int speed;
	int energy;
	int temperature;
};

class car : public vehicle {
public:
	int getHumidity() { return humidity; }
	void setHumidity(int _humidity) { humidity = _humidity; }

	void solar_panel_recharege() { setEnergy(getEnergy() + 200); }

private:
	int humidity;
};


class airplane : public vehicle {
public:
	int getHumidity() { return humidity; }
	void setHumidity(int _humidity) { humidity = _humidity; }

	int getAltitude() { return altitude; }
	void setAltitude(int _altitude) { altitude = _altitude; }

	int getOxygenRate() { return oxygen_rate; }
	void setOxygenRate(int _oxygen_rate) { oxygen_rate = _oxygen_rate; }

	int getAirDensity() { return air_density; }
	void setAirDensity(int _air_density) { air_density = _air_density; }

private:
	int humidity;
	int altitude;
	int oxygen_rate;
	int air_density;
};

class submarine : public vehicle {
public:
	int getDepth() { return depth; }
	void setDepth(int _depth) { depth = _depth; }

	int getOxygenRate() { return oxygen_rate; }
	void setOxygenRate(int _oxygen_rate) { oxygen_rate = _oxygen_rate; }

	int getWaterFlow() { return water_flow; }
	void setWaterFlow(int _water_flow) { water_flow = _water_flow; }

	void light(int distance) { setEnergy(getEnergy() - (30 * (distance / 10)));}

private:
	int depth;
	int oxygen_rate;
	int water_flow;
};

void temperature_and_energy_moveone(int temp, int *ener, int getEner) {
	if (temp > 0 && temp < 40) { *ener = getEner - 5; }
	else if (temp >= 40) { *ener = getEner - 10; }
	else if (temp == 0) { *ener = getEner - 8; }
}

void temperature_and_energy_movetwo(int temp, int *ener, int getEner, int distLeft, int unit) {
	if (temp > 0 && temp < 40) { *ener = getEner - 5 * (distLeft / unit); }
	else if (temp >= 40) { *ener = getEner - 10 * (distLeft / unit); }
	else if (temp == 0) { *ener = getEner - 8 * (distLeft / unit); }
}

void humidity_and_energy_moveone(int hum, int *ener, int getEner) {
	if (hum < 50) { *ener = getEner - 5; }
	else if (hum >= 50) { *ener = getEner - 8; }
}

void humidity_and_energy_movetwo(int hum, int *ener, int getEner, int distLeft, int unit) {
	if (hum < 50) { *ener = getEner - 5 * (distLeft / unit); }
	else if (hum >= 50) { *ener = getEner - 8 * (distLeft / unit); }
}

int energy_loss_by_temp(int temp) {
	if (temp > 0 && temp < 40) { return 5; }
	else if (temp >= 40) { return 10; }
	else if (temp == 0) { return  8; }
}

int energy_loss_by_hum(int hum) {
	if (hum < 50) { return 5; }
	else if (hum >= 50) { return 8; }
}

void when_energy_or_oxygen_goes_below_zero_print(int distLeft, int distWent, int ener, int oxy) {
	cout << "Successfully moved to next " << distLeft << " km" << endl;
	cout << "Final Status:" << endl;
	cout << "Distance: " << distWent + distLeft << " km" << endl;
	cout << "Energy: " << ener << endl;
	cout << "Oxygen Level: " << oxy << endl;
}

void car_print(int speed, int ener, int temp, int hum) {
	cout << "Speed: " << speed << " km/hr" << endl;
	cout << "Energy: " << ener << endl;
	cout << "Temperature: " << temp << " C" << endl;
	cout << "Humidity: " << hum << endl;
}

void airplane_print(int speed, int ener, int oxy, int temp, int hum, int alt, int airDen){
	cout << "Speed: " << speed << " km/hr" << endl;
	cout << "Energy: " << ener << endl;
	cout << "Oxygen Level: " << oxy << endl;
	cout << "Temperature: " << temp << " C" << endl;
	cout << "Humidity: " << hum << endl;
	cout << "Altitude: " << alt << " m" << endl;
	cout << "Air Density: " << airDen << endl;
}

void submarine_print(int speed, int ener, int oxy, int temp, int dep, int water) {
	cout << "Speed: " << speed << " km/hr" << endl;
	cout << "Energy: " << ener << endl;
	cout << "Oxygen Level: " << oxy << endl;
	cout << "Temperature: " << temp << " C" << endl;
	cout << "Depth: " << dep << " m" << endl;
	cout << "Water Flow: " << water << endl;
}

void exception_handle() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
	}
}

void file_initial_setting(int *ener, int *oxy, int *distWent) {
	*ener = 1000;
	*oxy = 100;
	*distWent = 0;
}

vector<string> modeResult_copy;
vector <int> distance_vec;
static int location = 0;
void text_graphic(int distCarWent, int distAirplaneWent, int distSubmarineWent, int distItWent) {
	cout << "|";
	if (distItWent == -1) { cout << "@"; }
	for (int i = 0; i < modeResult_copy.size(); i++) {
		location += distance_vec[i];
		if (modeResult_copy[i] == "Car") {
			for (int r = 0; r < (distance_vec[i] / 50); r++) {
				cout << "=";
				if (location - distance_vec[i] <= distItWent && distItWent <= location) {
					if (r == (distCarWent / 50) - 1) { cout << "@"; }
				}
			}
		}
		else if (modeResult_copy[i] == "Airplane") {
			for (int s = 0; s < (distance_vec[i] / 1000); s++) {
				cout << "^";
				if (location - distance_vec[i] <= distItWent && distItWent <= location) {
					if (s == (distAirplaneWent / 1000) - 1) { cout << "@"; }
				}
			}
		}
		else if (modeResult_copy[i] == "Submarine") {
			for (int o = 0; o < (distance_vec[i] / 10); o++) {
				cout << "~";
				if (location - distance_vec[i] <= distItWent && distItWent <= location) {
					if (o == (distSubmarineWent / 10) - 1) { cout << "@"; }
				}
			}
		}
	}
	location = 0;
	cout << "|" << endl;
}

int main() {
	int extra_or_normal;
	bool extra_mode_flag = 0;
	cout << "Mode Select(1 for EXTRA, 2 for NORMAL) : ";
	cin >> extra_or_normal;
	exception_handle();
	if (extra_or_normal == 1) { extra_mode_flag = 1; }

	static int energy = 1000;
	static int oxygen = 100;
	static int distanceItWent = 0;
	
	vector<string> modeResult;
	vector<int> energyResult;
	vector<int> oxygenResult;
	vector<int> speedResult;

	char testCase[2000] = { 0, };
	char* splited;
	const char* delimiter = ",";
	vector<char*> environment;

	char testCase_copy[2000] = { 0, };	// for text graphic
	vector<char*> environment_copy;		// for text graphic

	string TC1 = "[R300T0H10],[S4000T100H100A1000D30],[O20T100D100W100]";
	string TC2 = "[R200T60H10],[S5000T80H20A1000D70],[X],[O30T10D50W200],[R150T30H50]";
	string TC3 = "[R500T30H45],[S6000T70H70A1000D20],[R250T70H10],[O40T20D300W50],[R1000T30H40]";
	string TC4 = "[R500T20H20],[O10T20D30W40],[S2000T50H70A9000D30],[O90T10D200W50]";
	string TC5 = "[R150T20H70],[S1000T10H5A2000D20],[X],[O10T0D100W100],[Y],[R50T30H50],[O10T30D50W30]";
	string TC6 = "[R50T50H30],[O160T0D55W100],[Y],[R200T35H30],[S2000T20H100A1000D10],[R300T40H30]";
	string TC7 = "[R500T20H20],[O10T0D150W100],[S3000T10H5A2000D30],[O60T50D150W10],[S2000T0H40A3000D10]";
	string TC8 = "[R2200T50H100],[S15000T10H5A2000D20],[O80T0D100W100],[R150T30H50]";
	string TC9 = "[R50T20H30],[Y],[O80T0D100W100],[R150T30H50],[S3000T10H5A2000D20]";
	string TC10 = "[R100T20H30],[S1000T10H5A2000D20],[O80T0D100W100],[Y],[R150T30H50],[O80T0D100W100]";

	cout << "PJ1.PPJ.2016-17466" << endl;
	while (true) {
		bool stop_flag = 0;
		bool solar_panel_break_flag = 0;
		file_initial_setting(&energy, &oxygen, &distanceItWent);

		int caseChoice;
		cout << "Choose the number of the test case (1~10) : ";
		cin >> caseChoice;
		exception_handle();
		switch (caseChoice) {
		case 0:
			exit(0);
			return 0;
		case 1:
			strcpy_s(testCase, TC1.size() + 1, TC1.c_str());
			strcpy_s(testCase_copy, TC1.size() + 1, TC1.c_str()); // for text graphic
			cout << "Test case #1.\n" << endl;
			break;
		case 2:
			strcpy_s(testCase, TC2.size() + 1, TC2.c_str());
			strcpy_s(testCase_copy, TC2.size() + 1, TC2.c_str());
			cout << "Test case #2.\n" << endl;
			break;
		case 3:
			strcpy_s(testCase, TC3.size() + 1, TC3.c_str());
			strcpy_s(testCase_copy, TC3.size() + 1, TC3.c_str());
			cout << "Test case #3.\n" << endl;
			break;
		case 4:
			strcpy_s(testCase, TC4.size() + 1, TC4.c_str());
			strcpy_s(testCase_copy, TC4.size() + 1, TC4.c_str());
			cout << "Test case #4.\n" << endl;
			break;
		case 5:
			strcpy_s(testCase, TC5.size() + 1, TC5.c_str());
			strcpy_s(testCase_copy, TC5.size() + 1, TC5.c_str());
			cout << "Test case #5.\n" << endl;
			break;
		case 6:
			strcpy_s(testCase, TC6.size() + 1, TC6.c_str());
			strcpy_s(testCase_copy, TC6.size() + 1, TC6.c_str());
			cout << "Test case #6.\n" << endl;
			break;
		case 7:
			strcpy_s(testCase, TC7.size() + 1, TC7.c_str());
			strcpy_s(testCase_copy, TC7.size() + 1, TC7.c_str());
			cout << "Test case #7.\n" << endl;
			break;
		case 8:
			strcpy_s(testCase, TC8.size() + 1, TC8.c_str());
			strcpy_s(testCase_copy, TC8.size() + 1, TC8.c_str());
			cout << "Test case #8.\n" << endl;
			break;
		case 9:
			strcpy_s(testCase, TC9.size() + 1, TC9.c_str());
			strcpy_s(testCase_copy, TC9.size() + 1, TC9.c_str());
			cout << "Test case #9.\n" << endl;
			break;
		case 10:
			strcpy_s(testCase, TC10.size() + 1, TC10.c_str());
			strcpy_s(testCase_copy, TC10.size() + 1, TC10.c_str());
			cout << "Test case #10.\n" << endl;
			break;
		default:
			continue;
		}

		// text graphic - read distance of environments in TC first to print the whole map whenever the vehicle 'move's
		if (extra_mode_flag == 1) {
			splited = strtok(testCase_copy, delimiter); // testCase_copy is for text graphic
			while (splited != NULL) {
				environment_copy.push_back(splited);
				splited = strtok(NULL, delimiter);
			}
			int road, sky, ocean;
			int vector_size = environment_copy.size();
			for (int j = 0; j < vector_size; j++) {
				if (environment_copy[j][1] == 'R') {
					char* attribute;
					const char* delimiter = "[]RTH";
					vector <char*> text_graphic_vec;
					attribute = strtok(environment_copy[j], delimiter);
					while (attribute != NULL) {
						text_graphic_vec.push_back(attribute);
						attribute = strtok(NULL, delimiter);
					}
					road = atoi(text_graphic_vec[0]);
					modeResult_copy.push_back("Car");
					distance_vec.push_back(road);	// vector<int> vec: store 'distance' values into vector in sequence
				}
				if (environment_copy[j][1] == 'S') {
					char* attribute;
					const char* delimiter = "[]STHAD";
					vector <char*> text_graphic_vec;
					attribute = strtok(environment_copy[j], delimiter);
					while (attribute != NULL) {
						text_graphic_vec.push_back(attribute);
						attribute = strtok(NULL, delimiter);
					}
					sky = atoi(text_graphic_vec[0]);
					modeResult_copy.push_back("Airplane");
					distance_vec.push_back(sky);
				}
				if (environment_copy[j][1] == 'O') {
					char* attribute;
					const char* delimiter = "[]OTDW";
					vector <char*> text_graphic_vec;
					attribute = strtok(environment_copy[j], delimiter);
					while (attribute != NULL) {
						text_graphic_vec.push_back(attribute);
						attribute = strtok(NULL, delimiter);
					}
					ocean = atoi(text_graphic_vec[0]);
					modeResult_copy.push_back("Submarine");
					distance_vec.push_back(ocean);
				}
			}
		}

		// vehicle move
		splited = strtok(testCase, delimiter);
		while (splited != NULL) {
			environment.push_back(splited);
			splited = strtok(NULL, delimiter);
		}
		
		int count_for_initial_print = 0; // this is for printing initial speed which is 0, when right after choosing Test Case
		int size = environment.size();
		for (int i = 0; i < size; i++) {
			// CAR
			if (environment[i][1] == 'R') {
				char* attribute;
				const char* delimiter = "[]RTH";
				vector<char*> attribute_vec;

				attribute = strtok(environment[i], delimiter);
				while (attribute != NULL)	{
					attribute_vec.push_back(attribute);
					attribute = strtok(NULL, delimiter);
				}

				int _temperature = atoi(attribute_vec[1]);
				int _humidity = atoi(attribute_vec[2]);
				int distance = atoi(attribute_vec[0]);
				int distanceLeft = distance;

				car mycar;
				mycar.setSpeed(80);
				mycar.setEnergy(energy);
				mycar.setTemperature(_temperature);
				mycar.setHumidity(_humidity);
				oxygen = 100;

				// Solar Panel Recharge
				if (_humidity < 50 && solar_panel_break_flag == 0) {
					if (mycar.getEnergy() >= 800 && mycar.getEnergy() <= 1000) {
						energy = 1000;
						mycar.setEnergy(energy);
					}
					else if (0 < mycar.getEnergy() && mycar.getEnergy() <= 800) {
						mycar.solar_panel_recharege();
						energy = mycar.getEnergy();
					}
				}

				if (count_for_initial_print < 1) { // print only once right after Test Case is chosen
					cout << "Current Status: Car" << endl;
					cout << "Distance: " << distanceItWent << " km" << endl;
					cout << "Speed: " << "0" << " km/hr" << endl;
					cout << "Energy: " << energy << endl;
					cout << "Temperature: " << _temperature << " C" << endl;
					cout << "Humidity: " << _humidity << endl;
					text_graphic(-50, -1000, -10, -1); // -1 is an indicator to print initial location of the vehicle
				}
				count_for_initial_print++; // don't print this since there'll be no chance of speed being 0 (except the influence of Air Density or Water Flow)

				int distanceCarWent = 0;	// check if the Car moved through the whole given distance of Road
				while (distanceCarWent < distance) { // if distanceCarWent == distance, break out of while() and move to other environment
					cout << "Next Move? (1,2)" << endl;
					cout << "CP-2016-17466> ";
					int nextMoveChoice;
					cin >> nextMoveChoice;
					exception_handle();
					switch (nextMoveChoice) {
					case 1: // move one
						// check if the vehicle is able to move 1 unit farther
						temperature_and_energy_moveone(_temperature, &energy, mycar.getEnergy());
						mycar.setEnergy(energy);
						humidity_and_energy_moveone(_humidity, &energy, mycar.getEnergy());
						mycar.setEnergy(energy);

						if (mycar.getEnergy() <= 0) { // when vehicle is not able to move 1 unit farther...
							mycar.setEnergy(0);
							energy = mycar.getEnergy();
							distanceLeft = 50;	// to print "Successfully moved to next 50 km"

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
						}
						if (mycar.getEnergy() > 0) {
							distanceLeft -= 50;
							distanceItWent += 50;
							distanceCarWent += 50;

							cout << "Successfully moved to next 50 km" << endl;
							cout << "Current Status: Car" << endl;
							cout << "Distance: " << distanceItWent << " km" << endl;
							car_print(mycar.getSpeed(), energy, _temperature, _humidity);
							if (extra_mode_flag == 1) { text_graphic(distanceCarWent, -1000, -10, distanceItWent); }
						}
						break;

					case 2: // move two
						int energyTemp = energy;
						// check if the vehicle is able to move all the distance left within the environment
						temperature_and_energy_movetwo(_temperature, &energy, mycar.getEnergy(), distanceLeft, 50);
						mycar.setEnergy(energy);
						humidity_and_energy_movetwo(_humidity, &energy, mycar.getEnergy(), distanceLeft, 50);
						mycar.setEnergy(energy);

						if (mycar.getEnergy() <= 0) {
							mycar.setEnergy(0); // Energy couldn't be below 0. Set energy to 0
							energy = mycar.getEnergy();

							int enerCount = 0;
							while (true) {	// calculate how much farther the vehicle could move with remaining energy
								energyTemp -= energy_loss_by_temp(_temperature);
								enerCount++;
								if (energyTemp <= 0) { 
									break;
								}
							}
							distanceLeft = enerCount * 50;

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
						}
						if (mycar.getEnergy() > 0) {
							cout << "Successfully moved to next " << distanceLeft << " km" << endl;
							cout << "Current Status: Car" << endl;
							cout << "Distance: " << distanceItWent + distanceLeft << " km" << endl;
							car_print(mycar.getSpeed(), energy, _temperature, _humidity);

							distanceItWent += distanceLeft;
							distanceCarWent += distanceLeft;
							distanceLeft -= distanceLeft;

							if (extra_mode_flag == 1) { text_graphic(distanceCarWent, -1000, -10, distanceItWent); }
						}
						break;
					} // end of switch()

					if (energy <= 0) {
						break; // break out of while (distanceCarWent < distance)
					}
				} // end of while (distanceCarWent < distance)
				modeResult.push_back("Car");
				energyResult.push_back(energy);
				oxygenResult.push_back(oxygen);
				speedResult.push_back(mycar.getSpeed());
				attribute_vec.clear();
			}
			
			// AIRPLANE
			else if (environment[i][1] == 'S') {
				char* attribute;
				const char* delimiter = "[]STHAD";
				vector<char*> attribute_vec;

				attribute = strtok(environment[i], delimiter);
				while (attribute != NULL) {
					attribute_vec.push_back(attribute);
					attribute = strtok(NULL, delimiter);
				}

				int _temperature = atoi(attribute_vec[1]);
				int _humidity = atoi(attribute_vec[2]);
				int _altitude = atoi(attribute_vec[3]);
				int _airDensity = atoi(attribute_vec[4]);
				int distance = atoi(attribute_vec[0]);
				int distanceLeft = distance;

				airplane myplane;
				myplane.setSpeed(900);
				myplane.setEnergy(energy);
				myplane.setTemperature(_temperature);
				myplane.setOxygenRate(oxygen);
				myplane.setHumidity(_humidity);

				if (_airDensity >= 30 && _airDensity < 50) { myplane.setSpeed(myplane.getSpeed() - 200); }
				if (_airDensity >= 50 && _airDensity < 70) { myplane.setSpeed(myplane.getSpeed() - 300); }
				if (_airDensity >= 70) { myplane.setSpeed(myplane.getSpeed() - 500); }

				int distanceAirplaneWent = 0;
				while (distanceAirplaneWent < distance) {
					cout << "Next Move? (1,2)" << endl;
					cout << "CP-2016-17466> ";
					int nextMoveChoice;
					cin >> nextMoveChoice;
					exception_handle();
					switch (nextMoveChoice) {
					case 1:
						// check if the vehicle is able to move 1 unit farther
						temperature_and_energy_moveone(_temperature, &energy, myplane.getEnergy());
						myplane.setEnergy(energy);
						humidity_and_energy_moveone(_humidity, &energy, myplane.getEnergy());
						myplane.setEnergy(energy);

						if (myplane.getEnergy() > 0) {
							oxygen = myplane.getOxygenRate() - 10 * (_altitude / 1000);
							myplane.setOxygenRate(oxygen);
						}
						
						if (myplane.getEnergy() <= 0) {	 // when vehicle is not able to move 1 unit farther...
							myplane.setEnergy(0); // Energy couldn't be below 0. Set energy to 0
							energy = myplane.getEnergy();
							distanceLeft = 1000; // to print "Successfully moved to next 1000 km"

							oxygen = myplane.getOxygenRate() - 10 * (_altitude / 1000);
							if (oxygen <= 0) { oxygen = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
						}

						if (myplane.getOxygenRate() <= 0) {	 // when vehicle is not able to move 1 unit farther...
							myplane.setOxygenRate(0); // Oxygen rate couldn't be below 0. Set oxygen to 0
							oxygen = myplane.getOxygenRate();
							distanceLeft = 1000; // to print "Successfully moved to next 1000 km"

							temperature_and_energy_moveone(_temperature, &energy, myplane.getEnergy());
							myplane.setEnergy(energy);
							humidity_and_energy_moveone(_humidity, &energy, myplane.getEnergy());
							myplane.setEnergy(energy);
							if (energy <= 0) { energy = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Oxygen failure" << endl;
						}

						if (myplane.getEnergy() > 0 && myplane.getOxygenRate() > 0) {
							distanceLeft -= 1000;
							distanceItWent += 1000;
							distanceAirplaneWent += 1000;

							cout << "Successfully moved to next 1000 km" << endl;
							cout << "Current Status: Airplane" << endl;
							cout << "Distance: " << distanceItWent << " km" << endl;
							airplane_print(myplane.getSpeed(), energy, oxygen, _temperature, _humidity, _altitude, _airDensity);
							if (extra_mode_flag == 1) { text_graphic(-50, distanceAirplaneWent, -10, distanceItWent); }
						}
						break;

					case 2:
						int oxygenTemp = oxygen;
						int energyTemp = energy;
						// check if the vehicle is able to move all the distance left within the environment
						temperature_and_energy_movetwo(_temperature, &energy, myplane.getEnergy(), distanceLeft, 1000);
						myplane.setEnergy(energy);
						humidity_and_energy_movetwo(_humidity, &energy, myplane.getEnergy(), distanceLeft, 1000);
						myplane.setEnergy(energy);

						if (myplane.getEnergy() > 0) {
							oxygen = myplane.getOxygenRate() - 10 * ((_altitude / 1000) * (distanceLeft / 1000));
							myplane.setOxygenRate(oxygen);
						}

						if (myplane.getEnergy() <= 0) {
							myplane.setEnergy(0);
							energy = myplane.getEnergy();

							int enerCount = 0;
							while (true) {	// calculate how much farther the vehicle could move with remaining energy
								energyTemp -= (energy_loss_by_temp(_temperature) + energy_loss_by_hum(_humidity));
								enerCount++;
								if (energyTemp <= 0) {
									break;
								}
							}
							distanceLeft = enerCount * 1000;

							oxygen = myplane.getOxygenRate() - 10 * ((_altitude / 1000) * (distanceLeft / 1000));
							if (oxygen <= 0) { oxygen = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
						}

						if (myplane.getOxygenRate() <= 0) {
							myplane.setOxygenRate(0);
							oxygen = myplane.getOxygenRate();

							int oxyCount = 0;
							while (true) {	// calculate how much farther the vehicle could move with remaining oxygen
								oxygenTemp -= 10 * (_altitude / 1000);
								oxyCount++;
								if (oxygenTemp <= 0) {
									break;
								}
							}
							distanceLeft = oxyCount * 1000;

							temperature_and_energy_movetwo(_temperature, &energy, myplane.getEnergy(), distanceLeft, 1000);
							myplane.setEnergy(energy);
							humidity_and_energy_movetwo(_humidity, &energy, myplane.getEnergy(), distanceLeft, 1000);
							myplane.setEnergy(energy);
							if (energy <= 0) { energy = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Oxygen failure" << endl;
						}
						if (myplane.getEnergy() > 0 && myplane.getOxygenRate() > 0) {
							cout << "Successfully moved to next " << distanceLeft << " km" << endl;
							cout << "Current Status: Airplane" << endl;
							cout << "Distance: " << distanceItWent + distanceLeft << " km" << endl;
							airplane_print(myplane.getSpeed(), energy, oxygen, _temperature, _humidity, _altitude, _airDensity);

							distanceItWent += distanceLeft;
							distanceAirplaneWent += distanceLeft;
							distanceLeft -= distanceLeft;

							if (extra_mode_flag == 1) { text_graphic(-50, distanceAirplaneWent, -10, distanceItWent); }
						}
						break;
					} // end of switch()
					if (oxygen <= 0 || energy <= 0) {
						break;
					}
				}
				modeResult.push_back("Airplane");
				energyResult.push_back(energy);
				oxygenResult.push_back(oxygen);
				speedResult.push_back(myplane.getSpeed());
				attribute_vec.clear();
			}

			// SUBMARINE
			else if (environment[i][1] == 'O') {
				char* attribute;
				const char* delimiter = "[]OTDW";
				vector<char*> attribute_vec;

				attribute = strtok(environment[i], delimiter);
				while (attribute != NULL) {
					attribute_vec.push_back(attribute);
					attribute = strtok(NULL, delimiter);
				}

				int _temperature = atoi(attribute_vec[1]);
				int _depth = atoi(attribute_vec[2]);
				int _waterFlow = atoi(attribute_vec[3]);
				int distance = atoi(attribute_vec[0]);
				int distanceLeft = distance;

				submarine mysubmarine;
				mysubmarine.setSpeed(20);
				mysubmarine.setEnergy(energy);
				mysubmarine.setTemperature(_temperature);
				mysubmarine.setOxygenRate(oxygen);
				mysubmarine.setDepth(_depth);
				mysubmarine.setWaterFlow(_waterFlow);

				if (_waterFlow >= 30 && _waterFlow < 50) { mysubmarine.setSpeed(mysubmarine.getSpeed() - 3); }
				if (_waterFlow >= 50 && _waterFlow < 70) { mysubmarine.setSpeed(mysubmarine.getSpeed() - 5); }
				if (_waterFlow >= 70) { mysubmarine.setSpeed(mysubmarine.getSpeed() - 10); }

				int distanceSubmarineWent = 0;
				while (distanceSubmarineWent < distance) {
					cout << "Next Move? (1,2)" << endl;
					cout << "CP-2016-17466> ";
					int nextMoveChoice;
					cin >> nextMoveChoice;
					exception_handle();
					switch (nextMoveChoice) {
					case 1:
						// check if the vehicle is able to move 1 unit farther
						temperature_and_energy_moveone(_temperature, &energy, mysubmarine.getEnergy());
						mysubmarine.setEnergy(energy);

						mysubmarine.light(10);
						energy = mysubmarine.getEnergy();
						
						if (mysubmarine.getEnergy() > 0) {
							oxygen = mysubmarine.getOxygenRate() - 5 * (_depth / 50);
							mysubmarine.setOxygenRate(oxygen);
						}
						if (mysubmarine.getEnergy() <= 0) {
							mysubmarine.setEnergy(0);
							energy = mysubmarine.getEnergy();
							distanceLeft = 10;

							oxygen = mysubmarine.getOxygenRate() - 5 * (_depth / 50);
							if (oxygen <= 0) { oxygen = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
						}
						if (mysubmarine.getOxygenRate() <= 0) {
							mysubmarine.setOxygenRate(0);
							oxygen = mysubmarine.getOxygenRate();
							distanceLeft = 10;

							temperature_and_energy_moveone(_temperature, &energy, mysubmarine.getEnergy());
							mysubmarine.setEnergy(energy);
							mysubmarine.light(distanceLeft);
							energy = mysubmarine.getEnergy();
							if (energy <= 0) { energy = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Oxygen failure" << endl;
						}
						if (mysubmarine.getEnergy() > 0 && mysubmarine.getOxygenRate() > 0) { // energy and oxygen both above 0
							distanceLeft -= 10;
							distanceItWent += 10;
							distanceSubmarineWent += 10;

							cout << "Successfully moved to next 10 km" << endl;
							cout << "Current Status: Submarine" << endl;
							cout << "Distance: " << distanceItWent << " km" << endl;
							submarine_print(mysubmarine.getSpeed(), energy, oxygen, _temperature, _depth, _waterFlow);
							if (extra_mode_flag == 1) { text_graphic(-50, -1000, distanceSubmarineWent, distanceItWent); }
						}
						break;

					case 2:
						int oxygenTemp = oxygen;
						int energyTemp = energy;
						// check if the vehicle is able to move all the distance left within the environment
						temperature_and_energy_movetwo(_temperature, &energy, mysubmarine.getEnergy(), distanceLeft, 10);
						mysubmarine.setEnergy(energy);
						mysubmarine.light(distanceLeft);
						energy = mysubmarine.getEnergy();
						
						if (mysubmarine.getEnergy() > 0) {
							oxygen = mysubmarine.getOxygenRate() - 5 * ((_depth / 50) * (distanceLeft / 10));
							mysubmarine.setOxygenRate(oxygen);
						}
						if (mysubmarine.getEnergy() <= 0) {
							mysubmarine.setEnergy(0);
							energy = mysubmarine.getEnergy();

							int enerCount = 0;
							while (true) {
								energyTemp -= (energy_loss_by_temp(_temperature) + 30); // energy loss of 30 by light()
								enerCount++;
								if (energyTemp <= 0) {
									break;
								}
							}
							distanceLeft = enerCount * 10;

							oxygen = oxygenTemp - 5 * ((_depth / 50) * (distanceLeft / 10));
							if (oxygen <= 0) { oxygen = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
						}
						if (mysubmarine.getOxygenRate() <= 0) {
							mysubmarine.setOxygenRate(0);
							oxygen = mysubmarine.getOxygenRate();

							int oxyCount = 0;
							while (true) {
								oxygenTemp -= 5 * (_depth / 50);
								oxyCount++;
								if (oxygenTemp <= 0) {
									break;
								}
							}
							distanceLeft = oxyCount * 10;

							temperature_and_energy_movetwo(_temperature, &energy, mysubmarine.getEnergy(), distanceLeft, 10);
							mysubmarine.setEnergy(energy);
							mysubmarine.light(distanceLeft);
							energy = mysubmarine.getEnergy();

							if (energy <= 0) { energy = 0; }

							when_energy_or_oxygen_goes_below_zero_print(distanceLeft, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Oxygen failure" << endl;
						}
						if (mysubmarine.getEnergy() > 0 && mysubmarine.getOxygenRate() > 0) {
							cout << "Successfully moved to next " << distanceLeft << " km" << endl;
							cout << "Current Status: Submarine" << endl;
							cout << "Distance: " << distanceItWent + distanceLeft << " km" << endl;
							submarine_print(mysubmarine.getSpeed(), energy, oxygen, _temperature, _depth, _waterFlow);

							distanceItWent += distanceLeft;
							distanceSubmarineWent += distanceLeft;
							distanceLeft -= distanceLeft;

							if (extra_mode_flag == 1) { text_graphic(-50, -1000, distanceSubmarineWent, distanceItWent); }
						}
						break;
					} // end of switch()
					if (oxygen <= 0 || energy <= 0) {
						break;
					}
				} // end of while()
				modeResult.push_back("Submarine");
				energyResult.push_back(energy);
				oxygenResult.push_back(oxygen);
				speedResult.push_back(mysubmarine.getSpeed());
				attribute_vec.clear();
			} // end of SUBMARINE

			if (oxygen <= 0 || energy <= 0) {
				break; // break out of for() loop and go all the way bottom of the code to print Blackbox
			}

			if (extra_mode_flag == 1) {	// unexpected events
				if (environment[i][1] == 'X') {
					int possibility_array[20] = { 20, 20, 20, 20, 35, 35, 35, 35, 35, 35, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 20% = 4/20, 35% = 7/20 
					srand(time(0));
					int stop_possibility = possibility_array[rand() % 20]; // possibility_array[0] ~ possibility_array[19]
					if (stop_possibility == 20) { // randomly choose index of possibility_array and if the value of the index is 20, it's same as the probability of 20%
						when_energy_or_oxygen_goes_below_zero_print(0, distanceItWent, energy, oxygen);
						cout << "\n!FINISHED : Vehicle stop" << endl;
						stop_flag = 1;
						break;
					}
					else {
						energy -= 100;
						if (energy <= 0) {
							energy = 0;
							when_energy_or_oxygen_goes_below_zero_print(0, distanceItWent, energy, oxygen);
							cout << "\n!FINISHED : Energy failure" << endl;
							break;
						}
					}
				} // end of [X]

				if (environment[i][1] == 'Y') {
					int possibility_array[20] = { 20, 20, 20, 20, 35, 35, 35, 35, 35, 35, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 20% = 4/20, 35% = 7/20
					srand(time(0));
					int stop_possibility = possibility_array[rand() % 20]; // possibility_array[0] ~ possibility_array[19]
					if (stop_possibility == 35) { // randomly choose index of possibility_array and if the value of the index is 35, it's same as the probability of 35%
						when_energy_or_oxygen_goes_below_zero_print(0, distanceItWent, energy, oxygen);
						cout << "\n!FINISHED : Vehicle stop" << endl;
						stop_flag = 1;
						break;
					}
					else {
						if (modeResult[modeResult.size() - 1] == "Car") {
							int possibility_array[2] = { 50, 0 }; // 50% = 1/2
							srand(time(0));
							int solar_panel_break_possibility = possibility_array[rand() % 2]; // possibility_array[0] ~ possibility_array[1]
							if (solar_panel_break_possibility == 50) {
								solar_panel_break_flag = 1;
							}
						}
						if (modeResult[modeResult.size() - 1] == "Airplane" || modeResult[modeResult.size() - 1] == "Submarine") {
							int possibility_array[2] = { 50, 0 }; // 50% = 1/2
							srand(time(0));
							int oxygen_decrease_possibility = possibility_array[rand() % 2]; // possibility_array[0] ~ possibility_array[1]
							if (oxygen_decrease_possibility == 50) {
								oxygen -= 30;
							}

							if (oxygen <= 0) {
								oxygen = 0;
								when_energy_or_oxygen_goes_below_zero_print(0, distanceItWent, energy, oxygen);
								cout << "\n!FINISHED : Oxygen failure" << endl;
								break;
							}
						}
					}
				} // end of [Y]
			}
		} // end of for()
		
		if (energy > 0 && oxygen > 0 && stop_flag == 0) { cout << "\n!FINISHED : Arrived" << endl; }
		
		cout << "Blackbox:" << endl;
		cout << "Mode: ";
		for (int k = 0; k < modeResult.size() - 1; k++) {
			cout << modeResult[k] << " > ";
		}
		cout << modeResult.back() << endl;
		
		cout << "Energy Level: ";
		for (int k = 0; k < energyResult.size() - 1; k++) {
			cout << energyResult[k] << " > ";
		}
		cout << energyResult.back() << endl;
		
		cout << "Oxygen Level: ";
		for (int k = 0; k < oxygenResult.size() - 1; k++) {
			cout << oxygenResult[k] << " > ";
		}
		cout << oxygenResult.back() << endl;
		
		cout << "Speed: ";
		for (int k = 0; k < speedResult.size() - 1; k++) {
			cout << speedResult[k] << " > ";
		}
		cout << speedResult.back() << endl;

		cout << "--------------------" << endl;
		
		modeResult.clear();
		energyResult.clear();
		oxygenResult.clear();
		speedResult.clear();
		environment.clear();
		environment_copy.clear();
		modeResult_copy.clear();
		distance_vec.clear();
	} // end of while(true)
} // end of main()