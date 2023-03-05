#ifndef __COMPANY_DATABASE_H__
#define __COMPANY_DATABASE_H__

#include "trade_simulator.h"

/* Multiple company informations useful for selecting to trade */
company_info database[] =
{
    /* Company 1 */
    {
        .s_company_name         = "Ford Motor Co",
        .s_tick_symbol          = "F",
        .ul_outstanding_shares  = 4000000000,
        .f_market_capital       = 48073000000,
        .f_past_revenue         = 158057000000,
        .f_past_profit          = -1981000000,
        .f_prev_open_value      = 11.98,
        .f_prev_close_value     = 12.06,
        .f_purchase_value       = 12.06
    },
    /* Company 2 */
    {
        .s_company_name         = "Tata Motors Ltd",
        .s_tick_symbol          = "TATAMOTORS",
        .ul_outstanding_shares  = 764866397,
        .f_market_capital       = 1510000000000,
        .f_past_revenue         = 2765766900,
        .f_past_profit          = 857534200,
        .f_prev_open_value      = 419,
        .f_prev_close_value     = 1417.95,
        .f_purchase_value       = 1417.95 
    },
    /* Company 3 */
    {
        .s_company_name         = "Mahindra And Mahindra Ltd",
        .s_tick_symbol          = "M&M",
        .ul_outstanding_shares  = 1240000000,
        .f_market_capital       = 1579000000000,
        .f_past_revenue         = 892570500,
        .f_past_profit          = 372780800,
        .f_prev_open_value      = 1263.70,
        .f_prev_close_value     = 1275.35,
        .f_purchase_value       = 1275.35
    },
    /* Company 4 */
    {
        .s_company_name         = "Maruti Suzuki India Ltd",
        .s_tick_symbol          = "MARUTI",
        .ul_outstanding_shares  = 302071492,
        .f_market_capital       = 2605000000000,
        .f_past_revenue         = 851688000,
        .f_past_profit          = 157375000,
        .f_prev_open_value      = 8650,
        .f_prev_close_value     = 8654,
        .f_purchase_value       = 8654
    },
    /* Company 5 */
    {
        .s_company_name         = "Eicher Motors Ltd",
        .s_tick_symbol          = "EICHERMOT",
        .ul_outstanding_shares  = 273473606,
        .f_market_capital       = 849420000000,
        .f_past_revenue         = 101270700,
        .f_past_profit          = 39728300,
        .f_prev_open_value      = 3132,
        .f_prev_close_value     = 3105,
        .f_purchase_value       = 3105
    }
};

static int s_i_database_size = (int)(sizeof(database) / sizeof(company_info));

#endif /* __COMPANY_DATABASE_H__ */