#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cstdlib>
#include <algorithm>

// Функция для загрузки массива из файла
void loadArrayFromFile(const std::string& filename, double* arr, size_t size) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    for (size_t i = 0; i < size; ++i) {
        if (!(file >> arr[i])) {
            throw std::runtime_error("Ошибка чтения данных из файла: " + filename);
        }
    }
}

// Функция для вывода массива
void printArray(const double* arr, size_t size) {
    const size_t print_count = std::min(size, static_cast<size_t>(10));
    for (size_t i = 0; i < print_count; ++i) {
        std::cout << arr[i] << " ";
    }
    if (size > 10) {
        std::cout << "...";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // Получаем размер из переменной окружения
    const char* size_env = std::getenv("SIZE");
    if (!size_env) {
        std::cerr << "Ошибка: переменная окружения SIZE не установлена" << std::endl;
        return 1;
    }

    const size_t SIZE = std::stoul(size_env);
    if (SIZE <= 0) {
        std::cerr << "Размер массива должен быть положительным числом" << std::endl;
        return 1;
    }

    // Создаем массивы
    double* array1 = new double[SIZE];
    double* array2 = new double[SIZE];
    double* resultAdd = new double[SIZE];
    double* resultSub = new double[SIZE];
    double* resultMul = new double[SIZE];
    double* resultDiv = new double[SIZE];

    try {
        loadArrayFromFile("array.txt", array1, SIZE);
        loadArrayFromFile("array2.txt", array2, SIZE);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        delete[] array1;
        delete[] array2;
        delete[] resultAdd;
        delete[] resultSub;
        delete[] resultMul;
        delete[] resultDiv;
        return 1;
    }

#pragma omp parallel for
    for (size_t i = 0; i < SIZE; ++i) {
        resultAdd[i] = array1[i] + array2[i];
        resultSub[i] = array1[i] - array2[i];
        resultMul[i] = array1[i] * array2[i];

        // Проверка на деление на ноль
        if (array2[i] != 0) {
            resultDiv[i] = array1[i] / array2[i];
        } else {
            resultDiv[i] = std::numeric_limits<double>::quiet_NaN();
        }
    }

    // Освобождение памяти
    delete[] array1;
    delete[] array2;
    delete[] resultAdd;
    delete[] resultSub;
    delete[] resultMul;
    delete[] resultDiv;

    return 0;
}
