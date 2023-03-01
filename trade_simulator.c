#include <stdio.h>
#include <string.h>

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
            break;
        }
    }

    return loc_i_check_status;
}

int main(void)
{
    char loc_s_tick_symbol[15] = "";
    int loc_i_comp_select_flag;

    loc_i_comp_select_flag = 0;

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
    

    return 0;
}