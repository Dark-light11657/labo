#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "csv.h"

std::vector<CsvArray> csv_to_array(std::string path_stock){

    std::ifstream entree_stock;
    entree_stock.open(path_stock);

    if(entree_stock.fail()) {
        throw std::invalid_argument(path_stock + " inaccessible");
    }

    std::vector<CsvArray> liste_stock;
    std::string line;

    // Skip the first line with title
    getline(entree_stock, line);

    while(getline(entree_stock, line)){


        double stk_Open;
        double stk_High;
        double stk_Low;
        double stk_Close;
        double stk_AdjClose;
        long stk_Volume;

        std::string tempString;

        std::stringstream input_string(line);

        getline(input_string, tempString, ',');
        Date stk_Date = string_to_date(tempString);

        getline(input_string, tempString, ',');
        stk_Open = std::stod(tempString);

        getline(input_string, tempString, ',');
        stk_High = std::stod(tempString);

        getline(input_string, tempString, ',');
        stk_Low = std::stod(tempString);

        getline(input_string, tempString, ',');
        stk_Close = std::stod(tempString);

        getline(input_string, tempString, ',');
        stk_AdjClose = std::stod(tempString);

        getline(input_string, tempString, ',');
        stk_Volume = std::stol(tempString);


        CsvArray donnee_stock(stk_Date, stk_High, stk_Low, stk_Close);

        liste_stock.push_back(donnee_stock);

    }
    return liste_stock;
}

std::vector<Dividende> csv_to_dividendes(std::string path_dividende){

    std::ifstream entry_dividende;
    entry_dividende.open(path_dividende);

    if(entry_dividende.fail()){
        throw std::invalid_argument("Dividendes non disponible pour ce stock");
    }

    std::vector<Dividende> div_list;
    std::string line;

    // Skip the first line with title
    getline(entry_dividende, line);

    while (getline(entry_dividende, line)){

        double div_value;

        std::string temp_string;

        std::stringstream input_string(line);


        getline(input_string, temp_string, ',');
        Date div_date = string_to_date(temp_string);


        getline(input_string, temp_string, ',');
        div_value = std::stod(temp_string);

        Dividende div_data(div_date, div_value);
        div_list.push_back(div_data);

    }
    return div_list;
}

Date string_to_date(std::string input_date){
    std::string day;
    std::string month;
    std::string year;

    int day_value;
    int month_value;
    int year_value;

        for (int j = 0; j < 4; ++j) {
            year += input_date[j];
        }

        for (int j = 5; j < 7; ++j) {
            month += input_date[j];
        }

        for (int j = 9; j < 11; ++j) {
            day += input_date[j];
        }

        day_value = std::stoi(day);
        month_value = std::stoi(month);
        year_value = std::stoi(year);

        Date date(day_value, month_value, year_value);

return date;

}

