#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct PhoneNumber {     //PhoneNumber structure represents a single phone number
    string number;
    PhoneNumber* next;

    PhoneNumber(const string& number) : number(number), next(nullptr){} //constructor
};

struct Contact {         //Contact structure stores the name and a linked list of phone numbers for each contact
    string name;
    PhoneNumber* phoneNumbers;
    Contact* prev;
    Contact* next;

    Contact(const string& name) : name(name), phoneNumbers(nullptr), prev(nullptr), next(nullptr) {}

    void addPhoneNumber(const string& number) {
        PhoneNumber* newPhoneNumber = new PhoneNumber(number);
        if (phoneNumbers == nullptr) {
            phoneNumbers = newPhoneNumber;
        } else {
            PhoneNumber* current = phoneNumbers;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newPhoneNumber;
        }
    }

    void deletePhoneNumber(const string& number) {
        if (phoneNumbers == nullptr) {
            return;
        }
        
        if (phoneNumbers->number == number) {
            PhoneNumber* temp = phoneNumbers;
            phoneNumbers = phoneNumbers->next;
            delete temp;
            return;
        }

        PhoneNumber* current = phoneNumbers;
        while (current->next != nullptr) {
            if (current->next->number == number) {
                PhoneNumber* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    void deleteAllPhoneNumbers() {
        PhoneNumber* current = phoneNumbers;
        while (current != nullptr) {
            PhoneNumber* temp = current;
            current = current->next;
            delete temp;
        }
        phoneNumbers = nullptr;
    }
};

class PhoneDirectory {
private:
    Contact* head;
    Contact* tail;
    unordered_map<string, Contact*> contactMap;

public:
    PhoneDirectory() : head(nullptr), tail(nullptr) {}

    void addContact(const string& name, const string& number) { 
 /* It checks if the contact already exists in the contactMap. The contactMap is an unordered map that 
 stores the name as the key and the corresponding Contact object as the value.  */
       
        if (contactMap.find(name) == contactMap.end()) {     
            Contact* newContact = new Contact(name);        // a new Contact object is created with the given name 
                contactMap[name] = newContact ;            //and stored in the contactMap using name as the key.  
                                                                            
            if (head == nullptr) {
                head = newContact;
                tail = newContact;
            } else {
                tail->next = newContact;
                newContact->prev = tail;
                tail = newContact;
            }
        }
//After adding the contact to the contactMap and the linked list, the addPhoneNumber function of the corresponding 
//Contact object is called to add the phone number to the contact.
        contactMap[name]->addPhoneNumber(number);
        cout << "Contact added successfully." << endl;
    }

    void updateContact(const string& name, const string& oldNumber, const string& newNumber) {
        if (contactMap.find(name) == contactMap.end()) {
            cout << "Contact not found." << endl;
            return;
        }

        Contact* contact = contactMap[name];
        contact->deletePhoneNumber(oldNumber);
        contact->addPhoneNumber(newNumber);
        cout << "Contact updated successfully." << endl;
    }

    void deleteContact(const string& name) {
        if (contactMap.find(name) == contactMap.end()) {
            cout << "Contact not found." << endl;
            return;
        }

        Contact* contact = contactMap[name];

        if (contact == head && contact == tail) {
            head = nullptr;
            tail = nullptr;
        } else if (contact == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (contact == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            contact->prev->next = contact->next;
            contact->next->prev = contact->prev;
        }

        contact->deleteAllPhoneNumbers();
        contactMap.erase(name);
        delete contact;
        cout << "Contact deleted successfully." << endl;
    }

    void searchContact(const string& name) {
        if (contactMap.find(name) == contactMap.end()) {
            cout << "Contact not found." << endl;
            return;
        }

        Contact* contact = contactMap[name];
        cout << "Name: " << contact->name << endl;
        cout << "Phone Numbers: ";
        PhoneNumber* current = contact->phoneNumbers;
        while (current != nullptr) {
            cout << current->number << " ";
            current = current->next;
        }
        cout << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);

        if (file.is_open()) {                  //If the file was opened successfully, the function proceeds to save 
            Contact* current = head;           //the phone directory data to the file.
            while (current != nullptr) {
                file << current->name << endl;
                PhoneNumber* phoneNumber = current->phoneNumbers;
                while (phoneNumber != nullptr) {
                    file << phoneNumber->number << endl;
                    phoneNumber = phoneNumber->next;
                }
                file << endl;
                current = current->next;
            }
            file.close();
            cout << "Phone directory saved to file." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        clearDirectory();
/* If the file was opened successfully, the function proceeds to load the phone directory data from the file.
   The function uses a while loop and the getline function to read each line from the file.
   If the current line is not empty, it means that it contains either a contact name or a phone number.*/
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            string currentContactName;
            while (getline(file, line)) {
                if (!line.empty()) {
                    if (currentContactName.empty()) {
                        currentContactName = line;
                        addContact(currentContactName, line); 
                    } else {
                        addContact(currentContactName, line);  
                    }
                } else {
                    currentContactName.clear();
                }
            }
            file.close();
            cout << "Phone directory loaded from file." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    void clearDirectory() {
        Contact* current = head;
        while (current != nullptr) {
            Contact* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        contactMap.clear();
        cout << "Phone directory cleared." << endl;
    }
};

int main() {
    PhoneDirectory directory;

    directory.loadFromFile("phone_directory.txt");

    while (true) {
        cout << "Phone Directory" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Update Contact" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. Search Contact" << endl;
        cout << "5. Save to File" << endl;
        cout << "6. Clear Directory" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, number;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                cin >> number;
                directory.addContact(name, number);
                break;
            }
            case 2: {
                string name, oldNumber, newNumber;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter old phone number: ";
                cin >> oldNumber;
                cout << "Enter new phone number: ";
                cin >> newNumber;
                directory.updateContact(name, oldNumber, newNumber);
                break;
            }
            case 3: {
                string name;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                directory.deleteContact(name);
                break;
            }
            case 4: {
                string name;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                directory.searchContact(name);
                break;
            }
            case 5: {
                directory.saveToFile("phone_directory.txt");
                break;
            }
            case 6: {
                directory.clearDirectory();
                break;
            }
            case 7: {
                return 0;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
