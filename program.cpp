#include "program.hpp"
#include "Stock.hpp"
#include <string>
#include <tuple>
#include <iomanip>
#include <ctype.h>
#include "Product.hpp"

void menu()
{
  std::cout<<std::setfill('*')<<"\t"<<std::setw(25)<<'\n';
  std::cout<<"\t* 1-Add"<<std::setfill('-')<<std::setw(18)<<"*\n"
           <<"\t* 2-Delete"<<std::setfill('-')<<std::setw(15)<<"*\n"
           <<"\t* 3-Sell"<<std::setfill('-')<<std::setw(17)<<"*\n"
           <<"\t* 4-View"<<std::setfill('-')<<std::setw(17)<<"*\n"
           <<"\t* 5-Search"<<std::setfill('-')<<std::setw(15)<<"*\n"
           <<"\t* 6-Till"<<std::setfill('-')<<std::setw(17)<<"*\n"
           <<"\t* 7-History"<<std::setfill('-')<<std::setw(14)<<"*\n"
           <<"\t* 8-Exit"<<std::setfill('-')<<std::setw(17)<<"*\n";
   std::cout<<std::setfill('*')<<"\t"<<std::setw(25)<<'\n';
}

Menu read_menu()
{
  std::string input{};
  std::cout<<">";
  secured_input<std::string>(input);
  std::transform(std::begin(input),std::end(input),std::begin(input),toupper);
  if (input=="ADD" )
  {
      return Menu::Add;
  }
  else if (input=="DELETE")
  {
      return Menu::Delete;
  }
  else if (input=="SELL")
  {
     return Menu::Sell;
  }
  else if (input=="VIEW")
  {
      return Menu::View;
  }
  else if (input=="EXIT")
  {
      return Menu::Exit;
  }
  else if (input=="TILL")
  {
      return Menu::Till;
  }
  else if(input=="SEARCH")
  {
      return Menu::Search;
  }
  else if (input=="HISTORY")
  {
      return Menu::History;
  }
  
  
  else
  {
      throw std::runtime_error("Unavailable option.");
  } 
  
}


std::tuple<Product,int> product_treatment()
{
   Product product{};
   std::cout<<"-Product:";
   secured_input(product);
   std::cout<<"-Number:";
   int number{};
   secured_input(number);

   return {product,number};
}

Product single_treatment()
{
   Product product{};
   std::cout<<"-Product:";
   secured_input(product);
   return product;
}

bool confirm_operation()
{
    std::cout<<"(Y/N) :";
    std::string answer;
    secured_input(answer,[](std::string answer)->bool{
        return answer=="Y" || answer=="y" || answer=="N" || answer=="n";
    });
    std::transform(std::begin(answer),std::end(answer),std::begin(answer),toupper);
    if(answer=="Y")
    {
        return true;
    }
    return false;
    
}

bool run_menu(Menu menu,Stock &my_store,std::string &store_save,std::string &box_save)
{
  if (menu==Menu::Add)
  {
      auto[product,number]=product_treatment();
      std::cout<<"Confirm?";
      if(confirm_operation())
      {
         my_store.add_product(product,number);
      }
      my_store.save(store_save,box_save);
  }
  else if (menu==Menu::Delete)
  {
       auto[product,number]=product_treatment();
       std::cout<<"Confirm?";
       if(confirm_operation())
       {
         my_store.delete_product(product,number);
       }
       my_store.save(store_save,box_save);
  }
  else if (menu==Menu::Sell)
  {
       auto[product,number]=product_treatment();
       std::cout<<"Confirm?";
       if(confirm_operation())
       {
         my_store.sell(product,number);
       }
       my_store.save(store_save,box_save);
  }
  else if (menu==Menu::Search)
  {
     search:
      std::cout<<"-Product's name:";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      std::string name{""};
      std::getline(std::cin,name);
      auto[prod_found,number]=my_store.search(name);
      if (number!=0)
      {
          std::cout<<"Product found:"<<std::endl;
          my_store.view(prod_found);
      }
      else
      {
          std::cout<<"Product out of stock"<<std::endl;
      }
      std::cout<<"Search again?";
      if (confirm_operation())
      {
          goto search;
      }
      
  }
  
  else if (menu==Menu::View)
  {
      my_store.view();
  }
  else if (menu==Menu::Till)
  {
      my_store.checkBox();
  }
  
  else if (menu==Menu::History)
  {
      std::cout<<"1-Show"<<std::endl
      <<"2-Clear"<<std::endl;
      std::string input{};
      secured_input<std::string>(input);
      std::transform(std::begin(input),std::end(input),std::begin(input),toupper);
      if (input=="SHOW")
      {
         Stock::read_history();
      }
      else if (input=="CLEAR")
      {
          Stock::clear_history();
      }
      
      
  }
  
  else if (menu==Menu::Exit)
  {
      my_store.save(store_save,box_save);
      return false;
  }
  else
  {
      throw std::runtime_error("Unavailable choice.");
  }
  
   return true;
}