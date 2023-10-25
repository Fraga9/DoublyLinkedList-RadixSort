#include "DLL.h"
#include "logE2.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#define SHIFT    6
#define MASK     ((1 << SHIFT) - 1)
#define DIVISOR  (1 << SHIFT)

// Valor más alto
long long int getMax(Log* arr, int n) {
    long long int max = arr[0].key; // Assuming key is the field you want to sort on
    for (int i = 1; i < n; i++) {
        if (arr[i].key > max) {
            max = arr[i].key;
        }
    }
    return max;
}

long long int getMaxIp(Log* arr, int n){
    long long int max = arr[0].key2;
    for (int i = 1; i < n; i++) {
        if (arr[i].key2 > max) {
            max = arr[i].key2;
        }
    }
    return max;
}

// Radix Sort (modificación en comparación a la evidencia pasada sacada de stackoverflow) 
/*https://stackoverflow.com/questions/67750089/radix-sort-using-array-of-linked-list-as-bin-in-c*/

void radix_sort(Log* arr, int n) {
    long long int max = getMax(arr, n);

    for (int shift = 0; max > 0; shift += SHIFT) {
        int count[DIVISOR] = {0};
        Log* output = new Log[n];

        for (int i = 0; i < n; i++) {
            int digit = (arr[i].key >> shift) & MASK;
            count[digit]++;
        }

        for (int i = 1; i < DIVISOR; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i].key >> shift) & MASK;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        delete[] output;
        max >>= SHIFT;
    }
}

void radix_sortIp(Log* arr, int n){
    long long int max = getMaxIp(arr, n);

    for (int shift = 0; max > 0; shift += SHIFT) {
        int count[DIVISOR] = {0};
        Log* output = new Log[n];

        for (int i = 0; i < n; i++) {
            int digit = (arr[i].key2 >> shift) & MASK;
            count[digit]++;
        }

        for (int i = 1; i < DIVISOR; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i].key2 >> shift) & MASK;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        delete[] output;
        max >>= SHIFT;
    }
}

//Recopilación de rango de ip
long long int Input(){
    int ip1 = 10;
    int ip2 = 14;
    int ip3, ip4;
    std::cout << "Ingrese el tercer octeto de la ip: ";
    std::cin >> ip3;
    std::cout << "Ingrese el cuarto octeto de la ip: ";
    std::cin >> ip4;
    long long int ipInput = ip1 * 1000000000LL + ip2 * 1000000LL + ip3 * 1000LL + ip4;
    //std::cout << ipInput << std::endl;
    return ipInput;
}

// busqueda secuencial para data en el rango de ip de la doublelinkedlist key2
int sequentialSearch(DoublyLinkedList<Log> list, long long data){
    int index = 0;
    DNode<Log>* aux = list.getHead();
    //std::cout << "aux->data.key2 Inicial: " << aux->data.key2 << std::endl;
    while (aux != nullptr){
        if (aux->data.key2 > data){
            return index;
        }
        aux = aux->next;
        index++;
    }
    return -1;
}

//Despliega en pantalla la cantidad de ips en el archivo por cada año y mes
void sumatoriaDatos(DoublyLinkedList <Log> list){
    int sumatoria = 0;
    DNode<Log>* aux = list.getHead();
    while (aux->next != nullptr){
        if (aux->data.year == aux->next->data.year && aux->data.month == aux->next->data.month){
            sumatoria++;
        }
        else{
            sumatoria++;
            std::cout << "En el año " << aux->data.year << " y mes " << aux->data.month << " hay " << sumatoria << " ips" << std::endl;
            sumatoria = 0;
        }
        aux = aux->next;
    }
}



std::string convertStr(long long int ip){
    std::string ipStr = std::to_string(ip);
    std::string ip1 = ipStr.substr(0,2);
    std::string ip2 = ipStr.substr(2,3);
    std::string ip3 = ipStr.substr(5,3);
    std::string ip4 = ipStr.substr(8,3);
    std::string ipFinal = ip1 + "." + ip2 + "." + ip3 + "." + ip4;
    return ipFinal;
}




