//--------------------------------------------------------------------------------------------------
/**
 *  Implementation of the WatchdogTimeout class.
 *
 *  Copyright (C) Sierra Wireless, Inc. Use of this work is subject to license.
 */
//--------------------------------------------------------------------------------------------------

#include "mkTools.h"

namespace model
{


//--------------------------------------------------------------------------------------------------
/**
 * Assignment operator.  Validates and stores watchdogTimeout value
 *
 * @throws mk::Exception_t if timeout is not -1, 0 or positive.
 */
//--------------------------------------------------------------------------------------------------
void WatchdogTimeout_t::operator =
(
    int32_t milliseconds
)
//--------------------------------------------------------------------------------------------------
{
    if (milliseconds >= -1)
    {
        value = milliseconds;
        isSet = true;
    }
    else
    {
        throw mk::Exception_t("watchdogTimeout must be a positive number of milliseconds,"
                                   " 0 (expire immediately) or -1 (never expire).");
    }
}


//--------------------------------------------------------------------------------------------------
/**
 * Assignment operator.  Validates and stores the timeout value for 'never' timeout (-1)
 *
 * @throws mk::Exception_t if string is not 'never'
 */
//--------------------------------------------------------------------------------------------------
void WatchdogTimeout_t::operator =
(
    const std::string &never
)
//--------------------------------------------------------------------------------------------------
{
    if (never != "never")
    {
        throw mk::Exception_t("WatchdogTimeout must be a positive number of milliseconds or"
                                   " 'never'.");
    }
    else
    {
        // -1 is the numerical value of the define LE_WDOG_TIMEOUT_NEVER used in le_wdog to disable
        // timing out.
        value = -1;
        isSet = true;
    }
}


//--------------------------------------------------------------------------------------------------
/**
 * Fetches the timeout value.
 *
 * @throw   mk::Exception_t if the timeout is not set.
 *
 * @return  A non-negative timeout in milliseconds or -1 if the watchdog is disabled.
 */
//--------------------------------------------------------------------------------------------------
int32_t WatchdogTimeout_t::Get
(
    void
)
const
//--------------------------------------------------------------------------------------------------
{
    if (!isSet)
    {
        throw mk::Exception_t("Fetching watchdog timeout that has not been set.");
    }

    return value;
}





} // namespace model