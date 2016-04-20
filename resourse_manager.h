#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

namespace Textures {
    enum Code {
        MenuBackground,
        ScoreBackground
    };
}

namespace Fonts {
    enum Code {
        Menu,
        Score
    };

}

namespace ResourceLocations {
    extern std::string MenuFont;
    extern std::string MenuTexture;

    extern std::string ScoresFont;
    extern std::string ScoresTexture;

    extern std::string HighscoresData;
}


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


class ResourseManager {
public:
    sf::Texture* getTexture(Textures::Code code);
    sf::Font* getFont(Fonts::Code code);

private:
    TextureManager texture_manager;
    FontManager font_manager;
};


#endif
