#include<bits/stdc++.h>
#include<fstream>

using namespace std;
class ChanceLRU {
	private:
		int frame_size, page_faults, pointer, page_hits;
		int *arr;
		bool *second_chance;
		void replaceAndUpdate(int page) {
			page_faults++;
			while(true) {
				if(!second_chance[pointer]) {
					arr[pointer] = page;
					pointer = (pointer + 1) % frame_size;
					break;
				}
				second_chance[pointer] = false;
				pointer = (pointer + 1) % frame_size;
			}
		}
	
	public:
		ChanceLRU(int size) {
			page_faults=0;
			pointer=0;
			page_hits=0;
			frame_size = size;
			arr = (int*)calloc(sizeof(int), frame_size);
			second_chance = (bool*)calloc(sizeof(int), frame_size);
			for(int i=0; i<frame_size; i++)second_chance[i] = 0; //initialize with 0 to show no second chance
			for(int i=0; i<frame_size; i++)arr[i] = 0; //initialize with -1 to make it empty
		}
		void findAndUpdate(int page) {
			bool found = false;
			for(int i=0; i<frame_size; i++) {
				if(arr[i] == page) {
					second_chance[i] = true;
					found = true;
					page_hits++;
					break;	
				}
			}
			if(found == false) {
				replaceAndUpdate(page);
			}
		}
		void printData() {
			cout<<"Number of hits : "<<page_hits<<endl;
			cout<<"Number of faults : "<<page_faults<<endl;
		}
	
};
vector<int> createData(string file_name) { //dirty hack for getting only numbers between 0 and 9
char ch;
vector<int>pages;
fstream fin(file_name.c_str(), fstream::in);
while (fin  >> ch) {
    int num = int(ch) - int('0'); 
    if(num>0 && num<10) {
    	pages.push_back(num);
	}
}
return pages;
}
int main() {
	
	int frame_size;
	vector<int> pages;
	string file_name;
	cout<<"Enter name of file"<<endl;
	cin>>file_name;
	cout<<"Enter number of frames"<<endl;
	cin>>frame_size;
	pages = createData(file_name);
	cout<<"Number of pages "<<pages.size()<<endl;
	ChanceLRU cache(frame_size);
	auto start = std::chrono::high_resolution_clock::now();
	for(int i=0; i<pages.size(); i++)cache.findAndUpdate(pages.at(i));
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout<<"Elapsed time "<<elapsed.count()<<endl;
	cache.printData();
	
}
