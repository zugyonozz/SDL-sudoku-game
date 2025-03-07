#include <iostream>
using namespace std;

int main(){
	int counter = 1;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			cout << counter << "\t";
			counter++;
		}
		cout << endl << endl;
	}

	return 0;
}