#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void ShowMainMenue();
void ShowTransactionsMenue();
void ShowManagrUserMenue();
void ClearSkrean();
void LoginScreen();
void GoBackToMainMenue();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;

};

struct stUsers
{
    string Username;
    string Password;
    int Permissions;
    bool MarkForDeletUserByUsername = false;
};

stUsers GlobaleUser;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eManagrUser = 7, eLogout = 8 };

enum enManagrUserMenue { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eShowMainMenueSkrean = 6 };

enum enMainMenuPermissions { eeListClients = 1, eeAddNewClient = 2, eeDeleteClient = 4, eeUpdateClient = 8, eeFindClient = 16, eeShowTransactionsMenue = 32, eeManagrUser = 64 };

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

string ConvertRecordToLine(stUsers User, string Seperator = "#//#")
{

    string stUsersRecord = "";

    stUsersRecord += User.Username + Seperator;
    stUsersRecord += User.Password + Seperator;
    stUsersRecord += to_string(User.Permissions);

    return stUsersRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        system("color 4F");
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

stUsers ConvertLinetoRecordUsers(string line)
{
    stUsers Users;
    vector <string> vUsers = SplitString(line, "#//#");

    Users.Username = vUsers[0];
    Users.Password = vUsers[1];
    Users.Permissions = stoi(vUsers[2]);

    return Users;
}

vector <stUsers> LoadUsersDataFromFile(string FileName)
{

    vector <stUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUsers Users;

        while (getline(MyFile, Line))
        {

            Users = ConvertLinetoRecordUsers(Line);

            vUsers.push_back(Users);
        }

        MyFile.close();

    }

    return vUsers;

}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void MassgeDontAcses()
{
    cout << endl << "-------------------------------" << endl;
    cout << "You Dont Have Acses To Enratr Hear" << endl;
    cout << "Go To Your Coach To Talk With Him " << endl;
    cout << endl << "-------------------------------" << endl;
}

bool HeHaveAccessToEntarHear(enMainMenuPermissions Permissons)
{
    if (GlobaleUser.Permissions == -1)
        return true;
    else if ((GlobaleUser.Permissions & Permissons) == Permissons)
        return true;
    else
        return false;
}

void ShowAllClientsScreen()
{

    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeListClients))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    system("color 2F");

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void PrintUsersRecordBalanceLine(stUsers vUsers)
{
    cout << "| " << setw(15) << left << vUsers.Username;
    cout << "| " << setw(40) << left << vUsers.Password;
    cout << "| " << setw(12) << left << vUsers.Permissions;
}

void ShowUsersList()
{
    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\tUsers List (" << vUsers.size() << ") User(s) ." << endl << endl;
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(40) << "Pasword ";
    cout << "| " << left << setw(12) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
    {
        system("color 4F");
        cout << "\t\t\t\tNo Users Available In the System!";
    }
    else
    {
        for (stUsers Users : vUsers)
        {

            PrintUsersRecordBalanceLine(Users);

            cout << endl;
        }

        system("color 2F");

    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
    {
        system("color 4F");
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else

    {

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

    system("color 2F");
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "--------------------------------------";
    cout << "\nAccout      Number : " << Client.AccountNumber;
    cout << "\nPin       Code     : " << Client.PinCode;
    cout << "\nName               : " << Client.Name;
    cout << "\nPhone              : " << Client.Phone;
    cout << "\nAccount   Balance  : " << Client.AccountBalance;
    cout << "\n--------------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

vector <stUsers> SaveUsersDataToFile(string FileName, vector <stUsers> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open())
    {

        for (stUsers& user : vUsers)
        {

            if (user.MarkForDeletUserByUsername == false)
            {

                DataLine = ConvertRecordToLine(user);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vUsers;

}

bool MarkForDeletUserByUsername(stUsers User, vector <stUsers>& vUsers)
{
    for (stUsers& user : vUsers)
    {

        if (user.Username == User.Username)
        {
            user.MarkForDeletUserByUsername = true;
            return true;
        }

    }

    return false;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {

        cout << "Adding New Client:\n\n";

        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        system("color 2F");

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            system("color 2F");

        }
        else
        {
            cout << "\nClient Is Not Delete ." << endl;
            system("color 4F");

        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        system("color 4F");
    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            system("color 2F");

            return true;
        }
        else
        {
            cout << "Clientwith account number [" << AccountNumber << "] Is not Update " << endl;
            system("color 4F");

        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        system("color 4F");

        return false;
    }

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {

                C.AccountBalance += Amount;

                SaveCleintsDataToFile(ClientsFileName, vClients);

                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                system("color 2F");

                return true;
            }

        }


        return false;
    }
    else
    {
        cout << "YourBalnce is not change " << endl;
        system("color 4F");

    }

    return true;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeDeleteClient))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }


    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeUpdateClient))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }


    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeAddNewClient))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }


    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindClientScreen()
{
    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeFindClient))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();


    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        system("color 4F");
    }
    else
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

        system("color 4F");
    }
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();

        system("color 4F");
    }

    PrintClientCard(Client);

    double Amount = 0;

    do
    {
        cout << "\nPlease enter deposit amount? ";
        cin >> Amount;

    } while (Amount <= 0);

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