int main(){
    // Archivo de entrada
    std::ifstream fileIn("log603-2.txt");
    // Archivo de salida
    std::ofstream fileOut("output602-1.out"); // ordenados por fecha y hora
    std::ofstream fileOut2("iprange602-a.out"); // rango ascendente de ip
    std::ofstream fileOut3("iprange602-d.out"); // rango descendente de ip
    std::ofstream fileOut4("output602-2.out"); // ordenados por ip fecha y hora
    // Variable auxiliar para guardar el contenido del renglón leido
    std::string line;
    // Variable auxiliar para guardar el contenido de cada palabra del campo message
    std::string word;
    // Variables auxiliares para guardar el contenido de cada campo del archivo
    int year;
    std::string month;
    int day;
    std::string time;
    std::string ip;
    std::string message;

    DoublyLinkedList<Log> logs;
    int cont = 0;
    // Ciclo para leer todo los renglones del archivo de entrada
    while (getline(fileIn, line)) { 
        // Creamos una variable auxiliar ss para recorrer campo por campo
        std::stringstream ss(line);
        // Guardamos la información de cada campo en la variable auxiliar correspondiente
        ss >> month >> day >> year >> time >> ip >> message;
        // Ciclo para recorrer cada palabra del campo message
        while (ss >> word) {
            message = message + " " + word;
        }
        // cout << month << " " << day << " " << year << " " << time << " " << ip << " " << message << endl;
        Log log(year, month, day, time, ip, message);
        logs.addLast(log);
        //cout << log;
        // Incrementamos el contador de registros
        cont++;
    }
    std::cout << "La cantidad de registros es: " << logs.getSize() << std::endl;
    

    
   // menú de opciones
   DoublyLinkedList<Log> logsRange;
    int size = logs.getSize();
    Log* logArray = new Log[size];
    logs.toArray(logArray);
    int opcion = 0;
    long long int Inicio, Final;
    std::cout << "1. Buscar por rango de ip" << std::endl;
    std::cout << "2. Ordenar por fecha y hora" << std::endl;
    std::cout << "3. Ordenar por ip" << std::endl;
    std::cout << "4. Mostrar cantidad de ips por año y mes" << std::endl;
    std::cout << "5. Salir" << std::endl;

    while (opcion != 5) {
        std::cout << "Ingrese la opción que desea realizar: " << std::endl;
        std::cin >> opcion;
        switch (opcion) {
            case 1:
            {
                //if output602-2.out is empty, break and display sort by ip first
                if (fileOut4.peek() == std::ifstream::traits_type::eof()){
                    std::cout << "El archivo output602-2.out está vacío, por favor ordene por ip primero" << std::endl;
                    break;
                }
                std::cout << "Ingrese el rango de valores de IP a buscar: " << std::endl;
                std::cout << "----------------iP Inicial---------------"<< std::endl;
                Inicio = Input();
                std::cout << "-----------------iP Final----------------"<< std::endl;
                Final = Input(); 
                std::cout << std::endl;
                std::cout <<"Inicio del rango de búsqueda: "<< convertStr(Inicio) << std::endl;
                std::cout <<"Final del rango de búsqueda: " << convertStr(Final) << std::endl;
                int InicioIndex = sequentialSearch(logs, Inicio);
                std::cout << "InicioIndex: " << InicioIndex << std::endl;
                int FinalIndex = sequentialSearch(logs, Final);
                std::cout << "FinalIndex: " << FinalIndex << std::endl;
                if (InicioIndex >= 0 && FinalIndex < logs.getSize()) {
                    // orden ascendente
                    for (long long int i = InicioIndex; i <= FinalIndex; i++) {
                        fileOut2 << logs[i] << std::endl;
                        logsRange.addLast(logs[i]);
                    }
                    // orden descendente
                    for (long long int i = FinalIndex; i >= InicioIndex; i--) {
                        fileOut3 << logs[i] << std::endl;
                    }
                }
                else {
                    std::cout << "No se encontraron registros en el rango de búsqueda" << std::endl;
                }
                break;
            }
            case 2:
            {
                // Ordenamiento por fecha y hora
                radix_sort(logArray, size);

                // Creación de DLL a partir del array ordenado por fecha y hora
                logs.clear();
                for (int i = 0; i < size; i++) {
                    logs.addLast(logArray[i]);
                }

                // Impresión de la lista ordenada por fecha y hora
                for (int i = 0; i < size; i++) {
                    fileOut << logArray[i] << std::endl;
                }
                fileOut.close();

                break;
            }
            case 3:{
                // Ordenamiento por ip
                radix_sortIp(logArray, size);

                // Creación de DLL a partir del array ordenado por ip
                logs.clear();
                for (int i = 0; i < size; i++) {
                    logs.addLast(logArray[i]);
                }
                // Impresión de la lista ordenada por ip
                for (int i = 0; i < size; i++) {
                    fileOut4 << logArray[i] << std::endl;
                }
                fileOut4.close();
                break;
            }
            case 4:{
                // Ordenamiento por ip
                radix_sort(logArray, size);

                // Creación de DLL a partir del array ordenado por ip
                logs.clear();
                for (int i = 0; i < size; i++) {
                    logs.addLast(logArray[i]);
                }
                sumatoriaDatos(logs);
                break;
            }
            case 5:{
                std::cout << "Saliendo..." << std::endl;
                break;
            }
        }
    }


    return 0;
}