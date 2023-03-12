#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS

void OutputMatr(double** mas, int m) {
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			printf("%5.2lf", mas[i][j]);
		}
		printf("\n");
	}
}

void InputMatr(double** mas, double** p, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < (m - 1); ki++) {
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) {
			if (kj == j) dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}

double Det(double** mas, int m) {
	int i, j, k, n;
	double** p;
	double d;
	p = (double**)calloc(m, sizeof(double));
	for (i = 0; i < m; i++) {
		p[i] = (double*)calloc(m, sizeof(double));
	}
	j = 0; d = 0;
	k = 1;
	n = m - 1;
	if (m < 1) printf("Невозможно вычислить определитель!\n");
	if (m == 1) {
		d = mas[0][0];
	}
	if (m == 2) {
		d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
	}
	if (m > 2) {
		for (i = 0; i < m; i++) {
			InputMatr(mas, p, i, 0, m);
			d = d + k * mas[i][0] * Det(p, n);
			k = -k;
		}
	}
	return(d);
}



void CopyMatrix(double** input, double** output, int m)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			output[i][j] = input[i][j];
}

double** CallocMatrix(int m)
{
	double* data = (double*)calloc(m * m, sizeof(double));
	double** matrix = (double**)calloc(m, sizeof(double*));
	for (int i = 0; i < m; ++i)
		matrix[i] = &data[m * i];
	return matrix;
}

double** change_column(double** matrix, double* vector, int m, int column_id)
{
	double** new_matrix = CallocMatrix(m);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			if (j == column_id)
				new_matrix[i][j] = vector[i];
			else
				new_matrix[i][j] = matrix[i][j];
	return new_matrix;
}


int main() {
	int m, i, j;
	int x;
	double DetTemp, d;

	setlocale(LC_ALL, "Rus");
	printf("Размерность матрицы: ");
	scanf_s("%d", &m);
	double** mas = (double**)calloc(m, sizeof(double));
	for (i = 0; i < m; i++) {
		mas[i] = (double*)calloc(m, sizeof(double));
		for (j = 0; j < m; j++) {
			printf("mas[%d][%d] = ", i, j);
			scanf_s("%lf", &mas[i][j]);
		}
	}

	d = Det(mas, (double)m);
	printf("Определитель матрицы: %lf\n", d);


	double* X = (double*)calloc(m, sizeof(double));
	double* root = (double*)calloc(m, sizeof(double));

	printf("Введите вектор свободных членов: ");
	for (int i = 0; i < m; i++) {
		scanf_s("%lf", &X[i]);
	}

	DetTemp = Det(mas, (double)m);

	OutputMatr(mas, m);

	for (j = 0; j < m; j++) {
		double** d = change_column(mas, X, m, j);
		double determinant = Det(d, m);
		double rot = determinant / DetTemp;
		printf("x%d: %5.2lf\n", j + 1, rot);
	}
	system("pause");
	return 0;
}




