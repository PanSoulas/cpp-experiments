#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::fstream;
using std::vector;

class Product 
{
    protected:
        string name;
        float price;
        string ID;
        int quantity;
        string category;
        string supplier;
    public:
        Product()
        {
            name = "";
            price = 0.0;
            ID = "";
            quantity = 0;
            category = "";
            supplier = "";  
        }
        void setName(const string& n) { name = n; }
        void setPrice(float p) { price = p; }
        void setID(string id) { ID = id; }
        void setQuantity(int q) { quantity = q; }
        void setCategory(const string& cat) { category = cat; }
        void setSupplier(const string& supp) { supplier = supp; }
        string getName() const { return name; }
        float getPrice() const { return price; }
        string getID() const { return ID; }
        int getQuantity() const { return quantity; }
        string getCategory() const { return category; }
        string getSupplier() const { return supplier; }

        string toCSV() const
        {
            return ID + "," + name + "," + std::to_string(price) + "," + std::to_string(quantity) + "," + category + "," + supplier;
        }
        static Product fromCSV(const std::string& line)
        {
            Product product;
            size_t pos = 0;
            size_t nextPos = 0;

            nextPos = line.find(',', pos);
            product.setID(line.substr(pos, nextPos - pos));
            pos = nextPos + 1;

            nextPos = line.find(',', pos);
            product.setName(line.substr(pos, nextPos - pos));
            pos = nextPos + 1;

            nextPos = line.find(',', pos);
            product.setPrice(std::stof(line.substr(pos, nextPos - pos)));
            pos = nextPos + 1;

            nextPos = line.find(',', pos);
            product.setQuantity(std::stoi(line.substr(pos, nextPos - pos)));
            pos = nextPos + 1;

            nextPos = line.find(',', pos);
            product.setCategory(line.substr(pos, nextPos - pos));
            pos = nextPos + 1;

            product.setSupplier(line.substr(pos));

            return product;
        }
};



class Inventory 
{
private:
    vector<Product> products;
public:
    void addProduct(const Product& product) 
    {
        for (const auto& p : products) 
        {
            if (product.getID() == p.getID()) 
            {
                cout << "Product with this ID already exists." << endl;
                return;
            }
        }
        products.push_back(product);
        cout << "Product added successfully." << endl;
    }

    void removeProductbyID(const string& id) 
    {
        for (auto it = products.begin(); it != products.end(); ++it) 
        {
            if (it->getID() == id) 
            {
                products.erase(it);
                cout << "Product with ID " << id << " removed." << endl;
                return;
            }
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void updateQuantity(const string& id, int newQuantity) 
    {
        for (auto& product : products) 
        {
            if (product.getID() == id) 
            {
                product.setQuantity(newQuantity);
                cout << "Updated quantity for product ID " << id << " to " << newQuantity << "." << endl;
                return;
            }
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void updatePrice(const string& id, float newPrice) 
    {
        for (auto& product : products) 
        {
            if (product.getID() == id) 
            {
                product.setPrice(newPrice);
                cout << std::fixed << std::setprecision(2);
                cout << "Updated price for product ID " << id << " to " << newPrice << "." << endl;
                return;
            }
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void findProductByID(const string& id) const 
    {
        for (const auto& product : products) 
        {
            if (product.getID() == id) 
            {
                cout << std::fixed << std::setprecision(2);
                cout << "Product found: " << product.getName() 
                     << ", Price: " << product.getPrice() 
                     << ", Quantity: " << product.getQuantity() << endl;
                return;
            }
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void findByName(const string& name) const 
    {
        for (const auto& product : products) 
        {
            if (product.getName() == name) 
            {
                cout << std::fixed << std::setprecision(2);
                cout << "Product found: " << product.getName() 
                     << ", Price: " << product.getPrice() 
                     << ", Quantity: " << product.getQuantity() << endl;
                return;
            }
        }
        cout << "Product with name " << name << " not found." << endl;
    }

    void listAllProducts() const 
    {
        if (products.empty()) 
        {
            cout << "No products in inventory." << endl;
            return;
        }
        cout << std::fixed << std::setprecision(2);
        cout << "Listing all products:" << endl;
        for (const auto& product : products) 
        {
            cout << "ID: " << product.getID() 
                 << ", Name: " << product.getName() 
                 << ", Price: " << product.getPrice() 
                 << ", Quantity: " << product.getQuantity() 
                 << ", Category: " << product.getCategory() << endl;
        }
    }

    void listProductsByCategory(const string& category) const 
    {
        bool found = false;
        cout << std::fixed << std::setprecision(2);
        for (const auto& product : products) 
        {
            if (product.getCategory() == category) 
            {
                cout << "Product found: " << product.getName() 
                     << ", Price: " << product.getPrice() 
                     << ", Quantity: " << product.getQuantity() << endl;
                found = true;
            }
        }
        if (!found) 
        {
            cout << "No products found in category " << category << "." << endl;
        }
    }


    void totalValue() const 
    {
        float total = 0.0;
        for (const auto& product : products) 
        {
            total += product.getPrice() * product.getQuantity();
        }
        cout << std::fixed << std::setprecision(2);
        cout << "Total value of inventory: " << total << endl;
    }

    //CSV file operations
    void saveToCSV(const string& filename) const
    {
        fstream file(filename, std::ios::out);
        if (!file.is_open())
        {
            cout << "Error opening file for writing." << endl;
            return;
        }
        for (const auto& product : products)
        {
            file << product.toCSV() << "\n";
        }
        file.close();
        cout << "Inventory saved to " << filename << endl;
    }

    void loadFromCSV(const string& filename) 
    {
        fstream file(filename, std::ios::in);
        if (!file.is_open())
        {
            cout << "Error opening file for reading." << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                Product product = Product::fromCSV(line);
                addProduct(product);
            }
        }
        file.close();
        cout << "Inventory loaded from " << filename << endl;
    }

    //sort products by price
    void sortByPrice()
    {
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.getPrice() < b.getPrice();
        });
        cout << "Products sorted by price." << endl;
    }


    //low stock alert
    void lowStockAlert(int threshold) const
    {
        cout << "Products with stock below " << threshold << ":" << endl;
        bool any = false;
        for (const auto& product : products)
        {
            if (product.getQuantity() < threshold)
            {
                cout << "ID: " << product.getID()
                     << ", Name: " << product.getName()
                     << ", Quantity: " << product.getQuantity() << endl;
                any = true;
            }
        }
        if (!any)
        {
            cout << "No products with stock below " << threshold << "." << endl;
        }
    }
};


int main()
{
    Inventory inventory;
    Product product1;
    product1.setID("001");
    product1.setName("Widget");
    product1.setPrice(19.99);
    product1.setQuantity(100);
    product1.setCategory("Gadgets");
    product1.setSupplier("Supplier A");

    inventory.addProduct(product1);

    Product product2;
    product2.setID("002");
    product2.setName("Gadget");
    product2.setPrice(29.99);
    product2.setQuantity(50);
    product2.setCategory("Gadgets");
    product2.setSupplier("Supplier B");

    inventory.addProduct(product2);

    inventory.listAllProducts();
    
    inventory.saveToCSV("inventory.csv");
    
    inventory.loadFromCSV("inventory.csv");

    return 0;  
}