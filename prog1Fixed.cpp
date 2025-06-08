#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <cmath>

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

int main(int argc, char* argv[]) {
    // Проверяем, передан ли аргумент с размером массива
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <размер_массива>" << std::endl;
        return 1;
    }

    // Преобразуем аргумент в число
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

    double startTime = getTime();
    // Создаем динамический массив нужного размера
    int* array = new int[SIZE];
    int index = 0;

    while (index < SIZE && file >> array[index]) {
        index++;
    }

    file.close();

    int summ = 0;
    for(int i = 0; i < index; i++) {
        summ = summ + array[i];
    }
    double endTime = getTime();
    std::cout << endTime - startTime << "\n";

    appendTimeToBinaryFile(double (endTime - startTime));

    // Освобождаем память
    delete[] array;
    return 0;
}
