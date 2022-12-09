#include <sstream>
#include <algorithm>
#include "Product.hpp"
#include "program.hpp"

Product::Product()
{
    m_name="unknown product";
    m_serial="No serial";
}
Product::Product(std::string name,std::string serial,double price):m_name{name},m_serial{serial},m_price{price}
{
   if(m_name.empty())
   {
      m_name="unknown product";
   }
   if(m_serial.empty())
   {
      m_serial="No serial";
   }
}

Product::~Product()
{

}

std::string Product::getName() const
{
   return m_name;
}

std::string Product::getSerial() const
{
  return m_serial;
}

double Product::getPrice() const
{
   return m_price;
}

void Product::setName(std::string name)
{
   m_name=string_trim(name);
}

void Product::setPrice(double price)
{
   m_price=price;
}

void Product::setSerial(std::string serial)
{
   m_serial=string_trim(serial);
}

std::string string_trim(std::string &word)
{
  auto first_no_space{std::find_if_not(std::begin(word),std::end(word),isspace)};
  word.erase(std::begin(word),first_no_space);
  std::reverse(std::begin(word),std::end(word));

  auto no_space{std::find_if_not(std::begin(word),std::end(word),isspace)};
  word.erase(std::begin(word),no_space);
  std::reverse(std::begin(word),std::end(word));
  return word;
}

std::ostream& operator<<(std::ostream& out_stream,Product const& product)
{
  out_stream<<product.getName()<<" | "<<product.getSerial()<<" | "<<product.getPrice()<<"F.CFA";
  return out_stream;
}

std::istream& operator>>(std::istream& in_stream,Product &product)
{
   std::string word{};
   std::ostringstream string_stream{};
   while (in_stream>>word && word!="|")
   {
      string_stream<<word<<" ";
   }
   word=string_stream.str();
   product.setName(word);
   string_stream.str(std::string{});
   
   std::string serial{};
   while (in_stream>>serial && serial!="|")
   {
      string_stream<<serial<<" ";
   }
   serial=string_stream.str();
   product.setSerial(serial);
   string_stream.str(std::string{});

   double price{.0};
   in_stream>>price;
   product.setPrice(price);
   
   if(product.getName().empty())
   {
      product.setName("unknown product");
   }
   if(product.getSerial().empty())
   {
      product.setSerial("No serial");
   }
   
   return in_stream;
}

bool operator==(Product const& a, Product const& b)
{
   return a.getName()==b.getName() && a.getSerial()==b.getSerial() && a.getPrice()==b.getPrice();
}

bool operator!=(Product const& a, Product const& b)
{
   return !(a==b);
}