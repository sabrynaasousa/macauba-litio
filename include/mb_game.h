#ifndef MB_GAME_H
#define MB_GAME_H

#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>

#include "mb_level_factory.h"

using namespace ijengine;

namespace ijengine
{
    namespace game_event
    {
        const unsigned GAME_EVENT_JUMP =            1 << 4;
        const unsigned GAME_EVENT_DOWN_PRESSED =    1 << 5;
        const unsigned GAME_EVENT_DOWN_RELEASED =   1 << 6;
        const unsigned GAME_EVENT_MENU_SELECT =     1 << 7;
        const unsigned GAME_MOUSE_PRESSED =         1 << 8;
        const unsigned GAME_MOUSE_MOVEMENT =        1 << 9;
        const unsigned GAME_MOUSE_MOTION =          1 << 10;
        const unsigned GAME_EVENT_PUNCH =           1 << 11;
        const unsigned GAME_EVENT_UP_PRESSED =      1 << 12;
        const unsigned GAME_EVENT_UP_RELEASED =     1 << 13;
        const unsigned GAME_EVENT_LEFT_PRESSED =    1 << 14;
        const unsigned GAME_EVENT_LEFT_RELEASED =   1 << 15;
        const unsigned GAME_EVENT_RIGHT_PRESSED =   1 << 16;
        const unsigned GAME_EVENT_RIGHT_RELEASED =  1 << 17;
        const unsigned GAME_EVENT_ENTER =           1 << 18;
        const unsigned GAME_EVENT_DEBUG =           1 << 19;
        const unsigned GAME_MOUSE_RELEASED =        1 << 20;
    }
}

class MBGame {
    public:
        MBGame(const string& title, int w, int h);
        ~MBGame();

        int run(const string& level_id);

    private:
        class Translator : public EventsTranslator {
            bool translate(GameEvent& to, const MouseEvent& from){
                to.set_timestamp(from.timestamp());
                to.set_property<double>("x", from.x());
                to.set_property<double>("y", from.y());

                if (from.state() == MouseEvent::MOTION)
                    to.set_id(game_event::GAME_MOUSE_MOTION);
                else if (from.state() == MouseEvent::PRESSED)
                    to.set_id(game_event::GAME_MOUSE_PRESSED);
                else
                	to.set_id(game_event::GAME_MOUSE_RELEASED);

                return true;
            }

            bool translate(GameEvent& to, const SystemEvent& from){
                if(from.action() == SystemEvent::QUIT){
                    to.set_timestamp(from.timestamp());
                    to.set_id(game_event::QUIT);

                    return true;
                }

                return false;
            }


            virtual bool translate(GameEvent&, const JoystickEvent&){
                return false;
            }

            virtual bool translate(GameEvent& to, const KeyboardEvent& from){
                to.set_timestamp(from.timestamp());

                bool done = true;

                switch(from.key()){
                    case KeyboardEvent::SPACE:
                        if(from.state() == KeyboardEvent::PRESSED){
                            to.set_property<string>("jump", "space");
                            to.set_id(game_event::GAME_EVENT_JUMP);
                        }

                        break;

                    case KeyboardEvent::C:
                        to.set_property<string>("select", "c");
                        to.set_id(game_event::GAME_EVENT_MENU_SELECT);
                        break;

                    case KeyboardEvent::X:
                        to.set_property<string>("punch", "x");
                        to.set_id(game_event::GAME_EVENT_PUNCH);
                        break;

                    case KeyboardEvent::DOWN:
                        to.set_property<string>("slide", "down");

                        if(from.state() == KeyboardEvent::PRESSED)
                            to.set_id(game_event::GAME_EVENT_DOWN_PRESSED);
                        else if(from.state() == KeyboardEvent::RELEASED)
                            to.set_id(game_event::GAME_EVENT_DOWN_RELEASED);

                        break;

                    case KeyboardEvent::UP:
                        to.set_property<string>("slide", "up");

                        if(from.state() == KeyboardEvent::PRESSED)
                            to.set_id(game_event::GAME_EVENT_UP_PRESSED);
                        else if(from.state() == KeyboardEvent::RELEASED)
                            to.set_id(game_event::GAME_EVENT_UP_RELEASED);

                        break;

                    case KeyboardEvent::LEFT:
                        to.set_property<string>("slide", "left");

                        if(from.state() == KeyboardEvent::PRESSED)
                            to.set_id(game_event::GAME_EVENT_LEFT_PRESSED);
                        else if(from.state() == KeyboardEvent::RELEASED)
                            to.set_id(game_event::GAME_EVENT_LEFT_RELEASED);

                        break;

                    case KeyboardEvent::RIGHT:
                        to.set_property<string>("slide", "right");

                        if(from.state() == KeyboardEvent::PRESSED)
                            to.set_id(game_event::GAME_EVENT_RIGHT_PRESSED);
                        else if(from.state() == KeyboardEvent::RELEASED)
                            to.set_id(game_event::GAME_EVENT_RIGHT_RELEASED);

                        break;

                    case KeyboardEvent::RETURN:
                        to.set_property<string>("jump", "enter");
                        to.set_id(game_event::GAME_EVENT_ENTER);
                        break;

                    case KeyboardEvent::B:
                        to.set_property<string>("debug", "b");
                        to.set_id(game_event::GAME_EVENT_DEBUG);
                        break;

                    default:
                        done = false;
                }

                return done;
            }
        };

        Game m_game;
        Engine m_engine;
        Translator m_translator;
        MBLevelFactory m_level_factory;
};

#endif

