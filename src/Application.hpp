/**
 * @file TacRunner.hpp
 * @brief App driver definition
 * 
 */
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

// C++ includes
#include <string>
#include <vector>
#include <algorithm>

// Local includes
#include "TacReader.hpp"
#include "TacMachine.hpp"

// Defines & constants
#define APP_NAME "tac-runner"
#define SUCCESS 0 
#define FAIL 1

namespace TacRunner
{

    /**
     * @brief Possible actions for the app
     * 
     */
    enum class Action
    {
        SHOW_HELP,
        RUN_TAC_CODE
    };

    /**
     * @brief Data required for the application to know how to behave
     * 
     */
    struct Config
    {
        std::string filename; // file where to parse the tac code
        std::vector<Action> actions; // Which actions should the application perform
        bool quiet;
        bool callstack;
        bool memory;
        bool registers;
        bool labels;
        uint show_bytes_of_stack_mem; 
        // By default, the stack will only print memory that is active, 
        // provide this field (!= 0) to make it print the specified ammount of bytes

        /**
         * @brief Create a config from a list of arguments,
         *        the one specified by the user with the command line 
         *        arguments. First argument 
         * 
         * @param args Argument list as specified for the command line arguments
         * @param out_config where to store the generated config
         * 
         * @return 0 on sucess, 1 on fail parsing
         */
        static int from_arg_list(const std::vector<std::string> &args, Config& out_config);

        inline bool has_action(Action action) const { return std::find(actions.begin(), actions.end(), action) != actions.end(); }
    };

    class App 
    {
        public:
            /**
             * @brief Construct a new App object from configuration
             * 
             * @param config 
             */
            App(Config config) : m_config(config)
            { }

            /**
             * @brief Try to create an App from an argument list, 
             *        throw an error if it wasn't possible
             * @param args Argument list to parse args from 
             * @return valid App object created from arguments
             */
            static App from_arg_list(const std::vector<std::string> &args);

            /**
             * @brief Run an application with the provided configuration, 
             *        return a status on finish. 0 for success, 1 for failure.
             * @return int 0 for success, 1 for failure.
             */
            uint run();

            /**
             * @brief Get the help message for the CLI
             * 
             * @return std::string Help message
             */
            std::string help_msg() const;

            /**
             * @brief Application name
             * 
             * @return std::string name of the application
             */
            static inline  std::string name() { return APP_NAME; }

            /**
             * @brief Property with the help flag 
             * 
             * @return std::string 
             */
            static inline std::string help_flag() { return "--help"; }

            /**
             * @brief Property with quiet flag
             * 
             * @return std::string 
             */
            static inline std::string quiet() { return "--quiet"; }

            /**
             * @brief Property with callstack flag
             * 
             * @return std::string 
             */
            static inline std::string callstack()   { return "--callstack"; }

            /**
             * @brief Property with memory flag
             * 
             * @return std::string 
             */
            static inline std::string memory()      { return "--memory"; }

            /**
             * @brief Property with registers flag
             * 
             * @return std::string 
             */
            static inline std::string registers()   { return "--registers"; }

            /**
             * @brief Property with labels flag
             * 
             * @return std::string 
             */
            static inline std::string labels()      { return "--labels"; }

            /**
             * @brief Use this flag to ask the interpreter to show the specified 
             * amount of bytes from the stack, active or not.
             * 
             * @return std::string 
             */
            static inline std::string stack_mem_bytes()      { return "--stack-mem-bytes"; }

            /**
             * @brief Los a message to stderr formated as error
             * 
             * @param msg message to log
             */
            static void error(std::string msg);

            /**
             * @brief Los a message to stderr formated as warning
             * 
             * @param msg message to log
             */
            static void warning(std::string msg);

            /**
             * @brief Los a message to stdout formated as success
             * 
             * @param msg message to log
             */
            static void success(std::string msg);

            /**
             * @brief Los a message to stdout formated as a regular message
             * 
             * @param msg message to log
             */
            static void trace(std::string msg);

            /**
             * @brief log a message for the program currently running, not the app
             * 
             * @param msg message to log
             */
            static void program_log(std::string msg);

        private:
            /**
             * @brief Los a message to stdout
             * 
             * @param msg message to log
             */
            static void log_msg(std::string msg);

            /**
             * @brief Los a message to stderr
             * 
             * @param msg message to log
             */
            static void log_err(std::string msg);

            /**
             * @brief Run a tac code
             * 
             */
            void run_tac_code();

            /**
             * @brief Run a single tac instruction
             * 
             * @param tac Instruction to run
             * @return uint success status, 0 on success, 1 on failure
             */
            uint run_tac_inst(Tac tac);

        private:
            Config m_config;
            TacReader m_tac_reader;
    };
}

#endif // APPLICATION_HPP