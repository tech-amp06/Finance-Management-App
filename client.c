#include <stdio.h>
#include "graphingFunc.c"
#include "csv.c"
#include "tabulating.c"
#include "total_invoice.c"
#include "invoice.c"
#include "node.h"
#include "balance_sheet.c"
#include "temp.c"


int main() {
    int choice, invoice_type, invoice_no;

    printf("FINANCE MANAGEMENT APPLICATION\n");
    printf("------------------------------");
    printf("\n\t1. Transaction History\n\t2. Balance Sheets\n\t3. Generate Invoice\n\t4. Analyse\n\t5. Add expense\n\t6. Exit\n");

    struct node *head = read_csv();

    do {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printList(head);
                break;
            
            case 2:
                generate_balance_table(head);
                break;

            case 3:
                printf("Enter invoice type [0: Total transaction invoice, 1: Individual transaction invoice]: ");
                scanf("%d", &invoice_type);
                while (getchar() != '\n');

                switch (invoice_type) {
                    case 0:
                        generate_total_invoice(head);
                        break;
                    case 1:
                        printf("Enter invoice number: ");
                        scanf("%d", &invoice_no);
                        while (getchar() != '\n');
                        generate_invoice(head, invoice_no);
                        break;
                    default:
                        printf("Invalid invoice type!");
                        break;
                }
                break;
            
            case 4:
                analyse(head);
                break;
            
            case 5:
                head = addTransaction(head);
                break;
            
            case 6:
                printf("Saving changes...\n");
                // write_csv(head);
                break;

            default:
                printf("Invalid choice!");
        }
    } while (choice != 6);
    printf("Exited...");
    
    return 0;
}