#ifndef STL_OBJECT
#define STL_OBJECT

#include "../GrLib/GrLibCtx.hpp"
#include "../vectors/vectorDec.hpp"

// enum IsDraw 

class Scene;

class Object
{
public:
    bool isDraw;

    sf::Sprite  sprite;
    sf::Texture texture;
    sf::Image   image;

    // Scene* scene;

    Object (const VectorDec& size, const VectorDec& corner)
        : isDraw(1), 
        sprite(), texture(), image()
    {
        texture.create (size.x, size.y);
        sprite.setTexture (texture);
        sprite.setPosition (corner.x, corner.y);
        image.create (size.x, size.y, sf::Color (0, 0, 0, 0));
        texture.update (image);
    }

    Object (const VectorDec& size, const VectorDec& corner, const char* png)
        : isDraw(1), 
        sprite(), texture(), image()
    {
        texture.create (size.x, size.y);
        sprite.setTexture (texture);
        sprite.setPosition (corner.x, corner.y);
        image.loadFromFile (png);
        texture.update (image);
    }

    virtual ~Object () = default; 
};

#endif /* STL_OBJECT */