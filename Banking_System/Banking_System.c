#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef enum accountType{
    savings,
    current
}accountType;
typedef struct AccountInfo{
    int AccountNumber;
    accountType AccountType;
    char Name[50];
    float Balance;
}AccountInfo;
typedef struct node{
    AccountInfo data;
    struct node* next;
}node;
node* linked_list=NULL;

void createAccount(accountType AccountType,char* Name,float Amount){
    node* list=linked_list->next;
    while(list!=NULL)
    {
        if(list->data.AccountType==AccountType && strcmp(list->data.Name,Name)==0)
        {
            printf("Invalid: User already exists!\n");
            return;
        }
        list=list->next;
    }
    struct node* newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data.AccountNumber = 100;
    newNode->data.AccountType = AccountType;
    strcpy(newNode->data.Name,Name);
    newNode->data.Balance = Amount;
    struct node* old=linked_list;
    if(old==NULL){
        old=newNode;
    }
    else{
        while(old!=NULL){
            if(old->next==NULL){
                newNode->data.AccountNumber = old->data.AccountNumber+1;
                old->next=newNode;
                old=old->next;
                newNode->next = NULL;
            }
            else if(((old->next->data.AccountNumber)-(old->data.AccountNumber))>1){
                newNode->data.AccountNumber = old->data.AccountNumber+1;
                newNode->next=old->next;
                old->next=newNode;
                break;
            }
            old = old->next;
        }
    }
    
    printf("account created successfully\n");
    char status_string[][15] = {
            "savings",
            "current"
        };
    printf("Account Number:%d\nAccount Holder:%s\naccount Type:%s\nBalance:Rs%.2f\n",newNode->data.AccountNumber,newNode->data.Name,status_string[newNode->data.AccountType],newNode->data.Balance);
}
void deleteAccount(accountType AccountType,char* Name){
    struct node* current=linked_list;
    while(current!=NULL&&current->next!=NULL){
        if(current->next->data.AccountType==AccountType){ 
            if(strcmp(current->next->data.Name,Name)==0){
                current->next=current->next->next;
                printf("Account deleted successfully\n");
                return;
            }
        }
        current=current->next;
    }
    printf("Invalid: User does not exist\n");
}
void Display(struct node* linked_list){
    if(linked_list->next==NULL){
        printf("No Accounts to display\n");
    }
    else{
        printf("Account number\t\tAccount Type\t\tName\t\tBalance");
        printf("\n-----------------------------------------------------------------------\n");
        node* prev=linked_list->next;
        char status_string[][15] = {
            "savings",
            "current"
        };
        while(prev!=NULL){
            printf("%d\t\t\t%s\t\t\t%s\t\t%.2f\n",prev->data.AccountNumber, status_string[prev->data.AccountType],prev->data.Name,prev->data.Balance);
            prev=prev->next;
        }
    }
}
void lowBalanceAccounts(struct node* linked_list){
    struct node* sec=linked_list->next;
    int c=0;
    if(sec==NULL){
        printf("no accounts present\n");
        return;
    }
    else{
        while(sec!=NULL){
            if(sec->data.Balance<100){
                printf("Account Number:%d, Name:%s, Balance:%.2f\n",sec->data.AccountNumber,sec->data.Name,sec->data.Balance);
                c=1;
            }
            sec=sec->next;
        }
    }
    if(c==0)
    {
        printf("Every account has minimum Balance \n");
    }

}
void transaction(int accountNumber,int Amount ,int code){
    struct node* third=linked_list->next;
    if(code==1){
        while(third!=NULL){
           if(accountNumber==third->data.AccountNumber){
               third->data.Balance=third->data.Balance+Amount;
               printf("updated balance is Rs:%.2f",third->data.Balance);
               return;
           }
           third=third->next;
        }
    }
    else if(code==0){
        while(third!=NULL){
            if(accountNumber==third->data.AccountNumber){
                if(third->data.Balance-Amount<100){
                    printf("The balance is insufficient for the specified withdrawal."); 
                    return;
                }
                else{
                    third->data.Balance=third->data.Balance-Amount;
                    printf("updated balance is Rs:%.2f",third->data.Balance);
                    return;
                }
                break;
            }
            third=third->next;
        }
    }   
    printf("Invalid: User does not exist");
}

int main(){
    char op[20];
    char AccountTypeStr[20];
    char Name[20];
    float Amount;
    linked_list=(struct node*)malloc(sizeof(struct node));
    (linked_list->data).AccountNumber=99;
    linked_list->next=NULL;
    while(1){
        scanf("%s",op);
        if(strcmp(op,"EXIT")==0){
            break;
        }
        else if(strcmp(op,"CREATE")==0){
            scanf("%s",AccountTypeStr);
            accountType AccountType;
            if(strcmp(AccountTypeStr,"current") == 0){
                AccountType = current;
            }
            else if(strcmp(AccountTypeStr,"savings") == 0){
                AccountType = savings;
            }
            scanf("%s",Name);
            scanf("%f",&Amount);
            createAccount(AccountType,Name,Amount);
        }
        else if(strcmp(op,"DELETE")==0){
            scanf("%s",AccountTypeStr);
            accountType AccountType;
            if(strcmp(AccountTypeStr,"current") == 0){
                AccountType = current;
            }
            else if(strcmp(AccountTypeStr,"savings") == 0){
                AccountType = savings;
            }
            scanf("%s",Name);
            deleteAccount(AccountType,Name);
        }
        else if(strcmp(op,"DISPLAY")==0){
            Display(linked_list);   
        }
        else if(strcmp(op,"LOWBALANCE")==0){
            lowBalanceAccounts(linked_list);
        }
        else if(strcmp(op,"TRANSACTION")==0){
            int AccountNumber,Amount,Code;
            scanf("%d %d %d",&AccountNumber,&Amount,&Code);
            transaction(AccountNumber,Amount,Code);
        }
    }
    return 0;  
}