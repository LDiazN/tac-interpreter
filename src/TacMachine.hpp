/**
 * @file TacMachine.hpp
 * @brief  Virtual machine definition running the tac
 * 
 */

#ifndef TACMACHINE_HPP
#define TACMACHINE_HPP

// Local includes 
#include "Tac.hpp"

// C++ includes
#include <array>

namespace TacRunner 
{
    /**
     * @brief This class represents a Tac machine capable of running tac code
     *        as if it was a special processor for tac code
     * 
     */
    class TacMachine
    {

        private:
        Program m_program;
        /**
         * @brief Variable indicating at which point in the program is this program
         * 
         */
        uint    m_program_counter;
        

    };
}

#endif