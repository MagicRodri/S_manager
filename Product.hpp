#ifndef _PRODUCT_HPP_INCLUDED
#define _PRODUCT_HPP_INCLUDED

#include <string>
#include <iostream>
#include <tuple>

class Product
{
public:
    Product();
    Product(std::string name,std::string m_serial,double price);
    ~Product();

    // getters
    std::string getName() const ;
    std::string getSerial() const;
    double getPrice() const;

    // Setters
    void setName(std::string name) ;
    void setSerial(std::string serial);
    void setPrice(double price);

protected:
    std::string m_name{};
    std::string m_serial{};
    double m_price{0.0};

};

std::string string_trim(std::string &word);
std::ostream& operator<<(std::ostream& out_stream,Product const& product);
std::istream& operator>>(std::istream& in_stream,Product &product);
bool operator==(Product const& a, Product const& b);
bool operator!=(Product const& a, Product const& b);

#endif // _PRODUCT_HPP_INCLUDED