short ReadPermissions()
{
    short Permissions = 0;
    char Answer = 'n';

    cout << "\nDo You Want To Give Full Accses ? Y/N ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo You Want To Give  Accses to : " << endl;

    cout << "\nShow Client List ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeListClients;
    }

    cout << "\nAdd New Client ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeAddNewClient;
    }


    cout << "\nDelite Client ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeDeleteClient;
    }


    cout << "\nUpdate Client ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeUpdateClient;
    }

    cout << "\nFind Client ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeFindClient;
    }


    cout << "\nTransactions  ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeShowTransactionsMenue;
    }

    cout << "\nManage Users  ? Y/N ? " << endl;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::eeManagrUser;
    }





    return Permissions;
}

bool FindUserByUsername(stUsers& User)
{
    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUsers user : vUsers)
    {
        if (user.Username == User.Username)
        {
            User = user;
            return true;
        }
    }
    return false;
}

bool IsExixteUserByPassEndUsername(stUsers User, stUsers& GlobaleUser)
{
    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUsers user : vUsers)
    {
        if (user.Username == User.Username && user.Password == User.Password)
        {
            GlobaleUser = user;
            return true;

        }
    }
    return false;
}

stUsers ReadUserRecord()
{
    stUsers User;

    cout << "Enter  Username ? ";
    getline(cin >> ws, User.Username);

    while (FindUserByUsername(User))
    {
        cout << "User With [" << User.Username << "] is reali exist , Entar a Nother username ?";
        getline(cin >> ws, User.Username);
    }

    cout << "Enter Password ? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissions();

    return User;
}

void AddingNewUser()
{
    stUsers User = ReadUserRecord();
    string InfoUserInLine = ConvertRecordToLine(User);
    AddDataLineToFile(UsersFileName, InfoUserInLine);
}

