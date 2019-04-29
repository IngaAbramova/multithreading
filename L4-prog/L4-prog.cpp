
#include "pch.h"
#include <iostream>
#include <thread>
#include <ctime>
using namespace std;
//Объявляем массивы целых чисел
int *a,*h;
void f1(int &sum, int n)
{
	//Сортируем массив
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	//Находим сумму всех элементов массива
	for (int i = 0; i < n; i++)
	{
		 sum += a[i];
	}
	sum = sum / 1000000;
}
void f2(int &sum, int n)
{
	//Сортируем массив
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (h[j] < h[j + 1]) {
				// меняем элементы местами
				int temp = h[j];
				h[j] = h[j + 1];
				h[j + 1] = temp;
			}
		}
	}
	//Находим сумму всех элементов массива
	for (int i = 0; i < n; i++)
	{
		sum += h[i];
	}
	sum = sum / 1000000;
}
int main()
{
	cout << "Enter number of elements: ";
	int n;
	cin >> n;
	a = new int[n];
	h = new int[n];
	int Sum1, Sum2, Sum3, Sum4;
	//Генерируем элементы массивов
	for (int i = 0; i < n;i++)
	{
		a[i] = rand();
		h[i] = rand();
	}
	chrono::time_point<chrono::high_resolution_clock> first, end;
	//Определяем время начала выполнения последовательного процесса
	first = chrono::high_resolution_clock::now();
	//Вызываем функции для последовательного выполнения
	f1(ref(Sum3),n);
	f2(ref(Sum4),n);
	//Определяем время конца выполнения последовательного процесса
	end = chrono::high_resolution_clock::now();
	//Определяем время выполнения послеовательного процесса
	chrono::duration<float> duration_sequential = end - first;
	//Определяем время начала выполнения параллельного процесса
	first = chrono::high_resolution_clock::now();
	//Вызываем функции f1 и f2 для выполнения в отдельных потоках
	thread t1(f1,ref(Sum1),n);
	thread t2(f2,ref(Sum2),n); 
	if (t1.joinable())
		t1.join();
	if (t2.joinable())
		t2.join();
	//Определяем время конца выполнения параллельного процесса
	end = chrono::high_resolution_clock::now();
	//Определяем время выполнения параллельного процесса
	chrono::duration<float> duration_parallel = end - first;
	cout << endl;
	//Выводим суммы элементов двух массивов на экран
	cout << "Sequential process(result): " << Sum1 + Sum2 << endl;
	cout << "Parallel process(result): " << Sum3 + Sum4 << endl;
	cout << "Sequential process(duration): " << duration_sequential.count() << endl;
	cout << "Parallel process(duration): " << duration_parallel.count() << endl;
	return 0;
}
