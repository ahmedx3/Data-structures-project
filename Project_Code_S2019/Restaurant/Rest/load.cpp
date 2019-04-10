#include "load.h"



load::load(string path, Restaurant* restaurant)
{
	this->restaurant = restaurant;

	ifstream inFile;
	string sum = "";
	string line;
	string sn;
	string sf;
	string sv;
	string n[4];
	string f[4];
	string v[4];
	string autoS;
	string m;

	inFile.open(path);
	if (!inFile) {
		cerr << "Unable to open file";
	}
	else {
		int j = 1; // which line are we in
		while (getline(inFile, line)) {


			int curr = 0; // get indicator for vars
			for (int i = 0; i < line.length(); i++) {
				//cout << line[i] << endl;
				if (line[i] != ' ') {

					// get sn sf sv
					if (j == 1) { // first line

						if (curr == 0) {

							sn += line[i];
							//curr++;
						}
						else if (curr == 1) {

							sf += line[i];
							//curr++;
						}
						else if (curr == 2) {

							sv += line[i];
							//curr= 0;
						}
					}

					// get n f v for four regions

					if (j >= 2 && j <= 5) {
						if (curr == 0) {
							n[j - 2] += line[i];
							//curr++;
						}
						else if (curr == 1) {
							f[j - 2] += line[i];
							//curr++;
						}
						else if (curr == 2) {
							v[j - 2] += line[i];
							//curr = 0;
						}
					}

					// get number of timestamps 

					if (j == 6) {
						autoS += line[i];
					}
					//get number of events 

					if (j == 7) {
						m += line[i];
					}

					// get rest of files 
					if (j > 7) {
						if (line[i] == 'R') {
							// add to arrival events
							cout << " arrived order " << endl;
							i = 2;

							int timeStamp;
							char type;
							int ID;
							int distance;
							double money;
							char region;

							string tempTimeStamp = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempTimeStamp += line[i];
								i++;
							}
							timeStamp = stoi(tempTimeStamp);

							i++;

							type = line[i];

							i += 2;

							string tempID = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempID += line[i];
								i++;
							}
							ID = stoi(tempID);

							i++;

							string tempDistance = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempDistance += line[i];
								i++;
							}
							distance = stoi(tempDistance);

							i++;

							string tempMoney = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempMoney += line[i];
								i++;
							}
							money = stod(tempMoney);

							i++;

							region = line[i];

							addOrder(timeStamp, type, ID, distance, money, region);
							break;
						}
						else if (line[i] == 'X') {
							cout << " canceled order " << endl;
							// cancel the event

							i = 2;

							string tempTimeStamp = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempTimeStamp += line[i];
								i++;
							}
							int timeStamp = stoi(tempTimeStamp);

							i++;

							string tempID = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempID += line[i];
								i++;
							}
							int ID = stoi(tempID);

							cancelOrder(timeStamp, ID);
							break;
						}
						else if (line[i] == 'P') {
							cout << " promoted order " << endl;
							// promote order

							i = 2;

							string tempTimeStamp = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempTimeStamp += line[i];
								i++;
							}
							int timeStamp = stoi(tempTimeStamp);

							i++;

							string tempID = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempID += line[i];
								i++;
							}
							int ID = stoi(tempID);

							i++;

							string tempMoney = "";
							while ((line[i] != ' ') && (line[i] != '\0')) {
								tempMoney += line[i];
								i++;
							}
							double money = stod(tempMoney);

							promoteOrder(timeStamp, ID, money);
							break;
						}
					}
				}
				else {
					if (curr > 2) {
						curr = 0;
					}
					else {
						curr++;
					}

				}



			}



			j++;
		}
		inFile.close();
		this->sn = stoi(sn);
		this->sf = stoi(sf);
		this->sv = stoi(sv);

		int Normal[4];
		int Frozen[4];
		int VIP[4];

		for (int k = 0; k < 4; k++) {
			this->n[k] = stoi(n[k]);
			Normal[k] = stoi(n[k]);
			this->f[k] = stoi(f[k]);
			Frozen[k] = stoi(f[k]);
			this->v[k] = stoi(v[k]);
			VIP[k] = stoi(v[k]);
		}



		restaurant->setMCs(Normal, Frozen, VIP);
		
		
		
		this->autoS = stoi(autoS);
		this->m = stoi(m);
		//cout << "Sum = " << sum << endl;

		//get the events 


	}


}

void load::printInfo() {
	cout << " sn : " << sn << "  sf:  " << sf << " sv:  " << sv << endl;
	for (int k = 0; k < 4; k++) {
		cout << " normal regions " << n[k] << endl;
		cout << " frozen regions " << f[k] << endl;
		cout << " vip regions " << v[k] << endl;
	}
	cout << "time stamp " << autoS << endl;
	cout << " no of events " << m << endl;
}
load::~load()
{
}

void load::addOrder(int timeStamp, char type, int ID, int distance, double money, char region)
{
	ORD_TYPE oType;
	if (type == 'N')
		oType = TYPE_NRM;
	else if (type == 'F')
		oType = TYPE_FROZ;
	else
		oType = TYPE_VIP;

	REGION reg;
	if (region == 'A')
		reg = A_REG;
	else if (region == 'B')
		reg = B_REG;
	else if (region == 'C')
		reg = C_REG;
	else
		reg = D_REG;

	Event* event = new ArrivalEvent(timeStamp, ID, oType, reg, money, distance);

	restaurant->AddEvent(event);
}

void load::cancelOrder(int timeStamp, int ID)
{
	Event* event = new CancelationEvent(timeStamp, ID);

	restaurant->AddEvent(event);
}

void load::promoteOrder(int timeStamp, int ID, double money)
{
	Event* event = new PromotionEvent(timeStamp, ID, money);

	restaurant->AddEvent(event);
}
