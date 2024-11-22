
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Account
{
    char Phone_Number[13];
    int Balance;
    char pin[13];
    struct Account *next;
} Account;

void Create_New_Account();
void Login();
void Main_Menu();
void User_Menu(Account *temp);
void Send_Money(Account *temp);
void Mobile_Recharge(Account *temp);
void Cash_Out(Account *temp);
void Cash_In(Account *temp);
void Pay_Bill(Account *temp);
void Electricity(Account *temp);
void Gas(Account *temp);
void Internet(Account *temp);
void Water(Account *temp);
void Check_Balance(Account *temp);
void Save_Accounts_To_File();
void Load_Accounts_From_File();
void Change_Pin(Account *temp);
void Transaction();

Account *head = NULL;

int main()
{
    Load_Accounts_From_File();
    Main_Menu();
    Save_Accounts_To_File();
}
/*
//DEBUG
void Debug_Show_All_Accounts_From_File() {
    printf("\n--- DEBUG: Showing All Accounts from File ---\n");

    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("No saved accounts found or file could not be opened.\n");
        return;
    }

    Account temp;
    while (fread(&temp, sizeof(Account), 1, file)) {
        printf("Phone Number: %s\n", temp.Phone_Number);
        printf("Balance: %d\n", temp.Balance);
        printf("Pin: %s\n", temp.pin);
        printf("---------------------------\n");
    }

    fclose(file);
}
*/
void Main_Menu() {
    int Choice;
    printf("--------WELCOME TO ICASH----------\n\n\n");
    while (1) {
        printf("1. Create New Account\n");
        printf("2. Login\n");
        //printf("3. Debug: Show All Accounts from File\n");
        printf("5. Exit\n");
        scanf("%d", &Choice);
        switch (Choice) {
            case 1:
                Create_New_Account();
                break;
            case 2:
                Login();
                break;
                /*
            case 4:
                Debug_Show_All_Accounts_From_File(); // From file
                break;*/
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void Save_Accounts_To_File()
{
    FILE *file = fopen("accounts.dat", "wb");
    if (!file)
        {
            //printf("Error: Could not open file for saving.\n");
            return;
        }

    Account *current = head;
    while (current != NULL)
        {
            fwrite(current, sizeof(Account), 1, file);
            current = current->next;
        }

    fclose(file);
   // printf("Accounts saved to file successfully.\n");
}

void Load_Accounts_From_File()
{
    FILE *file = fopen("accounts.dat", "rb");
    if (!file)
        {
            //printf("No saved accounts found.\n\n\n");
            return;
        }

    Account temp;
    while (fread(&temp, sizeof(Account), 1, file))
        {
            Account *new_account = (Account *)malloc(sizeof(Account));
            *new_account = temp;
            new_account->next = head;
            head = new_account;
        }

    fclose(file);
    //printf("Accounts loaded from file successfully.\n");
}
void Create_New_Account()
{
    Account *temp = head;
    Account *New_Account = (Account*)malloc(sizeof(Account));
    printf("Enter Your Phone Number\n");
    scanf("%s",New_Account->Phone_Number);
    // Check for duplicate phone number
    while (temp != NULL)
        {
            if (strcmp(temp->Phone_Number, New_Account->Phone_Number) == 0)
                {
                    printf("Account with this phone number already exists!\n");
                    free(New_Account);
                    return;
                }
            temp = temp->next;
        }
    printf("Enter Your Pin Number\n");
    scanf("%s",New_Account->pin);
    New_Account->Balance = 0;// Initial Balance is Zero
    printf("\n\nAccount Created Successfully\n\n");
    New_Account->next = head;
    head = New_Account;
}
void Login()
{
    Account *temp = head;
    char Phone_Number[13];
    //printf("Loggin In...........\n");
    printf("Enter Your Phone Number\n");
    scanf("%s",Phone_Number);
    printf("Enter Your Pin\n");
    char pin[13];
    scanf("%s",pin);
    while(temp!=NULL)
        {
            if(strcmp(temp->Phone_Number,Phone_Number)==0 && strcmp(temp->pin,pin)==0)
                {
                    printf("Login Successfully\n");
                    User_Menu(temp);
                    return;
                }
            else
                {
                    temp = temp->next;
                }
        }
    printf("Invalid Phone Number or Pin, Please Try Again\n");
}
void User_Menu(Account *temp)
{
    while(1)
        {
            int Choice;
            printf("\n\n--- USER MENU ---\n\n");
            printf("1. Send Money\n");
            printf("2. Mobile Recharge\n");
            printf("3. Cash Out\n");
            printf("4. Pay Bill\n");
            printf("5. Cash In\n");
            printf("6. Transcation\n");
            printf("7. Check Balance\n");
            printf("8. Change Pin\n");
            printf("9. Exit\n");
            printf("Enter Your Choice\n");
            scanf("%d",&Choice);

            switch(Choice)
                {
                case 1:
                    Send_Money(temp);
                    break;
                case 2:
                    Mobile_Recharge(temp);
                    break;
                case 3:
                    Cash_Out(temp);
                    break;
                case 4:
                    Pay_Bill(temp);
                    break;
                case 5:
                    Cash_In(temp);
                    break;
                case 6:
                    Transaction();
                    break;
                case 7:
                    Check_Balance(temp);
                    break;
                case 8:
                    Change_Pin(temp);
                    break;
                case 9:
                    return;
                default:
                    printf("Invalid choice. Try again.\n");
                }
        }
}
void Send_Money(Account *temp)
{
    printf("Enter Recipent's Phone Number\n");
    char Phone_Number[13];
    scanf("%s",Phone_Number);
    printf("Enter The Ammount\n");
    int Ammount;
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[4];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Send Moeny To %s Successfull\n",Phone_Number);
                            Check_Balance(temp);
                            Save_Accounts_To_File(); // Save changes after money transfer
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Mobile_Recharge(Account *temp)
{
    printf("Enter Recipent's Phone Number\n");
    char Phone_Number[13];
    scanf("%s",Phone_Number);
    printf("Enter Recharge The Ammount\n");
    int Ammount;
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[13];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Recharge %d Taka to %s Successfull\n",Ammount,Phone_Number);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Cash_Out(Account *temp)
{
    int Ammount;
    printf("Enter The Ammount\n");
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[13];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Cash Out Successfull\n");
                            Save_Accounts_To_File(); // Save changes after cash out
                            Check_Balance(temp);
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}

void Pay_Bill(Account *temp)
{
    int Choice;
    while(1)
        {
            printf("\n--- PAY BILL MENU ---\n");
            printf("1. Electricity\n");
            printf("2. Gas\n");
            printf("3. Internet\n");
            printf("4. Water\n");
            printf("5. Exit\n");
            printf("Enter Your Choice\n");
            scanf("%d",&Choice);
            switch(Choice)
                {
                case 1:
                    Electricity(temp);
                    break;
                case 2:
                    Gas(temp);
                    break;
                case 3:
                    Internet(temp);
                    break;
                case 4 :
                    Water(temp);
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid choice. Try again.\n");
                }
        }
}
void Check_Balance(Account *temp)
{
    printf("Current Balance is %d Taka\n",temp->Balance);
}
void Cash_In(Account *temp)
{
    int Ammount;
    printf("Enter The Ammount\n");
    scanf("%d",&Ammount);
    temp->Balance += Ammount;
    printf("Cash In Successfull\n");
    Save_Accounts_To_File(); // Save changes after cash in
    Check_Balance(temp);
}


void Electricity(Account *temp)
{
    printf("Palli Biddut\n");
    printf("Enter Account Number\n");
    char Account_Number[13];
    scanf("%s",Account_Number);
    printf("Enter Recharge The Ammount\n");
    int Ammount;
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[13];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Paid %d Taka To Palli Biddut Successfull\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Gas(Account *temp)
{
    printf("Bashundhara Gas\n");
    printf("Enter Account Number\n");
    char Account_Number[13];
    scanf("%s",Account_Number);
    printf("Enter Recharge The Ammount\n");
    int Ammount;
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[13];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Paid %d Taka To Bashundhara Gas Successfull\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Internet(Account *temp)
{
    printf("Mesh Networks\n");
    printf("Enter Account Number\n");
    char Account_Number[13];
    scanf("%s",Account_Number);
    printf("Enter Recharge The Ammount\n");
    int Ammount;
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[13];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Paid %d Taka To Mesh Networks Successfull\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Water(Account *temp)
{
    printf("Rajshahi WASA\n");
    printf("Enter Account Number\n");
    char Account_Number[13];
    scanf("%s",Account_Number);
    printf("Enter Recharge The Ammount\n");
    int Ammount;
    scanf("%d",&Ammount);
    printf("Enter Your Pin\n");
    char pin[13];
    while(1)
        {
    scanf("%s",pin);
            if (strcmp(temp->pin,pin)==0)
                {
                    if (temp->Balance >= Ammount)
                        {
                            temp->Balance -= Ammount;
                            printf("Paid %d Taka To Rajshahi WASA Successfull\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            printf("Insufficient balance!\n");
                        }
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Change_Pin(Account *temp)
{
    printf("Enter Your Old Pin\n");
    char old_pin[13];
    while(1)
        {
            scanf("%s",old_pin);
            if (strcmp(temp->pin,old_pin)==0)
                {
                    printf("Enter New Pin\n");
                    char new_pin[4];
                    scanf("%s",new_pin);
                    strcpy(temp->pin, new_pin);
                    printf("Changed Pin Successfully\n");
                    Save_Accounts_To_File(); // Save changes after changing pin
                    break;
                }
            else
                {
                    printf("Invalid Pin, Please Try Again\n");
                }
        }
}
void Transaction(Account *temp)
{
    printf("Transaction is Coming Soon!\n");
}

