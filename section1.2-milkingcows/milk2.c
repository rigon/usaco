/*
ID: ricar.g1
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <stdlib.h>

int compar(const void *a, const void *b) {
	int *aa = (int *) a;
	int *bb = (int *) b;
	return aa[1] > bb[1];
}

int main() {
    FILE *fin  = fopen ("milk2.in", "r");
    FILE *fout = fopen ("milk2.out", "w");

	int n, i, j, lm = 0, ln = 0;
	int m[5000][2];

	fscanf(fin, "%d", &n);

	for(i=0; i<n; i++) {
		fscanf(fin, "%d %d", &m[i][0], &m[i][1]);
	}

	// Merge overlapping intervals
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if(m[i][1] >= m[j][0] && m[i][0] < m[j][0])
				m[j][0] = m[i][0];
			
			if(m[i][0] <= m[j][1] && m[i][1] > m[j][1])
				m[j][1] = m[i][1];
		}
	}

	// Sort by finishing times
	qsort(m, n, sizeof(int[2]), compar);

	for(i=0; i<n; i++) {
		// Find longest time interval at least one cow was milked
		if(m[i][1] - m[i][0] > lm)
			lm = m[i][1] - m[i][0];
		// Find longest time interval (after milking starts) during which no cows were being milked
		if(i>0 && m[i][0] - m[i-1][1] > ln)
			 ln = m[i][0] - m[i-1][1];
	}

	//for(i=0; i<n; i++)
	//	fprintf(fout, "[%d] %d %d\n", i, m[i][0], m[i][1]);

	fprintf(fout, "%d %d\n", lm, ln);

	return 0;
}
