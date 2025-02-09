#include <stdio.h>

#define MAX_PEOPLE 100

int main() {
    int num_people, i, j;

    printf("Enter the number of people: ");
    scanf("%d", &num_people);

    if (num_people > MAX_PEOPLE) {
        printf("Error: Maximum number of people supported is %d\n", MAX_PEOPLE);
        return 1;
    }

    int amount[num_people][num_people];

    printf("Enter the amount person i owes to person j (i, j = 0 to %d):\n", num_people - 1);
    for (i = 0; i < num_people; i++) {
        for (j = 0; j < num_people; j++) {
            scanf("%d", &amount[i][j]);
        }
    }

    printf("\nCash Flow Minimization:\n");

    // Track net balance for each person
    int net_balance[num_people];
    for (i = 0; i < num_people; i++) {
        net_balance[i] = 0;
        for (j = 0; j < num_people; j++) {
            // Calculate net balance: credits - debits
            net_balance[i] += amount[j][i] - amount[i][j];
        }
    }

    // Handle the case where everyone has a net balance of 0 (no cash flow)
    int all_zero = 1;
    for (i = 0; i < num_people; i++) {
        if (net_balance[i] != 0) {
            all_zero = 0;
            break;
        }
    }

    if (all_zero) {
        printf("Everyone has a net balance of 0. No cash flow required.\n");
        return 0;
    }

    // Greedy approach: minimize largest positive net balance by subtracting from
    // largest negative net balance (adjusted to minimize max transaction amount)
    while (1) {
        int max_creditor = -1, max_debtor = -1;
        int max_credit = 0, max_debit = 0;

        // Find maximum creditor and debtor (considering absolute values)
        for (i = 0; i < num_people; i++) {
            if (net_balance[i] > 0 && net_balance[i] > max_credit) {
                max_creditor = i;
                max_credit = net_balance[i];
            }
            if (net_balance[i] < 0 && abs(net_balance[i]) > max_debit) {
                max_debtor = i;
                max_debit = abs(net_balance[i]);
            }
        }

        // Check if no more transactions are needed
        if (max_credit == 0 || max_debit == 0) {
            break;
        }

        // Minimize transaction amount (avoid unnecessary large transactions)
        int transaction = (max_credit < max_debit) ? max_credit : max_debit;

        printf("Person %d pays %d to Person %d\n", max_debtor, transaction, max_creditor);

        // Update net balances
        net_balance[max_debtor] += transaction;
        net_balance[max_creditor] -= transaction;
    }

    return 0;
}
