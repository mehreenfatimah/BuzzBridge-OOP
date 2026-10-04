#include <algorithm>    
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <cstdlib> 
#include <limits>  

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;


const vector<string> businessCategories = {
    "Food",
    "Clothing",
    "Electronics",
    "Furniture",
    "Entertainment",
    "Beauty & Spa",
    "Education",
    "Health & Fitness",
    "Shopping Malls",
    "Automobiles"
};


struct Review {
    string customerName;
    string reviewText;
    int rating; // Rating from 1 to 5
};


string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


string chooseCategory(const vector<string>& categories) {
    while (true) {
        cout << "\n=== Select a Business Category ===\n";
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << i + 1 << ". " << categories[i] << "\n";
        }
        cout << "Enter the number corresponding to your category: ";
        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > (int)categories.size()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid selection. Please try again.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return categories[choice - 1];
        }
    }
}


class Profile {
protected:
    string name;
    string location;
    string contactInfo;

public:
    Profile(string n, string loc, string contact)
        : name(n), location(loc), contactInfo(contact) {}

    virtual void displayProfile() const = 0;

  
    string getName() const { return name; }
    string getLocation() const { return location; }
    string getContactInfo() const { return contactInfo; }
};


class Business : public Profile {
private:
    string businessType;
    vector<string> products;
    vector<string> promotions;
    vector<Review> feedback;

    
    int profileViews = 0;
    int promotionClicks = 0;
    int storeVisits = 0;

   
    string username;
    string password;

public:
    Business(string n, string loc, string contact, string type, string user, string pass)
        : Profile(n, loc, contact), businessType(type), username(user), password(pass) {}

   
    Business() : Profile("", "", ""), businessType(""), username(""), password("") {}

    void addProduct(string product) { products.push_back(product); }
    void addPromotion(string promotion) { promotions.push_back(promotion); }
    void addFeedback(string customerName, string reviewText, int rating) {
        Review newReview = { customerName, reviewText, rating };
        feedback.push_back(newReview);
    }

   
    const vector<Review>& getFeedback() const {
        return feedback;
    }

    string getBusinessType() const { return businessType; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }

    const vector<string>& getPromotions() const { return promotions; } 
    const vector<string>& getProducts() const { return products; }    

   
    void incrementProfileViews() { profileViews++; }
    void incrementPromotionClicks() { promotionClicks++; }
    void incrementStoreVisits() { storeVisits++; }

    
    double getAverageRating() const {
        if (feedback.empty()) return 0.0;
        int total = 0;
        for (const auto& rev : feedback)
            total += rev.rating;
        return static_cast<double>(total) / feedback.size();
    }

    void displayProfile() const override {
        cout << "\n=== Business Profile ===\n";
        cout << "Business Name: " << name
             << "\nType: " << businessType
             << "\nLocation: " << location
             << "\nContact Number: " << contactInfo << "\n";

        
        cout << "\nProducts:\n";
        if (products.empty()) {
            cout << "  No products available.\n";
        } else {
            for (const auto& product : products)
                cout << "- " << product << endl;
        }

        
        cout << "\nPromotions:\n";
        if (promotions.empty()) {
            cout << "  No promotions available.\n";
        } else {
            for (const auto& promo : promotions)
                cout << "- " << promo << endl;
        }

       
        cout << "\nFeedback:\n";
        if (feedback.empty()) {
            cout << "  No feedback available.\n";
        } else {
            for (const auto& rev : feedback) {
                cout << rev.customerName << " (" << rev.rating << "/5): " << rev.reviewText << endl;
            }
            cout << "\nAverage Rating: " << getAverageRating() << "/5\n";
        }
    }

    void saveToFile(ofstream& file) const {
        file << username << '\n'
             << password << '\n'
             << name << '\n'
             << location << '\n'
             << contactInfo << '\n'
             << businessType << '\n'
             << products.size() << '\n';
        for (const auto& product : products)
            file << product << '\n';
        file << promotions.size() << '\n';
        for (const auto& promo : promotions)
            file << promo << '\n';
        // Feedback
        file << feedback.size() << '\n';
        for (const auto& rev : feedback) {
            file << rev.customerName << '\n'
                 << rev.reviewText << '\n'
                 << rev.rating << '\n';
        }
        // Analytics
        file << profileViews << '\n' << promotionClicks << '\n' << storeVisits << '\n';
    }

