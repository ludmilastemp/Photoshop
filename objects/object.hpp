#ifndef STL_OBJECT
#define STL_OBJECT

#include "../GrLib/GrLibCtx.hpp"
#include "../vectors/vectorDec.hpp"

// enum IsDraw 

class Object
{
public:
    bool isDraw;

    sf::Sprite  sprite;
    sf::Texture texture;
    sf::Image   image;

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

class Scene
{
public:
    bool isDraw;
    std::vector <Object*> objects;
    std::vector <Scene*>  scenes;

    Scene () : isDraw(1) {}

    void addObject (Object& object)
    {
        objects.push_back(&object);
    }

    void addScene (Scene& scene)
    {
        scenes.push_back(&scene);
    }

    void setIsDraw (bool newDraw)
    {
        isDraw = newDraw;
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->isDraw = newDraw;
        }

        for (int i = 0; i < scenes.size(); i++)
        {
            scenes[i]->isDraw = newDraw;
        }
    }

    void draw (GraphicsCtx& ctx)
    {
        if (!isDraw) 
        {
            return;
        }
        
        for (int i = 0; i < objects.size(); i++)
        {
            ctx.window.draw (objects[i]->sprite);
        }

        for (int i = 0; i < scenes.size(); i++)
        {
            scenes[i]->draw (ctx);
        }
    }
};


#endif /* STL_OBJECT */