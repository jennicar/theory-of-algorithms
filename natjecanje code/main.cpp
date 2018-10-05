#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

bool check_duplicates(int array[], int n){
	for (int i = 1; i <= n; i++){
		for (int j = 2; j <= n; j++){
			if (array[i] == array[j]) return false;
			else break;
		}
		break;
	}
	return true;
}

bool check_input(int n, int s, int r){
	if ((n < 2) || (n > 10)) return false;
	if ((s < 2) || (s > n))	return false;
	if ((r < 1) || (r > n)) return false;
	return true;
}

int main(){
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
	if (check_duplicates(damaged_kayaks, s) == false) return false;
	
	// reading in teams with reserve kayaks
	int reserve_kayaks[r];
	for (int k = 1; k <= r; k++){
		int num = reserve_kayaks[k];
		cin >> num;
		has_reserve[num] = 1;		
	}
	if (check_duplicates(reserve_kayaks, r) == false) return false;
	
	// lending reserve kayaks to teams with damaged kayaks
	for (int b = 1; b <= n; b++){
		if ((has_reserve[b] == true) && (is_damaged[b] == true)){
			is_damaged[b] = false;
			has_reserve[b] = false;
		}
		if ((is_damaged[b] == true) && (has_reserve[b] == false)){
			if (has_reserve[b - 1] == true){
				has_reserve[b - 1] = false;
				is_damaged[b] = false;
			}
			else if (has_reserve[b + 1] == true){
				has_reserve[b + 1] = false;
				is_damaged[b] = false;
			}
		}
	}
	
	// counting teams that still have a damaged kayak
	for (int a = 1; a <= n; a++) if (is_damaged[a] == 1) count += 1;
	
	cout << count;
	return 0;
}