    void loadFromFile(ifstream& file) {
        getline(file, username);
        getline(file, password);
        getline(file, name);
        getline(file, location);
        getline(file, contactInfo);
        getline(file, businessType);
        size_t productCount;
        file >> productCount;
        file.ignore(); 
        products.clear();
        for (size_t i = 0; i < productCount; ++i) {
            string product;
            getline(file, product);
            products.push_back(product);
        }
        size_t promoCount;
        file >> promoCount;
        file.ignore(); 
        promotions.clear();
        for (size_t i = 0; i < promoCount; ++i) {
            string promo;
            getline(file, promo);
            promotions.push_back(promo);
        }
        // Feedback
        size_t feedbackCount;
        file >> feedbackCount;
        file.ignore(); 
        feedback.clear();
        for (size_t i = 0; i < feedbackCount; ++i) {
            Review rev;
            getline(file, rev.customerName);
            getline(file, rev.reviewText);
            file >> rev.rating;
            file.ignore(); 
            feedback.push_back(rev);
        }
      
        file >> profileViews >> promotionClicks >> storeVisits;
        file.ignore(); 
    }

  
    void viewAnalytics() const {
        cout << "\n=== Analytics for " << name << " ===\n";
        cout << "Profile Views: " << profileViews << "\n";
        cout << "Promotion Clicks: " << promotionClicks << "\n";
        cout << "Store Visits: " << storeVisits << "\n";
        cout << "Average Rating: " << getAverageRating() << "/5\n";
        cout << "Total Reviews: " << feedback.size() << "\n";
    }

   
    void displayAnalytics() const {
        cout << "\nAccessing analytics...\n";
        viewAnalytics();
    }

    // Function to verify password
    bool verifyPassword(const string& pass) const {
        return password == pass;
    }

  
    void editProduct() {
        if (products.empty()) {
            cout << "No products to edit.\n";
            return;
        }
        cout << "\n=== Edit Product ===\n";
        for (size_t i = 0; i < products.size(); ++i)
            cout << i + 1 << ". " << products[i] << "\n";
        cout << "Enter the number of the product to edit (0 to cancel): ";
        int choice;
        cin >> choice;
        if (choice == 0) return;
        if (choice < 1 || choice >(int)products.size()) {
            cout << "Invalid choice.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter new product name: ";
        string newProduct;
        getline(cin, newProduct);
        products[choice - 1] = newProduct;
        cout << "Product updated successfully.\n";
    }

    void deleteProduct() {
        if (products.empty()) {
            cout << "No products to delete.\n";
            return;
        }
        cout << "\n=== Delete Product ===\n";
        for (size_t i = 0; i < products.size(); ++i)
            cout << i + 1 << ". " << products[i] << "\n";
        cout << "Enter the number of the product to delete (0 to cancel): ";
        int choice;
        cin >> choice;
        if (choice == 0) return;
        if (choice < 1 || choice >(int)products.size()) {
            cout << "Invalid choice.\n";
            return;
        }
        products.erase(products.begin() + choice - 1);
        cout << "Product deleted successfully.\n";
    }

    
    void editPromotion() {
        if (promotions.empty()) {
            cout << "No promotions to edit.\n";
            return;
        }
        cout << "\n=== Edit Promotion ===\n";
        for (size_t i = 0; i < promotions.size(); ++i)
            cout << i + 1 << ". " << promotions[i] << "\n";
        cout << "Enter the number of the promotion to edit (0 to cancel): ";
        int choice;
        cin >> choice;
        if (choice == 0) return;
        if (choice < 1 || choice >(int)promotions.size()) {
            cout << "Invalid choice.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter new promotion details: ";
        string newPromo;
        getline(cin, newPromo);
        promotions[choice - 1] = newPromo;
        cout << "Promotion updated successfully.\n";
    }

    void deletePromotion() {
        if (promotions.empty()) {
            cout << "No promotions to delete.\n";
            return;
        }
        cout << "\n=== Delete Promotion ===\n";
        for (size_t i = 0; i < promotions.size(); ++i)
            cout << i + 1 << ". " << promotions[i] << "\n";
        cout << "Enter the number of the promotion to delete (0 to cancel): ";
        int choice;
        cin >> choice;
        if (choice == 0) return;
        if (choice < 1 || choice >(int)promotions.size()) {
            cout << "Invalid choice.\n";
            return;
        }
        promotions.erase(promotions.begin() + choice - 1);
        cout << "Promotion deleted successfully.\n";
    }
};


void displayWelcome() {
 
    string reset = "\033[0m";       
    string red = "\033[1;31m";      
    string green = "\033[1;32m";   
    string blue = "\033[1;34m";     
    string yellow = "\033[1;33m";   

    cout << "\n";
    cout << "==============================================================================================================\n";
    cout << red << "===================================  WELCOME to BUZZBRIDGE  =======================================" << reset << "\n";
    cout << red << "                        <<--- Bridging Businesses & Communities --->  " << reset << "\n";
    cout << yellow  << "                                Discover | Connect | Prosper  " << reset << "\n";
    cout << "==============================================================================================================\n";
    cout << "\n";
    cout << blue << ">>>  Connect with thriving businesses, explore their services, and unlock amazing deals!  <<<" << reset << "\n";
    cout << "\n";
    cout << blue << ">>>>>>  Businesses, join us to expand your reach and grow your customer base  <<<<<<\n" << reset;
    cout << "\n";
    cout << "*********                                                       **********\n";
    cout << green << "                                 >>> Let's Make it Happen :) <<<" << reset << "\n";
    cout << "\n";
    cout << "**************************************\n";
}

void clearScreen() {
    system(CLEAR);
}


void loadBusinesses(map<string, shared_ptr<Business>>& businesses, const string& filename = "businesses.txt") {
    ifstream file(filename);
    if (file.is_open()) {
        while (file.peek() != EOF) {
            auto business = make_shared<Business>();
            business->loadFromFile(file);
            if (!business->getUsername().empty()) {
                businesses[business->getUsername()] = business;
            }
        }
        file.close();
    }
}


void saveBusinesses(const map<string, shared_ptr<Business>>& businesses, const string& filename = "businesses.txt") {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : businesses)
            pair.second->saveToFile(file);
        file.close();
    }
}


