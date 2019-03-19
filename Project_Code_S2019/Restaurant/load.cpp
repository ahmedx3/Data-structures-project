#include "load.h"



load::load(string path)
{
	ifstream inFile;
	string sum = "";
	string line;
	char x;
	inFile.open(path);
	if (!inFile) {
		cerr << "Unable to open file";
	}
	else {
		int j = 1; // which line are we in
		while (getline(inFile, line)) {
			//sum += '\n';
			//sum += line;
			
			int curr = 0; // get indicator for vars
			for (int i = 0; i < line.length();i++) {
				
				if (line[i] != ' ') {
					// get sn sf sv
					if (j == 1) { // first line
						
						if (curr == 0) {
							
							sn =  line[i]-'0';
							curr++;
						}else if (curr == 1) {
							
							sf = line[i]-'0';
							curr++;
						}else if (curr == 2) {
							
							sv = line[i]-'0';
							curr= 0;
						}
					}

					// get n f v for four regions

					if (j >= 2 && j<= 5) {
						if (curr == 0) {
							n[j - 2] = line[i] - '0';
							curr++;
						}
						else if (curr == 1) {
							f[j - 2] = line[i] - '0';
							curr++;
						}
						else if (curr == 2) {
							v[j - 2] = line[i] - '0';
							curr = 0;
						}
					}

					// get number of timestamps 

					if (j == 6) {
						autoS = line[i] - '0';
					}
					//get number of events 

					if (j == 7) {
						m = line[i] - '0';
					}
				}


				
			}
			


			j++;
		}
		inFile.close();
		//cout << "Sum = " << sum << endl;
		cout << sn << " " << sf << " " << sv << endl;
		for (int k = 0; k < 4; k++) {
			cout << " normal regions " << n[k] << endl;
			cout << " frozen regions " << f[k] << endl;
			cout << " vip regions " << v[k] << endl;
		}
		cout << "time stamp " << autoS << endl;
		cout << " no of events " << m <<endl;
	}

	
}


load::~load()
{
}
