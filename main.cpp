#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "csv.h"
#include "calculation.h"


std::string	fix_width(std::string str, long unsigned max)
{
    if (str.size() > max)
    {
        str.resize(max);
        str[str.size() - 1] = '.';
    }
    return (str);
}

std::string	add_spaces(int n)
{
    std::string	str;

    while (n--)
        str.append(" ");
    return (str);
}



int main() {

    bool valid = false;
    std::vector<CsvArray> array_stock;
    std::string choix_stock;


    // Selection of Stock
    do {
        std::cout << "Dans quel produit voulez-vous investir ? \n";
        std::cin >> choix_stock;

        try {
            // Warning, path traversal incoming :(
            array_stock = csv_to_array("..//data//" + choix_stock + ".csv");

            /* Stock's Display for test
            for(int i = 0; i < array_stock.size() ;i++ ){
                std::cout << array_stock.at(i).to_string() << std::endl;
            }
            */

            valid = true;
        } catch (std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }while(!valid);


    // Verification and creation of an array for dividende
    std::vector<Dividende> div_array;

    // Initialiser à zéro

    std::vector<Date> dates_dividende;
    try {
        div_array = csv_to_dividendes("..//data//" + choix_stock + "-2.csv");
        std::cout << "dividendes trouvees" << std::endl;



    } catch (std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
    }


    // Selection of duration
    std::vector<int> months;
    do {
        std::cout << "Durees a considerer en mois ? \n";
        std::string months_durations;
        std::cin >> months_durations;
        std::istringstream sstr(months_durations);

        int month;
        while (sstr >> month) {
            months.push_back(month);
            valid = true;
        }
    } while (!valid);


    std::vector<Reponse> list_reponse;
    Reponse reponse(0,0,0,0,"",0,"");
    for (int i = 0; i < months.size(); ++i) {
        int month_nb = months.at(i);
        double roi_moyen = get_roi_moy(months.at(i), array_stock, div_array);
        double annualise = get_roi_annualise(months.at(i), array_stock, div_array);
        double roi_min = get_roi_min(months.at(i), array_stock, div_array);
        std::string date_min = get_date_min(months.at(i), array_stock, div_array);
        double roi_max = get_roi_max(months.at(i), array_stock, div_array);
        std::string date_max = get_date_max(months.at(i), array_stock, div_array);

        list_reponse.push_back(Reponse(month_nb, roi_moyen, annualise, roi_min, date_min, roi_max, date_max));

    }


    for (int i = 0; i < list_reponse.size(); ++i) {

        std::cout << " Nr Mois    |  ROI moyen |  Annualise |    ROI min |   Date min |    ROI max |   Date max"
                  << std::endl;

        std::string rep_mois = std::to_string(list_reponse.at(i).mois);
        std::string rep_roi_moy = std::to_string(list_reponse.at(i).roi_moyen)
                +"%";
        std::string rep_annualise = std::to_string(list_reponse.at(i).annualise)+"%";
        std::string rep_roi_min = std::to_string(list_reponse.at(i).roi_min)+"%";
        std::string rep_date_min = list_reponse.at(i).date_min;
        std::string rep_roi_max = std::to_string(list_reponse.at(i).roi_max)+"%";
        std::string rep_date_max = list_reponse.at(i).date_max;

        std::string str;

        str = fix_width(str, 12);

        std::cout << "" << add_spaces(12 - std::size(rep_mois));
        std::cout << rep_mois;

        std::cout << "|" << add_spaces(12 - std::size(rep_roi_moy)) << str;
        std::cout << rep_roi_moy;

        std::cout << "|" << add_spaces(12 - std::size(rep_annualise)) << str;
        std::cout << rep_annualise;

        std::cout << "|" << add_spaces(12 - std::size(rep_roi_min)) << str;
        std::cout << rep_roi_min;

        std::cout << "|" << add_spaces(12 - std::size(rep_date_min)) << str;
        std::cout << rep_date_min;

        std::cout << "|" << add_spaces(12 - std::size(rep_roi_max)) << str;
        std::cout << rep_roi_max;

        std::cout << "|" << add_spaces(12 - std::size(rep_date_max)) << str;
        std::cout << rep_date_max << std::endl;
    }

    return EXIT_SUCCESS;
}


