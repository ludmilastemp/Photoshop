#ifndef STL_OBJECT
#define STL_OBJECT

#include "../GrLib/GrLibCtx.hpp"
#include "../GrLib/color.hpp"
#include "../vectors/vectorDec.hpp"
#include <iostream>

class Object
{
private:
    bool isDraw;
    sf::Sprite  sprite;
    sf::Texture texture;
    sf::Image   image;

public:
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

    void            setIsDrawSimple (bool newDraw)        { isDraw = newDraw; }
    virtual void    setIsDraw       (bool newDraw)        { setIsDrawSimple (newDraw); }
    bool            getIsDraw       ()              const { return isDraw; }
    VectorDecUint32 getPosition     ()                    { return {(uint32_t)sprite.getPosition().x, (uint32_t)sprite.getPosition().y}; }

    void setPixel (int x, int y, Color color_)
    {
        if (0 <= x && x < image.getSize().x && 
            0 <= y && y < image.getSize().y)
        {
            Color color = color_ * 255;
            sf::Color c = {(uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a};
            image.setPixel (x, y, c);
        }
    }

    Color getPixel (int x, int y) const
    {
        sf::Color c = image.getPixel (x, y);
        return Color (c.r, c.g, c.b, c.a) / 255;
    }

    VectorDecUint32 getSize () const { return {image.getSize().x, image.getSize().y};}
    void            update () { texture.update (image); }
    void            setScale (double scale, int x, int y) 
    { 
        sf::Rect<int> rect {x, y, (int)(1.0 * kWidthCanvas / scale), (int)(1.0 * kHeightCanvas / scale)};
        sprite.setTexture     (texture);
        sprite.setTextureRect (rect);
        sprite.setScale (scale, scale);
    }
    void            draw (GraphicsCtx& ctx) const { ctx.window.draw (sprite); }

};

class Scene
{
private:
    bool isDraw;
    std::vector <Scene*> scenes;

public:
    std::vector <Object*> objects;
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
            objects[i]->setIsDraw (newDraw);
        }

        for (int i = 0; i < scenes.size(); i++)
        {
            scenes[i]->setIsDraw (newDraw);
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
            objects[i]->draw (ctx);
        }

        for (int i = 0; i < scenes.size(); i++)
        {
            scenes[i]->draw (ctx);
        }
    }

    void activate ()
    {
        setIsDraw (true);
    }

    void deactivate ()
    {
        setIsDraw (false);
    }

    bool getIsDraw () { return isDraw; }
};


#endif /* STL_OBJECT */