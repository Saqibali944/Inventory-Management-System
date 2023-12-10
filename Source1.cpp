#include"Source1.h"
Customer_Module::Customer_Module() {}
void Customer_Module::SetCustomerID(string id) {
    CustomerID = id;
}
string Customer_Module::GetCustomerID() const {
    return CustomerID;
}
void Customer_Module::SetFirstName(string firstName) {
    FirstName = firstName;
}
string Customer_Module::GetFirstName() const {
    return FirstName;
}
void Customer_Module::SetLastName(string lastName) {
    LastName = lastName;
}
string Customer_Module::GetLastName() const {
    return LastName;
}
void Customer_Module::SetAddress(string address) {
    Address = address;
}
string Customer_Module::GetAddress() const {
    return Address;
}
void Customer_Module::SetContactNo(string contactNo) {
    ContactNo = contactNo;
}
string Customer_Module::GetContactNo() const {
    return ContactNo;
}
void Customer_Module::SetUsername(string username) {
    Username = username;
}
string Customer_Module::GetUsername() const {
    return Username;
}
void Customer_Module::SetEmail(string email) {
    Email = email;
}
string Customer_Module::GetEmail() const {
    return Email;
}
void Customer_Module::SetPassword(string password) {
    Password = password;
}
string Customer_Module::GetPassword() const {
    return Password;
}
void Customer_Module::RegisterCustomer() {
    ifstream file("customer.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }
    string line;
    int maxID = 0;
    // Find the maximum existing Customer ID
    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        int num = stoi(id.substr(3));
        if (num > maxID) {
            maxID = num;
        }
    }
    file.close();
    // Generate a new Customer ID
    int num = maxID + 1;
    CustomerID = "000" + to_string(num);
    cout << "Enter First Name: ";
    getline(cin, FirstName);
    cout << "Enter Last Name: ";
    getline(cin, LastName);
    cout << "Enter Address: ";
    getline(cin, Address);
    cout << "Enter Contact No: ";
    getline(cin, ContactNo);
    cout << "Enter Username: ";
    getline(cin, Username);
    cout << "Enter Email: ";
    getline(cin, Email);
    cout << "Enter Password: ";
    getline(cin, Password);
    // Append the new Customer data to the file
    ofstream customerFile("customer.txt", ios::app);
    if (!customerFile.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
    customerFile << setw(4) << setfill('0') << CustomerID << " " << FirstName << " " << LastName << " "
        << Address << " " << ContactNo << " " << Username << " "
        << Email << " " << Password << endl;

    customerFile.close();

    cout << "Customer registered successfully!" << endl;
}
void Customer_Module::DisplayCustomerDetails() const {
    cout << "Customer ID: " << CustomerID << endl;
    cout << "First Name: " << FirstName << endl;
    cout << "Last Name: " << LastName << endl;
    cout << "Address: " << Address << endl;
    cout << "Contact No: " << ContactNo << endl;
    cout << "Username: " << Username << endl;
    cout << "Email: " << Email << endl;
    cout << "Password: " << Password << endl;
}
bool Customer_Module::CustomerSignIn() {
    string ID, Username, Password;
    string InputShopkeeper_Username, InputShopkeeper_Password;
    ifstream Login("customer.txt");
    cout << "Enter Customer Username: ";
    cin >> InputShopkeeper_Username;
    cout << "Enter Customer Password: ";
    cin >> InputShopkeeper_Password;
    if (!Login.is_open()) {
        cout << "Error: Unable to open shopkeeper login data file." << endl;
        return false;
    }
    else {
        bool found = false; // Variable to track if the shopkeeper credentials are found
        while (Login >> ID >> Username >> Password) {
            if (ID == "CUSTOMER") {
                if (InputShopkeeper_Username == Username && InputShopkeeper_Password == Password) {
                    cout << "Customer Sign-in successful!" << endl;
                    found = true;
                    break; // Exit the loop if credentials are found
                }
            }
        }
        Login.close();
        Sleep(2000);
        system("CLS");
        if (found) {
            return true;
        }
        else {
            cout << "Invalid credentials. Shopkeeper Sign-in failed." << endl;
            return false;
        }
    }
}
void Customer_Module::DisplayProductList() const {
    ifstream productFile("products.txt");
    if (!productFile.is_open()) {
        cout << "Error: Unable to open product file." << endl;
        return;
    }
    cout << "Product List:" << endl;
    string line;
    while (getline(productFile, line)) {
        istringstream iss(line);
        string pid, productName, description, category, size, color;
        int quantity;
        iss >> pid >> productName >> description >> category >> size >> color >> quantity;
        cout << "Product ID: " << pid << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Description: " << description << endl;
        cout << "Category: " << category << endl;
        cout << "Size: " << size << endl;
        cout << "Color: " << color << endl;
        cout << "Quantity: " << (quantity > 0 ? to_string(quantity) : "Out of Stock") << endl;
        cout << "-------------------------" << endl;
    }
    productFile.close();
}
void Customer_Module::AddToCart(const string& customerId, const string& productName, int quantity) {
    // Check if the product file and cart file exist
    ifstream productFile("products.txt");
    ofstream cartFile("addToCart.txt", ios::app);
    if (!productFile.is_open() || !cartFile.is_open()) {
        cout << "Error: Unable to open product or cart file." << endl;
        return;
    }
    string line;
    bool productFound = false;
    while (getline(productFile, line)) {
        istringstream iss(line);
        string pid, pName, description, category, size, color;
        int availableQuantity;
        float price;

        iss >> pid >> pName >> description >> category >> size >> color >> availableQuantity >> price;

        if (pName == productName && quantity > 0 && quantity <= availableQuantity) {
            cartFile << customerId << " " << pid << " " << pName << " " << quantity << " " << price * quantity << endl;
            productFound = true;
            break;
        }
    }
    productFile.close();
    cartFile.close();
    if (!productFound) {
        cout << "Error: Product not found or invalid quantity." << endl;
    }
}

// Checkout function
void Customer_Module::Checkout(const string& customerId) {
    // Display the list of products
    DisplayProductList();

    // Ask the customer to select products
    int numProducts;
    cout << "Enter the number of products you want to purchase: ";
    cin >> numProducts;

    double totalAmount = 0.0;

    // Clear the input buffer
    cin.ignore();

    for (int i = 0; i < numProducts; ++i) {
        // Get product details
        string productName;
        int quantity;

        cout << "Enter the name of the product you want to purchase: ";
        cin >> productName;
        cout << "Enter the quantity you want to purchase: ";
        cin >> quantity;

        // Calculate the total amount for the product
        // retrieve the price from the product data file and multiply it by the quantity
        double productAmount = 10.0 * quantity; // Placeholder calculation
        totalAmount += productAmount;
    }

    // Check if the customer has enough cash to pay for the total amount
    double customerAmount;
    cout << "Enter the customer's available amount: ";
    cin >> customerAmount;

    if (customerAmount < totalAmount) {
        cout << "Not enough cash. Payment failed." << endl;
        return;
    }

    // Get the shipment address
    string shipmentAddress;
    cout << "Enter the shipment address: ";
    cin.ignore();  // Clear the newline character
    getline(cin, shipmentAddress);

    // Process the payment and shipment
    // Implement your logic here
    cout << "Happy Shopping!" << endl;
}

void Customer_Module::PurchaseProduct(string& customerId) {
    // Display the list of products
    DisplayProductList();

    // Ask the customer to select products
    int numProducts;
    cout << "Enter the number of products you want to purchase: ";
    cin >> numProducts;

    // Clear the input buffer
    cin.ignore();

    for (int i = 0; i < numProducts; ++i) {
        // Get product details
        string productName;
        int quantity;

        cout << "Enter the name of the product you want to purchase: ";
        getline(cin, productName);

        cout << "Enter the quantity you want to purchase: ";
        cin >> quantity;

        // Add the product to the cart
        AddToCart(customerId, productName, quantity);

        cout << "Product '" << productName << "' added to the cart successfully!" << endl;
    }

    // Call the Checkout function after the for loop
    Checkout(customerId);
}

Administrator_Module::Administrator_Module() // Administrator Class Constructor
{
    InputAdmin_Username = "\0";
    InputAdmin_Password = "\0";
}

bool Administrator_Module::AdminSignIn() // Administrator Class SignIn Function
{
    string ID, UserName, Password;
    ifstream Login("Log_In_Data.txt");
    cout << endl << "Enter the User Name for Admin: ";
    cin >> InputAdmin_Username;
    cout << endl << "Enter the Password for Admin: ";
    cin >> InputAdmin_Password;
    if (!Login.is_open()) {
        cout << endl
            << "ERROR 404...\nThe LogIn Database cannot be accessed for the Username and Password! Please try again.";
        return false;
    }
    else {
        while (Login >> ID >> UserName >> Password) {
            if (ID == "ADMIN") {
                if (InputAdmin_Username == UserName && InputAdmin_Password == Password) {
                    system("color 4B");
                    Sleep(300);
                    cout << ("  0   0  00000  0      0      000   0     0  00000 ") << endl;
                    Sleep(300);
                    cout << ("  0   0  0      0      0     0   0  00   00  0     ") << endl;
                    Sleep(300);
                    cout << ("  0 0 0  0000   0      0     0   0  0 0 0 0  0000  ") << endl;
                    Sleep(300);
                    cout << ("  00 00  0      0      0     0   0  0  0  0  0     ") << endl;
                    Sleep(300);
                    cout << ("  0   0  00000  00000  00000  000   0     0  00000 ") << endl;
                    Login.close();
                    Sleep(2000);
                    system("CLS");
                    return true;
                }
                else {
                    cout << endl << "You have Entered the wrong UserName and password for Admin login!" << endl;
                    Login.close();
                    Sleep(2000);
                    system("CLS");
                    return false;
                }
            }
        }
    }
    return false; // Add a return statement in case the loop doesn't find a match
}

void Administrator_Module::AddNewShopkeeper() {
    ifstream CounterFile("shopkeeper.txt");
    int shopkeeperCounter = 0;
    if (CounterFile) {
        CounterFile >> shopkeeperCounter;
        CounterFile.close();
    }
    shopkeeperCounter++;
    ofstream CounterOutFile("shopkeeper.txt", ios::trunc);
    if (CounterOutFile) {
        CounterOutFile << shopkeeperCounter;
        CounterOutFile.close();
    }
    else {
        cout << endl << "ERROR: Failed to update the shopkeeper counter!";
        return;
    }
    // Generate the formatted shopkeeper ID
    ostringstream oss;
    oss << setw(4) << setfill('0') << shopkeeperCounter;
    string S_id = "Shopkeeper" + oss.str();
    string FirstName, LastName, Username, Password, RegistrationDate, Gender, BloodGroup, ContactNo, Address;
    cout << endl << "* Enter the Details of the New Shopkeeper *" << endl;
    cout << endl << "Enter First Name of the Shopkeeper: ";
    cin.ignore();
    getline(cin, FirstName);
    cout << endl << "Enter Last Name of the Shopkeeper: ";
    getline(cin, LastName);
    cout << endl << "Enter the Shopkeeper User Name for Login: ";
    getline(cin, Username);
    cout << endl << "Enter the Shopkeeper Password for Login: ";
    getline(cin, Password);
    cout << endl << "Enter the Registration Date of the Shopkeeper (dd/mm/yyyy): ";
    getline(cin, RegistrationDate);
    cout << endl << "Enter the Gender of the Shopkeeper: ";
    getline(cin, Gender);
    cout << endl << "Enter the Blood Group of the Shopkeeper: ";
    getline(cin, BloodGroup);
    cout << endl << "Enter the Contact Number of the Shopkeeper: ";
    getline(cin, ContactNo);
    cout << endl << "Enter the Address of the Shopkeeper: ";
    getline(cin, Address);
    ofstream ShopkeeperFile("shopkeeper.txt", ios::app);
    if (!ShopkeeperFile) {
        cout << endl << "ERROR: The Shopkeeper Database cannot be accessed to add a new shopkeeper! Please try again.";
    }
    else {
        ShopkeeperFile << S_id << " " << FirstName << " " << LastName << " " << Username << " "
            << Password << " " << RegistrationDate << " " << Gender << " " << BloodGroup << " "
            << ContactNo << " " << Address << endl;
        ShopkeeperFile.close();
        system("CLS");
        cout << endl << "\n\n\n\n\n\n\n\n\t\t\t\tNew Shopkeeper has been added to the system" << endl;
        Sleep(1250);
        system("CLS");
    }
}
void Administrator_Module::AddNewCustomer() {
    ifstream CounterFile("customer.txt");
    int customerCounter = 0;
    if (CounterFile) {
        CounterFile >> customerCounter;
        CounterFile.close();
    }
    customerCounter++;
    ofstream CounterOutFile("customer.txt");
    if (CounterOutFile) {
        CounterOutFile << setw(4) << setfill('0') << customerCounter;
        CounterOutFile.close();
    }
    else {
        cout << endl << "ERROR: Failed to update the customer counter!";
        return;
    }
    string C_id = "Customer" + to_string(customerCounter);
    string FirstName, LastName, Username, Password, RegistrationDate, Gender, BloodGroup, ContactNo, Address;
    cout << endl << "* Enter the Details of the New Customer *" << endl;
    cout << endl << "Enter First Name of the Customer: ";
    cin >> FirstName;
    cout << endl << "Enter Last Name of the Customer: ";
    cin >> LastName;
    cout << endl << "Enter the Customer User Name for Login: ";
    cin >> Username;
    cout << endl << "Enter the Customer Password for Login: ";
    cin >> Password;
    cin.ignore();
    cout << endl << "Enter the Registration Date of the Customer (dd/mm/yyyy): ";
    cin >> RegistrationDate;
    cout << endl << "Enter the Gender of the Customer: ";
    cin >> Gender;
    cout << endl << "Enter the Blood Group of the Customer: ";
    cin >> BloodGroup;
    cout << endl << "Enter the Contact Number of the Customer: ";
    cin >> ContactNo;
    cout << endl << "Enter the Address of the Customer: ";
    cin >> Address;
    ofstream CustomerFile;
    CustomerFile.open("customer.txt", ios::app);
    if (!CustomerFile) {
        cout << endl << "ERROR: The Customer Database cannot be accessed to add a new customer! Please try again.";
    }
    else {
        CustomerFile << C_id << " " << FirstName << " " << LastName << " " << Username << " "
            << Password << " " << RegistrationDate << " " << Gender << " " << BloodGroup << " "
            << ContactNo << " " << Address << endl;
        CustomerFile.close();
        system("CLS");
        cout << endl << "\n\n\n\n\n\n\n\n\t\t\t\tNew Customer has been added to the system" << endl;
        Sleep(1250);
        system("CLS");
    }
}

void Administrator_Module::AddNewProduct() {
    string categoryOptions[] = { "Sports", "Garments", "Eatables", "Medicines", "Fashion" };
    int numCategories = sizeof(categoryOptions) / sizeof(categoryOptions[0]);
    string categoryName;
    string categoryCode;
    cout << "Select Category:" << endl;
    for (int i = 0; i < numCategories; i++) {
        cout << i + 1 << ". " << categoryOptions[i] << endl;
    }
    int choice;
    cout << "Enter the category number: ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character after cin
    if (choice >= 1 && choice <= numCategories) {
        categoryName = categoryOptions[choice - 1];
        categoryCode = to_string(choice);
        if (categoryCode.length() == 1) {
            categoryCode = "0" + categoryCode;
        }
    }
    else {
        cout << "Invalid category choice!" << endl;
        return;
    }
    // Generate the product ID
    ifstream CounterFile("products.txt");
    int productCounter = 0;
    if (CounterFile) {
        CounterFile >> productCounter;
        CounterFile.close();
    }
    productCounter++;
    ofstream CounterOutFile("products.txt");
    if (CounterOutFile) {
        CounterOutFile << setw(4) << setfill('0') << productCounter;
        CounterOutFile.close();
    }
    else {
        cout << "ERROR: Failed to update the product counter!";
        return;
    }
    string P_id = "Product" + to_string(productCounter);
    string productName, description, size, color;
    int quantity;
    ofstream ProductFile("products.txt", ios::app);
    cout << endl << "* Enter the Details of the New Product *" << endl;
    cout << endl << "Enter the Product Name: ";
    getline(cin, productName);
    cout << endl << "Enter the Description of the Product: ";
    getline(cin, description);
    cout << endl << "Enter the Size of the Product (optional): ";
    getline(cin, size);
    cout << endl << "Enter the Color of the Product (optional): ";
    getline(cin, color);
    cout << endl << "Enter the Product Quantity: ";
    cin >> quantity;
    cin.ignore(); // Ignore the newline character after cin
    string stockStatus = (quantity > 0) ? "In Stock" : "Out of Stock";
    if (!ProductFile) {
        cout << endl << "ERROR: The Product Database cannot be accessed to add a new product! Please try again.";
    }
    else {
        ProductFile << categoryName << " " << P_id << " " << productName << " " << description << " " << size << " "
            << color << " " << quantity << " " << stockStatus << endl;
        ProductFile.close();
        cout << endl << "\n\n\n\n\n\n\n\n\t\t\t\tNew Product has been added to the system" << endl;
    }
}

void Administrator_Module::EditShopkeeperDetails() {
    string NewFirstName, NewLastName, NewAddress, NewContact, NewUsername, NewEmail, NewPassword;
    string IDCheck, ID, FirstName, LastName, Address, ContactNo, Username, Email, Password, Shopkeeper_Data;
    char choice;
    ifstream ShopkeeperFile("shopkeeper.txt");
    ofstream TempFile("temp_shopkeeper.txt");
    if (!ShopkeeperFile || !TempFile) {
        cout << endl << "ERROR 404...\nThe Shopkeeper Database cannot be accessed to edit shopkeeper details! Please try again.";
        return;
    }
    string shopkeeperID;
    cout << "Enter the Shopkeeper ID: ";
    cin >> shopkeeperID;
    bool found = false;
    while (getline(ShopkeeperFile, Shopkeeper_Data)) {
        istringstream Data(Shopkeeper_Data);
        Data >> ID >> FirstName >> LastName >> Address >> ContactNo >> Username >> Email >> Password;
        if (ID == shopkeeperID) {
            found = true;
            cout << endl << "Current Details:" << endl;
            cout << "1. First Name: " << FirstName << endl;
            cout << "2. Last Name: " << LastName << endl;
            cout << "3. Address: " << Address << endl;
            cout << "4. Contact No: " << ContactNo << endl;
            cout << "5. Username: " << Username << endl;
            cout << "6. Email: " << Email << endl;
            cout << "7. Password: " << Password << endl;
            cout << endl << "Enter the number corresponding to the field you want to edit: ";
            cin >> choice;
            switch (choice) {
            case '1':
                cout << "Enter the new First Name: ";
                cin.ignore();
                getline(cin, NewFirstName);
                FirstName = NewFirstName;
                break;
            case '2':
                cout << "Enter the new Last Name: ";
                cin.ignore();
                getline(cin, NewLastName);
                LastName = NewLastName;
                break;
            case '3':
                cout << "Enter the new Address: ";
                cin.ignore();
                getline(cin, NewAddress);
                Address = NewAddress;
                break;
            case '4':
                cout << "Enter the new Contact No: ";
                cin.ignore();
                getline(cin, NewContact);
                ContactNo = NewContact;
                break;
            case '5':
                cout << "Enter the new Username: ";
                cin.ignore();
                getline(cin, NewUsername);
                Username = NewUsername;
                break;
            case '6':
                cout << "Enter the new Email: ";
                cin.ignore();
                getline(cin, NewEmail);
                Email = NewEmail;
                break;
            case '7':
                cout << "Enter the new Password: ";
                cin.ignore();
                getline(cin, NewPassword);
                Password = NewPassword;
                break;
            default:
                cout << "Invalid choice. No changes made." << endl;
            }
        }
        TempFile << ID << " " << FirstName << " " << LastName << " " << Address << " "
            << ContactNo << " " << Username << " " << Email << " " << Password << endl;
    }
    ShopkeeperFile.close();
    TempFile.close();
    remove("shopkeeper.txt");
    rename("temp_shopkeeper.txt", "shopkeeper.txt");
    if (found) {
        cout << endl << "Shopkeeper details updated successfully!" << endl;
    }
    else {
        cout << endl << "Shopkeeper with ID " << shopkeeperID << " not found." << endl;
    }
}
void Administrator_Module::EditCustomerDetails() {
    string NewFirstName, NewLastName, NewAddress, NewContact, NewUsername, NewEmail, NewPassword;
    string IDCheck, ID, FirstName, LastName, Address, ContactNo, Username, Email, Password, Customer_Data;
    char choice;
    ifstream CustomerFile("customer.txt");
    ofstream TempFile("temp_customer.txt", ios::app);
    if (!CustomerFile || !TempFile) {
        cout << endl << "ERROR 404...\nThe Customer Database cannot be accessed to edit customer details! Please try again.";
        return;
    }
    cout << endl << "Enter the ID of the Customer whose data you want to edit: ";
    cin.ignore();
    getline(cin, IDCheck);
    bool found = false;
    while (getline(CustomerFile, Customer_Data)) {
        istringstream Data(Customer_Data);
        Data >> ID >> FirstName >> LastName >> Address >> ContactNo >> Username >> Email >> Password;
        if (ID == IDCheck) {
            found = true;
            cout << endl << "Current Details:" << endl;
            cout << "1. First Name: " << FirstName << endl;
            cout << "2. Last Name: " << LastName << endl;
            cout << "3. Address: " << Address << endl;
            cout << "4. Contact No: " << ContactNo << endl;
            cout << "5. Username: " << Username << endl;
            cout << "6. Email: " << Email << endl;
            cout << "7. Password: " << Password << endl;
            cout << endl << "Enter the number corresponding to the field you want to edit: ";
            cin >> choice;
            switch (choice) {
            case '1':
                cout << "Enter the new First Name: ";
                cin.ignore();
                getline(cin, NewFirstName);
                FirstName = NewFirstName;
                break;
            case '2':
                cout << "Enter the new Last Name: ";
                cin.ignore();
                getline(cin, NewLastName);
                LastName = NewLastName;
                break;
            case '3':
                cout << "Enter the new Address: ";
                cin.ignore();
                getline(cin, NewAddress);
                Address = NewAddress;
                break;
            case '4':
                cout << "Enter the new Contact No: ";
                cin.ignore();
                getline(cin, NewContact);
                ContactNo = NewContact;
                break;
            case '5':
                cout << "Enter the new Username: ";
                cin.ignore();
                getline(cin, NewUsername);
                Username = NewUsername;
                break;
            case '6':
                cout << "Enter the new Email: ";
                cin.ignore();
                getline(cin, NewEmail);
                Email = NewEmail;
                break;
            case '7':
                cout << "Enter the new Password: ";
                cin.ignore();
                getline(cin, NewPassword);
                Password = NewPassword;
                break;
            default:
                cout << "Invalid choice. No changes made." << endl;
            }
        }
        TempFile << ID << " " << FirstName << " " << LastName << " " << Address << " "
            << ContactNo << " " << Username << " " << Email << " " << Password << endl;
    }
    CustomerFile.close();
    TempFile.close();
    remove("customer.txt");
    rename("temp_customer.txt", "customer.txt");
    if (found) {
        cout << endl << "Customer details updated successfully!" << endl;
    }
    else {
        cout << endl << "Customer with ID " << IDCheck << " not found." << endl;
    }
}
void Administrator_Module::editProductDetails() {
    string NewProductName, NewDescription, NewQuantity, ProductIDCheck;
    string ID, Category, ProductID, Description, Quantity;
    string Product_Data;
    char choice;
    ifstream ProductFile("products.txt");
    ofstream TempFile("temp.txt", ios::out);
    cout << "Enter the ID of the product to edit: ";
    cin.ignore();
    getline(cin, ProductIDCheck);  // Use ProductIDCheck to store the user input
    bool found = false;
    while (getline(ProductFile, Product_Data)) {
        istringstream Data(Product_Data);
        Data >> ID >> ProductID >> Category >> Description >> Quantity;
        if (ProductID == ProductIDCheck) {  // Check against ProductIDCheck
            found = true;
            cout << "Enter the new name of the product: ";
            getline(cin, NewProductName);
            cout << "Enter the new description of the product: ";
            getline(cin, NewDescription);
            cout << "Enter the new quantity of the product: ";
            getline(cin, NewQuantity);
            TempFile << ID << " " << ProductID << " " << Category << " " << NewProductName << " " << NewDescription << " " << NewQuantity << endl;
            cout << "Product details updated successfully." << endl;
        }
        else {
            TempFile << Product_Data << endl;
        }
    }
    ProductFile.close();
    TempFile.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");
}
void Administrator_Module::DeleteShopkeeper() {
    string IDCheck, ID, FirstName, LastName, Address, ContactNo, Username, Email, Password, Shopkeeper_Data;
    cout << endl << "Enter the ID of the Shopkeeper you want to delete: ";
    cin.ignore();
    getline(cin, IDCheck);
    ifstream ShopkeeperFile("shopkeeper.txt");
    ofstream TempFile("temp_shopkeeper.txt", ios::app);
    if (!ShopkeeperFile || !TempFile) {
        cout << endl << "ERROR 404...\nThe Shopkeeper Database cannot be accessed to delete shopkeeper details! Please try again.";
        return;
    }
    bool shopkeeperFound = false;
    while (ShopkeeperFile >> ID >> FirstName >> LastName >> Address >> ContactNo >> Username >> Email >> Password) {
        if (ID == IDCheck) {
            shopkeeperFound = true;
            cout << endl << "Shopkeeper found and deleted:" << endl;
            cout << "ID: " << ID << endl;
            cout << "First Name: " << FirstName << endl;
            cout << "Last Name: " << LastName << endl;
            cout << "Address: " << Address << endl;
            cout << "Contact No: " << ContactNo << endl;
            cout << "Username: " << Username << endl;
            cout << "Email: " << Email << endl;
            cout << "Password: " << Password << endl;
            ShopkeeperFile.close();
            TempFile.close();
            remove("shopkeeper.txt");
            rename("temp_shopkeeper.txt", "shopkeeper.txt");
            if (!shopkeeperFound) {
                cout << endl << "Shopkeeper with ID " << IDCheck << " not found." << endl;
            }
            else {
                cout << endl << "Shopkeeper details deleted successfully!" << endl;
            }
            return;
        }
        else {
            TempFile << ID << " " << FirstName << " " << LastName << " " << Address << " "
                << ContactNo << " " << Username << " << Email << " << Password << endl;
        }
    }
    ShopkeeperFile.close();
    TempFile.close();
    remove("shopkeeper.txt");
    rename("temp_shopkeeper.txt", "shopkeeper.txt");
    if (!shopkeeperFound) {
        cout << endl << "Shopkeeper with ID " << IDCheck << " not found." << endl;
    }
    else {
        cout << endl << "Shopkeeper details deleted successfully!" << endl;
    }
}

void Administrator_Module::DeleteCustomer() {
    string IDCheck, ID, FirstName, LastName, Address, ContactNo, Username, Email, Password, Customer_Data;
    cout << endl << "Enter the ID of the Customer you want to delete: ";
    cin.ignore();
    getline(cin, IDCheck);
    ifstream CustomerFile("customer.txt");
    ofstream TempFile("temp_customer.txt", ios::app);
    if (!CustomerFile || !TempFile) {
        cout << endl << "ERROR 404...\nThe Customer Database cannot be accessed to delete customer details! Please try again.";
        return;
    }
    bool customerFound = false;
    while (CustomerFile >> ID >> FirstName >> LastName >> Address >> ContactNo >> Username >> Email >> Password) {
        if (ID == IDCheck) {
            cout << endl << "Customer found and deleted:" << endl;
            cout << "ID: " << ID << endl;
            cout << "First Name: " << FirstName << endl;
            cout << "Last Name: " << LastName << endl;
            cout << "Address: " << Address << endl;
            cout << "Contact No: " << ContactNo << endl;
            cout << "Username: " << Username << endl;
            cout << "Email: " << Email << endl;
            cout << "Password: " << Password << endl;

            customerFound = true;
        }
        else {
            TempFile << ID << " " << FirstName << " " << LastName << " " << Address << " "
                << ContactNo << " " << Username << " << Email << " << Password << endl;
        }
    }
    CustomerFile.close();
    TempFile.close();
    remove("customer.txt");
    rename("temp_customer.txt", "customer.txt");
    if (!customerFound) {
        cout << endl << "Customer with ID " << IDCheck << " not found." << endl;
    }
    else {
        cout << endl << "Customer details deleted successfully!" << endl;
    }
}

void Administrator_Module::DeleteProduct() {
    string ProductIDCheck, ProductID, ProductName, description, size, color, Product_Data;
    int quantity;

    cout << endl << "Enter the ID of the Product you want to delete: ";
    cin.ignore();
    getline(cin, ProductIDCheck);

    ifstream ProductFile("products.txt");
    ofstream TempFile("temp_products.txt");

    if (!ProductFile || !TempFile) {
        cout << endl << "ERROR 404...\nThe Product Database cannot be accessed to delete product details! Please try again.";
        return;
    }

    bool productFound = false;

    while (getline(ProductFile, Product_Data)) {
        istringstream Data(Product_Data);
        Data >> ProductID >> ProductName >> description >> size >> color >> quantity;

        if (ProductID == ProductIDCheck) {
            cout << endl << "Product found and deleted:" << endl;
            cout << "Product ID: " << ProductID << endl;
            cout << "Product Name: " << ProductName << endl;
            cout << "description:  " << description << endl;
            cout << "size: " << size << endl;
            cout << "color: " << color << endl;
            cout << "quantity: " << quantity << endl;
            productFound = true;
        }
        else {
            TempFile << Product_Data << endl;
        }
    }

    ProductFile.close();
    TempFile.close();

    remove("products.txt");
    rename("temp_products.txt", "products.txt");

    if (!productFound) {
        cout << endl << "Product with ID " << ProductIDCheck << " not found." << endl;
    }
    else {
        cout << endl << "Product details deleted successfully!" << endl;
    }
}

void Shopkeeper_Module::SetShopkeeperID(string id) {
    ShopkeeperID = id;
}

string Shopkeeper_Module::GetShopkeeperID() const {
    return ShopkeeperID;
}

void Shopkeeper_Module::SetFirstName(string firstName) {
    FirstName = firstName;
}

string Shopkeeper_Module::GetFirstName() const {
    return FirstName;
}

void Shopkeeper_Module::SetLastName(string lastName) {
    LastName = lastName;
}

string Shopkeeper_Module::GetLastName() const {
    return LastName;
}

void Shopkeeper_Module::SetUsername(string username) {
    Username = username;
}

string Shopkeeper_Module::GetUsername() const {
    return Username;
}

void Shopkeeper_Module::SetEmail(string email) {
    Email = email;
}

string Shopkeeper_Module::GetEmail() const {
    return Email;
}

void Shopkeeper_Module::SetPassword(string password) {
    Password = password;
}

string Shopkeeper_Module::GetPassword() const {
    return Password;
}

void Shopkeeper_Module::SetRegistrationDate(string date) {
    RegistrationDate = date;
}

string Shopkeeper_Module::GetRegistrationDate() const {
    return RegistrationDate;
}

void Shopkeeper_Module::SetGender(string gender) {
    Gender = gender;
}

string Shopkeeper_Module::GetGender() const {
    return Gender;
}

void Shopkeeper_Module::SetBloodGroup(string bloodGroup) {
    BloodGroup = bloodGroup;
}

string Shopkeeper_Module::GetBloodGroup() const {
    return BloodGroup;
}

void Shopkeeper_Module::SetContactNo(string contactNo) {
    ContactNo = contactNo;
}

string Shopkeeper_Module::GetContactNo() const {
    return ContactNo;
}

void Shopkeeper_Module::SetAddress(string address) {
    Address = address;
}

string Shopkeeper_Module::GetAddress() const {
    return Address;
}

void Shopkeeper_Module::RegisterShopkeeper() {
    ifstream file("shopkeeper.txt");

    if (!file.is_open()) {
        cout << "Error: Unable to open file for reading." << endl;
        return;
    }
    string line;
    int maxID = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        int num = stoi(id.substr(3));
        if (num > maxID) {
            maxID = num;
        }
    }
    file.close();
    int num = maxID + 1;
    ShopkeeperID = "000" + to_string(num);
    cout << "Enter First Name: ";
    cin >> FirstName;
    cout << "Enter Last Name: ";
    cin >> LastName;
    cout << "Enter Username: ";
    cin >> Username;
    cout << "Enter Email: ";
    cin >> Email;
    cout << "Enter Password: ";
    cin >> Password;
    cout << "Enter Registration Date (YYYY-MM-DD): ";
    cin >> RegistrationDate;
    cout << "Enter Gender: ";
    cin >> Gender;
    cout << "Enter Blood Group: ";
    cin >> BloodGroup;
    cout << "Enter Contact No: ";
    cin >> ContactNo;
    cout << "Enter Address: ";
    cin >> Address;

    ofstream shopkeeperFile("shopkeeper.txt", ios::app);

    if (!shopkeeperFile.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }

    shopkeeperFile << setw(4) << setfill('0') << ShopkeeperID << " " << FirstName << " " << LastName << " "
        << Username << " " << Email << " " << Password << " "
        << RegistrationDate << " " << Gender << " " << BloodGroup << " "
        << ContactNo << " " << Address << endl;

    shopkeeperFile.close();

    cout << "Shopkeeper registered successfully!" << endl;
}

