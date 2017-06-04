# Arkanoid
Arkanoid game based on design patterns
## Patterns
### Facade
Facade pattern hides the complexities of the system and provides an interface to the client using which the client can access the system.
* Class diagram

![screen](../master/screens/facade.png)

* Code sample

<b>resource_manager.h</b>

```C++
class ResourseManager {
public:
    sf::Texture* getTexture(Textures::Code code);
    sf::Font* getFont(Fonts::Code code);

private:
    TextureManager texture_manager;
    FontManager font_manager;
};
```

<b>resource_manager.cpp</b>
```C++
sf::Texture* ResourseManager::getTexture(Textures::Code code) {
    return texture_manager.getTexture(code);
}

sf::Font * ResourseManager::getFont(Fonts::Code code) {
    return font_manager.getFont(code);
}
```
### Flyweight
Flyweight pattern tries to reuse already existing similar kind objects by storing them and creates new object when no matching object is found.

* Code sample

```C++
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
```
### Command
Command pattern encapsulates a request or as an object, thereby letting you parametrize clients with different requests, queue or log requests, and support undoable operations.

* Class diagram

![screen](../master/screens/command.png)

* Code sample

<b>command.h</b>
```C++
class Command {
public:
    virtual void Execute(Paddle &paddle) = 0;
};


class MoveLeftCommand : public Command {
public:
    void Execute(Paddle &paddle) {
        paddle.moveLeft();
    }
};


class MoveRightCommand : public Command {
public:
    void Execute(Paddle &paddle) {
        paddle.moveRight();
    }
};


class DefaultCommand : public Command {
public:
    void Execute(Paddle &paddle) {
        paddle.stayAtPlace();
    }
};
```
<b>play_state.cpp</b>
```C++
    if(sf::Keyboard::isKeyPressed(BUTTON_LEFT) && paddle.getLeft() > 0)
        current_command = button_left;
    else if(sf::Keyboard::isKeyPressed(BUTTON_RIGHT) &&
            paddle.getRight() < WINDOW_WIDTH)
        current_command = button_right;
    else
        current_command = default_command;
```

## State pattern
In State pattern, we create objects which represent various states and a context object whose behavior varies as its state object changes.

* Class diagram

![screen](../master/screens/state.png)

* Code sample

<b>game_state.cpp</b>
```C++
class GameState {
public:
    GameState(Game *state_holder) : game(state_holder) {}

    virtual void render() = 0;
    virtual void update() = 0;
    virtual void processEvents() = 0;

protected:
    Game *game;
};
```
<b>game.cpp</b>
```C++
GameState* Game::getState() const {
    if(screens.empty()) return nullptr;
    return screens.top();
}

void Game::addState(States::Code state) {
    switch (state) {
        case States::Code::Game:
            screens.push(new PlayState(this));
            break;
        case States::Code::Menu:
            screens.push(new MenuState(this));
            break;
        case States::Code::Pause:
            break;
        case States::Code::Scores:
            screens.push(new ScoresState(this));
            break;
        case States::Code::EndGame:
            screens.push(new EndState(this));
        default:
            break;
    }
}

void Game::changeState(States::Code state) {
    if(!screens.empty())
        popState();
    addState(state);
}

void Game::popState() {
    delete screens.top();
    screens.pop();
}
```
### Observer pattern
Observer pattern is used when there is one-to-many relationship between objects such as if one object is modified, its depenedent objects are to be notified automatically.
* Class diagram

![screen](../master/screens/observer.png)

* Code sample

<b>ball.cpp</b>
```C++
void Ball::attach(IObserver *observer) {
    observers.push_back(observer);
}

void Ball::detach(IObserver *observer) {
    observers.remove(observer);
}

void Ball::notifyObservers() {
    for(IObserver *iter : observers) {
        iter->handleBallPosChange(*this);
    }
}
```

### Prototype
Prototype pattern refers to creating duplicate object while keeping performance in mind.

* Class diagram

![screen](../master/screens/prototype.png)

* Code sample

```C++
Block* BlockSpawner::getBlock(int type) const {
    Block *out = nullptr;

    switch (type) {
        case 3:
            out = strongBlock->clone();
            break;
        case 2:
            out = mediumBlock->clone();
            break;
        case 1:
            out = easyBlock->clone();
            break;
        default:
            break;
    }
```

## Screens
### Main menu
![screen](../master/screens/menu.png)

### Highscores
![screen](../master/screens/scores.png)

### Game process
![screen](../master/screens/game.png)

### Game over
![screen](../master/screens/over.png)
