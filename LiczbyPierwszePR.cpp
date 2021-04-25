#include <stdio.h>
#include <time.h>
#include <omp.h>
#include<math.h>
#include <vector>

#define start 2 
#define end 200000

bool pierwsza(int x) {
	double pierw;
	pierw = sqrt(x);
	int pierw2 = floor(pierw);
	for (int i = 2; i <= pierw2; i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;

}
void sito() {
	static const int pierw = floor(sqrt(end));
	int* table = new int[pierw];
	int* tab = new int[pierw - 1];
	int licznik = 0;

	for (int i = 2; i <= pierw; i++) {
		if (pierwsza(i)) {
			tab[licznik] = i;
			licznik += 1;
		}
	}
	int* pierwsze = new int[end - start + 1];
	for (int k = 0; k < (end - start + 1); k++) {
		pierwsze[k] = start + k;
	}
	printf("%d\n", tab[licznik - 1]);
	omp_set_num_threads(4);
#pragma omp parallel
	{
#pragma omp for nowait	
		for (int i = 0; i < licznik; i++) {
			for (int j = i; j < licznik; j++) {
				int nie_pierwsza = tab[i] * tab[j];
				while (nie_pierwsza <= end) {
					if (nie_pierwsza >= start) {
						pierwsze[nie_pierwsza - start] = 0;
					}
					nie_pierwsza = nie_pierwsza + tab[j];

				}
			}
		}
	}
	int suma = 0;
	for (int i = 0; i < (end - start + 1); i++) {
		if (pierwsze[i] != 0) {
			suma += 1;
		}
	}
	printf("w przedziale %d do %d mamy %d liczb pierwszych \n", start, end, suma);
	delete[] table;
	delete[] pierwsze;
	delete[] tab;
}
int main(int argc, char* argv[])
{
	clock_t start_time, stop_time;
	int badana_liczba;

	start_time = clock();
	sito();
	stop_time = clock();
	printf("Czas przetwarzania dla drugiego podejscia wynosi %f sekund\n", ((double)(stop_time - start_time) / 1000.0));
	start_time = clock();
	int ile = 0;
	for (int i = start; i <= end; i++) {
		if (pierwsza(i)) {
			ile++;
		}
	}
	stop_time = clock();

	printf("Czas przetwarzania dla pierwszego podejscia wynosi %f sekund, mamy %d liczb pierwszych\n", ((double)(stop_time - start_time) / 1000.0), ile);
	return 0;
}
