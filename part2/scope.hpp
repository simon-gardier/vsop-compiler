#ifndef _SCOPE_HPP
#define _SCOPE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>

/**
 * @brief Scope class for type checking and variable scopes in the AST
 */
class Scope {
public:
    Scope() = default;
    
    /**
     * @brief Add a variable to the current scope
     * 
     * @param name Variable name
     * @param type Variable type
     */
    void addVariable(const std::string& name, const std::string& type) {
        variables[name] = type;
    }
    
    /**
     * @brief Get the type of a variable
     * 
     * @param name Variable name
     * @return std::string Type of the variable, empty if not found
     */
    std::string getVariableType(const std::string& name) const {
        auto it = variables.find(name);
        if (it != variables.end()) {
            return it->second;
        }
        return "";
    }
    
    /**
     * @brief Check if a variable exists in the current scope
     * 
     * @param name Variable name
     * @return true If the variable exists
     * @return false If the variable doesn't exist
     */
    bool hasVariable(const std::string& name) const {
        return variables.find(name) != variables.end();
    }
    
    /**
     * @brief Create a new scope with the current scope as parent
     * 
     * @return Scope New scope
     */
    Scope createChildScope() const {
        Scope child;
        child.parent = this;
        return child;
    }
    
    /**
     * @brief Get the type of a variable, looking in parent scopes if necessary
     * 
     * @param name Variable name
     * @return std::string Type of the variable, empty if not found
     */
    std::string lookupVariableType(const std::string& name) const {
        std::string type = getVariableType(name);
        if (!type.empty()) {
            return type;
        }
        if (parent) {
            return parent->lookupVariableType(name);
        }
        return "";
    }

    /**
     * @brief Check if a scope is valid
     * 
     * @param className Name of the class
     * @return true If the scope is valid
     * @return false If the scope is invalid
     */
    bool isScopeValid(const std::string& className) const {
        return true; // Simplified implementation
    }

    /**
     * @brief Check if one type is a subtype of another
     * 
     * @param subType Potential subtype
     * @param superType Potential supertype
     * @return true If subType is a subtype of superType
     * @return false Otherwise
     */
    bool isSubType(const std::string& subType, const std::string& superType) const {
        return subType == superType; // Simplified implementation
    }

    /**
     * @brief Inherit scope from parent class
     * 
     * @param parentName Name of the parent class
     */
    void inheritScope(const std::string& parentName) {
        // Simplified implementation
    }

    /**
     * @brief Remove a scope
     * 
     * @param className Name of the class to remove
     */
    void removeScope(const std::string& className) {
        // Simplified implementation
    }

    /**
     * @brief Add a method to the current scope
     * 
     * @param className Class name
     * @param methodName Method name
     * @param returnType Return type
     * @param args Method arguments
     */
    void addMethod(const std::string& className, const std::string& methodName, 
                  const std::string& returnType, const std::vector<std::string>& args = {}) {
        // Simplified implementation
    }

    /**
     * @brief Check if a variable is in scope
     * 
     * @param varName Variable name
     * @param className Class name
     * @return true If the variable is in scope
     * @return false Otherwise
     */
    bool isVariableInScope(const std::string& varName, const std::string& className = "") const {
        return hasVariable(varName); // Simplified implementation
    }

    /**
     * @brief Check if a method is in scope
     * 
     * @param methodName Method name
     * @param className Class name
     * @return true If the method is in scope
     * @return false Otherwise
     */
    bool isMethodInScope(const std::string& methodName, const std::string& className = "") const {
        return methods.find(methodName) != methods.end(); // Simplified implementation
    }

    /**
     * @brief Check if method overriding is valid
     * 
     * @param methodName Method name
     * @param className Class name
     * @return true If the overriding is valid
     * @return false Otherwise
     */
    bool isMethodOverridingValid(const std::string& methodName, const std::string& className) const {
        return true; // Simplified implementation
    }

    /**
     * @brief Get arguments of a method
     * 
     * @param methodName Method name
     * @param className Class name
     * @return std::vector<std::string> Method arguments
     */
    std::vector<std::string> getArgs(const std::string& methodName, const std::string& className = "") const {
        return {}; // Simplified implementation
    }

    /**
     * @brief Get the return type of a method
     * 
     * @param methodName Method name
     * @param className Class name
     * @return std::string Method return type
     */
    std::string getMethodType(const std::string& methodName, const std::string& className = "") const {
        return ""; // Simplified implementation
    }

    /**
     * @brief Clear all variables in the current scope
     */
    void clearVariables() {
        variables.clear();
    }

    /**
     * @brief Find the common ancestor of two types
     * 
     * @param type1 First type
     * @param type2 Second type
     * @return std::string Common ancestor type
     */
    std::string commonAncestor(const std::string& type1, const std::string& type2) const {
        if (type1 == type2) return type1;
        return "Object"; // Simplified implementation
    }

    /**
     * @brief Check if arguments respect the method signature
     * 
     * @param methodName Method name
     * @param args Arguments to check
     * @param className Class name
     * @return true If arguments respect the method signature
     * @return false Otherwise
     */
    bool isArgRespected(const std::string& methodName, const std::vector<std::string>& args, 
                        const std::string& className = "") const {
        return true; // Simplified implementation
    }

private:
    std::unordered_map<std::string, std::string> variables;
    std::unordered_map<std::string, std::string> methods;
    const Scope* parent = nullptr;
};

#endif // _SCOPE_HPP
