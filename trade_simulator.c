#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "trade_simulator.h"
#include "company_database.h"

static void print_company_list(void)
{
    int loc_i_ind;

    printf("+------------------------+----------------------------------------+\n");
    for(loc_i_ind = 0; loc_i_ind < s_i_database_size; loc_i_ind++)
    {
        printf("|Company name            |%-40s|\n",   database[loc_i_ind].s_company_name);
        printf("|Ticker symbol           |%-40s|\n",   database[loc_i_ind].s_tick_symbol);
        printf("|Market capital          |%-40.3f|\n", database[loc_i_ind].f_market_capital);
        printf("|Outstanding shares      |%-40ld|\n",  database[loc_i_ind].ul_outstanding_shares);
        printf("|Last FY profit          |%-40.3f|\n", database[loc_i_ind].f_past_profit);
        printf("|Last FY revenue         |%-40.3f|\n", database[loc_i_ind].f_past_revenue);
        printf("|Previous opening value  |%-40.3f|\n", database[loc_i_ind].f_prev_open_value);
        printf("|Previous closing value  |%-40.3f|\n", database[loc_i_ind].f_prev_close_value);
        printf("+------------------------+----------------------------------------+\n");
    }

    return;
}

static int check_valid_tick_symbol(char *a_s_tick_symbol)
{
    int loc_i_check_status;
    int loc_i_index;

    loc_i_check_status = 1;

    for(loc_i_index = 0; loc_i_index < s_i_database_size; loc_i_index++)
    {
        loc_i_check_status = strcmp(database[loc_i_index].s_tick_symbol, a_s_tick_symbol);

        if(loc_i_check_status == 0)
        {
            stc_i_company_ind = loc_i_index;
            break;
        }
    }

    return loc_i_check_status;
}

static int check_valid_purchase(unsigned long a_ul_num_shares)
{
    if ((database[stc_i_company_ind].f_purchase_value * a_ul_num_shares) <= stc_f_trading_acc_balance)
    {
        return 0;
    }

    return 1;
}

static void buy_shares(unsigned long a_ul_shares_to_buy)
{
    /* Update the number of shares holding */
    stc_ul_shares_holding += a_ul_shares_to_buy;

    /* Update the balance amount in the trading account after the purchse */
    stc_f_trading_acc_balance = stc_f_trading_acc_balance - (a_ul_shares_to_buy * database[stc_i_company_ind].f_purchase_value);

    printf("Number of shares holding: %ld\tBalance amount: %.3f\n\n", stc_ul_shares_holding, stc_f_trading_acc_balance);

    return;
}

static void generate_new_purchase_values(double *a_a_purchase_values)
{
    int loc_i_loop;
    double loc_f_random_value;

    srand(time(0));

    loc_f_random_value = (double) (rand() % 21) - 10;
    a_a_purchase_values[0] = database[stc_i_company_ind].f_purchase_value + loc_f_random_value;

    for (loc_i_loop = 1; loc_i_loop < 5; loc_i_loop++)
    {
        loc_f_random_value = (double) (rand() % 21) - 10;
        a_a_purchase_values[loc_i_loop] = a_a_purchase_values[loc_i_loop-1] + loc_f_random_value;
    }
}

int main(void)
{
    char loc_s_tick_symbol[15] = "";
    int loc_i_comp_select_flag;
    int loc_i_valid_buy_flag;
    unsigned long loc_ul_shares_to_buy;
    double loc_a_purchase_values[5] = {0, 1, 2, 3, 4};
    int loc_i_loop;

    loc_i_comp_select_flag = 0;
    loc_i_valid_buy_flag = 1;
    loc_ul_shares_to_buy = 0;
    loc_i_loop = 0;

    /* Print the list of all companies available for trading */
    print_company_list();

    /* Setup a trading account with 10000 as available amount */
    stc_f_trading_acc_balance = 10000;

    /* Read the ticker symbol input from the user, till a valid ticker symbol is input */
    do
    {
        printf("Enter the ticker symbol of the company to trade (in uppercase, as shown in the table above): ");
        scanf("%[^\n]%*c", loc_s_tick_symbol);
        printf("%s\n", loc_s_tick_symbol);

        loc_i_comp_select_flag = check_valid_tick_symbol(loc_s_tick_symbol);

        if(loc_i_comp_select_flag != 0)
        {
            printf("ERR: Invalid ticker symbol, please try again\n\n");
        }
    } while (loc_i_comp_select_flag);
    
    printf("Available balance for purchasing is: %.3f\n\n", stc_f_trading_acc_balance);

    do
    {
        printf("How many shares to purchase?\n");
        scanf("%ld", &loc_ul_shares_to_buy);

        loc_i_valid_buy_flag = check_valid_purchase(loc_ul_shares_to_buy);

        if(loc_i_valid_buy_flag != 0)
        {
            printf("ERR: Insufficient funds, please try again\n\n");
        }
    } while (loc_i_valid_buy_flag);

    buy_shares(loc_ul_shares_to_buy);

    generate_new_purchase_values(loc_a_purchase_values);

    printf("Buy values changing: \n\n");
    for (loc_i_loop = 0; loc_i_loop < 5; loc_i_loop++)
    {
        printf("%.3f\n", loc_a_purchase_values[loc_i_loop]);
    }

    return 0;
}