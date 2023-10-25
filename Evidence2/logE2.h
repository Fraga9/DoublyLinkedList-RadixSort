#pragma once
#include <string>
#include <iostream>
#include <sstream>


class Log{
public:
    int year;
    std::string month;
    int mm;
    int tiempo;
    int day;
    std::string time;
    std::string ip;
    std::string message;
    long long int key;
    long long int key2;
    bool operator<(Log log);
    long long int keyGenerator();
    long long int keyGenerator2();
    Log(int year, std::string month, int day, std::string time, std::string ip, std::string message);
    friend std::ostream& operator<<(std::ostream& os, const Log& log) {
        os << log.month << " " << log.day << " " << log.year << " " << log.time << " " << log.ip << " " << log.message;
        return os;  
    }
// constructor predeterminado
    Log() {
        // Inicializa los miembros de la clase según sea necesario
        year = 0;
        month = "";
        mm = 0;
        tiempo = 0;
        day = 0;
        time = "";
        ip = "";
        message = "";
        key = 0;
        key2 = 0;
    }
};


// constructor con valores de entrada
Log::Log(int year, std::string month, int day, std::string time, std::string ip, std::string message) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->time = time;
    this->ip = ip;
    this->message = message;
    // Generar la clave 
    this->key = keyGenerator();
    this->key2 = keyGenerator2();
}


// ordenamiento por fecha y hora
long long int Log::keyGenerator() {
    if (month == "Jan") {
        mm = 1;
    }
    if (month == "Feb") {
        mm = 2;
    }
    if (month == "Mar") {
        mm = 3;
    }
    if (month == "Apr") {
        mm = 4;
    }
    if (month == "May") {
        mm = 5;
    }
    if (month == "Jun") {
        mm = 6;
    }
    if (month == "Jul") {
        mm = 7;
    }
    if (month == "Aug") {
        mm = 8;
    }
    if (month == "Sep") {
        mm = 9;
    }
    if (month == "Oct") {
        mm = 10;
    }
    if (month == "Nov") {
        mm = 11;
    }
    if (month == "Dec") {
        mm = 12;
    }
    int horas, minutos, segundos;
    std::stringstream ss(time);
    char colon;
    ss >> horas >> colon>> minutos >> colon >> segundos;
    tiempo = horas * 10000 + minutos * 100 + segundos;
    key = (year * 10000 + mm  * 100 + day) * 1000000LL + tiempo;


    return key;
}


// ordenamiento por ip fecha y hora
long long int Log::keyGenerator2(){
    int ip1, ip2, ip3, ip4;
    std::stringstream ss(ip);
    char dot;
    ss >> ip1 >> dot >> ip2 >> dot >> ip3 >> dot >> ip4;

    //std::cout << ip1 << " " << ip2 << " " << ip3 << " " << ip4 << std::endl;
    key2 = ip1 * 1000000000LL + ip2 * 1000000LL + ip3 * 1000LL + ip4;
    //std::cout << key2 << std::endl;
    //key2 = (ip1 * 1000000000LL + ip2 * 1000000LL + ip3 * 1000LL + ip4) * 100000000000000LL + (year * 10000 + mm  * 100 + day) * 1000000LL + tiempo;
    
    return key2;
}