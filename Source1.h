#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<Windows.h>
#include<iomanip>
#define BLUE   "\033[34m"
#define YELLOW "\033[33m"
#define RED    "\033[31m"
#define WHITE  "\033[37m"
#define RESET  "\033[0m"
using namespace std;
static int customerCounter = 0;
static int productCounter = 0;
class Administrator_Module {
private:
    string InputAdmin_Username;
    string InputAdmin_Password;
public:
    Administrator_Module();
    bool AdminSignIn();
    void AddNewShopkeeper();
    void AddNewCustomer();
    void AddNewProduct();
    void EditShopkeeperDetails();
    void EditCustomerDetails();
    void editProductDetails();
    void DeleteShopkeeper();
    void DeleteCustomer();
    void DeleteProduct();
};
class Shopkeeper_Module {
private:
    string ShopkeeperID;
    string FirstName;
    string LastName;
    string Username;
    string Email;
    string Password;
    string RegistrationDate;
    string Gender;
    string BloodGroup;
    string ContactNo;
    string Address;
public:
    Shopkeeper_Module() {}
    void SetShopkeeperID(string id);
    string GetShopkeeperID() const;
    void SetFirstName(string firstName);
    string GetFirstName() const;
    void SetLastName(string lastName);
    string GetLastName() const;
    void SetUsername(string username);
    string GetUsername() const;
    void SetEmail(string email);
    string GetEmail() const;
    void SetPassword(string password);
    string GetPassword() const;
    void SetRegistrationDate(string date);
    string GetRegistrationDate() const;
    void SetGender(string gender);
    string GetGender() const;
    void SetBloodGroup(string bloodGroup);
    string GetBloodGroup() const;
    void SetContactNo(string contactNo);
    string GetContactNo() const;
    void SetAddress(string address);
    string GetAddress() const;
    void RegisterShopkeeper();
    void DisplayShopkeeperDetails() const;
    bool ShopkeeperSignIn();
    void AddNewProduct();
    void EditProductDetails();
    void ViewProductsByShopkeeper();
};
class Customer_Module {
private:
    string CustomerID;
    string FirstName;
    string LastName;
    string Address;
    string ContactNo;
    string Username;
    string Email;
    string Password;
public:
    Customer_Module();
    void SetCustomerID(string id);
    string GetCustomerID() const;
    void SetFirstName(string firstName);
    string GetFirstName() const;
    void SetLastName(string lastName);
    string GetLastName() const;
    void SetAddress(string address);
    string GetAddress() const;
    void SetContactNo(string contactNo);
    string GetContactNo() const;
    void SetUsername(string username);
    string GetUsername() const;
    void SetEmail(string email);
    string GetEmail() const;
    void SetPassword(string password);
    string GetPassword() const;
    void RegisterCustomer();
    void DisplayCustomerDetails() const;
    bool CustomerSignIn();
    void DisplayProductList() const;
    void AddToCart(const string& customerId, const string& productName, int quantity);
    // Checkout function
    void Checkout(const string& customerId);
    void PurchaseProduct(string& customerId);
};
void welcome();
void welcome2();
void loading();





