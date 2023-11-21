#include "calculation.h"
#include "csv.h"
#include <cmath>
#include <limits>
#include <string>
#include <vector>

int get_roi_min(int month_duration , std::vector<CsvArray> Stock, std::vector<Dividende> dividende){


    int location;
    int val_min;
    int val_month;
    int val_year;


    for (int i = 0; i < Stock.size(); ++i) {

        int val_i = Stock.at(i).low;

        if(val_year < Stock.at(i).date.annee){

            if(val_month % Stock.at(i).date.mois != 0){

                if(location > val_i){
                    val_min = Stock.at(i).low;
                    location = val_i;
                }
            }
        }
    }

    return val_min;
}
#include "calculation.h"
#include "csv.h"
#include <cmath>
#include <limits>
#include <string>
#include <vector>

int get_roi_min(int month_duration , std::vector<CsvArray> Stock, std::vector<Dividende> dividende){


    int location;
    int val_min;
    int val_month;
    int val_year;


    for (int i = 0; i < Stock.size(); ++i) {

        int val_i = Stock.at(i).low;

        if(val_year < Stock.at(i).date.annee){

            if(val_month % Stock.at(i).date.mois != 0){

                if(location > val_i){
                    val_min = Stock.at(i).low;
                    location = val_i;
                }
            }
        }
    }

    return val_min;
}#je veux juste faire fonctionner le ROI moyen et le reste je vais me débrouiller
