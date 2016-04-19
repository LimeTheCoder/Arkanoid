#include "resourse_manager.h"


namespace ResourceLocations {
    std::string MenuFont = "Media/fonts/menu_font.otf";
    std::string MenuTexture = "Media/images/main_background.jpg";

    std::string ScoresFont = "Media/fonts/menu_font.otf";
    std::string ScoresTexture = "Media/images/main_background.jpg";

    std::string HighscoresData = "Media/highscores.dat";
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

    switch (code) {
        case Textures::Code::MenuBackground:
            if(textures.find(code) == textures.end()) { // not in map
                texture = new sf::Texture();
                texture->loadFromFile(ResourceLocations::MenuTexture);
                textures[code] = texture;
            }
            else
                texture = textures[code];
            break;

        case Textures::Code::GameBackground:
            break;

        default:
            break;
    }

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

    switch (code) {
        case Fonts::Code::Menu:
            if(fonts.find(code) == fonts.end()) { // not in map
                font = new sf::Font();
                font->loadFromFile(ResourceLocations::MenuFont);
                fonts[code] = font;
            }
            else
                font = fonts[code];
            break;

        case Fonts::Code::Score:
            break;

        default:
            break;
    }

    return font;
}