void Shopkeeper_Module::DisplayShopkeeperDetails() const {
    cout << "Shopkeeper ID: " << ShopkeeperID << endl;
    cout << "First Name: " << FirstName << endl;
    cout << "Last Name: " << LastName << endl;
    cout << "Username: " << Username << endl;
    cout << "Email: " << Email << endl;
    cout << "Password: " << Password << endl;
    cout << "Registration Date: " << RegistrationDate << endl;
    cout << "Gender: " << Gender << endl;
    cout << "Blood Group: " << BloodGroup << endl;
    cout << "Contact No: " << ContactNo << endl;
    cout << "Address: " << Address << endl;
}

bool Shopkeeper_Module::ShopkeeperSignIn() {
    string ID, Username, Password;
    string InputShopkeeper_Username, InputShopkeeper_Password;
    ifstream Login("shopkeeper.txt");

    cout << "Enter Shopkeeper Username: ";
    cin >> InputShopkeeper_Username;

    cout << "Enter Shopkeeper Password: ";
    cin >> InputShopkeeper_Password;

    if (!Login.is_open()) {
        cout << "Error: Unable to open shopkeeper login data file." << endl;
        return false;
    }
    else {
        bool found = false; // Variable to track if the shopkeeper credentials are found
        while (Login >> ID >> Username >> Password) {
            if (ID == "SHOPKEEPER") {
                if (InputShopkeeper_Username == Username && InputShopkeeper_Password == Password) {
                    cout << "Shopkeeper Sign-in successful!" << endl;
                    found = true;
                    break; // Exit the loop if credentials are found
                }
            }
        }
        Login.close();
        Sleep(2000);
        system("CLS");

        if (found) {
            return true;
        }
        else {
            cout << "Invalid credentials. Shopkeeper Sign-in failed." << endl;
            return false;
        }
    }
}
void Shopkeeper_Module::AddNewProduct() {
    string categoryOptions[] = { "Sports", "Garments", "Eatables", "Medicines", "Fashion" };
    int numCategories = sizeof(categoryOptions) / sizeof(categoryOptions[0]);
    string categoryName;
    string categoryCode;
    cout << "Select Category:" << endl;
    for (int i = 0; i < numCategories; i++) {
        cout << i + 1 << ". " << categoryOptions[i] << endl;
    }
    int choice;
    cout << "Enter the category number: ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character after cin

    if (choice >= 1 && choice <= numCategories) {
        categoryName = categoryOptions[choice - 1];
        categoryCode = to_string(choice);
        if (categoryCode.length() == 1) {
            categoryCode = "0" + categoryCode;
        }
    }
    else {
        cout << "Invalid category choice!" << endl;
        return;
    }

    // Generate the product ID
    ifstream CounterFile("products.txt");
    int productCounter = 0;
    if (CounterFile) {
        CounterFile >> productCounter;
        CounterFile.close();
    }

    productCounter++;
    ofstream CounterOutFile("products.txt");
    if (CounterOutFile) {
        CounterOutFile << setw(4) << setfill('0') << productCounter;
        CounterOutFile.close();
    }
    else {
        cout << "ERROR: Failed to update the product counter!";
        return;
    }
    string P_id = "Product" + to_string(productCounter);
    string productName, description, size, color;
    int quantity;
    ofstream ProductFile("products.txt", ios::app);
    cout << endl << "* Enter the Details of the New Product *" << endl;
    cout << endl << "Enter the Product Name: ";
    getline(cin, productName);
    cout << endl << "Enter the Description of the Product: ";
    getline(cin, description);
    cout << endl << "Enter the Size of the Product (optional): ";
    getline(cin, size);
    cout << endl << "Enter the Color of the Product (optional): ";
    getline(cin, color);
    cout << endl << "Enter the Product Quantity: ";
    cin >> quantity;
    cin.ignore(); // Ignore the newline character after cin
    string stockStatus = (quantity > 0) ? "In Stock" : "Out of Stock";
    if (!ProductFile) {
        cout << endl << "ERROR: The Product Database cannot be accessed to add a new product! Please try again.";
    }
    else {
        ProductFile << categoryName << " " << P_id << " " << productName << " " << description << " " << size << " "
            << color << " " << quantity << " " << stockStatus << endl;
        ProductFile.close();
        cout << endl << "\n\n\n\n\n\n\n\n\t\t\t\tNew Product has been added to the system" << endl;
    }
}

