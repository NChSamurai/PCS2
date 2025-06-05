#include <iostream>
#include <fstream>
#include <cstdlib>

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

        int summ = 0;
#pragma omp parallel
        {
                int localSumm = 0;
#pragma omp for
        for(int i = 0; i < index; i++){
                localSumm += array[i];
        }

#pragma omp critical
        summ += localSumm;

        };
        std::cout << summ;
delete[] array;
return 0;
}

