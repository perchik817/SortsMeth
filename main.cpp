#include <iostream>
#include <random>
#include <vector>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <chrono>

// 1. Удалить в массиве первую группу из двух подряд идущих одинаковых чисел.
// Если удаление элементов невозможно, выдать об этом сообщение.

// 2. Вставить заданное значение после каждого элемента массива, 
// расположенного после первого нулевого элемента. 
// Если вставка элементов невозможна, выдать об этом сообщение.

void pasteAfterZero(std::vector<int>& array, int& y) {
	std::cout << "pasteAfterZero" << std::endl;
	int num, n = array.size();
	array.resize(n * 2 - y);

	std::cout << "Enter an element: ";
	std::cin >> num;
	std::cout << std::endl;

	// insert the number after the first element
	for (int i = n - 1; i >= y; i--) {
		array[i * 2] = array[i];
		array[i * 2 - 1] = num;
	}
	array[1] = num;
	array[n * 2 - 1] = num;

	for (int k = 0; k < n * 2; k++) {
		std::cout << array[k] << " ";
	}
}



void deleteConsecutiveDuplicates(std::vector<int>& array) {
	std::cout << "deleteConsecutiveDuplicates" << std::endl;
	bool found = false;
	int n = array.size();
	int i = 0, j = 0, k = 0;

	while (i < n) {
		int j = i + 1;

		while (j < n && array[j] == array[i]) {
			j++;
		}

		if (j - i > 1) { // Found a group of identical numbers
			found = true;

			for (int k = j; k < n; k++) { // Shift remaining elements to the left
				array[k - (j - i)] = array[k];
			}
			n -= j - i; // Update the array size
			std::cout << "Updated array: ";

			for (int i = 0; i < n; i++) {
				std::cout << array[i] << " ";
			}
			std::cout << std::endl;
		}
		else {
			i++;
		}
	}
	if (!found) {
		std::cout << "No consecutive duplicates found." << std::endl;
	}	
}



void bubbleSort(std::vector<int>& array) {
	std::cout << "bubbleSort" << std::endl;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	int n = array.size();
	int count = 0;

	for (int i = 0; i < n - 1; i++) {

		for (int j = 0; j < n - i - 1; j++) {

			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				count++;
			}
		}

		std::cout << "Sorted array: ";
		for (int i = 0; i < array.size(); i++) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
	}

	/*std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "count: " << count;
	std::cout << "time difference: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();*/
}



void lowDensitySort(std::vector<int>& array) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	int n = array.size();
	int count = 0;

	int gap = n / 2;
	while (gap > 0) {
		for (int i = gap; i < n; i++) {
			int temp = array[i];
			int j = i;
			while (j >= gap && array[j - gap] > temp) {
				array[j] = array[j - gap];
				j -= gap;
			}
			array[j] = temp;
		}
		std::cout << "Updated array: ";
		for (int i = 0; i < n; i++) {
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;

		gap /= 2;
		count++;
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "count: " << count << std::endl;
	std::cout << "time difference: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
}



void merge(std::vector<int>& array, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (i = 0; i < n1; i++) {
        L[i] = array[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = array[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void batcherSort(std::vector<int>& array, int l, int r) {
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	int count = 0;

    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    batcherSort(array, l, mid);
    batcherSort(array, mid + 1, r);
    for (int i = l; i <= mid; i++) {
        for (int j = mid + 1; j <= r; j++) {
            if (array[i] > array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
				count++;
            }
        }
    }
    for (int k = mid; k > l; k--) {
        for (int i = l, j = k; j < r; i++, j++) {
            if (array[i] > array[j + 1]) {
                int temp = array[i];
                array[i] = array[j + 1];
                array[j + 1] = temp;
				count++;
            }
        }
    }
	/*std::cout << "Updated array: ";
	for (int x = 0; x < array.size(); x++) {
		std::cout << array[x] << " ";
	}std::cout << std::endl;*/

	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "count: " << count << std::endl;
	//std::cout << "time difference: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
}


int main() {
	int l, m;
	std::cout << "Enter a number of elements in array: ";
	std::cin >> l;
	std::cout << std::endl;
	std::cout << "Enter a maximum value of a number: ";
	std::cin >> m;
	std::cout << std::endl;
	
	std::vector<int> array = {};
	array.reserve(l);

	for (int x : array) {
		std::cout << x << " ";
	}

	for (int s = 0; s < l; s++) {
		array.push_back(l);
	}

	srand(time(NULL));

	std::cout << "Original array: ";
	for (int i = 0; i < array.size(); i++) {
		array[i] = round(rand() % m);
		std::cout << array[i] << ", ";
		
	}
	std::cout << std::endl;

	/*for (int y = 0; y < array.size(); y++) {
		if (array[y] == 0) {
			pasteAfterZero(array, y);
		}
		else {
			std::cout << "Insertion is not possible.";
		}
	}*/
	
	
	//deleteConsecutiveDuplicates(array);

	//bubbleSort(array);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	batcherSort(array, 0, array.size() - 1);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "time difference: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	
	//lowDensitySort(array);
	return 0;
}