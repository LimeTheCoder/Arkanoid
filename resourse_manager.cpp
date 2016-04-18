#include "resourse_manager.h"

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
                texture->loadFromFile(Textures::Location::MenuBg);
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
                font->loadFromFile(Fonts::Location::Menu);
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