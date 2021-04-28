#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include<math.h>
#include <vector>

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
int sito(int start,int end) {
	int pierw = floor(sqrt(end));
	int* tab = new int[pierw - 1];
	int licznik = 0;
	omp_set_num_threads(4);
	int suma = 0;

	// int ma 4 bajty wiec trzeba przemnozyc przez 16 dla kolejnej lini pamieci

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
#pragma omp parallel
		{
#pragma omp for	nowait
		for (int i = 0; i < licznik; i++) {
			for (int j = i; j < licznik; j++) {
				int nie_pierwsza = tab[i] * tab[j];
				while (nie_pierwsza <= end && tab[i]==tab[j]) {
					if (nie_pierwsza >= start) {
						pierwsze[nie_pierwsza - start] = 0;
					}
					nie_pierwsza = nie_pierwsza + tab[j];

				}
			}
		}
	}
		for (int i = 0; i < (end - start + 1); i++) {
			if (pierwsze[i] != 0) {
				suma += 1;
			}
		}	

	
	printf("w przedziale %d do %d mamy %d liczb pierwszych \n", start, end, suma);
	

	delete[] tab;
	return suma;
}
void testing() {
	FILE* ftests;
	FILE* fresults;
	ftests= fopen("tests/tests.txt", "r");
	fresults = fopen("tests/results.txt", "wb");

	int numberArray[16];
	int ile;
	int min, max;
	if (ftests == NULL) {
		perror("Failed: ");
	}
	fscanf_s(ftests, "%d", &ile);
	printf("%d", ile);
	for (int i = 0; i < ile; i++)
	{
		fscanf_s(ftests, "%d %d",&min,&max );
		int result = sito(min, max);
		fprintf(fresults, "%d\n", result);
	}

	fclose(ftests);
	fclose(fresults);

}
int main(int argc, char* argv[])
{
	int badana_liczba;
	clock_t start, stop;
	//testing();
	start = clock();
	sito(14077,94216);
	stop = clock();
	/*int ile = 0;
	for (int i = start; i <= end; i++) {
		if (pierwsza(i)) {
			ile++;
		}
	}
	*/
	printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / 1000.0));

	return 0;
}
