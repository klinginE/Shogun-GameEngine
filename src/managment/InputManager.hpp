#pragma once

#include <map>
#include <functional>

/* TODO: We need a way to handle mouse input as well as keyboard input
 *       Currently, this implementation handles only keyboard input.
 */

namespace sg {

    class InputManager {
        
        std::map<int, std::function<void()>> actions;
        std::set<int> keys;
    
        public:
            InputManager();
    
            void addAction(int key, std::function<void()> callback);
            void clearAction(int key);
            std::function<void()> getAction(int key);
            void processInput();
    
    };
    
}
