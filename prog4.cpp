#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cstdlib>
#include <algorithm>
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
double startTime = getTime();

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
    double endTime = getTime();

    std::cout << endTime - startTime << "\n";

    appendTimeToBinaryFile(double (endTime - startTime));
    // Освобождение памяти
    delete[] array1;
    delete[] array2;
    delete[] resultAdd;
    delete[] resultSub;
    delete[] resultMul;
    delete[] resultDiv;

    return 0;
}
[chernousov.nikita2005.gmail.com@mgr Lab2]$ ^C
[chernousov.nikita2005.gmail.com@mgr Lab2]$ cat prog4new.cpp
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>
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

// Функция для загрузки матрицы из файла
void loadMatrixFromFile(const std::string& filename, double** matrix, size_t rows, size_t cols) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (!(file >> matrix[i][j])) {
                throw std::runtime_error("Ошибка чтения данных из файла: " + filename);
            }
        }
    }
}

// Функция для вывода первых 10x10 элементов матрицы
void printMatrix(double** matrix, size_t rows, size_t cols) {
    const size_t print_rows = std::min(rows, static_cast<size_t>(10));
    const size_t print_cols = std::min(cols, static_cast<size_t>(10));

    for (size_t i = 0; i < print_rows; ++i) {
        for (size_t j = 0; j < print_cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "..." << std::endl; // Указываем, что массив больше
    }
}

int main() {
    // Получаем размер из переменной окружения
    const char* rows_env = std::getenv("ROWS");
    const char* cols_env = std::getenv("COLS");

    if (!rows_env || !cols_env) {
        std::cerr << "Ошибка: переменные окружения ROWS и COLS должны быть установлены" << std::endl;
        return 1;
    }

    const size_t ROWS = std::stoul(rows_env);
    const size_t COLS = std::stoul(cols_env);

    if (ROWS == 0 || COLS == 0) {
        std::cerr << "Ошибка: размеры матрицы должны быть положительными числами" << std::endl;
        return 1;
    }

    // Выделяем память под матрицы
    double** matrix1 = new double*[ROWS];
    double** matrix2 = new double*[ROWS];
    double** resultAdd = new double*[ROWS];
    double** resultSub = new double*[ROWS];
    double** resultMul = new double*[ROWS];
    double** resultDiv = new double*[ROWS];

    for (size_t i = 0; i < ROWS; ++i) {
        matrix1[i] = new double[COLS];
        matrix2[i] = new double[COLS];
        resultAdd[i] = new double[COLS];
        resultSub[i] = new double[COLS];
        resultMul[i] = new double[COLS];
        resultDiv[i] = new double[COLS];
    }

    try {
        loadMatrixFromFile("matrix.txt", matrix1, ROWS, COLS);
        loadMatrixFromFile("matrix2.txt", matrix2, ROWS, COLS);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;

        // Освобождаем память в случае ошибки
        for (size_t i = 0; i < ROWS; ++i) {
            delete[] matrix1[i];
            delete[] matrix2[i];
            delete[] resultAdd[i];
            delete[] resultSub[i];
            delete[] resultMul[i];
            delete[] resultDiv[i];
        }
        delete[] matrix1;
        delete[] matrix2;
        delete[] resultAdd;
        delete[] resultSub;
        delete[] resultMul;
        delete[] resultDiv;

        return 1;
    }
double startTime = getTime();
#pragma omp parallel for
    for (size_t i = 0; i < ROWS; ++i) {
        for (size_t j = 0; j < COLS; ++j) {
            resultAdd[i][j] = matrix1[i][j] + matrix2[i][j];
            resultSub[i][j] = matrix1[i][j] - matrix2[i][j];
            resultMul[i][j] = matrix1[i][j] * matrix2[i][j];

            // Проверка на деление на ноль
            if (matrix2[i][j] != 0) {
                resultDiv[i][j] = matrix1[i][j] / matrix2[i][j];
            } else {
                resultDiv[i][j] = std::numeric_limits<double>::quiet_NaN(); // Если деление на ноль, записываем NaN
            }
        }
    }
double endTime = getTime();

std::cout << endTime - startTime << "\n";

appendTimeToBinaryFile(double (endTime - startTime));

    // Освобождаем память
    for (size_t i = 0; i < ROWS; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
        delete[] resultAdd[i];
        delete[] resultSub[i];
        delete[] resultMul[i];
        delete[] resultDiv[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] resultAdd;
    delete[] resultSub;
    delete[] resultMul;
    delete[] resultDiv;

    return 0;
}
