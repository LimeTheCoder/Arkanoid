#include "resourse_manager.h"


namespace ResourceLocations {
    std::string MenuFont = "Media/fonts/menu_font.otf";
    std::string MenuTexture = "Media/images/main_background.jpg";

    std::string ScoresFont = "Media/fonts/menu_font.otf";
    std::string ScoresTexture = "Media/images/main_background.jpg";

    std::string HighscoresData = "Media/highscores.dat";

    std::string GameTexture = "Media/images/game_background.jpg";
}


/** Primary manager implementation **/

sf::Texture* ResourseManager::getTexture(Textures::Code code) {
    return texture_manager.getTexture(code);
}

sf::Font * ResourseManager::getFont(Fonts::Code code) {
    return font_manager.getFont(code);
}


/** Texture manager implementation **/

TextureManager::~TextureManager() {
    std::map<Textures::Code, sf::Texture*>::iterator it;
    for (it = textures.begin(); it != textures.end(); ++it)
        delete it->second;
}

sf::Texture *TextureManager::getTexture(Textures::Code code) {
    sf::Texture *texture = nullptr;

    if(textures.find(code) != textures.end())
        return textures[code];

    texture = new sf::Texture();

    switch (code) {
        case Textures::Code::MenuBackground:
            texture->loadFromFile(ResourceLocations::MenuTexture);
            break;

        case Textures::Code::ScoreBackground:
            texture->loadFromFile(ResourceLocations::ScoresTexture);
            break;

        case Textures::Code::GameBackground:
            texture->loadFromFile(ResourceLocations::GameTexture);
            break;

        default:
            break;
    }

    textures[code] = texture;

    return texture;
}


/** Font manager implementation **/


FontManager::~FontManager() {
    std::map<Fonts::Code, sf::Font*>::iterator it;
    for (it = fonts.begin(); it != fonts.end(); ++it)
        delete it->second;
}

sf::Font *FontManager::getFont(Fonts::Code code) {
    sf::Font *font = nullptr;

    if(fonts.find(code) != fonts.end())
        return fonts[code];

    font = new sf::Font();

    switch (code) {
        case Fonts::Code::Menu:
            font->loadFromFile(ResourceLocations::MenuFont);
            break;

        case Fonts::Code::Score:
            font->loadFromFile(ResourceLocations::ScoresFont);
            break;

        default:
            break;
    }

    fonts[code] = font;

    return font;
}