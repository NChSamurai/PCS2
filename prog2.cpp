#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <iomanip>

double getTime(){
    auto now = std::chrono::high_resolution_clock::now();

    // Преобразуем в количество секунд с дробной частью
    auto duration = now.time_since_epoch();
    double seconds = std::chrono::duration<double>(duration).count();

    // Округляем до 5 знаков после запятой
    seconds = std::round(seconds * 1e5) / 1e5;

    return seconds;
}

void appendTimeToBinaryFile(double timeValue) {
    // Открываем файл в режиме добавления бинарных данных
    std::ofstream outfile("GeneralTime.bin", std::ios::binary | std::ios::app);

    if (!outfile) {
        std::cerr << "Ошибка открытия файла GeneralTime.bin" << std::endl;
        return;
    }

    // Записываем значение double в файл
    outfile.write(reinterpret_cast<const char*>(&timeValue), sizeof(double));

    // Проверяем успешность записи
    if (!outfile.good()) {
        std::cerr << "Ошибка записи в файл" << std::endl;
    }

    outfile.close();
}

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

                quickSort(arr, low, pi - 1);
                quickSort(arr, pi + 1, high);
        }
}

int main(int argc, char* argv[]) {
        if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <размер_массива>" << std:                   :endl;
        return 1;
    }


    const int SIZE = atoi(argv[1]);
    if (SIZE <= 0) {
        std::cerr << "Размер массива должен быть положительным числом" << std::e                   ndl;
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
        double startTime = getTime();
        quickSort(array, 0, index - 1);
        double endTime = getTime();
        std::ofstream out("arraySorted.txt");
        for (int i = 0; i < index; i++){
                out << index << '\n';
        }
        out.close();
        std::cout << endTime - startTime << "\n";
        appendTimeToBinaryFile(double (endTime - startTime));
        delete[] array;
        return 0;
}
[chernousov.nikita2005.gmail.com@mgr Lab2]$ ^C
[chernousov.nikita2005.gmail.com@mgr Lab2]$ cat progOpenMp2.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <iomanip>

double getTime(){
    auto now = std::chrono::high_resolution_clock::now();

    // Преобразуем в количество секунд с дробной частью
    auto duration = now.time_since_epoch();
    double seconds = std::chrono::duration<double>(duration).count();

    // Округляем до 5 знаков после запятой
    seconds = std::round(seconds * 1e5) / 1e5;

    return seconds;
}

void appendTimeToBinaryFile(double timeValue) {
    // Открываем файл в режиме добавления бинарных данных
    std::ofstream outfile("GeneralTime.bin", std::ios::binary | std::ios::app);

    if (!outfile) {
        std::cerr << "Ошибка открытия файла GeneralTime.bin" << std::endl;
        return;
    }

    // Записываем значение double в файл
    outfile.write(reinterpret_cast<const char*>(&timeValue), sizeof(double));

    // Проверяем успешность записи
    if (!outfile.good()) {
        std::cerr << "Ошибка записи в файл" << std::endl;
    }

    outfile.close();
}

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

            quickSort(arr, low, pi - 1);

            quickSort(arr, pi + 1, high);


                }
        }


void parallelQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Порог для переключения на последовательную версию
        if (high - low > 10000) {  // Оптимальное значение зависит от системы
            #pragma omp task shared(arr)
            parallelQuickSort(arr, low, pi - 1);

            #pragma omp task shared(arr)
            parallelQuickSort(arr, pi + 1, high);

            #pragma omp taskwait  // Ожидаем завершения обеих задач
        } else {
            quickSort(arr, low, high);
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
        double startTime = getTime();
        #pragma omp parallel
        {
        #pragma omp single
        parallelQuickSort(array, 0, index - 1);
        }
        double endTime = getTime();
        std::ofstream out("arraySorted.txt");
        for (int i = 0; i < index; i++){
                out << array[i] << '\n';
        }
        out.close();

        std::cout << endTime - startTime << "\n";
        appendTimeToBinaryFile(double (endTime - startTime));
        delete[] array;
        return 0;
}
