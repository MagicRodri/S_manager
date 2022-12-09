#include <stdexcept>
#include <algorithm>
#include <limits>
#include "Stock.hpp"
#include <chrono>
#include <ctime>
#include <sstream>

std::string current_moment()
{
  std::chrono::system_clock::time_point now=std::chrono::system_clock::now();
  std::time_t now_time{std::chrono::system_clock::to_time_t(now)};
  std::ostringstream sstring{std::ctime(&now_time)};
  std::string curr_moment{sstring.str()};
  return curr_moment;
}

Money_box::Money_box()
{

}

Money_box::~Money_box()
{

}

void Money_box::save(std::string file) const
{
    std::ofstream save{file};
    if (save)
    {
        save<<m_amount;
        std::cout<<"Box save successful"<<std::endl;
    }
    else
    {
        std::cout<<"Box save failed"<<std::endl;
    }
    
    
}

void Money_box::load(std::string file)
{
    std::ifstream load{file};
    if (load)
    {
        load>>m_amount;
        std::cout<<"Box load successful"<<std::endl;
    }
    else
    {
        std::cout<<"Box load failed"<<std::endl;
    }
    
    
}
void Money_box::spend(double money)
{
    m_amount-=money;
    if (m_amount<0)
    {
        throw std::runtime_error("Amount less than zero!");
    }
    
}

void Money_box::earn(double money)
{
    m_amount+=money;
}

void Money_box::show() const
{
  std::cout<<"Amount:"<<m_amount<<"F.CFA"<<std::endl;
}

std::ofstream Stock::m_history{"history.DAT ",std::ios::app};

 Stock::Stock()
{

}

Stock::~Stock()
{

}

void Stock::delete_product(Product product,int number)
{
    if(std::count(std::begin(m_content),std::end(m_content),product)<number)
    {
       throw std::runtime_error("Available number less than the asked for deletion");
    }
    else
    {
       std::cout<<"Deleting "<<number<<" "<<product.getName()<<std::endl;
        for (size_t i = 0; i < number; i++)
        {
            auto trash{std::find(std::begin(m_content),std::end(m_content),product)};
            m_content.erase(trash);
        }
        m_content.shrink_to_fit();   
        m_history<<number<<" "<<product<<" deleted at "<<current_moment()<<std::endl;
    }   
}

void Stock::add_product(Product product,int number)
{
    std::cout<<"Adding "<<number<<" "<<product.getName()<<std::endl;
    for (size_t i = 0; i < number; i++)
    {
        m_content.push_back(product);
    }
    m_content.shrink_to_fit();
    m_history<<number<<" "<<product<<" added at "<<current_moment()<<std::endl;
}

void Stock::view()
{
    
    std::stable_sort(std::begin(m_content),std::end(m_content),[](Product const &A,Product const &B)->bool{
        return A.getName()<B.getName();
    });
    std::cout<<"Available items:"<<std::endl;
    Product current_product{};
    for(auto const& prod:m_content)
    {
        if (prod!=current_product)
        {
             current_product=prod;
             std::cout<<"\t"<<prod<<std::endl;
             std::cout<<"\tRemaining:"<<this->count(prod)<<std::endl<<std::endl;
        }
    }
}

void Stock::view(Product const& product)
{
    std::cout<<product<<std::endl;
    std::cout<<"Remaining:"<<this->count(product)<<std::endl<<std::endl;
}

std::tuple<Product,int> Stock::search(std::string &product_name)
{
    string_trim(product_name);
    auto search_iterator(std::find_if(std::begin(m_content),std::end(m_content),[product_name](Product const& prod)->bool{
        return product_name==prod.getName();
    }));
    if(search_iterator!=std::end(m_content))
    {
        return {*search_iterator,this->count(*search_iterator)};
    }
    else
    {
        Product empty{};
        return {empty,0};
    }
    
}

void Stock::checkBox() const
{
   m_box.show();
}

void Stock::sell(Product product,int number)
{
    std::cout<<"Selling "<<number<<" "<<product.getName()<<std::endl;
    this->delete_product(product,number);
    m_box.earn(number*product.getPrice());
    m_history<<number<<" "<<product<<" sold at "<<current_moment()<<std::endl;
}
void Stock::sell(Product product)
{
    std::cout<<"Selling 1 "<<product.getName()<<std::endl;
    this->delete_product(product,1);
    m_box.earn(product.getPrice());
    m_history<<"1 "<<product<<" sold at "<<current_moment()<<std::endl;
}

void Stock::read_history()
{
   std::string line{};
   std::ifstream history{"history.DAT"};
   if (history)
   {
       while (std::getline(history,line))
       {
           std::cout<<line<<std::endl;
       }
       
   }
   else
   {
       throw std::runtime_error("Unable to read history");
   }

}

void Stock::clear_history()
{
    std::ofstream history{"history.DAT"};
    if (history)
    {
        history.clear();
        std::cout<<"History cleared successfully."<<std::endl;
    }
    else
    {
        throw std::runtime_error("Clearing failed");
    }
    
    
}

int Stock::count(Product product) const
{
    return std::count(std::begin(m_content),std::end(m_content),product);
}

void Stock::save(std::string store,std::string box)const
{
    std::ofstream my_save{store};
    m_box.save(box);
    if (my_save)
    {
        for(auto const& product:m_content)
        {
            my_save<<product<<std::endl;
        }

        std::cout<<"Save complete"<<std::endl;
    }
    else
    {
        std::cout<<"Save failed"<<std::endl;
    }
    
}

bool Stock::load(std::string store,std::string box)
{
    Product product;
    std::ifstream my_load{store};
    m_box.load(box);
    if (my_load)
    {     
        while (my_load>>product)
        {
           m_content.push_back(product);
           my_load.clear();
           my_load.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        std::cout<<"Loading stock successful"<<std::endl;
        return true;
    }
    else
    {
        std::cout<<"Loading stock failed"<<std::endl;
        return false;
    }
    
}