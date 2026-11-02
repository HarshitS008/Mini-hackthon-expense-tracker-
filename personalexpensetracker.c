
#include <stdio.h>

#define MAX 100
#define CATEGORIES 4

struct Expense {
    int category;
    float amount;
    char note[50];
};

struct Expense expenses[MAX];

char categoryNames[CATEGORIES][20] = {
    "Food", "Travel", "Books", "Entertainment"
};

float budget = 0;
float total = 0;
float categoryTotal[CATEGORIES] = {0};
int expenseCount = 0;

void addExpense() {
    int category;
    float amount;

    if (expenseCount >= MAX) {
        printf("\nExpense limit reached!\n");
        return;
    }

    printf("\n--- ADD NEW EXPENSE ---\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categoryNames[i]);
    }

    printf("Choose category: ");
    if (scanf("%d", &category) != 1) {
        while (getchar() != '\n');
        printf("Invalid category!\n");
        return;
    }

    if (category < 1 || category > CATEGORIES) {
        printf("Invalid category!\n");
        return;
    }

    printf("Enter amount (Rs.): ");
    if (scanf("%f", &amount) != 1 || amount <= 0) {
        while (getchar() != '\n');
        printf("Invalid amount!\n");
        return;
    }

    printf("Enter a short note: ");
    scanf(" %49[^\n]", expenses[expenseCount].note);

    expenses[expenseCount].category = category;
    expenses[expenseCount].amount = amount;

    expenseCount++;
    total += amount;
    categoryTotal[category - 1] += amount;

    printf("\nExpense saved successfully!\n");

    if (total > budget) {
        printf("ALERT: You have exceeded your budget!\n");
    }
}

void viewExpenses() {
    printf("\n--- EXPENSE HISTORY ---\n");

    if (expenseCount == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("%-5s %-16s %-12s %s\n",
           "No.", "Category", "Amount", "Note");

    for (int i = 0; i < expenseCount; i++) {
        printf("%-5d %-16s Rs.%-9.2f %s\n",
               i + 1,
               categoryNames[expenses[i].category - 1],
               expenses[i].amount,
               expenses[i].note);
    }
}

void showSummary() {
    float remaining = budget - total;
    int highest = 0;

    printf("\n--- MONTHLY EXPENSE REPORT ---\n");

    printf("Monthly Budget : Rs. %.2f\n", budget);
    printf("Total Spending : Rs. %.2f\n", total);
    printf("Remaining      : Rs. %.2f\n", remaining);

    printf("\nCategory-wise Spending:\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%-16s : Rs. %.2f\n",
               categoryNames[i], categoryTotal[i]);

        if (categoryTotal[i] > categoryTotal[highest]) {
            highest = i;
        }
    }

    if (expenseCount > 0) {
        printf("\nHighest Spending: %s\n",
               categoryNames[highest]);
    } else {
        printf("\nNo expenses added yet.\n");
    }

    if (total > budget) {
        printf("\nWARNING: Budget exceeded by Rs. %.2f\n",
               total - budget);
    } else {
        printf("\nYou are within your monthly budget.\n");
    }
}

void spendingAdvisor() {
    float percentage;

    printf("\n--- SMART SPENDING ADVISOR ---\n");

    percentage = (total / budget) * 100;

    printf("Budget Used: %.2f%%\n", percentage);

    if (percentage < 50) {
        printf("Status: EXCELLENT\n");
        printf("Tip: Great! Keep tracking your expenses.\n");
    }
    else if (percentage < 80) {
        printf("Status: GOOD\n");
        printf("Tip: You are managing your money well.\n");
    }
    else if (percentage <= 100) {
        printf("Status: CAUTION\n");
        printf("Tip: Try to avoid unnecessary purchases.\n");
    }
    else {
        printf("Status: OVER BUDGET\n");
        printf("Tip: Reduce spending and review your expenses.\n");
    }

    if (expenseCount > 0) {
        int highest = 0;

        for (int i = 1; i < CATEGORIES; i++) {
            if (categoryTotal[i] > categoryTotal[highest]) {
                highest = i;
            }
        }

        printf("Suggestion: Review your %s expenses first.\n",
               categoryNames[highest]);
    }
}

int main() {
    int choice;

    printf("====================================\n");
    printf("     CAMPUSSPEND - EXPENSE TRACKER\n");
    printf("====================================\n");

    do {
        printf("Enter your monthly budget (Rs.): ");
        if (scanf("%f", &budget) != 1) {
            while (getchar() != '\n');
            budget = 0;
        }

        if (budget <= 0) {
            printf("Please enter a positive budget.\n");
        }
    } while (budget <= 0);

    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add Expense\n");
        printf("2. View Expense History\n");
        printf("3. Monthly Expense Summary\n");
        printf("4. Smart Spending Advisor\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                showSummary();
                break;

            case 4:
                spendingAdvisor();
                break;

            case 5:
                printf("\nThank you for using CampusSpend!\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
