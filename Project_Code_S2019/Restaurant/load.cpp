#include "load.h"



load::load(string path)
{
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
			for (int i = 0; i < line.length();i++) {
				//cout << line[i] << endl;
				if (line[i] != ' ') {
					
					// get sn sf sv
					if (j == 1) { // first line
						
						if (curr == 0) {
							
							sn +=  line[i];
							//curr++;
						}else if (curr == 1) {
							
							sf += line[i];
							//curr++;
						}else if (curr == 2) {
							
							sv += line[i];
							//curr= 0;
						}
					}

					// get n f v for four regions

					if (j >= 2 && j<= 5) {
						if (curr == 0) {
							n[j - 2] += line[i];
							//curr++;
						}
						else if (curr == 1) {
							f[j - 2] += line[i] ;
							//curr++;
						}
						else if (curr == 2) {
							v[j - 2] += line[i] ;
							//curr = 0;
						}
					}

					// get number of timestamps 

					if (j == 6) {
						autoS += line[i] ;
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
						}
						else if (line[i] == 'X') {
							cout << " canceled order " << endl;
							// cancel the event
						}
						else if (line[i] == 'P') {
							cout << " promoted order " << endl;
							// promote order
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
		for (int k = 0; k < 4; k++) {
			this->n[k] = stoi(n[k]);
			this->f[k] = stoi(f[k]);
			this->v[k] = stoi(v[k]);
		}
		this->autoS = stoi(autoS);
		this->m = stoi(m);
		//cout << "Sum = " << sum << endl;

		//get the events 

		
	}

	
}

void load::printInfo() {
	cout << " sn : " <<sn << "  sf:  " << sf << " sv:  " << sv << endl;
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
