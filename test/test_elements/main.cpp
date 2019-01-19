#include<Shogun/Elements/AnimatedSprite.hpp>
#include<Shogun/Management/GameLoop.hpp>
#include<Shogun/Management/GameState.hpp>
#include<Shogun/Management/StateManager.hpp>
#include<Shogun/Management/GameWindow.hpp>
#include<Shogun/Management/GameWorld.hpp>
#include<Shogun/Elements/Entity.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include"TestEntityState.hpp"
#include"TestAnimationState.hpp"

void testAnimatedSprite()
{
    //test initilization
    sg::AnimatedSprite as0 = sg::AnimatedSprite();
    std::cout << "TESTING initilization" << std::endl;
    std::cout << "Adress of sprite: " << &as0 << std::endl;
    std::cout << "Number of frames: " << as0.getNumOfFrames() << std::endl;
    std::cout << "Invalid bound: " << as0.getFrameBound(10) << std::endl;
    std::cout << "Invalid Rect: " << as0.getFrameRect(10) << std::endl;
    std::cout << "Frame Delay: " << as0.getFrameDelay().asSeconds() << std::endl;
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //test set frame delay
    as0.setFrameDelay(sf::seconds(10.0f));
    std::cout << "Frame Delay: " << as0.getFrameDelay().asSeconds() << std::endl;
    std::cout << "Updateing after 3 seconds while not playing and no frames" << std::endl;
    as0.update(sf::seconds(3.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    std::cout << "Updateing after 3 seconds while playing and no frames" << std::endl;
    as0.start();
    as0.update(sf::seconds(3.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //testing adding a frame
    sf::IntRect frameRect0 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds0 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    std::cout << "New Frame index:  " << as0.addFrame(frameRect0, frameBounds0) << std::endl;
    std::cout << "Number of frames: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Outside chane to frameRect0 top testing get FrameRect
    frameRect0.top = 2;
    std::cout << "Geting frame rect:" << std::endl;
    std::cout << "    left:   " << as0.getFrameRect(0)->left << std::endl;
    std::cout << "    top:    " << as0.getFrameRect(0)->top << std::endl;
    std::cout << "    width:  " << as0.getFrameRect(0)->width << std::endl;
    std::cout << "    height: " << as0.getFrameRect(0)->height << std::endl;
    std::cout << std::endl;

    //test get frame Bound
    const sf::Transformable *bound0 =  as0.getFrameBound(0);
    std::cout << "Addresses match: " << (dynamic_cast<void *>(&frameBounds0) == dynamic_cast<const void *>(bound0)) << std::endl;
    std::cout << std::endl;

    //test remove invalid frame
    std::cout << "Removing invalid frame" << std::endl;
    std::pair<sf::IntRect *, sf::Transformable *> removeFramePair = as0.removeFrame(10);
    std::cout << "removeFramePair.first:  " << removeFramePair.first << std::endl;
    std::cout << "removeFramePair.second: " << removeFramePair.second << std::endl;
    std::cout << std::endl;

    //test remove valid frame
    std::pair<sf::IntRect *, sf::Transformable *> removePair = as0.removeFrame(0);
    std::cout << "remove rect:   " << removePair.first << std::endl;
    std::cout << "remove bounds: " << removePair.second << std::endl;
    std::cout << "rect addresses match:   " << (&frameRect0 == removePair.first) << std::endl;
    std::cout << "bounds addresses match: " << (dynamic_cast<void *>(&frameBounds0) == dynamic_cast<void *>(removePair.second)) << std::endl;
    std::cout << std::endl;

    //Test update while playing with one frame
    as0.addFrame(*removePair.first, *removePair.second);
    std::cout << "Updateing after 3 seconds while playing and one frame" << std::endl;
    as0.update(sf::seconds(3.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //Test update while playing with one frame
    std::cout << "Updateing after 22 seconds while playing and one frame" << std::endl;
    as0.update(sf::seconds(22.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    std::cout << "Adding 4 more frames" << std::endl;
    sf::IntRect frameRect1 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds1 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect1, frameBounds1);
    sf::IntRect frameRect2 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds2 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect2, frameBounds2);
    sf::IntRect frameRect3 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds3 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect3, frameBounds3);
    sf::IntRect frameRect4 = sf::IntRect(0, 0, 10, 20);
    sf::RectangleShape frameBounds4 = sf::RectangleShape(sf::Vector2f(10.0f, 20.0f));
    as0.addFrame(frameRect4, frameBounds4);
    std::cout << "Number of frame: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Test update while playing with five frames
    std::cout << "Updateing after 22 seconds while playing and two frame" << std::endl;
    as0.update(sf::seconds(22.0f));
    std::cout << "Frame Index: " << as0.getFrameIndex() << std::endl;
    std::cout << "Time Past:   " << as0.getTimePast().asSeconds() << std::endl;
    std::cout << "Is Playng:   " << as0.getIsPlaying() << std::endl;
    std::cout << std::endl;

    //Test transformations 5 frames
    std::cout << "Seting origin to 2.0f, 2.0f" << std::endl;
    as0.setOrigin(2.0f, 2.0f);
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    as0.setOrigin(sf::Vector2f(2.0f, 2.0f));
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    std::cout << "Seting position to 10.0f, 12.0f" << std::endl;
    as0.setPosition(10.0f, 12.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    as0.setPosition(sf::Vector2f(10.0f, 12.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by 2.0f, 2.0f" << std::endl;
    as0.move(2.0f, 2.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by -2.0f, -2.0f" << std::endl;
    as0.move(sf::Vector2f(-2.0f, -2.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Set rotation to 15.0f" << std::endl;
    as0.setRotation(15.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "Rotating by 30.0f" << std::endl;
    as0.rotate(30.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "set scale by 4.0f, 1.5f" << std::endl;
    as0.setScale(4.0f, 1.5f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    as0.setScale(sf::Vector2f(4.0f, 1.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 0.5f, 2.0f" << std::endl;
    as0.scale(0.5f, 2.0f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 2.0f, 0.5f" << std::endl;
    as0.scale(sf::Vector2f(2.0f, 0.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << std::endl;

    std::cout << "removing all but one frame and setting bounds0 back to 0" << std::endl;
    removePair = as0.removeFrame(0);
    as0.removeFrame(0);
    as0.removeFrame(0);
    as0.removeFrame(0);
    sf::Transformable *t = removePair.second;
    t->setOrigin(0.0f, 0.0f);
    t->setPosition(0.0f, 0.0f);
    t->setRotation(0.0f);
    t->setScale(1.0f, 1.0f);
    std::cout << "Frame count: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Test transformations 1 frames
    std::cout << "Seting origin to 2.0f, 2.0f" << std::endl;
    as0.setOrigin(2.0f, 2.0f);
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    as0.setOrigin(sf::Vector2f(2.0f, 2.0f));
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    std::cout << "Seting position to 10.0f, 12.0f" << std::endl;
    as0.setPosition(10.0f, 12.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    as0.setPosition(sf::Vector2f(10.0f, 12.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by 2.0f, 2.0f" << std::endl;
    as0.move(2.0f, 2.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by -2.0f, -2.0f" << std::endl;
    as0.move(sf::Vector2f(-2.0f, -2.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Set rotation to 15.0f" << std::endl;
    as0.setRotation(15.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "Rotating by 30.0f" << std::endl;
    as0.rotate(30.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "set scale by 4.0f, 1.5f" << std::endl;
    as0.setScale(4.0f, 1.5f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    as0.setScale(sf::Vector2f(4.0f, 1.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 0.5f, 2.0f" << std::endl;
    as0.scale(0.5f, 2.0f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 2.0f, 0.5f" << std::endl;
    as0.scale(sf::Vector2f(2.0f, 0.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << std::endl;

    std::cout << "removing last frame" << std::endl;
    as0.removeFrame(0);
    std::cout << "Number of Frames: " << as0.getNumOfFrames() << std::endl;
    std::cout << std::endl;

    //Test transformations 0 frames
    std::cout << "Seting origin to 2.0f, 2.0f" << std::endl;
    as0.setOrigin(2.0f, 2.0f);
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    as0.setOrigin(sf::Vector2f(2.0f, 2.0f));
    std::cout << "as0 origin.x: " << as0.getOrigin().x << " y: " << as0.getOrigin().y << std::endl;
    std::cout << "bound0 origin.x: " << bound0->getOrigin().x << " y: " << bound0->getOrigin().y << std::endl;
    std::cout << "Seting position to 10.0f, 12.0f" << std::endl;
    as0.setPosition(10.0f, 12.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    as0.setPosition(sf::Vector2f(10.0f, 12.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by 2.0f, 2.0f" << std::endl;
    as0.move(2.0f, 2.0f);
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Moving by -2.0f, -2.0f" << std::endl;
    as0.move(sf::Vector2f(-2.0f, -2.0f));
    std::cout << "as0 position.x: " << as0.getPosition().x << " y: " << as0.getPosition().y << std::endl;
    std::cout << "bound0 position.x: " << bound0->getPosition().x << " y: " << bound0->getPosition().y << std::endl;
    std::cout << "Set rotation to 15.0f" << std::endl;
    as0.setRotation(15.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "Rotating by 30.0f" << std::endl;
    as0.rotate(30.0f);
    std::cout << "as0 rotation: " << as0.getRotation() << std::endl;
    std::cout << "bound0 rotation: " << bound0->getRotation() << std::endl;
    std::cout << "set scale by 4.0f, 1.5f" << std::endl;
    as0.setScale(4.0f, 1.5f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    as0.setScale(sf::Vector2f(4.0f, 1.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 0.5f, 2.0f" << std::endl;
    as0.scale(0.5f, 2.0f);
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << "Scaling by 2.0f, 0.5f" << std::endl;
    as0.scale(sf::Vector2f(2.0f, 0.5f));
    std::cout << "as0 scale.x: " << as0.getScale().x << " y: " << as0.getScale().y << std::endl;
    std::cout << "bound0 scale.x: " << bound0->getScale().x << " y: " << bound0->getScale().y << std::endl;
    std::cout << std::endl;
}

void testEntity()
{
    // Initialize gameloop
    sg::GameLoop::inst().init(sf::Vector2u(600, 600),
                              sf::String("Test Elements"));
    sg::GameLoop::inst().getRenderWindow().setFramerateLimit(60);

    TestEntityState tes;
    TestAnimationState tas;
    sg::StateManager::inst().pushState(tes);
    sg::StateManager::inst().pushState(tas);

    // Start gameloop
    sg::GameLoop::inst().start();
}

int main()
{

    testAnimatedSprite();
    testEntity();

    return 0;
}
