#ifndef __TRADE_SIMULATOR_H__
#define __TRADE_SIMULATOR_H__

typedef struct
{
    char            s_company_name[50];
    char            s_tick_symbol[15];
    unsigned long   ul_outstanding_shares;
    double          f_market_capital;
    double          f_past_revenue;
    double          f_past_profit;
    float           f_prev_open_value;
    float           f_prev_close_value;
}comapny_info;

static double trading_acc_balance;

static void print_company_list(void);
static int check_valid_tick_symbol(char *par_s_tick_symbol);

#endif /* __TRADE_SIMULATOR_H__ */