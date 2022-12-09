#include <iostream>
#include "Product.hpp"
#include <limits>
#include "Stock.hpp"
#include "program.hpp"

int main()
{   
    /*
    Product prod{"Phone","1233255548",24545},prod1{"flash disk","",124000};
    Stock store{};
    store.add_product(prod,3);
    store.add_product(prod1,5);
    store.delete_product(prod1,1);
    store.sell(prod1,1);
    */ // For tests
    
    Stock my_store;
    std::string load_store{"store.bin"},load_box{"box.bin"};
    bool executing{false};

    my_store.load(load_store,load_box);
bloc_1:
    try
    {
        do
        {
           menu();
           auto menu=read_menu();
           executing=run_menu(menu,my_store,load_store,load_box);

        }while(executing);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        goto bloc_1;
    }
     
    return 0;
}