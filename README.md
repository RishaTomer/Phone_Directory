# Phone_Directory
A Phone Directory project using doubly linked list, HapMap and File handling in C++

The program implements a phone directory using a doubly linked list and a hashmap in C++. 
It allows users to add contacts with multiple phone numbers, update existing contacts, delete contacts, search for contacts,
and save/load the phone directory to/from a file.
The PhoneDirectory class represents the phone directory and contains member variables such as head and tail pointers for the doubly linked list,
a contactMap hashmap for efficient lookup of contacts by name, and a filename to specify the file where the directory is stored.
Contacts are represented by the Contact class, which has a name and a linked list of phone numbers. The phone numbers are stored using the PhoneNumber 
class, which contains the number and pointers to the next and previous phone numbers in the linked list.
The program provides a menu-driven interface for users to interact with the phone directory. Users can add a contact with one or more phone numbers, 
update the phone number(s) of an existing contact, delete a contact, search for a contact and display their details, save the phone directory to a file, 
clear the phone directory, or exit the program.
The program ensures that the phone directory data is persisted by saving it to a file after each modification and loading it from the file when the program starts.

Overall, the program allows users to manage a phone directory efficiently, store contact information persistently, and perform various operations on contacts 
and their phone numbers.
