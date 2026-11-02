
#include <stdio.h>
#include <math.h>

#define MAX 100
#define CATEGORIES 4

struct Expense {
    int category;
    double amount;
    char note[50];
};

struct Expense expenses[MAX];

char categoryNames[CATEGORIES][20] = {
    "Food",
    "Travel",
    "Books",
    "Entertainment"
};

double budget = 0;
double total = 0;
double categoryTotal[CATEGORIES] = {0};
int expenseCount = 0;

/* Function to clear invalid input */
void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/* Function to accept a valid number */
int readNumber(int *number) {
    if (scanf("%d", number) != 1) {
        clearInput();
        return 0;
    }
    clearInput();
    return 1;
}

/* Function to accept a valid amount */
int readAmount(double *amount) {
    if (scanf("%lf", amount) != 1) {
        clearInput();
        return 0;
    }
    clearInput();

    if (!isfinite(*amount) || *amount <= 0) {
        return 0;
    }
    return 1;
}

/* Function to set monthly budget */
void setBudget() {
    do {
        printf("\nEnter Monthly Budget (Rs.): ");

        if (!readAmount(&budget)) {
            budget = 0;
            printf("Invalid budget! Enter a positive amount.\n");
        }

    } while (budget <= 0);

    printf("\nMonthly budget set successfully!\n");
}

/* Function to add a new expense */
void addExpense() {
    int category;
    double amount;

    if (expenseCount >= MAX) {
        printf("\nExpense storage is full!\n");
        return;
    }

    printf("\n========== ADD EXPENSE ==========\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categoryNames[i]);
    }

    printf("Choose category (1-4): ");

    if (!readNumber(&category) ||
        category < 1 || category > CATEGORIES) {
        printf("Invalid category!\n");
        return;
    }

    printf("Enter expense amount (Rs.): ");

    if (!readAmount(&amount)) {
        printf("Invalid amount! Enter a positive number.\n");
        return;
    }

    printf("Enter a short note: ");

    if (fgets(expenses[expenseCount].note, 50, stdin) == NULL) {
        expenses[expenseCount].note[0] = '\0';
    }

    /* Remove newline from note */
    for (int i = 0; i < 50; i++) {
        if (expenses[expenseCount].note[i] == '\n') {
            expenses[expenseCount].note[i] = '\0';
            break;
        }
        if (expenses[expenseCount].note[i] == '\0') {
            break;
        }
    }

    expenses[expenseCount].category = category;
    expenses[expenseCount].amount = amount;

    expenseCount++;
    total += amount;
    categoryTotal[category - 1] += amount;

    printf("\nExpense added successfully!\n");

    if (total > budget) {
        printf("WARNING: Budget exceeded by Rs. %.2f\n",
               total - budget);
    }
    else if (total >= budget * 0.80) {
        printf("ALERT: You have used 80%% or more of your budget.\n");
    }
}

/* Function to display all expenses */
void viewExpenses() {
    printf("\n========== EXPENSE HISTORY ==========\n");

    if (expenseCount == 0) {
        printf("No expenses recorded yet.\n");
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

/* Function to find highest spending category */
int highestCategory() {
    int highest = 0;

    for (int i = 1; i < CATEGORIES; i++) {
        if (categoryTotal[i] > categoryTotal[highest]) {
            highest = i;
        }
    }

    return highest;
}

/* Function to display monthly summary */
void showSummary() {
    double remaining = budget - total;
    double percentage = (total / budget) * 100;

    printf("\n========== MONTHLY SUMMARY ==========\n");

    printf("Monthly Budget  : Rs. %.2f\n", budget);
    printf("Total Spending  : Rs. %.2f\n", total);
    printf("Remaining Budget: Rs. %.2f\n", remaining);
    printf("Budget Used     : %.2f%%\n", percentage);

    printf("\nCategory-wise Spending:\n");

    for (int i = 0; i < CATEGORIES; i++) {
        printf("%-16s : Rs. %.2f\n",
               categoryNames[i], categoryTotal[i]);
    }

    if (expenseCount > 0) {
        int highest = highestCategory();

        printf("\nHighest Spending Category: %s\n",
               categoryNames[highest]);
    }
    else {
        printf("\nNo expenses recorded yet.\n");
    }

    if (total > budget) {
        printf("\nWARNING: Monthly Budget Exceeded!\n");
        printf("Exceeded Amount: Rs. %.2f\n",
               total - budget);
    }
    else {
        printf("\nBudget Status: Within Budget\n");
    }
}

/* Function for smart spending suggestions */
void spendingAdvisor() {
    double percentage, remaining, dailyLimit;
    int highest, daysLeft;

    printf("\n====================================\n");
    printf("       SMART SPENDING ADVISOR\n");
    printf("====================================\n");

    percentage = (total / budget) * 100;
    remaining = budget - total;

    printf("\nMonthly Budget : Rs. %.2f\n", budget);
    printf("Total Spent    : Rs. %.2f\n", total);
    printf("Budget Used    : %.2f%%\n", percentage);

    if (expenseCount == 0) {
        printf("\nNo expenses recorded yet.\n");
        printf("Tip: Start recording your daily expenses.\n");
    }
    else {
        if (percentage < 50) {
            printf("\nStatus: EXCELLENT\n");
            printf("Tip: Your spending is under control.\n");
        }
        else if (percentage < 80) {
            printf("\nStatus: GOOD\n");
            printf("Tip: Keep checking your expenses regularly.\n");
        }
        else if (percentage <= 100) {
            printf("\nStatus: CAUTION\n");
            printf("Tip: Avoid unnecessary purchases.\n");
        }
        else {
            printf("\nStatus: OVER BUDGET\n");
            printf("Tip: Reduce optional expenses immediately.\n");
        }

        highest = highestCategory();

        printf("\nHighest Spending Category: %s\n",
               categoryNames[highest]);

        printf("\nPERSONALIZED SUGGESTION:\n");

        switch (highest) {
            case 0:
                printf("Food spending is highest.\n");
                printf("Try homemade meals or affordable canteen food.\n");
                break;

            case 1:
                printf("Travel spending is highest.\n");
                printf("Try shared rides or public transport.\n");
                break;

            case 2:
                printf("Books spending is highest.\n");
                printf("Use the college library when possible.\n");
                break;

            case 3:
                printf("Entertainment spending is highest.\n");
                printf("Reduce unnecessary subscriptions and outings.\n");
                break;
        }
    }

    printf("\nEnter number of days remaining in month: ");

    if (!readNumber(&daysLeft) ||
        daysLeft < 1 || daysLeft > 31) {
        printf("Invalid days! Enter a value from 1 to 31.\n");
        return;
    }

    if (remaining > 0) {
        dailyLimit = remaining / daysLeft;

        printf("\nSuggested Daily Spending Limit: Rs. %.2f\n",
               dailyLimit);
        printf("Try to stay within this amount each day.\n");
    }
    else {
        printf("\nNo budget remaining for this month.\n");
        printf("Avoid additional non-essential expenses.\n");
    }
}

/* Main function */
int main() {
    int choice;

    printf("====================================\n");
    printf("     CAMPUSSPEND - EXPENSE TRACKER\n");
    printf("          UPES | BATCH 24\n");
    printf("====================================\n");

    setBudget();

    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Add Expense\n");
        printf("2. View Expense History\n");
        printf("3. Monthly Expense Summary\n");
        printf("4. Smart Spending Advisor\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");

        if (!readNumber(&choice)) {
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
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
