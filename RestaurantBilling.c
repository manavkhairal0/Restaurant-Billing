#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer [50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

//Function to generate bills.
void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
    printf("\t   Priya ka Dhaba");
    printf("\n\t  ----------------");
    printf("\nDate: %s", date);
    printf("\nInvoice to : %s", name);
    printf("\n");
    printf("-----------------------------------------\n");
    printf("Item\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30], int qty, float price){
    printf("%s\t\t", item);
    printf("%d\t\t",qty);
    printf("%.2f\t",qty *price);
    printf("\n\n");

}

    void generateBillFooter(float total){
        printf("\n");
        float dis = 0.1 * total;
        float netTotal = total -dis;
        float cgst = 0.09 * netTotal,grandTotal=netTotal + 2*cgst;
        printf("-----------------------------------------\n");
        printf("Sub Total\t\t\t %.2f",total);
        printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
        printf("\n\t\t\t\t------");
        printf("\nNet Total\t\t\t%.2f", netTotal);
        printf("\nCGST @9%s\t\t\t%.2f","%", cgst);
        printf("\nSGST @9%s\t\t\t%.2f","%", cgst);
        printf("\n-----------------------------------------\n");
        printf("\nGrand Total\t\t\t%.2f",grandTotal);
        printf("\n-----------------------------------------\n");
    }
    
    

int main(){
    
    int opt, n;
    float total;
    struct orders ord;
    struct orders order;
    char saveBill ='y';
    FILE *fp;

    //dashboard
    printf("\t===============Priya ka dhaba===============");
    printf("\n\nPlease select your prefered operation: ");
    printf("\n\n");
    printf("\n1.Generate Invoices");
    printf("\n2.Show all the Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Exit");

    printf("\n\nPlease enter your choice : ");
    scanf("%d", &opt);
    
fgetc(stdin);

    switch(opt){
        case 1 :
    system("cls");
          printf("\nPlease Enter the name of the customer:\t");
          fgets(ord.customer,50,stdin);
          ord.customer[strlen(ord.customer)-1]=0;
          strcpy(ord.date,__DATE__);
          printf("\nPlease enter the number of items: \t");
          scanf("%d", &n);
          ord.numOfItems = n;

          for(int i =0;i<n;i++){
              fgetc(stdin);
              printf("\n");
              printf("Please enter the Items:%d\t",i+1);
              fgets(ord.itm[i].item,20,stdin);
              ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
              printf("Please enter the quantity:\t");
              scanf("%d", &ord.itm[i].qty);
              printf("Please enter the unit price:\t");
              scanf("%f", &ord.itm[i].price);
              total +=ord.itm[i].qty * ord.itm[i].price;
          }
          generateBillHeader(ord.customer,ord.date);
          for (int i = 0; i < ord.numOfItems; i++)
          {
              generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
          }
          generateBillFooter(total);

          printf("\nDo you want to save bill?[Y/N] :");
          scanf("%s", &saveBill);

          if (saveBill=='y')
          {
             fp = fopen("RestaurantBill.dat","a+");
             fwrite(&ord,sizeof(struct orders),1,fp);
             if (fwrite != 0)
             
                 printf("successfully saved.");
                 else
                 printf("Error saving.");
                 fclose(fp);
             
             break;
             
          }
          case 2:
          system("cls");
          fp = fopen("RestaurantBill.dat","r");
          printf("\n  *****Your Previous Invoices*****\n");
          while(fread(&order,sizeof(struct orders),1,fp)){
              float tot =0;
              generateBillHeader(order.customer,order.date);
              for(int i=0;i<order.numOfItems; i++){
                  generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                  tot+=order.itm[i].qty * order.itm[i].price;
              }
              generateBillFooter(tot);
          }
          fclose(fp);
          break;

    }


    printf("\n\n");


return 0;
    
}