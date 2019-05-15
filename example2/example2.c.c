#include<stdio.h>
int yatay[225], dikey[225], sonuc[225];
int ismyword(int, int);
void resultpuzzle(int x, int y, int result);
int length;
char input[16];
char stars[15][15];
char puzzle[15][16] = { "GSLNFRNPRENDPOR", "NANFDKUOLMKIACN", "IFVACSFPTAASROH",
		"LEPIISINRSTNTAA", "ISRLIRLNMIYIDYD", "ABTLAIDGSOSRTER",
		"WUENGTNAFISIDGR", "GNAHEINSHSVSMOO", "CHTONVIECAPSSTB",
		"LOAIUBRACKETEOR", "WIADETNUOMRRLTO", "RTGERMSEUEIEIHW",
		"EFSHADRIEFEPTEN", "ASWITCHDTPLAQUE", "DNERGSHELESPACN" };
int main() {
	int sonucindex;
	int i = 0;
	int j = 0;
	scanf("%s", &input);
	while (input[i] != '\0') {
		i++;
	}
	length = i;
	sonucindex = 0;
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 16; j++) {
			if (puzzle[i][j] == input[0]) {
				int result = ismyword(i, j);
				if (result != 0) {
					yatay[sonucindex] = i;
					dikey[sonucindex] = j;
					sonuc[sonucindex] = result;
					sonucindex++;
				}
			}

		}
	}
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 16; j++) {
			stars[i][j] = '*';
		}
	}
	for (i = 0; i < sonucindex; i++) {
		resultpuzzle(yatay[i], dikey[i], sonuc[i]);
	}

	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			printf("%c", stars[i][j]);
		}
		printf("\n");
	}

	return 0;
}
void resultpuzzle(int x, int y, int result) {
	int k;

	if (result == 1) {
		for (k = 0; k < length; k++) {
			stars[x][y + k] = input[k];
		}
	}
	if (result == 2) {
		for (k = 0; k < length; k++) {
			stars[k + x][y] = input[k];
		}
	}
	if (result == 3) {
		for (k = 0; k < length; k++) {
			stars[x + k][y + k] = input[k];
		}
	}
}

int ismyword(int i, int j) {
	int k;
	int yataybulundu = 1;
	int dikeybulundu = 1;
	for (k = 1; k < length; k++) {
		if (puzzle[i][j + k] != input[k]) {
			yataybulundu = 0;
			break;
		}
	}
	for (k = 1; k < length; k++) {
		if (puzzle[i + k][j] != input[k]) {
			dikeybulundu = 0;
			break;
		}
	}
	if (yataybulundu == 1 && dikeybulundu == 1)
		return 3;
	if (yataybulundu == 1)
		return 1;
	if (dikeybulundu == 1)
		return 2;
	else
		return 0;
}
