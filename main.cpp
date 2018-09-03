#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

class Kayak{
	private: bool check_input(int, int, int);
	private: bool check_duplicates(int[], int);
	public: int num_teams_cant_start();
};

bool Kayak::check_duplicates(int array[], int n){
	for (int i = 1; i <= n; i++){
		for (int j = 2; j <= n; j++){
			if (array[i] == array[j]) return false;
			else break;
		}
		break;
	}
	return true;
}

int Kayak::num_teams_cant_start(){
	int n = 0, s = 0, r = 0, count = 0;
	
	// reading and checking input
	cin >> n >> s >> r;
	if (check_input(n, s, r) == false) return 0;
	
	// initializing values
	bool has_reserve[n];
	bool is_damaged[n];
	for (int i = 0; i <= n; i++) {
		has_reserve[i] = 0;
		is_damaged[i] = 0;
	}
	
	// reading in damaged kayaks
	int damaged_kayaks[s];
	for (int j = 1; j <= s; j++){
		int num = damaged_kayaks[j];
		cin >> num;
		is_damaged[num] = 1;
	}
	if (check_duplicates(damaged_kayaks, s) == false) return 0;
	
	// reading in teams with reserve kayaks
	int reserve_kayaks[r];
	for (int k = 1; k <= r; k++){
		int num = reserve_kayaks[k];
		cin >> num;
		has_reserve[num] = 1;		
	}
	if (check_duplicates(reserve_kayaks, r) == false) return 0;
	
	// teams with damaged kayaks will use their own reserve
	for (int q = 1; q <= n; q++){
		if ((has_reserve[q] == true) && (is_damaged[q] == true)){
			is_damaged[q] = false;
			has_reserve[q] = false;
		}
	}
	
	// lending reserve kayaks to teams with damaged kayaks
	for (int b = 1; b <= n; b++){
		if ((is_damaged[b] == 1) && (has_reserve[b] == 0)){
			if (has_reserve[b - 1] == 1){
				has_reserve[b - 1] = 0;
				is_damaged[b] = 0;
			}
			else if (has_reserve[b + 1] == 1){
				has_reserve[b + 1] = 0;
				is_damaged[b] = 0;
			}
		}
	}
	
	// counting teams that still have a damaged kayak
	for (int a = 1; a <= n; a++) if (is_damaged[a] == 1) count += 1;
	
	return count;
}

bool Kayak::check_input(int n, int s, int r){
	if ((n < 2) || (n > 10)) return false;
	if ((s < 2) || (s > n))	return false;
	if ((r < 1) || (r > n)) return false;
	return true;
}

int main(){
	Kayak k;
	cout << k.num_teams_cant_start();
	return 0;
}
