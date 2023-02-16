#include <iostream>
#include <fstream>


class contact
{
private:
    char fName[50], lName[50], email[50];
    long long phone;

public:
    void createContact()
    {
        std::cout << "Enter first name: ";
        std::cin >> fName;

        std::cout << "Enter last name: ";
        std::cin >> lName;

        std::cout << "Enter email address: ";
        std::cin >> email;

        std::cout << "Enter phone number: ";
        std::cin >> phone;
    }

    void showContact()
    {
        std::cout << "Name: " << fName << " " << lName << "\n";
        std::cout << "Email: " << email << "\n";
        std::cout << "Phone: " << phone << "\n\n";
    }

    long long searchViaPhone()
    {
        long long phoneNum;
        std::cout << "Search via phone number: ";
        std::cin >> phoneNum;
        return phoneNum;
    }

    std::string searchViaName(std::string viaName)
    {
        std::string nameQuery;
        std::cout << "Search via " << viaName << ": ";
        std::cin >> nameQuery;
        return nameQuery;
    }

    int searchOptions()
    {
        int choice;
        std::cout << "-------- Search Options --------\n";
        std::cout << "*** [1] search via phone number\n";
        std::cout << "*** [2] search via first name\n";
        std::cout << "*** [3] search via last name\n";
        std::cout << "*** [4] search via email address\n";
        std::cout << "--------------------------------\n\n";
        std::cout << "How do you want to search? ";
        std::cin >> choice;
        std::cout << "\n\n";
        return choice;
    }