void Shopkeeper_Module::EditProductDetails() {
    string NewProductName, NewDescription, NewQuantity, ProductIDCheck;
    string ID, Category, ProductID, Description, Quantity;
    string Product_Data;
    char choice;
    ifstream ProductFile("products.txt");
    ofstream TempFile("temp.txt", ios::out);
    cout << "Enter the ID of the product to edit: ";
    cin.ignore();
    getline(cin, ProductIDCheck);  // Use ProductIDCheck to store the user input
    bool found = false;
    while (getline(ProductFile, Product_Data)) {
        istringstream Data(Product_Data);
        Data >> ID >> ProductID >> Category >> Description >> Quantity;
        if (ProductID == ProductIDCheck) {  // Check against ProductIDCheck
            found = true;
            cout << "Enter the new name of the product: ";
            getline(cin, NewProductName);
            cout << "Enter the new description of the product: ";
            getline(cin, NewDescription);
            cout << "Enter the new quantity of the product: ";
            getline(cin, NewQuantity);
            TempFile << ID << " " << ProductID << " " << Category << " " << NewProductName << " " << NewDescription << " " << NewQuantity << endl;
            cout << "Product details updated successfully." << endl;
        }
        else {
            TempFile << Product_Data << endl;
        }
    }
    ProductFile.close();
    TempFile.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");
}

