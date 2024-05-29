#include <iostream>
#include <limits>
using namespace std;

class Phone
{
private:
    int id;
    string name;
    string lname;
    long long phn_no;
    string email;
    string address;
    string category;
    bool edited;

public:
    int getId()
    {
        return id;
    }
    void setId(int id)
    {
        this->id = id;
    }
    string getName()
    {
        return name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    string getLname()
    {
        return lname;
    }
    void setLname(string lname)
    {
        this->lname = lname;
    }
    long long getPhoneNo()
    {
        return phn_no;
    }
    void setPhoneNo(long long phn_no)
    {
        this->phn_no = phn_no;
    }
    string getEmail()
    {
        return email;
    }
    void setEmail(string email)
    {
        this->email = email;
    }
    string getAddress()
    {
        return address;
    }
    void setAddress(string address)
    {
        this->address = address;
    }
    string getCategory()
    {
        return category;
    }
    void setCategory(string category)
    {
        this->category = category;
    }
    bool isEdited()
    {
        return edited;
    }
    void setEdited(bool edited)
    {
        this->edited = edited;
    }
};

class Node
{
private:
    Node *next;
    Node *prev;

public:
    Phone data;
    Node *getNext()
    {
        return next;
    }
    void setNext(Node *next)
    {
        this->next = next;
    }
    Node *getPrev()
    {
        return prev;
    }
    void setPrev(Node *prev)
    {
        this->prev = prev;
    }
    void setPhoneData(int id, string name, string lname, long long phn_no, string email, string address, string category)
    {
        this->data.setId(id);
        this->data.setName(name);
        this->data.setLname(lname);
        this->data.setPhoneNo(phn_no);
        this->data.setEmail(email);
        this->data.setAddress(address);
        this->data.setCategory(category);
        this->data.setEdited(false); // Initially, the contact is not edited
    }
    string getPhoneData()
    {
        string result = "Id: " + to_string(this->data.getId()) +
                        "\nName: " + this->data.getName() + " " + this->data.getLname() +
                        "\nPhone No: " + to_string(this->data.getPhoneNo()) +
                        "\nEmail: " + this->data.getEmail() +
                        "\nAddress: " + this->data.getAddress() +
                        "\nCategory: " + this->data.getCategory();
        if (this->data.isEdited())
        {
            result += "\n(This contact has been edited)";
        }
        return result;
    }
};

class List
{
    Node *head;
    Node *curr;
    int size;

   

public:
    List()
    {
        head = new Node();
        head->setNext(NULL);
        head->setPrev(NULL);
        size = 0;
        curr = head;
    }
    int length()
    {
        return size;
    }
    bool idExists(int id)
    {
        Node *temp = head->getNext();
        while (temp != NULL)
        {
            if (temp->data.getId() == id)
            {
                return true;
            }
            temp = temp->getNext();
        }
        return false;
    }
    bool phoneExists(long long phoneNo)
    {
        Node *temp = head->getNext();
        while (temp != NULL)
        {
            if (temp->data.getPhoneNo() == phoneNo)
            {
                return true;
            }
            temp = temp->getNext();
        }
        return false;
    }
    void addContact(int id, string name, string lname, long long phnNo, string address, string email, string category)
    {
        if (idExists(id))
        {
            cout << "ID already exists. Contact not added.\n";
            return;
        }
        if (phoneExists(phnNo))
        {
            cout << "Phone number already exists. Contact not added.\n";
            return;
        }
        Node *newNode = new Node();
        newNode->setPhoneData(id, name, lname, phnNo, email, address, category);
        newNode->setNext(curr->getNext());
        if (curr->getNext() != NULL)
        {
            curr->getNext()->setPrev(newNode);
        }
        newNode->setPrev(curr);
        curr->setNext(newNode);
        curr = newNode;
        size++;
        cout << "Contact Added Successfully";
        cout << "\n--------------------------\n";
    }
    void remove(int id)
    {
        cout << "Removing id " << id << endl;
        Node *temp = head->getNext();
        int found = 0;
        while (temp != NULL)
        {
            if (temp->data.getId() == id)
            {
                found = 1;
                break;
            }
            else
            {
                temp = temp->getNext();
            }
        }
        if (found == 1)
        {
            curr = temp;
            if (size != 0 && curr->getNext() != NULL)
            {
                curr->getPrev()->setNext(curr->getNext());
                curr->getNext()->setPrev(curr->getPrev());
                size--;
            }
            else if (size != 0 && curr->getNext() == NULL)
            {
                curr->getPrev()->setNext(NULL);
                size--;
            }
            cout << "Given ID " << id << " removed\n";
        }
        else
        {
            cout << "Given ID " << id << " not found\n";
        }
        curr = head->getNext() == NULL ? head : head->getNext();
    }
    void editContact(int id, string name, string lname, long long phnno, string email, string address, string category)
    {
        Node *temp = head->getNext();
        while (temp != nullptr && temp->data.getId() != id)
        {
            temp = temp->getNext();
        }
        if (temp != nullptr && temp->data.getId() == id)
        {
            if (phoneExists(phnno) && temp->data.getPhoneNo() != phnno)
            {
                cout << "Phone number already exists. Contact not edited.\n";
                return;
            }
            temp->data.setName(name);
            temp->data.setLname(lname);
            temp->data.setPhoneNo(phnno);
            temp->data.setEmail(email);
            temp->data.setAddress(address);
            temp->data.setCategory(category);
            temp->data.setEdited(true); // Mark the contact as edited

            cout << "Contact has been Edited Successfully\n";
        }
        else
        {
            cout << "Id not found\n";
        }
    }
     Node *mergeSortedLists(Node *a, Node *b)
    {
        if (!a)
            return b;
        if (!b)
            return a;

        if (a->data.getId() < b->data.getId())
        {
            a->setNext(mergeSortedLists(a->getNext(), b));
            a->getNext()->setPrev(a);
            a->setPrev(nullptr);
            return a;
        }
        else
        {
            b->setNext(mergeSortedLists(a, b->getNext()));
            b->getNext()->setPrev(b);
            b->setPrev(nullptr);
            return b;
        }
    }

