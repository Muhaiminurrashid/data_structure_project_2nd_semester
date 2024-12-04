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
void Send_Money_Non_iCash_User(Account *temp);
void Admin();
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
void Debug_Show_All_Accounts_From_File();
void Transaction();
void line_break();
void border_line();
void retry_pass();
void insufi_balance();
void Send_Money_iCash_User(Account *temp);

Account *head = NULL;

int main()
{
    Load_Accounts_From_File();
    Main_Menu();
    Save_Accounts_To_File();
}

void Main_Menu()
{
    int Choice;
    while (1)
        {
            printf(" \t\t\t      ======================\n");
            printf(" \t\t\t      || WELCOME TO ICASH || ");
            printf("\n\t\t\t      ======================\n\n");
            line_break();
            printf("1. Create New Account\n");
            printf("2. Login\n");
            printf("3. Admin Login\n");
            printf("4. Exit\n\n");
            printf("Enter Your Choice\n");
            scanf("%d", &Choice);
            switch (Choice)
                {
                case 1:
                    Create_New_Account();
                    break;
                case 2:
                    Login();
                    break;

                case 3:
                    Admin();
                    break;
                case 4:
                    exit(0);
                default:
                    printf("Invalid choice. Try again.\n");
                }
        }
}

void Admin()
{
    int admin_pin =111;
    int pin;
    printf("Admin Pin\n");
    scanf("%d",&pin);
    if (pin==admin_pin)
        {
            Debug_Show_All_Accounts_From_File();
            border_line();
        }
    else
        {
            printf("\nWrong Password!\n");
        }

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
                    printf("\nAccount with this phone number already exists!!!!\n");
                    free(New_Account);
                    return;
                }
            temp = temp->next;
        }
    printf("Enter Your Pin Number\n");
    scanf("%s",New_Account->pin);
    New_Account->Balance = 0;// Initial Balance is Zero
    printf("\n\n\t\t\t*** ACCOUNT CREATED SUCCESSFULLY ***\n\n");
    New_Account->next = head;
    head = New_Account;
    Save_Accounts_To_File();
    border_line();
    free(temp);
}
void Login()
{
    Account *temp = head;
    char Phone_Number[13];
    printf("Enter Your Phone Number\n");
    scanf("%s",Phone_Number);
    printf("Enter Your Pin\n");
    char pin[13];
    scanf("%s",pin);
    while(temp!=NULL)
        {
            if(strcmp(temp->Phone_Number,Phone_Number)==0 && strcmp(temp->pin,pin)==0)
                {
                    border_line();
                    printf("\t\t\t\t\t\t\t***Login Successfull***\n\n\n\n");
                    User_Menu(temp);
                    return;
                }
            else
                {
                    temp = temp->next;
                }
        }
    printf("\nInvalid Phone Number or Pin, Please Try Again!!\n\n");
    border_line();

}
void User_Menu(Account *temp)
{
    int Choice;
    while(1)
        {
            printf(" \t\t\t\t ===============\n");
            printf(" \t\t\t\t || USER MENU || ");
            printf("\n\t\t\t\t ===============\n\n");
            printf("1. Send Money To iCash User\n");
            printf("2. Mobile Recharge\n");
            printf("3. Cash Out\n");
            printf("4. Pay Bill\n");
            printf("5. Cash In\n");
            printf("6. Send Money Non iCash_User\n");
            printf("7. Check Balance\n");
            printf("8. Change Pin\n");
            printf("9. Transacation\n");
            printf("10. Exit\n");
            printf("\nEnter Your Choice\n");
            scanf("%d",&Choice);

            switch(Choice)
                {
                case 1:
                    Send_Money_iCash_User(temp);
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
                    Send_Money_Non_iCash_User(temp);
                    break;
                case 7:
                    Check_Balance(temp);
                    break;
                case 8:
                    Change_Pin(temp);
                    break;
                case 9:
                    Transaction();
                    break;
                case 10:
                    return;
                default:
                    printf("Invalid choice. Try again.\n\n");
                }
        }
}
void Send_Money_iCash_User(Account *temp)
{
    printf("Enter Recipent's Phone Number\n");
    char Phone_Number[13];
    scanf("%s",Phone_Number);
    int Ammount;
    char pin[13];
    Account *current = head;
    while(current != NULL)
        {
            if (strcmp(current->Phone_Number,Phone_Number)==0 && strcmp(temp->Phone_Number,Phone_Number))
                {
                    printf("Enter The Ammount\n");
                    scanf("%d",&Ammount);
                    while(1)
                        {
                            printf("Enter Your Pin\n");
                            scanf("%s",pin);
                            if (strcmp(temp->pin,pin)==0)
                                {
                                    if (temp->Balance >= Ammount)
                                        {
                                            temp->Balance -= Ammount;
                                            current->Balance += Ammount;
                                            printf("\n\n***Send %d Taka To %s Successfull***\n\n\n",Ammount,Phone_Number);
                                            Check_Balance(temp);
                                            Save_Accounts_To_File(); // Save changes after money transfer
                                            return;
                                        }
                                    else
                                        {
                                            insufi_balance();
                                        }
                                    break;
                                }
                            else
                                {
                                    retry_pass();
                                }
                        }
                }

            current=current->next;
        }
    printf("\nInvalid Request!!!!\n\n");
}

