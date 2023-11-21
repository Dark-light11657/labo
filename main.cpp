#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "csv.h"
#include "calculation.h"


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

        /* Dividendes's display for test
        for (int i = 0; i < div_array.size();i++){
            std::cout << div_array.at(i).to_string() << std::endl;
        }
        */


    } catch (std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
    }


    // Selection of duration
    valid = false;
    std::vector<int> months;

    do {
        std::cout << "Durees a considerer en mois ? \n";
        std::string months_durations;
        std::cin >> months_durations;
        std::istringstream sstr(months_durations);

        long int month;

        while(sstr >> month){
            months.push_back(month);
            valid = true;
        }

        // S'assure que au moins toutes les valeurs entree sont des int, si un non-int est entrer la suite ne sera pas prise en compte.

    }while (!valid);



    // Calcule des ROI et dates de la reponse

    for (int i = 0; i < months.size(); ++i) {

        int roi_moyen = get_roi_moyen(months.at(i), array_stock, div_array);

        int annualise = get_roi_annualise(months.at(i), array_stock, div_array);

        int roi_min = get_roi_min(months.at(i), array_stock, div_array);

        std::string date_min = get_date_min(months.at(i), array_stock, div_array);

        int roi_max = get_roi_max(months.at(i), array_stock, div_array);

        std::string date_max = get_date_max(months.at(i), array_stock, div_array);

    }

    return EXIT_SUCCESS;
}


