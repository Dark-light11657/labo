#include "csv.h"
#include "vector"

#ifndef PRG1_LABO3_CG_CALCULATION_H
#define PRG1_LABO3_CG_CALCULATION_H

struct Reponse{

    int mois;
    double roi_moyen;
    double annualise;
    double roi_min;
    std::string date_min;
    double roi_max;
    std::string date_max;

    Reponse(int mois, double roi_moyen, double annualise, double roi_min, std::string date_min, double roi_max, std::string date_max)
            : mois(mois), roi_moyen(roi_moyen), annualise(annualise), roi_min(roi_min), date_min(date_min), roi_max(roi_max), date_max(date_max){}

};


int get_roi_moyen(int mois , std::vector<CsvArray> Stock, std::vector<Dividende> dividende);

int get_roi_annualise(int mois , std::vector<CsvArray> Stock, std::vector<Dividende> dividende);

int get_roi_min(int mois , std::vector<CsvArray> Stock, std::vector<Dividende> dividende);

std::string get_date_min(int mois , std::vector<CsvArray> Stock, std::vector<Dividende> dividende);

int get_roi_max (int mois , std::vector<CsvArray> Stock, std::vector<Dividende> dividende);

std::string get_date_max(int mois , std::vector<CsvArray> Stock, std::vector<Dividende> dividende);


#endif //PRG1_LABO3_CG_CALCULATION_H