void Send_Money_Non_iCash_User(Account *temp)
{
    printf("Enter Recipent's Phone Number\n");
    char Phone_Number[13];
    scanf("%s",Phone_Number);
    printf("Enter The Ammount\n");
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
                            printf("\n\n***Send Money To %s Successfull***\n\n\n",Phone_Number);
                            Check_Balance(temp);
                            Save_Accounts_To_File(); // Save changes after money transfer
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
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
                            printf("***Recharge %d Taka to %s Successfull***\n\n\n",Ammount,Phone_Number);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
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
                            printf("***Cash Out Successfull***\n\n\n");
                            Save_Accounts_To_File(); // Save changes after cash out
                            Check_Balance(temp);
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
                }
        }
}

void Pay_Bill(Account *temp)
{
    int Choice;
    while(1)
        {
            printf(" \t\t\t\t ==============\n");
            printf(" \t\t\t\t || PAY BILL || ");
            printf("\n\t\t\t\t ==============\n\n");
            printf("1. Electricity\n");
            printf("2. Gas\n");
            printf("3. Internet\n");
            printf("4. Water\n");
            printf("5. Exit\n\n");
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

void Cash_In(Account *temp)
{
    int Ammount;
    printf("Enter The Ammount\n");
    scanf("%d",&Ammount);
    temp->Balance += Ammount;
    printf("\n***Cash In Successfull***\n\n");
    Save_Accounts_To_File(); // Save changes after cash in
    Check_Balance(temp);
}


void Electricity(Account *temp)
{
    printf("\n*Palli Biddut\n\n");
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
                            printf("\n***Paid %d Taka To Palli Biddut Successfull***\n\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
                }
        }
}
void Gas(Account *temp)
{
    printf("\n*Bashundhara Gas\n\n");
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
                            printf("\n***Paid %d Taka To Bashundhara Gas Successfull***\n\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
                }
        }
}
void Internet(Account *temp)
{
    printf("\n*Mesh Networks\n\n");
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
                            printf("\n***Paid %d Taka To Mesh Networks Successfull***\n\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
                }
        }
}
void Water(Account *temp)
{
    printf("\n*Rajshahi WASA\n\n");
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
                            printf("\n***Paid %d Taka To Rajshahi WASA Successfull***\n\n",Ammount);
                            Save_Accounts_To_File(); // Save changes after sending money
                            Check_Balance(temp);
                        }
                    else
                        {
                            insufi_balance();
                        }
                    break;
                }
            else
                {
                    retry_pass();
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
                    printf("\n\n***Changed Pin Successfully***\n\n");
                    Save_Accounts_To_File(); // Save changes after changing pin
                    break;
                }
            else
                {
                    retry_pass();
                }
        }
}
void Transaction(Account *temp)
{
    printf("Transaction is Coming Soon!\n");
    border_line();
}
void Debug_Show_All_Accounts_From_File()
{
    printf(" \t\t\t\t =================\n");
    printf(" \t\t\t\t ||  User Data  || ");
    printf("\n\t\t\t\t =================\n\n");
    line_break();

    FILE *file = fopen("accounts.dat", "rb");
    if (!file)
        {
            //printf("No saved accounts found or file could not be opened.\n");
            return;
        }

    Account temp;
    while (fread(&temp, sizeof(Account), 1, file))
        {
            printf("Phone Number: %s\n", temp.Phone_Number);
            printf("Balance: %d Taka\n", temp.Balance);
            printf("Pin: %s\n", temp.pin);
            printf("---------------------------\n");
        }
    printf("\n\n\n");

    fclose(file);
}
void Save_Accounts_To_File()
{
    FILE *file = fopen("accounts.dat", "wb");
    if (!file)
        {
            //printf("Error: Could not open file for saving.\n");
            return;
        }

    Account *Current = head;
    while (Current != NULL)
        {
            fwrite(Current, sizeof(Account), 1, file);
            Current = Current->next;
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
void border_line()
{
    printf("_______________________________________________________________________________\n\n\n");
}

void line_break()
{
    printf("\n\n");
}
void retry_pass()
{
    {
        printf("\t\t\t\t\t\tInvalid Pin, Please Try Again!!!\n\n");
    }
}
void Check_Balance(Account *temp)
{
    printf("\nCURRENT BALANCE : %d TAKA\n\n",temp->Balance);
    border_line();
}
void insufi_balance()
{
    printf("\nInsufficient balance, Please Cash In !!!!\n\n");
    border_line();
}
