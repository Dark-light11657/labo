#include "calculation.h"
#include <vector>
#include <limits>
#include <cmath>  // Pour la fonction std::abs

bool isDurationValid(const Date& start, const Date& end, int month_duration) {
    int year_diff = end.annee - start.annee;
    int month_diff = (end.annee - start.annee) * 12 + (12 - end.mois + 12 - start.mois);

    // Gérer les jours du mois pour l'ajustement final de la différence de mois
    if (end.jour > start.jour) {
        // Si le jour de fin est après le jour de début, considérer comme un mois complet
        month_diff++;
    } else if (end.jour < start.jour && month_diff > 0) {
        // Si le jour de fin est avant le jour de début et que la différence de mois est positive,
        // soustraire un mois car la période complète n'est pas encore atteinte
        month_diff--;
    }

    // Gérer les cas limites pour une durée exactement égale à la durée spécifiée
    if (month_diff == month_duration && end.jour < start.jour) {
        // Si la différence est exactement égale à la durée spécifiée mais le jour de fin est inférieur,
        // cela signifie que la période complète de month_duration mois n'est pas encore atteinte
        return false;
    }

    return month_diff >= month_duration;
}




// Fonction pour vérifier si une date se trouve dans une plage donnée
bool isDateWithinRange(const Date& div_date, const Date& start_date, const Date& end_date) {
    if (div_date.annee > start_date.annee ||
        (div_date.annee == start_date.annee && div_date.mois > start_date.mois) ||
        (div_date.annee == start_date.annee && div_date.mois == start_date.mois && div_date.jour >= start_date.jour)) {
        if (div_date.annee < end_date.annee ||
            (div_date.annee == end_date.annee && div_date.mois < end_date.mois) ||
            (div_date.annee == end_date.annee && div_date.mois == end_date.mois && div_date.jour <= end_date.jour)) {
            return true;
        }
    }
    return false;
}

// Fonction pour calculer le ROI moyen
double get_roi_moy(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende) {
    double total_roi = 0.0;
    int count = 0;

    for (size_t i = 0; i < Stock.size(); ++i) {
        size_t end_index = i + month_duration - 1;
        if (end_index >= Stock.size()) {
            break;
        }

        if (!isDurationValid(Stock[i].date, Stock[end_index].date, month_duration)) {
            continue;
        }

        double start_value = Stock[i].close;
        double end_value = Stock[end_index].close;
        double dividends = 0.0;

        for (const auto& div : Dividende) {
            if (isDateWithinRange(div.date, Stock[i].date, Stock[end_index].date)) {
                dividends += div.value;
            }
        }

        double roi = ((end_value + dividends - start_value) / start_value) * 100.0;
        total_roi += roi;
        ++count;
    }

    double average_roi = count > 0 ? total_roi / count : 0.0;
    return average_roi;
}

// Fonction pour calculer le ROI minimum
double get_roi_min(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende) {
    double min_roi = std::numeric_limits<double>::max();

    for (size_t i = 0; i < Stock.size(); ++i) {
        size_t end_index = i + month_duration - 1;
        if (end_index >= Stock.size()) {
            break;
        }

        if (!isDurationValid(Stock[i].date, Stock[end_index].date, month_duration)) {
            continue;
        }

        double start_value = Stock[i].close;
        double end_value = Stock[end_index].close;
        double dividends = 0.0;

        for (const auto& div : Dividende) {
            if (isDateWithinRange(div.date, Stock[i].date, Stock[end_index].date)) {
                dividends += div.value;
            }
        }

        double roi = ((end_value + dividends - start_value) / start_value) * 100.0;
        min_roi = std::min(min_roi, roi);
    }

    return min_roi == std::numeric_limits<double>::max() ? 0.0 : min_roi;
}

// Fonction pour calculer le ROI maximum
double get_roi_max(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende) {
    double max_roi = std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < Stock.size(); ++i) {
        size_t end_index = i + month_duration - 1;
        if (end_index >= Stock.size()) {
            break;
        }

        if (!isDurationValid(Stock[i].date, Stock[end_index].date, month_duration)) {
            continue;
        }

        double start_value = Stock[i].close;
        double end_value = Stock[end_index].close;
        double dividends = 0.0;

        for (const auto& div : Dividende) {
            if (isDateWithinRange(div.date, Stock[i].date, Stock[end_index].date)) {
                dividends += div.value;
            }
        }

        double roi = ((end_value + dividends - start_value) / start_value) * 100.0;
        max_roi = std::max(max_roi, roi);
    }


    return max_roi == std::numeric_limits<double>::lowest() ? 0.0 : max_roi;
}

double get_roi_annualise(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende) {
    double moy_roi = get_roi_moy(month_duration, Stock, Dividende);
    double annualised_roi = pow((1 + moy_roi / 100.0), 12.0 / month_duration) - 1.0;

    return annualised_roi;
}

std::string get_date_min(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende) {
    double min_roi = std::numeric_limits<double>::max();
    std::string min_date = "";

    for (size_t i = 0; i < Stock.size(); ++i) {
        size_t end_index = i + month_duration - 1;
        if (end_index >= Stock.size()) {
            break;
        }

        if (!isDurationValid(Stock[i].date, Stock[end_index].date, month_duration)) {
            continue;
        }

        double start_value = Stock[i].close;
        double end_value = Stock[end_index].close;
        double dividends = 0.0;

        for (const auto& div : Dividende) {
            if (isDateWithinRange(div.date, Stock[i].date, Stock[end_index].date)) {
                dividends += div.value;
            }
        }

        double roi = ((end_value + dividends - start_value) / start_value) * 100.0;
        if (roi < min_roi) {
            min_roi = roi;
            min_date = std::to_string(Stock[i].date.jour) + "-" + std::to_string(Stock[i].date.mois) + "-" + std::to_string(Stock[i].date.annee);
        }
    }

    return min_date;
}

std::string get_date_max(int month_duration, const std::vector<CsvArray>& Stock, const std::vector<Dividende>& Dividende) {
    double max_roi = std::numeric_limits<double>::lowest();
    std::string max_date = "";

    for (size_t i = 0; i < Stock.size(); ++i) {
        size_t end_index = i + month_duration - 1;
        if (end_index >= Stock.size()) {
            break;
        }

        if (!isDurationValid(Stock[i].date, Stock[end_index].date, month_duration)) {
            continue;
        }

        double start_value = Stock[i].close;
        double end_value = Stock[end_index].close;
        double dividends = 0.0;

        for (const auto& div : Dividende) {
            if (isDateWithinRange(div.date, Stock[i].date, Stock[end_index].date)) {
                dividends += div.value;
            }
        }

        double roi = ((end_value + dividends - start_value) / start_value) * 100.0;
        if (roi > max_roi) {
            max_roi = roi;
            max_date = std::to_string(Stock[i].date.jour) + "-" + std::to_string(Stock[i].date.mois) + "-" + std::to_string(Stock[i].date.annee);
        }
    }

    return max_date;
}