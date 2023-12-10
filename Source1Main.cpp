#include "Source1.h"
int main() {
    system("color 8E");
    welcome();
    system("color 8B");
    welcome2();
    system("color 8E");
    welcome2();
    system("color 8B");
    welcome2();
    system("color 8E");
    welcome2();
    system("color 8B");
    welcome2();
    loading();

    Administrator_Module admin;
    if (admin.AdminSignIn()) {
        // Administrator signed in successfully
        int adminChoice;
        do {
            // Display administrator menu and get choice
            // (add Sleep if needed)
            cout << "========== ADMINISTRATOR MODULE ==========" << endl;
            cout << "1. Add New Shopkeeper" << endl;
            cout << "2. Add New Customer" << endl;
            cout << "3. Add New Product" << endl;
            cout << "4. Edit Shopkeeper Details" << endl;
            cout << "5. Edit Customer Details" << endl;
            cout << "6. Edit Product Details" << endl;
            cout << "7. Delete Shopkeeper Details" << endl;
            cout << "8. Delete Customer Details" << endl;
            cout << "9. Delete Product Details" << endl;
            cout << "10. Exit" << endl;
            cout << "Enter your choice: ";

            // Get and process administrator choice
            bool adminAgain = true;
            while (adminAgain) {
                try {
                    cin >> adminChoice;

                    if (adminChoice < 1 || adminChoice > 10)
                        throw "Enter between 1-10: ";
                    if (!cin)
                        throw "Enter a number: ";

                    adminAgain = false;
                }
                catch (const char* error) {
                    cin.clear();
                    cin.ignore();
                    cout << error;
                }
            }

            // Process administrator choice
            switch (adminChoice) {
            case 1:
                admin.AddNewShopkeeper();
                break;
            case 2:
                admin.AddNewCustomer();
                break;
            case 3:
                admin.AddNewProduct();
                break;
            case 4:
                admin.EditShopkeeperDetails();
                break;
            case 5:
                admin.EditCustomerDetails();
                break;
            case 6:
                admin.editProductDetails();
                break;
            case 7:
                admin.DeleteShopkeeper();
                break;
            case 8:
                admin.DeleteCustomer();
                break;
            case 9:
                admin.DeleteProduct();
                break;
            case 10:
                Sleep(400);
                cout << "Exiting the program..." << endl;
                break;
            default:
                Sleep(400);
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (adminChoice != 10);
    }
    else {
        // Administrator sign-in failed
        cout << "Admin failed to sign in!" << endl;

        // Check if Shopkeeper sign-in is successful
        Shopkeeper_Module shopkeeper;
        if (shopkeeper.ShopkeeperSignIn()) {
            int shopkeeperChoice;
            do {
                // Display shopkeeper menu and get choice
                cout << "========== SHOPKEEPER MODULE ==========" << endl;
                cout << "1. Register a new shopkeeper " << endl;
                cout << "2. Display shopkeeper details " << endl;
                cout << "3. Add New Product by shopkeeper " << endl;
                cout << "4. Edit Product Details By Shopkeeper " << endl;
                cout << "5. View Product Details By Shopkeeper " << endl;
                cout << "6. Exit " << endl;
                cout << "Enter your choice: ";

                // Get and process shopkeeper choice
                bool shopkeeperAgain = true;
                while (shopkeeperAgain) {
                    try {
                        cin >> shopkeeperChoice;

                        if (shopkeeperChoice < 1 || shopkeeperChoice > 6)
                            throw "Enter between 1-6: ";
                        if (!cin)
                            throw "Enter a number: ";

                        shopkeeperAgain = false;
                    }
                    catch (const char* error) {
                        cin.clear();
                        cin.ignore();
                        cout << error << endl;
                    }
                }

                // Process shopkeeper choice
                switch (shopkeeperChoice) {
                case 1:
                    shopkeeper.RegisterShopkeeper();
                    break;
                case 2:
                    shopkeeper.DisplayShopkeeperDetails();
                    break;
                case 3:
                    shopkeeper.AddNewProduct();
                    break;
                case 4:
                    shopkeeper.EditProductDetails();
                    break;
                case 5:
                    shopkeeper.ViewProductsByShopkeeper();
                    break;
                case 6:
                    cout << "Exiting the program..........!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }

                cout << endl;

            } while (shopkeeperChoice != 6);
        }
        else {
            // Shopkeeper sign-in failed
            cout << "Shopkeeper failed to sign in!" << endl;

            // Proceed to Customer Module
            Customer_Module customer;
            if (customer.CustomerSignIn()) {
                int customerChoice;
                string customerId;
                bool exitProgram = false;
                do {
                    // Display customer menu and get choice
                    cout << "+++++ CUSTOMER MODULE +++++" << endl;
                    cout << "1. Register Customer" << endl;
                    cout << "2. Display Customer Details" << endl;
                    cout << "3. Display Product List" << endl;
                    cout << "4. Purchase Product" << endl;
                    cout << "5. CheckOut" << endl;
                    cout << "6. Exit" << endl;
                    cout << "Enter your choice: ";

                    // Get and process customer choice
                    bool customerAgain = true;
                    while (customerAgain) {
                        try {
                            cin >> customerChoice;

                            if (customerChoice < 1 || customerChoice > 6)
                                throw "Enter between 1-6: ";
                            if (!cin)
                                throw "Enter a number: ";

                            customerAgain = false;
                        }
                        catch (const char* error) {
                            cin.clear();
                            cin.ignore();
                            cout << error << endl;
                        }
                    }

                    // Process customer choice
                    switch (customerChoice) {
                    case 1:
                        customer.RegisterCustomer();
                        break;
                    case 2:
                        customer.DisplayCustomerDetails();
                        break;
                    case 3:
                        customer.DisplayProductList();
                        break;
                    case 4:
                        customer.PurchaseProduct(customerId);
                        break;
                    case 5:
                    {  
                        customer.Checkout(customerId);
                        break;
                    }
                    case 6:
                        exitProgram = true;
                        cout << "Exiting the program..........." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        cout << endl;
                    }
                } while (customerChoice != 6);

                if (!exitProgram) {
                    system("pause");
                }
            }
            else {
                // Customer sign-in failed
                cout << "Customer failed to sign in!" << endl;
                // The program will end here
            }
        }
        }
    return 0;
}
