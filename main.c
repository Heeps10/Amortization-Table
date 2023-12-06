#include <stdio.h>
#include <math.h>

//function that asks and returns the number of years on the loan
double fun_years(int min, int max){
    double years;

    printf("Enter number of years (2-40) for this loan or 0 to quit: \n");
    scanf("%lf", &years);

    if (years == 0){
        return 0;
    }
    else if (years < min || years > max){
        printf("You entered a value outside of the parameters. Please start over.");
        return 0;
    }
    return years;
}

//function that asks and returns the interest rate of the loan
double fun_int(int min, int max){
    double intRate;

    printf("Enter the interest rate (1-20) for this loan or 0 to quit: \n");
    scanf("%lf", &intRate);

    if (intRate == 0){
        return 0;
    }
    else if (intRate < min || intRate > max){
        printf("You entered a value outside of the parameters. Please start over.");
        return 0;
    }
    return intRate;
}

//function that asks and returns the total loan amount
double fun_loan(int min, int max){
    double loanTotal;

    printf("Enter the total amount for this loan (5000 - 2000000) or 0 to quit: \n");
    scanf("%lf", &loanTotal);

    if (loanTotal == 0){
        return 0;
    }
    else if (loanTotal < min || loanTotal > max){
        printf("You entered a value outside of the parameters. Please start over.");
        return 0;
    }
    return loanTotal;
}

//princ_balance_fun prototype
double princ_balance(double, double);

//monthly_int_pay_fun prototype
double monthly_int(double, double);

//adjusted_princ_pay prototype
double principal(double, double);

//monthly_pay prototype
double monthly_pay(double, double, double);


int main(void) {
    int const min_years = 2;
    int const max_years = 40;
    int const min_int = 1;
    int const max_int = 20;
    int const min_loan = 5000;
    int const max_loan = 2000000;


    int years = fun_years(min_years, max_years);

    if (years == 0){
        return 0;
    }
    //numPayments
    int numPayments = years * 12;

    //intRate
    int intRate = fun_int(min_int, max_int);

    if (intRate == 0){
        return 0;
    }

    double per_int_rate = (intRate/100.0) / 12.0;

    //loanTotal
    double loanTotal = fun_loan(min_loan, max_loan);

    if (loanTotal == 0){
        return 0;
    }

    //fixed_pay
    double fixed_pay = monthly_pay(per_int_rate, numPayments, loanTotal);

    double balance = loanTotal;
    double monthlyInterest = per_int_rate;

    double interestTotal = 0;
    double paymentTotal = 0;
    double principalPayed = 0;

    //loop that iterates through the numPayments and prints out an amortization table
    int n = numPayments;
    for (int i = 1; i < n+1; i++){
        monthlyInterest = monthly_int(per_int_rate, balance);

        double payment = principal(fixed_pay, monthlyInterest);

        balance = princ_balance(balance, payment);

        printf("|  %.3d  |  %.2lf  |  %.2lf  |  %.2lf\n", i, monthlyInterest, payment, balance);

        numPayments = numPayments-1;

        interestTotal = interestTotal + monthlyInterest;
        principalPayed = principalPayed + payment;
    }
    paymentTotal = interestTotal + principalPayed;

    printf("Total Cost:      $%.2lf\n", paymentTotal);
    printf("Total Interest:  $%.2lf\n", interestTotal);
    printf("Principal Payed: $%.2lf\n", principalPayed);



    return 0;
}

//function that finds the adjusted monthly interest
double monthly_int(double per_int_rate, double balance){

    double interest = per_int_rate * balance;

    return interest;
}

//function that finds the adjusted principal payment
double principal(double fixed_pay, double monthlyInterest){

    double result = fixed_pay - monthlyInterest;

    return result;
}

//function that finds the adjusted principal balance
double princ_balance(double balance, double payment){

    balance = balance - payment;

    return balance;
}

//function that finds the fixed monthly pay
double monthly_pay(double per_int_rate, double numPayments, double loanTotal){

    //p= a ( (r(1+r)^n) / ((1+r)^n – 1) ) a = loan, r = pmrate, n = numPay
    double fixed_pay1 = per_int_rate * pow(1+per_int_rate, numPayments);
    double fixed_pay2 = pow(1+per_int_rate, numPayments) - 1;

    double fixed_pay = loanTotal * (fixed_pay1/fixed_pay2);

    return fixed_pay;
}
