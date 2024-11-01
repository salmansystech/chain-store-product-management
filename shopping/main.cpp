/* Chain Store
 *
 * Desc:
 *   This program reads input data concerning chain store products from a file,
 * where each line is formatted as:
 * chain_store;store_location;product_name;product_price.
 * The program validates the file content, ensuring each line has the required
 * four fields. It then processes the data and stores it in an appropriate
 * structure using STL containers like maps, vectors, and sets to manage
 * chains, stores, and their corresponding products and prices.
 *   The program allows the user to execute various commands to retrieve
 * information about chains, stores, product availability, and prices. The
 * supported commands are:
 *
 * chains: Lists all available chain stores.
 * stores <chain_store>: Lists all store locations for the given chain.
 * selection <chain_store> <store_location>: Lists all products and their
 * prices (or out-of-stock status) in the specified store.
 * cheapest <product_name>: Finds the lowest price of the given product
 * across all chains and stores and lists the locations offering the lowest price.
 * products: Lists all unique product names across all stores.
 * quit: Terminates the program.
 *
 *   For each command, the program ensures that the correct number of parameters
 * are provided and that the specified chain stores, store locations, and product
 * names exist in the data structure.
 *
 * Error handling is incorporated for invalid commands, erroneous input lines
 * in the data file, and incorrect parameters.

 * Program author ( Salman Khan )
 * Name: Salman khan
 * Student number: 153089910
 * UserID: cvh642
 * E-Mail: salman.khan@tuni.fi
 *
* Notes:
 * The program uses "out-of-stock" for products that are unavailable in a store.
 * Double.MAX is used to represent out-of-stock items when calculating prices.
 * The user interacts with the program through a simple command-line interface.
 *
 * Program flow:
 * Read the input file and build the data structure.
 * Continuously prompt the user for commands until 'quit' is entered.
 * */


#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

// for holding info.
struct Product{
    string product_name;
    double price;
};
// storing all products by chain and store.
map<string, map<string, vector<Product>>> products;
// function to split a string.
vector<string> split(const string& str, char delimiter){
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)){
        tokens.push_back(token);
    }
    return tokens;
}
//Function for reading the input file
bool read_input_file(const string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }
    string line;
    while (getline(file, line)){
        auto fields = split(line, ';');
        if (fields.size() != 4){
            cout << "Error: the input file has an erroneous line" << endl;
            return false;
        }
        string chain = fields[0];
        string store = fields[1];
        string product_name = fields[2];
        string price_str = fields[3];
        double price;
        if (price_str == "out-of-stock"){
            price = numeric_limits<double>::max();
        } else {
            try {
                price = stod(price_str);
            } catch (const invalid_argument&){
                cout << "Error: the input file has an erroneous line" << endl;
                return false;
            }
        }

        // check if the product already exists & update its price
        bool product_found = false;
        for (auto& product : products[chain][store]){
            if (product.product_name == product_name){
                product.price = price;
                product_found = true;
                break;
            }
        }
        if (!product_found){
            products[chain][store].push_back({product_name, price});
        }
    }
    return true;
}
// function for adding a new product
void add_product(const string& chain, const string& store, const string& product_name, const string& price_str) {
    double price;
    if (price_str == "out-of-stock"){
        price = numeric_limits<double>::max();  //use max double to represent out of stock
    } else{
        try{
            price = stod(price_str);
        } catch (const exception&){
            cout << "Error: invalid price format." << endl;
            return;
        }
    }
    bool product_found = false;
    for (auto& product : products[chain][store]){
        if (product.product_name == product_name){
            product.price = price;
            product_found = true;
            break;
        }
    }
    if (!product_found){
        products[chain][store].push_back({product_name, price});
    }
    cout << "Product added successfully!" << endl;
}
//function for handling printing chains
void cmd_chains(){
    for (const auto& chain : products){
        cout << chain.first << endl;
    }
}
//function to handle printing stores for a specific chain
 void cmd_stores(const string& chain){
    if (products.find(chain) == products.end()){
        cout << "Error: unknown chain name" << endl;
        return;
    }
    for (const auto& store : products[chain]){
        cout << store.first << endl;
    }
}
//function to handle the selection chain store' command
        void cmd_selection(const string& chain, const string& store){
    if (products.find(chain) == products.end()){
      cout << "Error: unknown chain name" << endl;
                 return;
    }
    if (products[chain].find(store) == products[chain].end()){
        cout << "Error: unknown store" << endl;
        return;
    }
    const vector<Product>& product_list = products[chain][store];
    for (const auto& product : product_list){
         if (product.price == numeric_limits<double>::max()){
         cout << product.product_name << " out of stock" << endl;
        } else {
 cout << product.product_name << " " << fixed << setprecision(2) << product.price << endl;
        }
    }
}
//function to handle the cheapest product command
void cmd_cheapest(const string& product_name){
    double min_price = numeric_limits<double>::max();
    vector<pair<string, string>> cheapest_stores;
    bool product_found = false;
    for (const auto& [chain, stores] : products){
        for (const auto& [store, product_list] : stores){
            for (const auto& product : product_list){
                if (product.product_name == product_name){
                    product_found = true;
                    if (product.price != numeric_limits<double>::max()){
                        if (product.price < min_price){
                            min_price = product.price;
                            cheapest_stores.clear();
                            cheapest_stores.push_back({chain, store});
                        } else if (product.price == min_price){
                            cheapest_stores.push_back({chain, store});
                        }
                    }
                }
            }
        }
    }
    if (!product_found){
        cout << "The product is not part of product selection" << endl;
    } else if (min_price == numeric_limits<double>::max()) {
        cout << "The product is temporarily out of stock everywhere" << endl;
    } else{
        cout << fixed << setprecision(2) << min_price << " euros" << endl;
        for (const auto& [chain, store] : cheapest_stores) {
            cout << chain << " " << store << endl;
        }
    }
}

