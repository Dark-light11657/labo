#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#ifndef PRG1_LABO3_CG_CSV_H
#define PRG1_LABO3_CG_CSV_H



struct Date{
    int jour;
    int mois;
    int annee;

    Date(int jour, int mois, int annee)
            : jour(jour), mois(mois), annee(annee){}

    std::string to_string(){
        return "Jour: "  + std::to_string(jour) + ", mois: " + std::to_string(mois) + ", annee: " + std::to_string(annee);
    }

};

struct CsvArray {
    Date date;
    double high;
    double low;
    double close;

    CsvArray(Date date, double high, double low, double close)
            : date(date), high(high), low(low), close(close){}

    std::string to_string(){
        return "Date: " + std::to_string(date.jour) + "-" + std::to_string(date.mois) + "-" + std::to_string(date.annee) + ", High: " + std::to_string(high) + ", Low: " + std::to_string(low) + ", close: " + std::to_string(close);
    }
};

struct Dividende {

    Date date;
    double value;

    Dividende(Date date, double dividende)
    : date(date), value(dividende){}

    std::string to_string(){
        return "Date: " + std::to_string(date.jour) + "-" + std::to_string(date.mois) + "-" + std::to_string(date.annee) + ", value: " + std::to_string(value);
    }

};



// Function's Initialization

std::vector<CsvArray> csv_to_array (std::string path_stock);

std::vector<Dividende> csv_to_dividendes(std::string path_dividende);

Date string_to_date(std::string date);



#endif //PRG1_LABO3_CG_CSV_H