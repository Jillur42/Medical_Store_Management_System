#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Medicine {
    string name;
    string manufacturer;
    int quantity;
    float price;
};

struct Customer {
    string name;
    string address;
    string phone;
};

vector<Medicine> inventory;
vector<Customer> customers;

const string dataFolderPath = "data/";

void loadInventoryData() {
    ifstream file(dataFolderPath + "medicine.dat");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Medicine medicine;
            size_t pos = line.find(',');
            medicine.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            medicine.manufacturer = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            medicine.quantity = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            medicine.price = stof(line);
            inventory.push_back(medicine);
        }
        file.close();
    } else {
        cout << "Unable to load medicine data.\n";
    }
}

void saveInventoryData() {
    ofstream file(dataFolderPath + "medicine.dat");
    if (file.is_open()) {
        for (const Medicine& medicine : inventory) {
            file << medicine.name << "," << medicine.manufacturer << "," << medicine.quantity << "," << medicine.price << endl;
        }
        file.close();
    } else {
        cout << "Unable to save medicine data.\n";
    }
}

void loadCustomerData() {
    ifstream file(dataFolderPath + "customer.dat");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Customer customer;
            size_t pos = line.find(',');
            customer.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            customer.address = line.substr(0, pos);
            line.erase(0, pos + 1);
            customer.phone = line;
            customers.push_back(customer);
        }
        file.close();
    } else {
        cout << "Unable to load customer data.\n";
    }
}

void saveCustomerData() {
    ofstream file(dataFolderPath + "customer.dat");
    if (file.is_open()) {
        for (const Customer& customer : customers) {
            file << customer.name << "," << customer.address << "," << customer.phone << endl;
        }
        file.close();
    } else {
        cout << "Unable to save customer data.\n";
    }
}

void loadInventoryAndCustomerData() {
    loadInventoryData();
    loadCustomerData();
}

void addMedicine() {
    Medicine medicine;
    cout << "Enter medicine name: ";
    cin >> medicine.name;
    cout << "Enter manufacturer name: ";
    cin >> medicine.manufacturer;
    cout << "Enter quantity: ";
    cin >> medicine.quantity;
    cout << "Enter price: ";
    cin >> medicine.price;

    inventory.push_back(medicine);
    cout << "Medicine added successfully!\n";
    saveInventoryData();
}

void updateMedicine() {
    string name;
    cout << "Enter the name of the medicine to update: ";
    cin >> name;

    bool found = false;
    for (Medicine& medicine : inventory) {
        if (medicine.name == name) {
            cout << "Enter new quantity: ";
            cin >> medicine.quantity;
            cout << "Enter new price: ";
            cin >> medicine.price;
            cout << "Medicine updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Medicine not found!\n";
    } else {
        saveInventoryData();
    }
}

void searchMedicine() {
    string name;
    cout << "Enter the name of the medicine to search: ";
    cin >> name;

    bool found = false;
    for (const Medicine& medicine : inventory) {
        if (medicine.name == name) {
            cout << "Name: " << medicine.name << endl;
            cout << "Manufacturer: " << medicine.manufacturer << endl;
            cout << "Quantity: " << medicine.quantity << endl;
            cout << "Price: " << medicine.price << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Medicine not found!\n";
    }
}

void displayInventory() {
    cout << "Medicine Inventory:\n";
    for (const Medicine& medicine : inventory) {
        cout << "Name: " << medicine.name << endl;
        cout << "Manufacturer: " << medicine.manufacturer << endl;
        cout << "Quantity: " << medicine.quantity << endl;
        cout << "Price: " << medicine.price << endl;
        cout << "------------------------\n";
    }
}

void saveCustomerInfo() {
    Customer customer;
    cout << "Enter customer name: ";
    cin >> customer.name;
    cout << "Enter customer address: ";
    cin.ignore();
    getline(cin, customer.address);
    cout << "Enter customer phone number: ";
    cin >> customer.phone;

    customers.push_back(customer);
    cout << "Customer information saved successfully!\n";
    saveCustomerData();
}

void displayCustomers() {
    cout << "Customer Information:\n";
    for (const Customer& customer : customers) {
        cout << "Name: " << customer.name << endl;
        cout << "Address: " << customer.address << endl;
        cout << "Phone: " << customer.phone << endl;
        cout << "------------------------\n";
    }
}

void billingSystem() {
    string medicineName;
    int quantity;
    float totalPrice = 0;

    cout << "Enter medicine name: ";
    cin >> medicineName;

    bool found = false;
    for (Medicine& medicine : inventory) {
        if (medicine.name == medicineName) {
            found = true;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity <= medicine.quantity) {
                medicine.quantity -= quantity;
                totalPrice = quantity * medicine.price;
            } else {
                cout << "Insufficient quantity available!\n";
                return;
            }

            break;
        }
    }

    if (!found) {
        cout << "Medicine not found!\n";
        return;
    }

    cout << "Billing Information:\n";
    cout << "Medicine Name: " << medicineName << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Total Price: " << totalPrice << endl;
    saveInventoryData();
}

void mainMenu() {
    char choice;
    while (true) {
        cout << "Medical Store Management System\n";
        cout << "1. Add Medicine\n";
        cout << "2. Update Medicine\n";
        cout << "3. Search Medicine\n";
        cout << "4. Display Inventory\n";
        cout << "5. Save Customer Information\n";
        cout << "6. Display Customers\n";
        cout << "7. Billing System\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                addMedicine();
                break;
            case '2':
                updateMedicine();
                break;
            case '3':
                searchMedicine();
                break;
            case '4':
                displayInventory();
                break;
            case '5':
                saveCustomerInfo();
                break;
            case '6':
                displayCustomers();
                break;
            case '7':
                billingSystem();
                break;
            case '8':
                cout << "Exiting program...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        cout << endl;

        // Ask for continuation
        char continueChoice;
        cout << "Do you want to continue (y/n)? ";
        cin >> continueChoice;

        if (continueChoice != 'y' && continueChoice != 'Y') {
            mainMenu();
            return;
        }
    }
}

int main() {
    // Create the "data" folder if it doesn't exist
    string createFolderCommand = "mkdir -p " + dataFolderPath;
    system(createFolderCommand.c_str());

    // Load existing data from files
    loadInventoryAndCustomerData();

    mainMenu();

    // Save data to files before exiting
    saveInventoryData();
    saveCustomerData();

    return 0;
}