void Shopkeeper_Module::ViewProductsByShopkeeper() {
    ifstream ProductFile("products.txt");

    if (!ProductFile) {
        cout << endl << "ERROR 404...\nThe Product Database cannot be accessed to view products! Please try again.";
        return;
    }
    string shopkeeperName;
    cout << "Enter the shopkeeper name: ";
    getline(cin, shopkeeperName);
    string ProductID, ProductName, Description, Size, Color, Shopkeeper, Product_Data;
    int Quantity;
    bool productsFound = false;
    while (getline(ProductFile, Product_Data)) {
        istringstream Data(Product_Data);
        Data >> ProductID >> ProductName >> Description >> Size >> Color >> Quantity >> Shopkeeper;
        // Check if the shopkeeper name matches
        if (Shopkeeper == shopkeeperName) {
            productsFound = true;
            cout << endl << "Product ID: " << ProductID << endl;
            cout << "Name: " << ProductName << endl;
            cout << "Description: " << Description << endl;
            cout << "Size: " << Size << endl;
            cout << "Color: " << Color << endl;
            cout << "Quantity: " << Quantity << endl;
            cout << "Shopkeeper: " << Shopkeeper << endl;
            cout << "-----------------------------" << endl;
        }
    }
    ProductFile.close();

    if (!productsFound) {
        cout << endl << "No products found for the shopkeeper: " << shopkeeperName << endl;
    }
}
void welcome()
{
    Sleep(200);
    cout << "00  000       00  00               00  0000000000  000       00  0000000000000  00000000  00000000  00         00" << endl;
    Sleep(200);
    cout << "    0000      00   00             00   00          0000      00       00        00    00  00    00   00       00 " << endl;
    Sleep(200);
    cout << "00  00 00     00    00           00    00          00 00     00       00        00    00  00    00    00     00  " << endl;
    Sleep(200);
    cout << "00  00  00    00     00         00     00          00  00    00       00        00    00  00    00     00   00   " << endl;
    Sleep(200);
    cout << "00  00   00   00      00       00      0000000000  00   00   00       00        00    00  00 00000      00000    " << endl;
    Sleep(200);
    cout << "00  00    00  00       00     00       00          00    00  00       00        00    00  00    000      00      " << endl;
    Sleep(200);
    cout << "00  00     00 00        00   00        00          00     00 00       00        00    00  00     00      00      " << endl;
    Sleep(200);
    cout << "00  00      0000         00 00         00          00      0000       00        00    00  00      00     00      " << endl;
    Sleep(200);
    cout << "00  00       000          000          0000000000  00       000       00        00000000  00       00    00      " << endl;
    Sleep(200);
    cout << "                                                                                                                 " << endl;
    Sleep(200);
    cout << "000         000  0000000  000      00  00000000  000000000  000000    000          000  000000  000      00  000000000" << endl;
    Sleep(200);
    cout << "00 00     00 00  00   00  0000     00  00    00  00         00        00 00      00 00  00      0000     00     00    " << endl;
    Sleep(00);
    cout << "00  00   00  00  00   00  00 00    00  00    00  00         00        00   00  00   00  00      00 00    00     00    " << endl;
    Sleep(200);
    cout << "00   00 00   00  0000000  00  00   00  00000000  00         00        00    000     00  00      00  00   00     00    " << endl;
    Sleep(200);
    cout << "00    000    00  00   00  00   00  00  00    00  00   0000  000000    00    000     00  000000  00   00  00     00    " << endl;
    Sleep(200);
    cout << "00           00  00   00  00    00 00  00    00  00     00  00        00            00  00      00    00 00     00    " << endl;
    Sleep(200);
    cout << "00           00  00   00  00     0000  00    00  00     00  00        00            00  00      00     0000     00    " << endl;
    Sleep(200);
    cout << "00           00  00   00  00      000  00    00  000000000  000000    00            00  000000  00      000     00    " << endl;
    cout << "                                                                                                                      " << endl;
    cout << "          00000000000   00       00   00000000000    00000000000000   0000000000000   0000       0000" << endl;
    Sleep(200);
    cout << "          00              00    00    00                   00         00              00 00     00 00" << endl;
    Sleep(200);
    cout << "          00               00  00     00                   00         00              00  00   00  00" << endl;
    Sleep(200);
    cout << "          00000000000       0000      00000000000          00         0000000000000   00   00 00   00" << endl;
    Sleep(200);
    cout << "                   00        00                00          00         00              00    000    00" << endl;
    Sleep(200);
    cout << "                   00        00                00          00         00              00           00" << endl;
    Sleep(200);
    cout << "                   00        00                00          00         00              00           00" << endl;
    Sleep(200);
    cout << "          00000000000        00       00000000000          00         0000000000000   00           00" << endl;
    Sleep(200);
    cout << "                                                                                            " << endl;
    Sleep(500);
    system("CLS");
}

