#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>


namespace Textures {
    enum Code {
        MenuBackground,
        GameBackground
    };

    namespace Location {
        std::string MenuBg = "Media/images/menu_background.jpg";
    }
}


namespace Fonts {
    enum Code {
        Menu,
        Score
    };

    namespace Location {
        std::string Menu = "Media/fonts/menu_font.otf";
    }
}


class ResourseManager {

};

class TextureManager {
public:
    ~TextureManager();

    sf::Texture* getTexture(Textures::Code code);
private:
    std::map<Textures::Code, sf::Texture*> textures;
};


class FontManager {
public:
    ~FontManager();

    sf::Font* getFont(Fonts::Code code);
private:
    std::map<Fonts::Code, sf::Font*> fonts;
};


#endif