void AddingUsers()
{
    char choice = 'y';

    do
    {
        system("color 0F");
        cout << "\nAdding New User : " << endl << endl;
        AddingNewUser();

        cout << "\nUser Added Succesfully , do you wantt to ad more Users ? Y/N ? " << endl;
        system("color 2F");
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}

void ShowAddNewUserSkrean()
{


    cout << "\n-----------------------------------------------\n";
    cout << "                Add New User Skrean               ";
    cout << "\n-----------------------------------------------\n";


    AddingUsers();

}

void DeletUserByUsername(stUsers userorg)
{

    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    MarkForDeletUserByUsername(userorg, vUsers);


    // Delete
    SaveUsersDataToFile(UsersFileName, vUsers);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        system("color 4F");
        AccountNumber = ReadClientAccountNumber();

    }

    system("color 2F");

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {

        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;

        cout << "Please enter another amount? ";

        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

void PrintSimpleCarteUserByUsername(stUsers User)
{
    cout << "\nThe Following are the client details :  " << endl;

    cout << "------------------------------------------------" << endl;
    cout << "Username      : " << User.Username << endl;
    cout << "Password      : " << User.Password << endl;
    cout << "Permissions   : " << User.Permissions << endl;
    cout << "------------------------------------------------" << endl;
}

void ShowDeleteUserSkrean()
{
    cout << "\n-------------------------------------------\n";
    cout << "             Delete User Skrean          \n";
    cout << "-------------------------------------------\n";

    stUsers User;
    char Answer = 'n';

    cout << "Please Enter Username ? " << endl;
    getline(cin >> ws, User.Username);


    if (!FindUserByUsername(User))
    {
        cout << "\nUser with Username [" << User.Username << "] is Not Found ! " << endl;
        system("color 4F");
    }
    else if (GlobaleUser.Username == User.Username)
    {
        cout << endl << endl << "You Cant Delet This User " << endl;
        system("color 4F");
    }
    else
    {
        PrintSimpleCarteUserByUsername(User);


        cout << "Are You Sure you wante to delete this User ? Y/N ? ";
        cin >> Answer;


        if (Answer == 'Y' || Answer == 'y')
        {


            DeletUserByUsername(User);
            cout << endl << "User Delet Succsefully " << endl;
            system("color 2F");

        }
        else
        {
            cout << endl << "User is not delete ." << endl;
            system("color 4F");
        }
    }
}

void UpdateDateUserFromFaile(stUsers UsersNewInfo)
{

    vector <stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    // Update


    for (stUsers& us : vUsers)
    {
        if (us.Username == UsersNewInfo.Username)
        {
            us = UsersNewInfo;
        }
    }

    SaveUsersDataToFile(UsersFileName, vUsers);
}

void ShowUpdateUserSkrean()
{

    cout << "\n-------------------------------------------\n";
    cout << "            Update User Skrean             \n";
    cout << "-------------------------------------------\n";

    stUsers User;
    char Answer = 'n';

    cout << "Please Enter Username ? " << endl;
    getline(cin >> ws, User.Username);


    if (!FindUserByUsername(User))
    {
        cout << "\nUser with Username [" << User.Username << "] is Not Found ! " << endl;
        system("color 4F");
    }
    else
    {
        PrintSimpleCarteUserByUsername(User);


        cout << "Are You Sure you wante to Update this User ? Y/N ? ";
        cin >> Answer;


        if (Answer == 'Y' || Answer == 'y')
        {

            cout << "Please Enter Passwoed ? " << endl;
            getline(cin >> ws, User.Password);

            User.Permissions = ReadPermissions();


            UpdateDateUserFromFaile(User);

            cout << "User Update Data Sucssfuly ." << endl;
            system("color 2F");
        }
        else
        {
            cout << endl << "User is not Update ." << endl;
            system("color 4F");
        }
    }


}

void ShowFindUserSkrean()
{

    cout << "\n-------------------------------------------\n";
    cout << "              Find User Skrean             \n";
    cout << "-------------------------------------------\n";

    stUsers User;

    cout << "Please Enter Username ? " << endl;
    getline(cin >> ws, User.Username);

    cout << endl << endl;


    if (!FindUserByUsername(User))
    {
        cout << "\nUser with Username [" << User.Username << "] is Not Found ! " << endl;
        system("color 4F");
    }
    else
    {
        PrintSimpleCarteUserByUsername(User);
        system("color 2F");

    }
}

void GoBackToMainMenue()
{

    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}

void GoBackToManagrUserMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowManagrUserMenue();
}

void GoBackToTransactionsMenue()
{

    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}

void  ClearSkrean()
{
    system("cls");
    system("color 0F");
}

void LanchManagrUserMenue(enManagrUserMenue ManagrUserMenue)
{
    switch (ManagrUserMenue)
    {
    case enManagrUserMenue::eListUsers:
    {

        ClearSkrean();
        ShowUsersList();
        GoBackToManagrUserMenue();
        break;

    }
    case enManagrUserMenue::eAddNewUser:
    {
        ClearSkrean();
        ShowAddNewUserSkrean();
        GoBackToManagrUserMenue();
        break;
    }
    case enManagrUserMenue::eDeleteUser:
    {
        ClearSkrean();
        ShowDeleteUserSkrean();
        GoBackToManagrUserMenue();
        break;
    }
    case enManagrUserMenue::eUpdateUser:
    {
        ClearSkrean();
        ShowUpdateUserSkrean();
        GoBackToManagrUserMenue();
        break;
    }
    case enManagrUserMenue::eFindUser:
    {
        ClearSkrean();
        ShowFindUserSkrean();
        GoBackToManagrUserMenue();
        break;
    }
    case enManagrUserMenue::eShowMainMenueSkrean:
    {
        ClearSkrean();
        ShowMainMenue();
        break;
    }

    }
}

short ReadManagrUserMenue()
{
    short Choice = 0;

    do
    {
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> Choice;

    } while (Choice > 6 || Choice < 1);

    return Choice;
}

void ShowManagrUserMenue()
{
    ClearSkrean();
    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeManagrUser))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }

    cout << "===========================================\n";
    cout << "\t\tManagr Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Useres.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User .\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";

    LanchManagrUserMenue((enManagrUserMenue)ReadManagrUserMenue());
}

