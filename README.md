# Chain Stores Data Management
This project manages product and pricing data across different chain stores. It reads information from a CSV file, allowing users to search by store and product and find the cheapest available products across chains.

# Features
Product Database: Reads product, store, and price information from a file at startup.
Search Commands:
chains: Lists all available chains.
stores <chain>: Lists stores for a specified chain.
selection <chain> <store>: Shows all products and prices in a specific store.
cheapest <product>: Finds the cheapest available price for a product across stores.
products: Lists all products carried across stores.
Error Handling: Provides informative error messages for invalid commands, incorrect parameters, and unrecognized items.
Requirements
C++17 or later: This project uses Standard Template Library (STL) containers and requires a C++17 compatible compiler.
Installation and Setup
Clone the Repository:
bash
git clone https://salmansystech/your-username/chain-stores.git
cd chain-stores

Compile the Code:
# Use Qtcreator

./chain_stores
Input File Requirement: When prompted, provide the path to a CSV input file containing product data in the format:

# CSV.
S-Market;Hervantakeskus;yogurt;1.05
Prisma;Koivistonkyla;chocolate;out-of-stock
S-Market;Pirkkala;chocolate;out-of-stock
Prisma;Koivistonkyla;sausage;2.90
S-Market;Hervantakeskus;sausage;3.25
S-Market;Pirkkala;yogurt;out-of-stock
K-Citymarket;Linnainmaa;sausage;2.90
S-Market;Kaukajarvi;sausage;3.25
K-Citymarket;Pirkkala;yogurt;0.95
Prisma;Kaleva;sausage;2.90
K-Citymarket;Pirkkala;sausage;2.90
Prisma;Lielahti;yogurt;0.90
K-Citymarket;Turtola;sausage;out-of-stock
S-Market;Kaukajarvi;yogurt;1.05
K-Citymarket;Lielahti;yogurt;0.90
K-Citymarket;Linnainmaa;yogurt;0.95
Prisma;Kaleva;yogurt;0.90
Prisma;Lielahti;sausage;2.90
S-Market;Pirkkala;sausage;2.90
Prisma;Koivistonkyla;yogurt;0.90
K-Citymarket;Lielahti;sausage;3.00
K-Citymarket;Turtola;yogurt;0.95

Note: If the program encounters an error in file structure, it will notify you and terminate.

# User Commands
The program supports several commands for exploring chain and product data:

chains: Lists all chain names in alphabetical order.
stores <chain>: Lists all stores for the specified chain.
selection <chain> <store>: Shows all products and prices for the given store.
cheapest <product>: Displays the cheapest price for the product and lists the stores offering that price.
products: Lists all unique products available across stores.
quit: Exits the program.
Example Usage
Upon running, the program might look like this:

plaintext

Input file: products.input
> chains
K-Citymarket
Prisma
S-Market

> stores S-Market
Hervantakeskus
Kaukajarvi
Pirkkala

> selection S-Market Pirkkala
sausage 2.90
yogurt out-of-stock
chocolate out-of-stock

> cheapest yogurt
0.90 euros
K-Citymarket Lielahti
Prisma Kaleva
Prisma Koivistonkyla
Prisma Lielahti

> products
chocolate
sausage
yogurt
Error Messages
Error: unknown command: Command not recognized.
Error: error in command <command>: Command has incorrect parameters.
Error: unknown chain name: Chain does not exist.
Error: unknown store: Store does not exist within the specified chain.
Contributing
If you'd like to contribute to this project, please fork the repository and submit a pull request.

# License
This project is for educational use and does not include any license for commercial deployment. For further information, please contact the project author.
