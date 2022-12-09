#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include <iostream>
#include <stdexcept>
#include <tuple>
#include <limits>
#include <string>
#include <algorithm>
#include "Product.hpp"
#include "Stock.hpp"

template<typename T>
void secured_input(T &variable)
{
    while(!(std::cin>>variable))
    {
        if(std::cin.eof())
        {
           throw std::runtime_error("Closed stream ,unable to use.");
        }
        else
        {
            std::cout<<"Invalid input"<<std::endl;
        }
        std::cout<<"Please, try again:"<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());   
    }
}

template<typename T,typename Predicat>
void secured_input(T &variable,Predicat predicat)
{
    while(!(std::cin>>variable) && !predicat(variable))
    {
        if(std::cin.eof())
        {
           throw std::runtime_error("Closed stream ,unable to use.");
        }
        else if(std::cin.fail())
        {
            std::cout<<"Invalid input"<<std::endl;
        }
        else
        {
            std::cout<<"Unavailable choice"<<std::endl;
        }
        
        std::cout<<"Please, try again:"<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());   
    }
}

enum class Menu
{
   Add,
   Delete,
   Sell,
   Search,
   View,
   Till,
   History,
   Exit
};

void menu();
Menu read_menu();
std::tuple<Product,int> product_treatment();
Product single_treatment();
bool run_menu(Menu menu,Stock &my_store,std::string &store_save,std::string &box_save);
bool confirm_operation();

#endif //PROGRAM_HPP_INCLUDED