short ReadTransactionsMenueOption()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> Choice;

    } while (Choice < 1 || Choice >4);

    return Choice;
}

void LanchTransactions(enTransactionsMenueOptions TransactionMenueOption)
{

    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        ClearSkrean();
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        ClearSkrean();
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        ClearSkrean();
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();

    }
    }

}

void ShowTransactionsMenue()
{
    ClearSkrean();
    if (!HeHaveAccessToEntarHear(enMainMenuPermissions::eeShowTransactionsMenue))
    {
        system("color 4F");
        MassgeDontAcses();
        GoBackToMainMenue();
        return;
    }

    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";


    LanchTransactions((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
    short Choice = 0;

    do
    {
        cout << "Choose what do you want to do? [1 to 8]? ";
        cin >> Choice;

    } while (Choice > 8 || Choice < 1);

    return Choice;
}

void LanchBanck(enMainMenueOptions MainMenueOption)
{

    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {

        ClearSkrean();
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;

    }
    case enMainMenueOptions::eAddNewClient:
    {
        ClearSkrean();
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eDeleteClient:
    {
        ClearSkrean();
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eUpdateClient:
    {
        ClearSkrean();
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eFindClient:
    {
        ClearSkrean();
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eShowTransactionsMenue:
    {
        ClearSkrean();
        ShowTransactionsMenue();
        break;
    }
    case enMainMenueOptions::eManagrUser:
    {
        ClearSkrean();
        ShowManagrUserMenue();
        break;
    }
    case enMainMenueOptions::eLogout:
    {
        ClearSkrean();
        LoginScreen();
        break;
    }

    }

}

void ShowMainMenue()
{
    ClearSkrean();


    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";

    LanchBanck((enMainMenueOptions)ReadMainMenueOption());
}

stUsers Login()
{
    stUsers User;

    cout << "Entar Username ? ";
    getline(cin >> ws, User.Username);

    cout << "Entar Password ? ";
    getline(cin >> ws, User.Password);


    return User;
}

void PrintLoginSckrean()
{
    ClearSkrean();

    cout << "\n--------------------------------------------------" << endl;
    cout << "                   Login Screen                     " << endl;
    cout << "--------------------------------------------------" << endl << endl;

}

void LoginScreen()
{

    PrintLoginSckrean();

    while (!IsExixteUserByPassEndUsername(Login(), GlobaleUser))
    {
        PrintLoginSckrean();
        cout << "Invalide Username / Password " << endl;

    }

    ShowMainMenue();

}

int main()
{
    LoginScreen();
    system("pause>0");
    return 0;
}