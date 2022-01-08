// Local includes 
#include "Application.hpp"
#include "TacReader.hpp"
#include "Tac.hpp"
#include "TacMachine.hpp"

// C++ includes 
#include <sstream>
#include <fstream>
#include <algorithm>

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

    uint App::run()
    {
        // Show help if requested so
        if (m_config.has_action(Action::SHOW_HELP))
            std::cout << help_msg() << std::endl;
        
        // Run a tac code
        if (m_config.has_action(Action::RUN_TAC_CODE))
        {
            run_tac_code();
        }
        
        return SUCCESS;
    }

    void App::run_tac_code()
    {
        std::stringstream ss;
        // Read tac code from file
        Program tac_code;

        ss << "Parsing tac program from '" << m_config.filename << "'...";
        App::trace(ss.str());
        ss.clear();

        auto result = m_tac_reader.parse(m_config.filename, tac_code);

        // If couldn't parse, tell the user that this was an invalid tac file
        if (result == FAIL)
        {
            App::error("Invalid TAC code.");
            return;
        }

        App::success("TAC code successfully parsed.");

        // Try to run program 
        App::trace("Creating tac machine...");
        TacMachine machine(tac_code);

        // Start rogram
        App::trace("Starting program...");
        machine.run_tac_program();
        // vv TESTING AREA, DELETE LATER --------------------------------------------------------------------------------



        // ^^ TESTING AREA, DELETE LATER --------------------------------------------------------------------------------
        // Display summary 
        if (machine.status() == TacMachine::Status::ERROR)
        {
            stringstream ss;
            ss << "Program execution failed at line " << machine.program_counter();
            App::error(ss.str());

        }
        else if(machine.status() == TacMachine::Status::FINISHED)
            App::success("Program execution successful");

        if(!m_config.quiet)
        {
            App::trace("Resulting state summary: ");
            cout << machine.str(
                m_config.memory, 
                m_config.labels, 
                m_config.registers, 
                m_config.callstack) << endl;
        }
    }

    std::string App::help_msg() const
    {
        std::stringstream ss;
        ss << "Tac Runner is a simple virtual machine capable of running tac code." << endl;
        ss << "\tUsage:" << endl;
        ss << "\t\ttac-runner <name_of_file> [flags]" << endl;
        ss << "\tWhere:" << endl;
        ss << "\t\t<name_of_file> : is the name of the file to be run, should be a valid tac code." << endl;
        ss << "\t\t [flags] : Configuration flags, part of the following: " << endl;
        ss << "\t\t\t--help : Show this help" << endl;

        return ss.str();
    }

    int Config::from_arg_list(const std::vector<std::string> &args, Config& out_config)
    {
        // Store actions here
        std::vector<Action> actions;

        // Check number of arguments
        uint min_expected_args = 2; // program name + filename
        if (args.size() < min_expected_args)
        {
            App::error("Not enough arguments");
            return FAIL;
        }

        // First argument will be the file to parse 
        auto filename = args[1];

        // check if it's just the help flag
        if (filename == App::help_flag())
        {
            actions.push_back(Action::SHOW_HELP);
            // This is the only field for now
            out_config.filename = "";
            out_config.actions = actions;
            return SUCCESS;
        }

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

        // Check for flags
        // Check help flag
        auto help_flag = App::help_flag();
        if(std::find(args.begin(), args.end(), help_flag) != args.end())
            actions.push_back(Action::SHOW_HELP);

        // Check if should be quiet
        bool quiet = std::find(args.begin(), args.end(), App::quiet()) != args.end();

        // Check if should show callstack
        bool callstack = std::find(args.begin(), args.end(), App::callstack()) != args.end();

        // Check if should show memory
        bool memory = std::find(args.begin(), args.end(), App::memory()) != args.end();

        // Check if should show registers
        bool registers = std::find(args.begin(), args.end(), App::registers()) != args.end();

        // Check if should show labels
        bool labels = std::find(args.begin(), args.end(), App::labels()) != args.end();

        // Check if stack memory flag is provided
        uint stack_mem_bytes;
        for(size_t i = 0; i < args.size(); i++)
        {
            auto const& arg = args[i];
            if(arg != App::stack_mem_bytes())
                continue;
            
            // Check for enough args
            if (i == args.size() - 1)
            {
                stringstream ss;
                ss << "Missing amount of bytes arg in " << App::stack_mem_bytes() << " flag";
                App::error(ss.str());
                return FAIL;
            }

            // Check if following arg is a valid int
            try
            {
                stack_mem_bytes = stoi(args[i+1]);
            }
            catch(std::invalid_argument&)
            {
                stringstream ss;
                ss << "Invalid amount of bytes for flag " << App::stack_mem_bytes() << ". Provided: " << args[i+1];
                App::error(ss.str());
            }
        
        }

        // Tell the app to run some code
        actions.push_back(Action::RUN_TAC_CODE);

        // This is the only field for now
        out_config.filename = filename;
        out_config.actions.swap(actions);
        out_config.quiet        = quiet;
        out_config.callstack    = callstack;
        out_config.memory       = memory;
        out_config.registers    = registers;
        out_config.labels       = labels;
        out_config.show_bytes_of_stack_mem = stack_mem_bytes;

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
        ss << GREEN << "[SUCCESS] " << msg << RESET;
        App::log_msg(ss.str());
    }
    
    void App::trace(std::string msg)
    {
        stringstream ss;
        ss << "[TRACE] " << msg;
        App::log_msg(ss.str());
    }

    void App::program_log(std::string msg)
    {
        cout << "program: " << msg << std::endl;;
    }
    
}