void welcome2()
{
    cout << "00  000       00  00               00  0000000000  000       00  0000000000000  00000000  00000000  00         00" << endl;
    cout << "    0000      00   00             00   00          0000      00       00        00    00  00    00   00       00 " << endl;
    cout << "00  00 00     00    00           00    00          00 00     00       00        00    00  00    00    00     00  " << endl;
    cout << "00  00  00    00     00         00     00          00  00    00       00        00    00  00    00     00   00   " << endl;
    cout << "00  00   00   00      00       00      0000000000  00   00   00       00        00    00  00 00000      00000    " << endl;
    cout << "00  00    00  00       00     00       00          00    00  00       00        00    00  00    000      00      " << endl;
    cout << "00  00     00 00        00   00        00          00     00 00       00        00    00  00     00      00      " << endl;
    cout << "00  00      0000         00 00         00          00      0000       00        00    00  00      00     00      " << endl;
    cout << "00  00       000          000          0000000000  00       000       00        00000000  00       00    00      " << endl;
    cout << "                                                                                                              " << endl;
    cout << "000         000  0000000  000      00  00000000  000000000  000000    000          000  000000  000      00  000000000" << endl;
    cout << "00 00     00 00  00   00  0000     00  00    00  00         00        00 00      00 00  00      0000     00     00    " << endl;
    cout << "00  00   00  00  00   00  00 00    00  00    00  00         00        00   00  00   00  00      00 00    00     00    " << endl;
    cout << "00   00 00   00  0000000  00  00   00  00000000  00         00        00    000     00  00      00  00   00     00    " << endl;
    cout << "00    000    00  00   00  00   00  00  00    00  00   0000  000000    00    000     00  000000  00   00  00     00    " << endl;
    cout << "00           00  00   00  00    00 00  00    00  00     00  00        00            00  00      00    00 00     00    " << endl;
    cout << "00           00  00   00  00     0000  00    00  00     00  00        00            00  00      00     0000     00    " << endl;
    cout << "00           00  00   00  00      000  00    00  000000000  000000    00            00  000000  00      000     00    " << endl;
    cout << "                                                                                                                      " << endl;
    cout << "          00000000000   00       00   00000000000    00000000000000   0000000000000   0000       0000" << endl;
    cout << "          00              00    00    00                   00         00              00 00     00 00" << endl;
    cout << "          00               00  00     00                   00         00              00  00   00  00" << endl;
    cout << "          00000000000       0000      00000000000          00         0000000000000   00   00 00   00" << endl;
    cout << "                   00        00                00          00         00              00    000    00" << endl;
    cout << "                   00        00                00          00         00              00           00" << endl;
    cout << "                   00        00                00          00         00              00           00" << endl;
    cout << "          00000000000        00       00000000000          00         0000000000000   00           00" << endl;
    cout << "                                                                                            " << endl;
    Sleep(500);
    system("CLS");
}
void loading()
{
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                                           " << endl;
    cout << "                                                       LOADING";
    for (int i = 0; i < 20; i++)
    {
        cout << ".";
        Sleep(200);
    }
    system("CLS");
}     