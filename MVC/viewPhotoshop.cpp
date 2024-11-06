#include "viewPhotoshop.hpp" 

/**************************************************************************/

ViewPhotoshop::ViewPhotoshop (Scene& init_main_scene)
    :main_scene(init_main_scene)
{}

/**************************************************************************/

void ViewPhotoshop::update (GraphicsCtx& ctx)
{
    CleanWindow (ctx);

    // sf::Sprite  sprite;
    // sf::Texture texture;
    // sf::Image   image;

    //     texture.create (600, 400);
    //     sprite.setTexture (texture);
    //     sprite.setPosition (100, 100);
    //     image.create (600, 400, sf::Color (0, 0, 0, 0));

    // for (int x = 0; x < 600; x++)
    // {
    //     for (int y = 0; y < 400; y++)
    //     {
    //         image.setPixel (x, y, sf::Color (1, 1, (x+y) %255, 1));
    //     }
    // }

    //     texture.update (image);

    // ctx.window.draw (sprite);

    main_scene.draw(ctx);

    DisplayWindow(ctx);    
}

/**************************************************************************/
