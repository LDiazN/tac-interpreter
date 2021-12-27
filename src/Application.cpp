// Local includes 
#include "Application.hpp"

// C++ includes 
#include <sstream>
#include <fstream>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"                  /* Black */
#define RED     "\033[31m"                  /* Red */
#define GREEN   "\033[32m"                  /* Green */
#define YELLOW  "\033[33m"                  /* Yellow */
#define BLUE    "\033[34m"                  /* Blue */
#define MAGENTA "\033[35m"                  /* Magenta */
#define CYAN    "\033[36m"                  /* Cyan */
#define WHITE   "\033[37m"                  /* White */
#define BOLDBLACK   "\033[1m\033[30m"       /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"       /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"       /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"       /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"       /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"       /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"       /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"       /* Bold White */

namespace TacRunner
{
    int Config::from_arg_list(const std::vector<std::string> &args, Config& out_config)
    {
        // Check number of arguments
        uint min_expected_args = 2; // program name + filename
        if (args.size() < min_expected_args)
        {
            App::error("Not enough arguments");
            return FAIL;
        }

        // First argument will be the file to parse 
        auto filename = args[1];

        // Check if not exists
        std::ifstream my_file(filename.c_str());
        if (!my_file.good())
        {
            // Print error and quit
            std::stringstream error_msg;
            error_msg << "File: '" << filename << "' is not valid";
            App::error(error_msg.str());
            return FAIL;
        }

        // This is the only field for now
        out_config.filename = filename;
        return SUCCESS;
    }

    App App::from_arg_list(const std::vector<std::string> &args)
    {
        Config config;
        auto result = Config::from_arg_list(args, config);

        if (result == FAIL)
            throw "Couldn't run tac machine";

        return App(config);
    }

    void App::log_msg(std::string msg)
    {
        cout << App::name() << ": " << msg << std::endl;
    }

    void App::log_err(std::string msg)
    {
        cerr << App::name() << ": " << msg << std::endl;
    }

    void App::error(std::string msg)
    {
        stringstream ss;
        ss << RED << "[ERROR] " << msg << RESET;
        App::log_err(ss.str());
    }

    void App::warning(std::string msg)
    {
        stringstream ss;
        ss << YELLOW << "[WARNING] " << msg << RESET;
        App::log_err(ss.str());
    }

    void App::success(std::string msg)
    {
        stringstream ss;
        ss << GREEN << "[WARNING] " << msg << RESET;
        App::log_msg(ss.str());
    }
    
    void App::trace(std::string msg)
    {
        stringstream ss;
        ss << "[TRACE] " << msg;
        App::log_msg(ss.str());
    }
    
}