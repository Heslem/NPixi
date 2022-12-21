#include "QuadTree.h"

//** Collidable **//
Collidable::Collidable() {
};

//** QuadTree **//
QuadTree::QuadTree() : QuadTree({}, 0, 0) { }
QuadTree::QuadTree(const QuadTree &other) : QuadTree(other.bounds, other.capacity, other.maxLevel) { }
QuadTree::QuadTree(const sf::FloatRect&_bound, unsigned _capacity, unsigned _maxLevel) :
    bounds(_bound),
    capacity(_capacity),
    maxLevel(_maxLevel) {

    objects.reserve(_capacity);
    foundObjects.reserve(_capacity);

    shape.setOutlineThickness(4.f);
    shape.setSize(sf::Vector2f((float)bounds.width - shape.getOutlineThickness(), (float)bounds.height));
    shape.setOutlineColor(sf::Color::Red);
    shape.setPosition((float)_bound.left, (float)_bound.top);
    shape.setFillColor(sf::Color(0, 0, 0, 0));
}

// Inserts an object into this quadtree
bool QuadTree::insert(Collidable *obj) {
    if (obj->qt != nullptr) return false;

    if (!isLeaf) {
        // insert object into leaf
        if (QuadTree *child = getChild(obj->getCollision()))
            return child->insert(obj);
    }
    objects.push_back(obj);
    obj->qt = this;

    // Subdivide if required
    if (isLeaf && level < maxLevel && objects.size() >= capacity) {
        subdivide();
        update(obj);
    }
    return true;
}

// Removes an object from this quadtree
bool QuadTree::remove(Collidable *obj) {
    if (obj->qt == nullptr) return false; // Cannot exist in vector
    if (obj->qt != this) return obj->qt->remove(obj);

    objects.erase(std::find(objects.begin(), objects.end(), obj));
    obj->qt = nullptr;
    discardEmptyBuckets();
    return true;
}

// Removes and re-inserts object into quadtree (for objects that move)
bool QuadTree::update(Collidable *obj) {
    if (!remove(obj)) return false;

    // Not contained in this node -- insert into parent
    if (parent != nullptr && !bounds.contains(obj->getCollision().left, obj->getCollision().top))
        return parent->insert(obj);
    if (!isLeaf) {
        // Still within current node -- insert into leaf
        if (QuadTree *child = getChild(obj->getCollision()))
            return child->insert(obj);
    }
    return insert(obj);
}

// Searches quadtree for objects within the provided boundary and returns them in vector
std::vector<Collidable*> &QuadTree::getObjectsInBound_unchecked(const sf::FloatRect& bound) {
    foundObjects.clear();
    for (const auto &obj : objects) {
        // Only check for intersection with OTHER boundaries
        foundObjects.push_back(obj);
    }
    if (!isLeaf) {
        // Get objects from leaves
        if (QuadTree *child = getChild(bound)) {
            child->getObjectsInBound_unchecked(bound);
            foundObjects.insert(foundObjects.end(), child->foundObjects.begin(), child->foundObjects.end());
        } else for (QuadTree *leaf : children) {
            if (leaf->bounds.intersects(bound)) {
                leaf->getObjectsInBound_unchecked(bound);
                foundObjects.insert(foundObjects.end(), leaf->foundObjects.begin(), leaf->foundObjects.end());
            }
        }
    }
    return foundObjects;
}

// Returns total children count for this quadtree
unsigned QuadTree::totalChildren() const noexcept {
    unsigned total = 0;
    if (isLeaf) return total;
    for (QuadTree *child : children)
        total += child->totalChildren();
    return 4 + total;
}

// Returns total object count for this quadtree
unsigned QuadTree::totalObjects() const noexcept {
    unsigned total = (unsigned)objects.size();
    if (!isLeaf) {
        for (QuadTree *child : children)
            total += child->totalObjects();
    }
    return total;
}

// Removes all objects and children from this quadtree
void QuadTree::clear() noexcept {
    if (!objects.empty()) {
        for (auto&& obj : objects)
            obj->qt = nullptr;
        objects.clear();
    }
    if (!isLeaf) {
        for (QuadTree *child : children)
            child->clear();
        isLeaf = true;
    }
}

// Subdivides into four quadrants
void QuadTree::subdivide() {
    double width  = bounds.width  * 0.5f;
    double height = bounds.height * 0.5f;
    double x = 0, y = 0;
    for (unsigned i = 0; i < 4; ++i) {
        switch (i) {
            case 0: x = bounds.left + width; y = bounds.top; break; // Top right
            case 1: x = bounds.left;         y = bounds.top; break; // Top left
            case 2: x = bounds.left;         y = bounds.top + height; break; // Bottom left
            case 3: x = bounds.left + width; y = bounds.top + height; break; // Bottom right
        }
        children[i] = new QuadTree(sf::FloatRect(x, y, width, height), capacity, maxLevel);
        children[i]->level  = level + 1;
        children[i]->parent = this;
    }
    isLeaf = false;
}

// Discards buckets if all children are leaves and contain no objects
void QuadTree::discardEmptyBuckets() {
    if (!objects.empty()) return;
    if (!isLeaf) {
        for (QuadTree *child : children)
            if (!child->isLeaf || !child->objects.empty())
                return;
    }
    if (clear(), parent != nullptr)
        parent->discardEmptyBuckets();
}

QuadTree *QuadTree::getLeaf(const sf::FloatRect& bound) {
    QuadTree *leaf = this;
    if (!isLeaf) {
        if (QuadTree *child = getChild(bound))
            leaf = child->getLeaf(bound);
    }
    return leaf;
}

// Returns child that contains the provided boundary
QuadTree *QuadTree::getChild(const sf::FloatRect& bound) const noexcept {
    bool left = bound.left + bound.width < bounds.left + (bounds.width * 0.5f);
    bool right = bound.left > bounds.left + (bounds.width * 0.5f);
    
    if (bound.top + bound.height < bounds.top + (bounds.height * 0.5f)) {
        if (left)  return children[1]; // Top left
        if (right) return children[0]; // Top right
    } else if (bound.top > bounds.top + (bounds.height * 0.5f)) {
        if (left)  return children[2]; // Bottom left
        if (right) return children[3]; // Bottom right
    }
    return nullptr; // Cannot contain boundary -- too large
}

QuadTree::~QuadTree() {
    clear();
    if (children[0]) delete children[0];
    if (children[1]) delete children[1];
    if (children[2]) delete children[2];
    if (children[3]) delete children[3];
}

void QuadTree::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);

    if (!isLeaf) {
        for (QuadTree* child : children)
            target.draw(*child);
    }
}
