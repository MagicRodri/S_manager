 #ifndef STOCK_HPP_INCLUDED
#define STOCK_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Product.hpp"


class Money_box
{
  public:
  Money_box();
  ~Money_box();
   
   void spend(double money);
   void earn(double money);
   void show() const;

   inline double getAmount() const{return m_amount;}
   
   inline void setAmount(double amount) {m_amount=amount;}

   void save(std::string file) const;
   void load(std::string file);

  private:
  double m_amount{0.0};
};


class Stock
{        
public:
    Stock();
    ~Stock();
    
    void delete_product(Product product,int number);
    void add_product(Product product,int number);
    void sell(Product product,int number);
    void sell(Product product);
    int count(Product product) const;
    void view() ;
    void view(Product const& product) ;
    std::tuple<Product,int> search(std::string &product_name);
    void checkBox() const;
    void save(std::string store,std::string box)const;
    bool load(std::string store,std::string box);

    static void read_history();
    static void clear_history();

private:
  std::vector<Product> m_content{};
  static std::ofstream m_history;
  Money_box m_box;
};
std::string current_moment();

#endif // STOCK_HPP_INCLUDED