bool registerBusiness(map<string, shared_ptr<Business>>& businesses) {
    string username, password, name, location, contact, type;

    cout <<"\n=== Register a New Business ===\n";
    cout << "Enter Username: ";
    cin >> username;


    if (businesses.find(username) != businesses.end()) {
        cout << "Username already exists. Please choose a different username.\n";
        return false;
    }

    cout << "Enter Password: ";
    cin >> password;


    string selectedCategory = chooseCategory(businessCategories);

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    cout << "Enter Business Name: ";
    getline(cin, name);
    cout << "Enter Location: ";
    getline(cin, location);
    cout << "Enter Contact Info: ";
    getline(cin, contact);

    auto business = make_shared<Business>(name, location, contact, selectedCategory, username, password);
    businesses[username] = business;

    cout << "Business registered successfully!\n";
    return true;
}


shared_ptr<Business> loginBusiness(map<string, shared_ptr<Business>>& businesses) {
    string username, password;
    cout <<"\n=== Business Login ===\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    auto it = businesses.find(username);
    if (it != businesses.end()) {
        if (it->second->verifyPassword(password)) {
            cout << "Login successful! Welcome, " << it->second->getName() << "!\n";
            return it->second;
        } else {
            cout << "Incorrect password.\n";
            return nullptr;
        }
    } else {
        cout << "Username not found.\n";
        return nullptr;
    }
}


