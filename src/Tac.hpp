#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <stdint.h>

namespace TacRunner {

    /**
     * AST node. If you can call it AST at all...
     * It keeps function name and a list of arguments.
     */
    class Tac
    {
    public:
        Tac(const std::string &name, const std::vector<uint64_t> arguments);
        Tac(const std::string &name);
        Tac();
        ~Tac();
        
        std::string str() const;
        std::string name() const;
        
    private:
        std::string m_name;
        std::vector<uint64_t> m_args;
    };

}

#endif // COMMAND_H