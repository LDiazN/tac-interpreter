#ifndef TAC_H
#define TAC_H

// C++ includes
#include <variant>
#include <utility>
#include <string>
#include <vector>
#include <stdint.h>
#include <assert.h>

namespace TacRunner {

    /**
     * @brief Possible values for a tac instruction
     * 
     */
    enum class Instr
    {
        METASTATICV,
        METALABEL,
        METASTRING,
        ASSIGNW,
        ASSIGNB,
        ADD,
        SUB,
        MULT,
        DIV,
        MOD,
        MINUS,
        EQ,
        NEQ,
        LT,
        LEQ,
        GT,
        GEQ,
        GOTO,
        GOIF,
        GOIFNOT,
        MALLOC,
        MEMCPY,
        FREE,
        EXIT,
        RETURN,
        PARAM,
        CALL,
        PRINTI,
        PRINTF,
        PRINT,
        PRINTC,
        READI,
        READF,
        READ,
        READC,
        METAFUNBEGIN,
        METAFUNEND
    };

    std::string instr_to_str(Instr instr);

    /**
     * @brief Variable of a variable
     * 
     */
    struct Variable 
    {
        std::string name;
        int index;
        bool is_access;
    };

    /**
     * @brief Possible types of a value
     * 
     */
    using ValueType = std::variant<bool, char, int, float, Variable, std::string>;


    /**
     * @brief This class represents a possible argument for a tac instruction
     * 
     */
    class Value
    {
        public:
            /**
             * @brief Construct a new Value object
             * 
             * @param value actual value to store
             */
            Value(ValueType value) : m_actual_value(value) { }

            /**
             * @brief Construct a new Value object with a default int value of 0
             * 
             */
            Value() : Value(0) { }

            /**
             * @brief Tells if the stored variant is of type T
             * 
             * @tparam T Type  you want to check if the variant holds
             * @return true if is of the given value
             * @return false else 
             */
            template<typename T>
            inline bool is() const { return std::holds_alternative<T>(m_actual_value); }

            /**
             * @brief Get the value stored in the variant
             * 
             * @tparam T variant type you'll try to get
             * @return T value if it's actually of type T, exception otherwise
             */
            template<typename T>
            inline T get() const { return std::get<T>(m_actual_value); }

            /**
             * @brief Set the value of this type to the given one
             * 
             * @param value new value to store
             */
            inline void set(ValueType value) { m_actual_value = value; }

            /**
             * @brief String representation of this value
             * 
             * @return std::string String representation of this value
             */
            std::string str() const;

        private:
            ValueType m_actual_value;
    };

    /**
     * AST node. If you can call it AST at all...
     * It keeps function name and a list of arguments.
     */
    class Tac
    {
    public:
        Tac() { };
        Tac(Instr &inst);
        Tac(Instr &inst, const Value argument);
        Tac(Instr &inst, const Value argument1, const Value argument2);
        Tac(Instr &inst, const Value argument1, const Value argument2, const Value argument3);
        ~Tac();
        
        std::string str() const;
        inline Instr instr() const {return m_instr;}
        
    private:
        Instr m_instr;
        std::vector<Value> m_args;
    };

    using Program = std::vector<Tac>;
}

#endif // TAC_H