    void merge(Node *source, Node **frontRef, Node **backRef)
    {
        Node *p;
        Node *q;
        q = source;
       p = source->getNext();

        while (p != nullptr)
        {
           p = p->getNext();
            if (p != nullptr)
            {
                q = q->getNext();
                p = p->getNext();
            }
        }

        *frontRef = source;
        *backRef = q->getNext();
       q->setNext(nullptr);
    }

    void mergeSortByID(Node **headRef)
    {
        Node *head = *headRef;
        Node *a;
        Node *b;

        if ((head == nullptr) || (head->getNext() == nullptr))
        {
            return;
        }
        merge(head, &a, &b);
        mergeSortByID(&a);
        mergeSortByID(&b);

        *headRef = mergeSortedLists(a, b);
    }
    void display()
    {
        if (size == 0)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            cout << "Contacts are: " << endl;
            cout << "\n-------------------------\n";
            Node *temp = head->getNext();
            while (temp != NULL)
            {
                cout << temp->getPhoneData() << "\n-----------------\n"
                     << endl;
                temp = temp->getNext();
            }
        }
    }
    void findContactById(int id)
    {
        Node *temp = head->getNext();
        bool found = false;
        while (temp != NULL)
        {
            if (temp->data.getId() == id)
            {
                found = true;
                cout << "Contact Found:\n";
                cout << temp->getPhoneData() << "\n-----------------\n";
            }
            temp = temp->getNext();
        }
        if (!found)
        {

            cout << "Contact with ID " << id << " not found.\n";
        }
    }

