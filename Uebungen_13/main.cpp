#include <cstdio>
#include <cstdlib>

#include <fstream>


int main() {
	std::ifstream file;
	file.open("../text.txt");

	if(!file.is_open()) {
		printf("Error opening file\n");
		return 1;
	}

	int counts[26]{};

	int total = 0;

	while(!file.eof()) {
		char c;
		file.read(&c, 1);

		int index = -1;
		if(c >= 'A' && c <= 'Z')
			index = c - 'A';
		if(c >= 'a' && c <= 'z')
			index = c - 'a';

		if(index != -1) {
			counts[index]++;
			total++;
		}
	}

	// float rel[26]{};
	// for(int i = 0; i < 26; i++)
	// 	rel[i] = counts[i] * 100. / total;

	for(int i = 0; i < 26; i++)
		printf("Anzahl[%c] = %d\n", 'A'+i, counts[i]);

	for(int i = 0; i < 26; i++)
		printf("Anzahl[%c] = %f\n", 'A'+i, counts[i] * 100. / total);
	return 0;
}