void businessMenu(shared_ptr<Business> business) {
    while (true) {
        clearScreen();
        cout <<"\n=== Business Dashboard ===\n";
        cout << "Logged in as: " << business->getName() << "\n\n";
        cout << "1. Add a Product & Price \n"
             << "2. Add a Promotion\n"
             << "3. View Profile\n"
             << "4. View Promotions\n"
             << "5. View Analytics\n"
             << "6. Edit a Product\n"
             << "7. Delete a Product\n"
             << "8. Edit a Promotion\n"
             << "9. Delete a Promotion\n"
             << "10. Logout\n"
             << "Enter your choice: ";
        int choice;
        cin >> choice;

        clearScreen();

        switch (choice) {
            case 1: {
                string product;
                cout << "Enter Product Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, product);
                business->addProduct(product);
                cout << "Product added successfully.\n";
                break;
            }
            case 2: {
                string promo;
                cout << "Enter Promotion Details: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, promo);
                business->addPromotion(promo);
                cout << "Promotion added successfully.\n";
                break;
            }
            case 3: {
                business->displayProfile();
                break;
            }
            case 4: {
                cout <<"\n=== Promotions ===\n";
                const vector<string>& promos = business->getPromotions(); // Use getter
                if (promos.empty()) {
                    cout << "No promotions available.\n";
                } else {
                    for (const auto& promo : promos)
                        cout << "- " << promo << endl;
                }
                break;
            }
            case 5: {
                business->displayAnalytics();
                break;
            }
            case 6: {
                business->editProduct();
                break;
            }
            case 7: {
                business->deleteProduct();
                break;
            }
            case 8: {
                business->editPromotion();
                break;
            }
            case 9: {
                business->deletePromotion();
                break;
            }
            case 10:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}


void businessFlow(map<string, shared_ptr<Business>>& businesses) {
    while (true) {
        clearScreen();
        cout << "\n=== Business Services ===\n";
        cout << "1. Register a New Business\n"
             << "2. Login\n"
             << "3. Back to Main Menu\n"
             << "Enter your choice: ";
        int choice;
        cin >> choice;

        clearScreen();

        switch (choice) {
            case 1:
                if (registerBusiness(businesses)) {
                    saveBusinesses(businesses);
                }
                break;
            case 2: {
                auto business = loginBusiness(businesses);
                if (business != nullptr) {
                    businessMenu(business);
                    saveBusinesses(businesses);
                }
                break;
            }
            case 3:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}


void customerFlow(map<string, shared_ptr<Business>>& businesses) {
    while (true) {
        clearScreen();
        cout << "\n=== Customer Services ===\n";
        cout << "Which service are you looking for? Select from the following categories:\n\n";

        // Display categories
        for (size_t i = 0; i < businessCategories.size(); ++i)
            cout << i + 1 << ". " << businessCategories[i] << endl;

        cout << "\nEnter the number corresponding to your choice (0 to go back): ";
        int categoryChoice;
        cin >> categoryChoice;

        if (categoryChoice == 0) {
            return;
        }

        if (categoryChoice < 1 || categoryChoice > (int)businessCategories.size()) {
            cout << "Invalid selection. Try again.\n";
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            continue;
        }

     
        string location;
        cout << "Enter your preferred location: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, location);

        
        clearScreen();
        cout << "\n=== Businesses in the " << businessCategories[categoryChoice - 1]
             << " category in " << location << " ===\n\n";
        bool found = false;
        int index = 1;
        vector<shared_ptr<Business>> matchedBusinesses;
        
        for (const auto& pair : businesses) {
            auto business = pair.second;
           
            if (toLowerCase(business->getBusinessType()) == toLowerCase(businessCategories[categoryChoice - 1]) &&
                toLowerCase(business->getLocation()) == toLowerCase(location))
            {
                found = true;
                matchedBusinesses.push_back(business);

               
                cout << index << ". " << business->getName()
                     << " (Contact: " << business->getContactInfo() << ") "
                     << " - Average Rating: " << business->getAverageRating() << "/5\n";

                
                const auto& products = business->getProducts();
                if (products.empty()) {
                    cout << "   Products: No products available.\n";
                } else {
                    cout << "   Products:\n";
                    for (const auto &prod : products) {
                        cout << "     - " << prod << "\n";
                    }
                }

            
                const auto& promos = business->getPromotions();
                if (promos.empty()) {
                    cout << "   Promotions: No promotions available.\n";
                } else {
                    cout << "   Promotions:\n";
                    for (const auto &promo : promos) {
                        cout << "     - " << promo << "\n";
                    }
                }

                {
                    cout << "Feedback:\n";
                    const auto& feedbackList = business->getFeedback();
                    if (feedbackList.empty()) {
                        cout << "     No feedback available.\n";
                    } else {
                        for (const auto& rev : feedbackList) {
                            cout << "     " << rev.customerName
                                 << " (" << rev.rating << "/5): "
                                 << rev.reviewText << "\n";
                        }
                    }
                }
                cout << "\n";
                index++;
            }
        }

        if (!found) {
            cout << "No businesses found in your preferred location for the selected category.\n";
        }

        
        if (found) {
            cout << "\nWould you like to add a review for any business? (y/n): ";
            char addReview;
            cin >> addReview;

            if (addReview == 'y' || addReview == 'Y') {
                cout << "Enter the number of the business you'd like to review: ";
                int businessIndex;
                cin >> businessIndex;
                if (businessIndex > 0 && businessIndex <= (int)matchedBusinesses.size()) {
                    string customerName, reviewText;
                    int rating;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter your name: ";
                    getline(cin, customerName);
                    cout << "Enter your review: ";
                    getline(cin, reviewText);
                    while (true) {
                        cout << "Enter your rating (1-5): ";
                        cin >> rating;
                        if (cin.fail() || rating < 1 || rating > 5) {
                            cin.clear(); // Clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << "Invalid rating. Please enter a number between 1 and 5.\n";
                        } else {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            break;
                        }
                    }
                    matchedBusinesses[businessIndex - 1]->addFeedback(customerName, reviewText, rating);
                    cout << "Review added successfully.\n";
                } else {
                    cout << "Invalid business number.\n";
                }
            }
        }

        cout << "\n1. Continue browsing\n2. Exit to Main Menu\nEnter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 2) return;
    }
}

int main() {
    map<string, shared_ptr<Business>> businesses;

   
    loadBusinesses(businesses);

    while (true) {
        clearScreen();
        displayWelcome();
        cout << "\n                                           === Main Menu ===                                                            \n";
        cout << "\n";
        cout << "1. Business Services\n"
             << "2. Customer Services\n"
             << "3. Exit\n";
        cout << "\n";
        cout<< "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                businessFlow(businesses);
                break;
            case 2:
                customerFlow(businesses);
                break;
            case 3:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
 
                cin.get();
                break;
        }
    }

    return 0;
}