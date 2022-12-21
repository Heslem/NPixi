#pragma once
#include <any>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../../sfml.h"

class GameObject;
struct Collidable
    {
    friend class QuadTree;
public:
    virtual const sf::FloatRect getCollision() const = 0;
    virtual GameObject& getGameObject() = 0;

    virtual void onCollision(GameObject& collision) = 0;
    Collidable();
private:
    QuadTree *qt = nullptr;
    Collidable(const Collidable&) = delete;
};

class QuadTree : public sf::Drawable {
public:
    QuadTree(const sf::FloatRect& _bound, unsigned _capacity, unsigned _maxLevel);
    QuadTree(const QuadTree&);
    QuadTree();

    bool insert(Collidable *obj);
    bool remove(Collidable *obj);
    bool update(Collidable *obj);
    std::vector<Collidable*> &getObjectsInBound_unchecked(const sf::FloatRect& bound);
    unsigned totalChildren() const noexcept;
    unsigned totalObjects() const noexcept;
    void clear() noexcept;
    QuadTree *getLeaf(const sf::FloatRect& bound);
    

    ~QuadTree();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool      isLeaf = true;
    unsigned  level  = 0;
    unsigned  capacity;
    unsigned  maxLevel;
    sf::FloatRect bounds;
    QuadTree* parent = nullptr;
    QuadTree* children[4] = { nullptr, nullptr, nullptr, nullptr };
    std::vector<Collidable*> objects, foundObjects;

    sf::RectangleShape	     shape;

    void subdivide();
    void discardEmptyBuckets();
    inline QuadTree *getChild(const sf::FloatRect& bound) const noexcept;
};
