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
/* roi MOYEN 
#include "csv.h"  // Include your CSV header file

double get_roi_moy(int month_duration, const std::vector<CsvArray>& Stock) {
    if (month_duration <= 0 || Stock.size() < month_duration) return 0.0;

    double total_roi = 0.0;
    int count = 0;

    for (size_t i = 0; i <= Stock.size() - month_duration; ++i) {
        double opening_price = Stock.at(i).close;  // Using at(index) for safe access
        double closing_price = Stock.at(i + month_duration - 1).close;  // Closing price after 'month_duration' months
        double roi = (closing_price - opening_price) / opening_price;

        total_roi += roi;
        count++;
    }

    if (count == 0) return 0.0; // No periods to calculate the average

    return total_roi / count; // Average ROI
}
*/