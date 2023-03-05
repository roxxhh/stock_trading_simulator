#ifndef __TRADE_SIMULATOR_H__
#define __TRADE_SIMULATOR_H__

#define NUMBER_OF_TRADING_DECISIONS 5

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
 * Output: NA
 * 
 * Description:
 * Buy the number of shares specified and deduct the available funds accordingly
 */
static void buy_shares(unsigned long par_ul_shares_to_buy);

/*
 * Input: Number of shares to sell
 *
 * Output: NA
 * 
 * Description:
 * Sell the number of shares specified and credit the available funds accordingly
 */
static void sell_shares(unsigned long par_ul_shares_to_sell);

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Read the number of shares to purchase and buy them
 */
static void make_valid_purchase(void);

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Read the number of shares to sell and sell them
 */
static void make_valid_sale(void);

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

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Update the purchase value after simulation
 */
static void simulate_new_share_prices(void);

#endif /* __TRADE_SIMULATOR_H__ */