//function for handling printing all unique products.
void cmd_products(){
    set<string> unique_products;
    for (const auto& chain : products){
        for (const auto& store : chain.second){
            for (const auto& product : store.second){
                unique_products.insert(product.product_name);
            }
        }
    }
    for (const auto& product_name : unique_products) {
        cout << product_name << endl;
    }
}
//function for handling user commands
void handle_commands(){
    string command;
           string chain, store, product_name;
   while (true){
       cout << "> ";
         cin >> command;
            if (command == "quit"){
       break;
   } else if (command == "chains"){
            string extra;
       if (cin.peek() != '\n'){
             cin >> extra;
 cout << "Error: error in command chains" << endl;
   cin.clear();   //this is for Clearing the error flag
   cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring the lines
                continue;
            }
            cmd_chains();
        } else if (command == "stores"){
            if (cin.peek() == '\n'){
                cout << "Error: error in command stores" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin >> chain;
            if (cin.fail() || cin.peek() != '\n'){
                cout << "Error: error in command stores" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cmd_stores(chain);
        } else if (command == "selection"){
            if (cin.peek() == '\n'){
                cout << "Error: error in command selection" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin >> chain;
            if (cin.peek() == '\n'){
                cout << "Error: error in command selection" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin >> store;
            if (cin.fail() || cin.peek() != '\n'){
                cout << "Error: error in command selection" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cmd_selection(chain, store);
        } else if (command == "cheapest"){
            if (cin.peek() == '\n') {
                cout << "Error: error in command cheapest" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin >> product_name;
            if (cin.fail() || cin.peek() != '\n'){
                cout << "Error: error in command cheapest" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cmd_cheapest(product_name);
        } else if (command == "products"){
            string extra;
            if (cin.peek() != '\n') {
                cin >> extra;
                cout << "Error: error in command products" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cmd_products();
        } else{
            cout << "Error: unknown command: " << command << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
int main() {
    string input_file;
    cout << "Input file: ";
    cin >> input_file;
    if (!read_input_file(input_file)) {
        return EXIT_FAILURE;
    }
    //start user input handling
    handle_commands();
    return EXIT_SUCCESS;
}
