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

// Local includes
#include "TacReader.hpp"

// Defines & constants
#define APP_NAME "tac-runner"
#define SUCCESS 0 
#define FAIL 1

namespace TacRunner
{
    /**
     * @brief Data required for the application to know how to behave
     * 
     */
    struct Config
    {
        std::string filename;

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
             * @brief Get the help message for the CLI
             * 
             * @return std::string Help message
             */
            std::string help_msg();

            /**
             * @brief Application name
             * 
             * @return std::string name of the application
             */
            static inline  std::string name() { return APP_NAME; }

            // Allow config to use logging functions
            friend class Config;
            
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
            void trace(std::string msg);

        private:
            Config m_config;
            TacReader m_tac_reader;
    };
}

#endif // APPLICATION_HPP