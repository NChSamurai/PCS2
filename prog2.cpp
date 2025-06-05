#include <iostream>
#include <fstream>
#include <cstdlib>

int partition(int arr[], int low, int high){
        int pivot = arr[high];
        int i =(low - 1);

        for (int j = low; j <= high - 1; j++) {
                if (arr[j] < pivot) {
                        i++;
                        std::swap(arr[i], arr[j]);
                }
        }
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
}

void quickSort(int arr[], int low, int high) {
        if (low < high) {
                int pi = partition(arr, low, high);

        #pragma omp parallel sections if (high - low > 1000)
                {
                #pragma omp section

                quickSort(arr, low, pi - 1);

                #pragma omp section
                quickSort(arr, pi + 1, high);
                }
        }
}

int main(int argc, char* argv[]) {
        if (argc < 2) {
                std::cerr << "Использование: " << argv[0] << " <размер_массива>" << std::endl;
                return 1;
        }


        const int SIZE = atoi(argv[1]);
        if (SIZE <= 0) {
                std::cerr << "Размер массива должен быть положительным числом" << std::endl;
                return 1;
        }

        std::ifstream file("array.txt");
        if (!file.is_open()) {
                std::cerr << "Ошибка открытия файла :(" << std::endl;
                return 1;
        }

        int* array = new int[SIZE];
        int index = 0;

        while (index < SIZE && file >> array[index]) {
                index++;
        }

        file.close();
        quickSort(array, 0, index - 1);
        std::ofstream out("arraySorted.txt");
        for (int i = 0; i < index; i++){
                out << index << '\n';
        }
        out.close();
        delete[] array;
        return 0;
}

