#include <clang/AST/AST.h>

#include "oclint/Rule.h"
#include "oclint/RuleSet.h"

class UselessParenthesesRule : public Rule<UselessParenthesesRule>
{
private:
    static RuleSet rules;

    void addParenExprToViolation(Expr *expr)
    {
        if (expr && isa<ParenExpr>(expr))
        {
            addViolation(expr, this);
        }
    }

public:
    virtual const string name() const
    {
        return "useless parentheses";
    }

    virtual const int priority() const
    {
        return 3;
    }

    bool VisitIfStmt(IfStmt *ifStmt)
    {
        addParenExprToViolation(ifStmt->getCond());

        return true;
    }

    bool VisitReturnStmt(ReturnStmt *returnStmt)
    {
        addParenExprToViolation(returnStmt->getRetValue());

        return true;
    }

    bool VisitVarDecl(VarDecl *varDecl)
    {
        addParenExprToViolation(varDecl->getInit());

        return true;
    }
};

RuleSet UselessParenthesesRule::rules(new UselessParenthesesRule());