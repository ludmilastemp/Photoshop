#ifndef STL_BUTTON
#define STL_BUTTON

#include <cassert>
#include "object.hpp"
#include "../MVC/Managers/actions.hpp"
#include "../vectors/vectorDec.hpp"

class Button : public Object
{
public:
    VectorDec size;
    VectorDec corner;

    std::vector <Action*> actions; 

    Button (const VectorDec& size, const VectorDec& corner, Action& action);
    Button (const VectorDec& size, const VectorDec& corner, Action& action, const char* png);
    Button (const VectorDec& size, const VectorDec& corner, const char* png);
    
    void addAction (Action* action)
    {
        assert (action);
        actions.push_back (action);
    }

    virtual void setIsDraw (bool newDraw) override;
};

bool IsButton (const VectorDec& pos, const Button& button);

#endif /* STL_BUTTON */