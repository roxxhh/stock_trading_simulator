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

static void buy_shares(unsigned long a_ul_shares_to_buy)
{
    /* Update the number of shares holding */
    stc_ul_shares_holding += a_ul_shares_to_buy;

    /* Update the balance amount in the trading account after the purchse */
    stc_f_trading_acc_balance = stc_f_trading_acc_balance - (a_ul_shares_to_buy * database[stc_i_company_ind].f_purchase_value);

    printf("\nNumber of shares holding: %ld\tBalance amount: %.3f\n\n", stc_ul_shares_holding, stc_f_trading_acc_balance);

    return;
}

static void sell_shares(unsigned long par_ul_shares_to_sell)
{
    /* Update the number of shares holding */
    stc_ul_shares_holding -= par_ul_shares_to_sell;

    /* Update the balance amount in the trading account after the sale */
    stc_f_trading_acc_balance = stc_f_trading_acc_balance + (par_ul_shares_to_sell * database[stc_i_company_ind].f_purchase_value);

    printf("\nNumber of shares holding: %ld\tBalance amount: %.3f\n\n", stc_ul_shares_holding, stc_f_trading_acc_balance);

    return;
}

static void make_valid_purchase(void)
{
    unsigned long   loc_ul_shares_to_buy;
    int             loc_i_valid_buy_flag;

    loc_ul_shares_to_buy    = 0;
    loc_i_valid_buy_flag    = 1;

    /* Read the number of shares to buy from the user, till a valid number of shares is input */
    do
    {
        printf("\nHow many shares to purchase?\n");
        scanf("%ld", &loc_ul_shares_to_buy);

        if ((database[stc_i_company_ind].f_purchase_value * loc_ul_shares_to_buy) <= stc_f_trading_acc_balance)
        {
            loc_i_valid_buy_flag = 0;
        }

        if(loc_i_valid_buy_flag != 0)
        {
            printf("ERR: Insufficient funds, please try again\n\n");
        }
    } while (loc_i_valid_buy_flag);

    /* Buy the number of shares and update the trading account balance */
    buy_shares(loc_ul_shares_to_buy);

    return;
}

static void make_valid_sale(void)
{
    unsigned long   loc_ul_shares_to_sell;
    int             loc_i_valid_sale_flag;

    loc_ul_shares_to_sell   = 0;
    loc_i_valid_sale_flag   = 1;

    /* Read the number of shares to sell from the user, till a valid number of shares is input */
    do
    {
        printf("\nHow many shares to sell?\n");
        scanf("%ld", &loc_ul_shares_to_sell);

        if (loc_ul_shares_to_sell <= stc_ul_shares_holding)
        {
            loc_i_valid_sale_flag = 0;
        }

        if (loc_i_valid_sale_flag != 0)
        {
            printf("ERR: Invalid number of shares to sell, you are not holding %ld number of shares\n\n", loc_ul_shares_to_sell);
        }
    } while (loc_i_valid_sale_flag);

    /* Sell the number of shares and update the trading account balance */
    sell_shares(loc_ul_shares_to_sell);

    return;
}

static void generate_new_purchase_values(double *a_a_purchase_values)
{
    int loc_i_loop;
    double loc_f_random_value;

    srand(time(0));

    for (loc_i_loop = 0; loc_i_loop < 5; loc_i_loop++)
    {
        loc_f_random_value = (((float)rand()/(float)RAND_MAX) * 21) - 10.0f;
        a_a_purchase_values[loc_i_loop] = database[stc_i_company_ind].f_purchase_value + loc_f_random_value;

        if (a_a_purchase_values[loc_i_loop] < 0)
        {
            a_a_purchase_values[loc_i_loop] = 1.0f;
        }
    }
}

static void simulate_new_share_prices(void)
{
    double          loc_a_purchase_values[5] = {0};
    int             loc_i_loop;

    loc_i_loop  = 0;

    /* Generate five new purchase values using random number generator */
    generate_new_purchase_values(loc_a_purchase_values);

    printf("+-----------------------------+\n");
    printf("|Change in company share price|\n");
    printf("+-----------------------------+\n");
    for (loc_i_loop = 0; loc_i_loop < 5; loc_i_loop++)
    {
        printf("|%-29.3f|\n", loc_a_purchase_values[loc_i_loop]);
    }
    printf("+-----------------------------+\n\n");

    /* Update the purchase value with the latest random number */
    database[stc_i_company_ind].f_purchase_value = loc_a_purchase_values[4];

    return;
}

int main(void)
{
    char            loc_s_tick_symbol[15] = "";
    int             loc_i_comp_select_flag;
    int             loc_i_trade_choice;
    int             loc_i_trade_count;
    int             loc_i_trade_invalid;

    loc_i_comp_select_flag  = 0;
    loc_i_trade_choice      = 0;
    loc_i_trade_count       = 0;
    loc_i_trade_invalid    = 0;

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
    
    /* Print the available balance in the trading account */
    printf("\nAvailable balance for purchasing is: %.3f\n\n", stc_f_trading_acc_balance);

    make_valid_purchase();

    simulate_new_share_prices();

    printf("The new purchase value of \"%s\" is: %.3f\n", database[stc_i_company_ind].s_company_name, database[stc_i_company_ind].f_purchase_value);
    printf("The number of shares holding is: %ld\n", stc_ul_shares_holding);
    printf("The current trading account balance is: %.3f\n\n", stc_f_trading_acc_balance);

    do
    {
        printf("\nNumber of trade decisions pending: %d\n", (NUMBER_OF_TRADING_DECISIONS - loc_i_trade_count));
        printf("Make a choice from the following options:\n");
        printf("1. Buy more shares\n");
        printf("2. Sell shares\n");
        printf("3. Keep the shares\n");
        scanf("%d", &loc_i_trade_choice);

        switch(loc_i_trade_choice)
        {
            case 1:
                make_valid_purchase();
                break;

            case 2:
                make_valid_sale();
                break;

            case 3:
                break;
            
            default:
                printf("ERR: Invalid trade choice\n\n");
                loc_i_trade_invalid = 1;
                break;
        }

        if (loc_i_trade_invalid)
        {
            loc_i_trade_invalid = 0;

            continue;
        }

        loc_i_trade_invalid = 0;

        if (loc_i_trade_count != NUMBER_OF_TRADING_DECISIONS - 1)
        {
            simulate_new_share_prices();

            printf("The new purchase value of \"%s\" is: %.3f\n", database[stc_i_company_ind].s_company_name, database[stc_i_company_ind].f_purchase_value);
            printf("The number of shares holding is: %ld\n", stc_ul_shares_holding);
            printf("The current trading account balance is: %.3f\n\n", stc_f_trading_acc_balance);
        }

        loc_i_trade_count++;
    } while (loc_i_trade_count < NUMBER_OF_TRADING_DECISIONS);

    printf("Trading decisions complete. Selling all shares\n");

    /* Sell all the shares holding and update the trading account balance */
    sell_shares(stc_ul_shares_holding);

    return 0;
}