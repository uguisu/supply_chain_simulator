// Copyright (c) 2023
// All rights reserved.
//
// Author: xin he
//
#ifndef SCS_CONFIG_HPP
#define SCS_CONFIG_HPP

namespace scs { namespace entity {

class ScsConfig
{
    public:
        /**
         * setNodeAmount
         * @param node_amount total node amount
         */
        void setNodeAmount(const int16_t &node_amount);
        /**
         * getNodeAmount
         */
        int16_t getNodeAmount();

        ~ScsConfig();
    private:
        /** node_amount */
        int16_t node_amount = 1;
};

}}

#endif /* SCS_CONFIG_HPP */