    bool doesFileExist()
    {
        std::ifstream checkFile;
        checkFile.open("contacts.dat");
        if (checkFile)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void displayNoFile()
    {
        char check;
        std::cout << "*** No Contacts yet ***\n";
        std::cout << "**** Create a contact? (y/n) : ";
        std::cin >> check;
        if (check == 'y')
        {
            writeToFile();
        }
    }

    void writeToFile()
    {
        char check;
        std::ofstream file;
        file.open("contacts.dat", std::ios::binary | std::ios::app);

        do
        {
            system("clear");
            std::cout << "\n--------------------------------------\n";
            std::cout << "-------- CREATE A NEW CONTACT --------";
            std::cout << "\n--------------------------------------\n\n";
            createContact();
            file.write(reinterpret_cast<char *>(this), sizeof(*this));
            std::cout << "\nDo you want to enter another contact? (y/n): ";
            std::cin >> check;
        } while (check == 'y');

        system("clear");
        std::cout << "\n\nContact(s) have been created.\n\n";
        file.close();
    }

    void showAllContacts()
    {
        if (doesFileExist())
        {
            std::ifstream file2;
            file2.open("contacts.dat", std::ios::binary);

            std::cout << "\n----------------------------------\n";
            std::cout << "-------------CONTACTS-------------";
            std::cout << "\n----------------------------------\n\n";

            while (!file2.eof())
            {
                if (file2.read(reinterpret_cast<char *>(this), sizeof(*this)))
                {
                    showContact();
                    std::cout << "**********************************\n\n";
                }
            }
            file2.close();
        }
        else
        {
            displayNoFile();
        }
    }

    void searchFile()
    {
        if (doesFileExist())
        {
            std::string nameQuery;
            long long phoneNum;

            std::ifstream file3;
            std::cout << "\n--------------------------------------\n";
            std::cout << "--------- SEARCH FOR CONTACT ---------";
            std::cout << "\n--------------------------------------\n\n";

            int searchChoice = searchOptions(); // Seach options

            file3.open("contacts.dat", std::ios::binary);

            while (!file3.eof())
            {
                if (file3.read(reinterpret_cast<char *>(this), sizeof(*this)))
                {
                    system("clear");
                    switch (searchChoice)
                    {
                    case 1:                          // PHONE
                        phoneNum = searchViaPhone(); // Phone Query
                        if (phoneNum == phone)
                        {
                            std::cout << "\n***** FOUND CONTACT *****\n\n";
                            showContact();
                            return;
                        }
                        break;

                    case 2:                                      // FIRST NAME
                        nameQuery = searchViaName("first name"); // First Name Query
                        if (nameQuery == fName)
                        {
                            std::cout << "\n***** FOUND CONTACT *****\n\n";
                            showContact();
                            return;
                        }
                        break;

                    case 3:                                     // LAST NAME
                        nameQuery = searchViaName("last name"); // Last Name Query
                        if (nameQuery == lName)
                        {
                            std::cout << "\n***** FOUND CONTACT *****\n\n";
                            showContact();
                            return;
                        }
                        break;

                    case 4:                                         // EMAIL
                        nameQuery = searchViaName("email address"); // Email Query
                        if (nameQuery == email)
                        {
                            std::cout << "\n***** FOUND CONTACT *****\n\n";
                            showContact();
                            return;
                        }
                        break;

                    default:
                        break;
                    }
                }
            }
            std::cout << "\n\n No Record Found\n\n";
            file3.close();
        }
        else
        {
            displayNoFile();
        }
    }

    void deleteContact()
    {
        if (doesFileExist())
        {
            std::string nameQuery;
            long long phoneNum;
            int flag = 0;
            std::ofstream file4;
            std::ifstream file5;

            file5.open("contacts.dat", std::ios::binary);
            file4.open("temp.dat", std::ios::binary);

            std::cout << "\n--------------------------------------\n";
            std::cout << "----------- DELETE CONTACT -----------";
            std::cout << "\n--------------------------------------\n\n";

            std::cout << "---- SEARCH FOR CONTACT TO DELETE ----\n\n";
            int searchChoice = searchOptions(); // Seach options

            while (!file5.eof())
            {
                if (file5.read(reinterpret_cast<char *>(this), sizeof(*this)))
                {
                    system("clear");
                    switch (searchChoice)
                    {
                    case 1:                          // PHONE
                        phoneNum = searchViaPhone(); // Phone Query
                        if (phone != phoneNum)
                        {
                            file4.write(reinterpret_cast<char *>(this), sizeof(*this));
                        }
                        else
                            flag = 1;
                        break;

                    case 2:                                      // FIRST NAME
                        nameQuery = searchViaName("first name"); // First Name Query
                        if (fName != nameQuery)
                        {
                            file4.write(reinterpret_cast<char *>(this), sizeof(*this));
                        }
                        else
                            flag = 1;
                        break;

                    case 3:                                     // LAST NAME
                        nameQuery = searchViaName("last name"); // Last Name Query
                        if (lName != nameQuery)
                        {
                            file4.write(reinterpret_cast<char *>(this), sizeof(*this));
                        }
                        else
                            flag = 1;
                        break;

                    case 4:                                         // EMAIL
                        nameQuery = searchViaName("email address"); // Email Query
                        if (email != nameQuery)
                        {
                            file4.write(reinterpret_cast<char *>(this), sizeof(*this));
                        }
                        else
                            flag = 1;
                        break;

                    default:
                        break;
                    }
                }
            }
            file5.close();
            file4.close();
            remove("contacts.dat");
            rename("temp.dat", "contacts.dat");

            flag == 1 ? std::cout << "\n\n\t Contact deleted.\n\n" : std::cout << "\n\n\tContact not found.\n\n";
        }
        else
        {
            displayNoFile();
        }
    }

    void editContact()
    {
        if (doesFileExist())
        {
            std::string nameQuery;
            long long phoneNum;
            std::fstream file6;

            std::cout << "\n--------------------------------------\n";
            std::cout << "------------ EDIT CONTACT ------------";
            std::cout << "\n--------------------------------------\n\n";

            std::cout << "---- SEARCH FOR CONTACT TO EDIT ----\n\n";
            int searchChoice = searchOptions(); // Seach options

            file6.open("contacts.dat", std::ios::binary | std::ios::out | std::ios::in);

            while (!file6.eof())
            {
                if (file6.read(reinterpret_cast<char *>(this), sizeof(*this)))
                {
                    system("clear");
                    switch (searchChoice)
                    {
                    case 1:                          // PHONE
                        phoneNum = searchViaPhone(); // Phone Query
                        if (phoneNum == phone)
                        {
                            std::cout << "\nEnter new record\n\n";
                            createContact();

                            int pos = -1 * sizeof(*this);
                            file6.seekp(pos, std::ios::cur);
                            file6.write(reinterpret_cast<char *>(this), sizeof(*this));
                            std::cout << "\n\n\tContact successfully updated.\n\n";
                            return;
                        }
                        break;

                    case 2:                                      // FIRST NAME
                        nameQuery = searchViaName("first name"); // First Name Query
                        if (nameQuery == fName)
                        {
                            std::cout << "\nEnter new record\n\n";
                            createContact();

                            int pos = -1 * sizeof(*this);
                            file6.seekp(pos, std::ios::cur);
                            file6.write(reinterpret_cast<char *>(this), sizeof(*this));
                            std::cout << "\n\n\tContact successfully updated.\n\n";
                            return;
                        }
                        break;

                    case 3:                                     // LAST NAME
                        nameQuery = searchViaName("last name"); // Last Name Query
                        if (nameQuery == lName)
                        {
                            std::cout << "\nEnter new record\n\n";
                            createContact();

                            int pos = -1 * sizeof(*this);
                            file6.seekp(pos, std::ios::cur);
                            file6.write(reinterpret_cast<char *>(this), sizeof(*this));
                            std::cout << "\n\n\tContact successfully updated.\n\n";
                            return;
                        }
                        break;

                    case 4:                                         // EMAIL
                        nameQuery = searchViaName("email address"); // Email Query
                        if (nameQuery == email)
                        {
                            std::cout << "\nEnter new record\n\n";
                            createContact();

                            int pos = -1 * sizeof(*this);
                            file6.seekp(pos, std::ios::cur);
                            file6.write(reinterpret_cast<char *>(this), sizeof(*this));
                            std::cout << "\n\n\tContact successfully updated.\n\n";
                            return;
                        }
                        break;

                    default:
                        break;
                    }
                }
            }
            std::cout << "\n\nNo Record Found\n\n";
            file6.close();
        }
        else
        {
            displayNoFile();
        }
    }
};

int main()
{
    system("close");
    system("Color 3F"); // Color XY, x=background, y=text

    std::cout << "\n\n\n\n\n*** Contact Management System ***\n";

    while (1)
    {
        contact c1;
        int choice;

        system("clear");

        std::cout << "*********************************\n";
        std::cout << "*** CONTACT MANAGEMENT SYSTEM ***\n";
        std::cout << "*********************************\n\n";
        std::cout << "Options:\n";
        std::cout << "********************************\n";
        std::cout << "*** [1] New Contact\n";
        std::cout << "*** [2] Show All Contacts\n";
        std::cout << "*** [3] Search Contacts\n";
        std::cout << "*** [4] Delete Contact\n";
        std::cout << "*** [5] Edit Contact\n";
        std::cout << "*** [0] Close CMS\n";
        std::cout << "********************************\n\n";
        std::cout << "What do you want to do? OPTION:";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            system("clear");
            c1.writeToFile();
            break;

        case 2:
            system("clear");
            c1.showAllContacts();
            break;

        case 3:
            system("clear");
            c1.searchFile();
            break;

        case 4:
            system("clear");
            c1.deleteContact();
            break;

        case 5:
            system("clear");
            c1.editContact();
            break;

        case 0:
            system("clear");
            std::cout << "\n\n\n\nThank You\n";
            exit(0);
            break;

        default:
            continue;
        }

        int opt;
        std::cout << "Enter [1] Main Menu or [2] Exit: ";
        std::cin >> opt;

        switch (opt)
        {
        case 2:
            system("clear");
            std::cout << "\n\n\n\nThank You\n";
            exit(0);
            break;

        default:
            continue;
        }
    }
}