    void findContactByName(string name)
    {
        Node *temp = head->getNext();
        bool found = false;
        while (temp != NULL)
        {
            if (temp->data.getName() == name || temp->data.getLname() == name)
            {
                found = true;
                cout << "Contact Found:\n";
                cout << temp->getPhoneData() << "\n-----------------\n"
                     << endl;
            }
            temp = temp->getNext();
        }
        if (!found)
        {
            cout << "Contact with name " << name << " not found.\n";
        }
    }
    void findContactByNumber(long long phn_no)
    {
        Node *temp = head->getNext();
        bool found = false;
        while (temp != NULL)
        {
            if (temp->data.getPhoneNo() == phn_no)
            {
                found = true;
                cout << "Contact Found:\n";
                cout << temp->getPhoneData() << "\n-----------------\n"
                     << endl;
            }
            temp = temp->getNext();
        }
        if (!found)
        {
            cout << "Contact with phone number " << phn_no << " not found.\n";
        }
    }
    void findContactByCategory(string category)
    {
        Node *temp = head->getNext();
        bool found = false;
        while (temp != NULL)
        {
            if (temp->data.getCategory() == category)
            {
                found = true;
                cout << "Contact Found:\n";
                cout << temp->getPhoneData() << "\n-----------------\n"
                     << endl;
            }
            temp = temp->getNext();
        }
        if (!found)
        {
            cout << "Contact with category " << category << " not found.\n";
        }
    }
    void sortContactsById()
    {
        if (size > 1)
        {
            Node *n = head->getNext();
            mergeSortByID(&n);

            // Update head and curr pointers
            head->setNext(n);
            n->setPrev(head);
            Node *temp = n;
            while (temp->getNext() != nullptr)
            {
                temp = temp->getNext();
            }
            curr = temp;
        }
        cout << "Contacts sorted by ID.\n";
    }
    void print()
    {
        cout<<endl<<"__________Select one from given menu___________" << endl;
        cout << "1. Add a Contact." << endl;
        cout << "2. Edit Contact" << endl;
        cout << "3. Display Contacts" << endl;
        cout<< "4. Find Contact by ID" << endl;
        cout<< "5. Find Contact by Name" << endl;
        cout<< "6. Find Contact by Phone Number" << endl;
        cout<< "7. Find Contact by Category" << endl;
        cout<< "8. Remove Contact " << endl;
        cout << "9. Sort Contacts by ID" << endl; 
        cout<<"-------------------------"<<endl;
        cout << "Enter your choice:" << endl;
    }
};

int main()
{
    List l;
    while (true)
    {
        int choice;
        l.print();
        cin >> choice;
        if (choice == 1)
        {
            cout << "     -------Welcome-------- "<<endl;
            cout <<" Here you can Add your new Contact: "<< endl;
            int id;
            string name;
            string lname;
            long long phoneno;
            string address;
            string email;
            string category;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter First Name: ";
            cin >> name;
            cout << "Enter Last Name: ";
            cin >> lname;
            cout << "Enter Phone No: ";
            cin >> phoneno;
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Address (Without Spaces): ";
            cin >> address;
            cout << "Enter Category (Work/Home/Office/Other): ";
            cin >> category;
            l.addContact(id, name, lname, phoneno, address, email, category);
        }
        else if (choice == 2)
        {
            cout << "-------Welcome (Here you can edit your Contacts)----- " << endl;
            int id;
            cout << "Enter ID: ";
            cin >> id;
            string name;
            string lname;
            long long phoneno;
            string address;
            string email;
            string category;
            cout << "Enter the new Details for the given ID\n";
            cout << "Enter First Name: ";
            cin >> name;
            cout << "Enter Last Name: ";
            cin >> lname;
            cout << "Enter Phone No: ";
            cin >> phoneno;
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter Address (Without Spaces): ";
            cin >> address;
            cout << "Enter Category (Work/Home/Office/Other): ";
            cin >> category;
            l.editContact(id, name, lname, phoneno, email, address, category);
        }
        else if (choice == 3)
        {
            l.display();
        }
        else if (choice == 4)
        {
            int id;
            cout << "Enter the ID to find: ";
            cin >> id;
            l.findContactById(id);
        }
        else if (choice == 5)
        {
            string name;
            cout << "Enter the name to find: ";
            cin.ignore(); // Ignore newline character in buffer
            getline(cin, name);
            l.findContactByName(name);
        }
        else if (choice == 6)
        {
            long long phn_no;
            cout << "Enter the phone number to find: ";
            cin >> phn_no;
            l.findContactByNumber(phn_no);
        }
        else if (choice == 7)
        {
            string category;
            cout << "Enter the category to find: ";
            cin >> category;
            l.findContactByCategory(category);
        }
        else if (choice == 8)
        {
            int id;
            cout << "Enter id ";
            cin >> id;
            l.remove(id);
        }
        else if (choice == 9)
        { // Added sorting option
            l.sortContactsById();
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
