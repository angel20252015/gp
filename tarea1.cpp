// Example program
#include <iostream>
#include <string>


int PerimetroRectangulo(int base, int altura)
{
	return base * 2 + altura * 2;
}

float AreaTriangulo(float base, float altura)
{
	return (base*altura) / 2;
}

int Mayor(int numero1, int numero2, int numero3)
{
	int n = numero1;
	if (numero2 > n)
	{
		n = numero2;
	}
	if (numero3 > n)
	{
		n = numero3;
	}
	return n;
}

int Menor(int numero1, int numero2, int numero3)
{
	int n = numero1;
	if (numero2 < n)
	{
		n = numero2;
	}
	if (numero3 < n)
	{
		n = numero3;
	}
	return n;
}

void FilaEstrellas(int n)
{
	int n1 = 0;
	while (n1<n)
	{
		std::cout << "*";
		n1++;
	}
}

void MatrizEstrellas(int n)
{
	int n2 = 0;
	while (n2<n)
	{
		int n1 = 0;
		while (n1<n)
		{
			std::cout << "*";
			n1++;
		}
		n2++;
		std::cout << "\n";
	}
}

void PiramideEstrellas(int n)
{
	int n2 = 0;
	while (n2<n)
	{
		int n1 = 0;
		while (n1 <= n2)
		{
			std::cout << "*";
			n1++;
		}
		n2++;
		std::cout << "\n";
	}
}

void Fibonacci(int n)
{
	int n1 = 1;
	int n2 = 1;
	int n3 = 0;
	int c = 0;
	if (n == 1) {
		std::cout << "1";
	}
	else {
		std::cout << "1 1" << " ";
		while (c < n - 2)
		{
			n3 = n1 + n2;
			n1 = n2;
			n2 = n3;
			std::cout << n3 << " ";
			c++;
		}
	}
}

bool EsPrimo (int numero) 
{
	int n = 2;
	bool primo = true;
	while (n < numero) 
	{
		if (numero%n == 0) 
		{
			primo = false;
		}
		n++;
	}
	return primo;
}
/**int main()
{
	PiramideEstrellas(4);
	std::cout << EsPrimo(4);
	getchar();
	return 0;
}**/
