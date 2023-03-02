#ifndef __TRADE_SIMULATOR_H__
#define __TRADE_SIMULATOR_H__

/* Information elements for a company */
typedef struct
{
    char            s_company_name[50];     /* Company name                 */
    char            s_tick_symbol[15];      /* Ticker symbol                */
    unsigned long   ul_outstanding_shares;  /* Number of outstanding shares */
    double          f_market_capital;       /* Market capital               */
    double          f_past_revenue;         /* Revenue                      */
    double          f_past_profit;          /* Profit                       */
    float           f_prev_open_value;      /* Previous open value          */
    float           f_prev_close_value;     /* Previous close value         */
    float           f_purchase_value;       /* Purchase value               */
}comapny_info;

/* Trading account balance */
static double stc_f_trading_acc_balance;

/* Shares holding */
static unsigned long stc_ul_shares_holding;

/* Index of selected company */
static int stc_i_company_ind;

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Print all the company information that has been stored in the database
 * 
 */
static void print_company_list(void);

/*
 * Input: Ticker symbol
 *
 * Output: Status of ticker symbol search in database
 * 
 * Description:
 * Check if the ticker symbol input by the user is found in the company database
 * 
 */
static int check_valid_tick_symbol(char *par_s_tick_symbol);

/*
 * Input: Number of shares to purchase
 *
 * Output: Status of the purchase
 * 
 * Description:
 * Check if the balance in the account and current price of shares meet the
 * requirements to buy the number of shares
 */
static int check_valid_purchase(unsigned long par_ul_num_shares);

/*
 * Input: Number of shares to purchase
 *
 * Output: NA
 * 
 * Description:
 * Buy the number of shares specified and deduct the available funds accordingly
 */
static void buy_shares(unsigned long par_ul_shares_to_buy);

/*
 * Input: NA
 *
 * Output: An array with new purchase values
 * 
 * Description:
 * Generate five new purchase values using a random values in the range [-10, 10]
 * and adding that to the previous purchase values
 */
static void generate_new_purchase_values(double *par_a_purchase_values);

#endif /* __TRADE_SIMULATOR_H__ */