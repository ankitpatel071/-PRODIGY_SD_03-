#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to hold contact information
struct Contact {
    string name;
    string phone;
    string email;
};

// Function to display the menu
void showMenu() {
    cout << "\n1. Add Contact" << endl;
    cout << "2. View Contacts" << endl;
    cout << "3. Edit Contact" << endl;
    cout << "4. Delete Contact" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

// Function to load contacts from the file
void loadContacts(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error loading contacts from file.\n";
        return;
    }

    Contact contact;
    while (file >> contact.name >> contact.phone >> contact.email) {
        contacts.push_back(contact);
    }

    file.close();
}

// Function to save contacts to the file
void saveContacts(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename, ios::trunc); // Open in trunc mode to overwrite file
    if (!file.is_open()) {
        cout << "Error saving contacts to file.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << " " << contact.phone << " " << contact.email << "\n";
    }

    file.close();
}

// Function to add a new contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter Name: ";
    cin >> newContact.name;
    cout << "Enter Phone: ";
    cin >> newContact.phone;
    cout << "Enter Email: ";
    cin >> newContact.email;

    contacts.push_back(newContact);
    cout << "Contact added successfully.\n";
}

// Function to display all contacts
void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". " << contacts[i].name << " - " << contacts[i].phone << " - " << contacts[i].email << endl;
    }
}

// Function to edit a contact
void editContact(vector<Contact>& contacts) {
    int index;
    viewContacts(contacts);
    
    cout << "Enter the contact number to edit: ";
    cin >> index;

    if (index <= 0 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    Contact& contactToEdit = contacts[index - 1];
    cout << "Editing contact: " << contactToEdit.name << endl;

    cout << "Enter new Name (current: " << contactToEdit.name << "): ";
    cin >> contactToEdit.name;
    cout << "Enter new Phone (current: " << contactToEdit.phone << "): ";
    cin >> contactToEdit.phone;
    cout << "Enter new Email (current: " << contactToEdit.email << "): ";
    cin >> contactToEdit.email;

    cout << "Contact updated successfully.\n";
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    int index;
    viewContacts(contacts);
    
    cout << "Enter the contact number to delete: ";
    cin >> index;

    if (index <= 0 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully.\n";
}

// Main function
int main() {
    vector<Contact> contacts;
    const string filename = "contacts.txt";

    // Load contacts from the file at the start
    loadContacts(contacts, filename);

    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                cout << "Exiting program.\n";
                saveContacts(contacts, filename); // Save contacts before exit
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }

    } while (choice != 5);

    return 0;
}
