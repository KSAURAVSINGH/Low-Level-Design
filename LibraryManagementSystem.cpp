#include<bits/stdc++.h>
using namespace std;

int fetchLastGeneratedLibId(){
    return 123;
}

string generateLibID(){
    
    int lastLibID = fetchLastGeneratedLibId();
    string libID = "LIB" + to_string(lastLibID+1);
    return libID;
}

int fetchFinePerDayOnDue(){
    
    // fetch the data from database;
    return 5;
}

class Book{
    private:
        string name;
        string bookId;
        string category;
        int price;
        int quantity;
        int remQuantity;
    
    public:
        
        Book(string name, string category, int price, int quantity){
            this->name = name;
            this->category = category;
            this->price = price;
            this->quantity = quantity;
            
            if(this->category.size()==0)
            {
                this->category = "DefaultCategory";
            }
        }
        
        int getRemQuantityLeft(){
            
        }
        
        int getBookPrice(){
            return this->price;
        }
        
        string addQuantity(){
            
        }
        
        string subtractQuantity(){
            
        }
        
        string getNameofBook(){
            return this->name;
        }
        
};

class User{
    
    private: 
        string name;
        string address;
        string libId;
        int mobileNumber;
        string password;
        string role;
        bool isPasswordSet;
        
    public:
        unordered_map<Book*,pair<string,string>> booksIssued;
        
        User(string name, string address, int mobNum, string role)
        {
            this->name = name;
            this->address = address;
            this->mobileNumber = mobNum;
            this->role = role;
            this->isPasswordSet = false;
        }
        
        int getTotalAmtDue(){
            
        }
        
        string setPassword(string password){
            if(!isPasswordSet)
            {
                this->password = password;
                return "Password is set for the user";
            }
            else
            {
                return "Password is already set by the user. Please select forgot password incase.";
            }
        }
        
        string forgotPassword(string newPass, string oldPass)
        {
            if(password==oldPass)
            {
                password = newPass;
                return "Password changed successfully.";
            }
            else
            {
                return "Incorrect password to proceed for password reset.";
            }
        }
        
        string changeAddress(string ad){
            
        }
        
        string changeMobNumber(int mobNum){
            
        }
        
        string issueBook(Book* book, string issueDate, string returnDate){
            if(booksIssued.find(book) != booksIssued.end())
                return "Same copy of this book is already issued by the user.";
            
            booksIssued[book] = {issueDate, returnDate};
            return "Book has been issued";
        }
        
        string returnBook(Book* book){
            
            if(booksIssued.find(book) == booksIssued.end())
                return "Book is not in the list of issue for this user";
            
            booksIssued.erase(book);
            
        }
      
};


class CheckOut{
    private:
        vector<Book*> bookForIssue;
        User* user;
        
    public: 
        
        CheckOut(vector<Book*> bookList, User* user){
            this->bookForIssue = bookList;
            this->user = user;
        }
        
        int findTotalAmt()
        {
            int costForBookForIssue = 0;
            for(auto book: bookForIssue)
            {
                costForBookForIssue += book->getBookPrice();
            }
            
            costForBookForIssue += findDueAmt();
            
            return costForBookForIssue;
        }
        
        int findDueAmt(){
            
            int findPerDay = fetchFinePerDayOnDue();
            int costForBookAlreadyIssued = 0;
            
            for(auto detail: user->booksIssued)
            {
                // if(detail.second<currentDate)
                // {
                //     int diff = currentDate - detail.second;
                //     costForBookAlreadyIssued += (diff*findPerDay);
                // }
            }
            
            return costForBookAlreadyIssued;
            
        }
};

class Library{
    private:    
        vector<Book*> bookGallery;
        vector<User*> allUsers;
        
    public:
        
        string addBookToLibrary(Book* book){
            bookGallery.push_back(book);
            return "A new book has been added to the library";
        }
        
        string removeBookFromLibrary(Book* book)
        {
            // bookGallery.erase(book)
            
            return "Book has been removed from the library";
        }
        
        string addUser(User* user){
            allUsers.push_back(user);
            
            return "User has been added to library";
        }
        
        string removeUser(){
            return "User has been removed from library";   
        }
        
};


int main(){
    
    User* user1 = new User("Sam", "Delhi", 7870122112, "student");
    Book* sciBook = new Book("Science", "Computer", 500, 10);
    Book* mathBook = new Book("Math", "Computer", 100, 10);
    Book* engBook = new Book("English", "Computer", 200, 10);
    
    Library* library = new Library();
    
    cout<<library->addBookToLibrary(sciBook)<<endl;
    cout<<library->addBookToLibrary(mathBook)<<endl;
    cout<<library->addBookToLibrary(engBook)<<endl;
    
    cout<<library->addUser(user1)<<endl;
    
    vector<Book*> bookForIssue;
    bookForIssue.push_back(sciBook);
    bookForIssue.push_back(mathBook);
    bookForIssue.push_back(engBook);
    
    CheckOut* checkout = new CheckOut(bookForIssue, user1);
    int totalCost = checkout->findTotalAmt();
    cout<<"Total amt for the book issued by the user is "<<totalCost<<endl;
    
    // if payment is success
    for(auto book: bookForIssue)
    {   
        user1->issueBook(book, "today", "tomorrow");
    }
    
    for(auto book: user1->booksIssued)
    {
        cout<<book.first->getNameofBook()<<" is issued by the user"<<endl;
    }      
}
