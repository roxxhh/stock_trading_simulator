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
}comapny_info;

/* Trading account balance */
static double stc_f_trading_acc_balance;

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

#endif /* __TRADE_SIMULATOR_H__ */