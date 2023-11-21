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


// Déclaration des fonctions
double get_roi_moy(int mois, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende);
double get_roi_min(int mois, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende);
double get_roi_max(int mois, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende);
double get_roi_annualise(int mois, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende);
std::string get_date_min(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende);
std::string get_date_max(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende);

#endif // PRG1_LABO3_CG_CALCULATION_H