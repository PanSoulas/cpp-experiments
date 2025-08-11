Φυσικά! Θα σου ετοιμάσω τη δομή φακέλων, τα αρχεία .cpp στους αντίστοιχους φακέλους και ένα README.md που να εξηγεί ότι το repository είναι beginner level, πειραματικό, και προορίζεται για ασκήσεις και πειραματισμούς σε C++.

### Δομή

```
cpp-experiments/
│
├── Inventory/
│   └── Inventory.cpp
│
├── Students/
│   └── Students.cpp
│
└── README.md
```

Δες τα αρχεία έτοιμα για να τα κάνεις copy-paste ή upload!

---

```cpp name=Inventory/Inventory.cpp
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
```

---

```cpp name=Students/Students.cpp
#include <iostream>
#include <string>
#include <vector>


using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

class Student
{
protected:
    string name;
    int age;
    float gpa;
public:
    Student() : name(""), age(0), gpa(0.0f) {}

    void setName(const string& studentName) { name = studentName; }
    void setAge(int studentAge) { age = studentAge; }
    void setGPA(float studentGPA) { gpa = studentGPA; }
    string getName() const { return name; }
    int getAge() const { return age; }
    float getGPA() const { return gpa; }

};


class Classroom:public Student
{
    private:
        vector<Student> students;
    public:
        Classroom() = default;

        void addStudent(const Student& student)    
        {
            students.push_back(student);
        }
        void avgGPA() const 
        {
            if (students.empty()) 
            {
                cout << "No students in the classroom." << endl;
                return;
            }

            float totalGPA = 0.0f;
            for (const auto& student : students) 
            {
                totalGPA += student.getGPA();
            }
            cout << "Average GPA: " << (totalGPA / students.size()) << endl;
        }

        void bestStudent() const 
        {
            if (students.empty()) 
            {
                cout << "No students in the classroom." << endl;
                return;
            }

            const Student* best = &students[0];
            for (const auto& student : students) 
            {
                if (student.getGPA() > best->getGPA()) 
                {
                    best = &student;
                }
            }
            cout << "Best Student: " << best->getName() << " with GPA: " << best->getGPA() << endl;
        }
};


int main()
{
    Classroom classroom;
    cout << "Enter number of students: ";
    int numStudents;
    cin >> numStudents;
    cin.ignore(); // Clear the newline character from the input buffer
    for (int i = 0; i < numStudents; ++i) 
    {
        Student student;
        string name;
        int age;
        float gpa;

        cout << "Enter name of student " << (i + 1) << ": ";
        getline(cin, name);
        if(name.empty()) 
        {
            cout << "Name cannot be empty. Please enter a valid name." << endl;
            --i; 
            continue; 
        }
        else if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) 
        {
            cout << "Name can only contain letters and spaces. Please enter a valid name." << endl;
            --i; 
            continue; 
        }
        student.setName(name);
        cout << "Enter age of student " << (i + 1) << ": ";
        cin >> age;
        if(age <= 0) 
        {
            cout << "Age must be a positive integer. Please enter a valid age." << endl;
            --i; 
            cin.ignore(); 
            continue; 
        }
        else if (age!= static_cast<int>(age)) 
        {
            cout << "Age must be an integer. Please enter a valid age." << endl;
            --i; 
            cin.ignore(); 
            continue; 
        }
        student.setAge(age);
        cin.ignore();

        cout << "Enter GPA of student " << (i + 1) << ": ";
        cin >> gpa;
        student.setGPA(gpa);
        cin.ignore(); // Clear the newline character from the input buffer

        classroom.addStudent(student);
    }
    classroom.avgGPA();
    classroom.bestStudent();
    return 0; 
}
```

---

````markdown name=README.md
# C++ Experiments (Beginner Level)

Αυτό το repository δημιουργήθηκε ως χώρος πειραματισμού και εξάσκησης σε προγράμματα C++ αρχικού έως ενδιάμεσου επιπέδου. Εδώ θα βρείτε απλά projects, δομές δεδομένων και μικρές εφαρμογές που γράφτηκαν κυρίως για την εξάσκησή μου και τη δοκιμή διαφόρων δυνατοτήτων της C++.

## Στόχος

- **Εκμάθηση και πειραματισμός** με βασικές δομές και τεχνικές της C++.
- Κάλυψη θεμάτων όπως: κλάσεις, vectors, αρχεία, βασικός χειρισμός strings, κ.ά.
- Ο κώδικας απευθύνεται σε αρχάριους ή όσους θέλουν να δουν παραδείγματα "βήμα-βήμα".
- Τα παραδείγματα εδώ αποτελούν προσωπική προσπάθεια πειραματισμού και αυτοβελτίωσης.

## Περιεχόμενα

- **Inventory:** Διαχείριση αποθέματος προϊόντων (με χρήση αρχείων CSV).
- **Students:** Εισαγωγή και διαχείριση φοιτητών, υπολογισμός μέσου όρου και καλύτερου φοιτητή.

## Δομή

```
Inventory/   -> Inventory.cpp (Διαχείριση αποθέματος)
Students/    -> Students.cpp (Διαχείριση φοιτητών)
README.md    -> Αυτό το αρχείο
```

## Πώς να τρέξετε τα παραδείγματα

1. Μεταβείτε στον φάκελο του project που θέλετε.
2. Κάντε compile το αντίστοιχο αρχείο:
   - `g++ Inventory.cpp -o Inventory`
   - `g++ Students.cpp -o Students`
3. Τρέξτε το εκτελέσιμο:
   - `./Inventory`
   - `./Students`

## Σημείωση

Αυτό το repository θα εμπλουτίζεται με παρόμοια προγράμματα και πειραματισμούς σε C++ στο μέλλον. 
Ο κώδικας είναι απλός και δεν ακολουθεί απαραίτητα βέλτιστες πρακτικές παραγωγής — ο στόχος είναι η μάθηση και ο πειραματισμός!

---

**PanSoulas**
````
