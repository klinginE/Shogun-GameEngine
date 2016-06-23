#include <Shogun/Management/Layer.hpp>
#include <Shogun/Elements/Entity.hpp>

#include <algorithm>

namespace sg {

    const std::vector<Entity *> &Layer::getEntityList() const {

        return this->entityList;

    }

    const std::vector<Entity *> &Layer::getRenderList() const {

        return this->renderList;

    }

    const std::function<bool(const Entity *, const Entity *)> Layer::getRenderOrder() const {

        return this->renderOrder;

    }

    void Layer::addEntity(Entity &newE) {

        newE.layer = this;
        this->entityList.push_back(&newE);
        this->renderList.push_back(&newE);
        this->sortStatus = true;

    }

    void Layer::removeEntity(Entity &re) {

        int index0 = -1;
        int index1 = -1;
        for (uint32_t i = 0; i < this->entityList.size(); ++i) {

            if (index0 >= 0 && index1 >= 0)
                break;
            if (dynamic_cast<const void *>(this->entityList[i]) == dynamic_cast<const void *>(&re))
                index0 = i;
            if (dynamic_cast<const void *>(this->renderList[i]) == dynamic_cast<const void *>(&re))
                index1 = i;

        }

        if (index0 >= 0 && index0 < static_cast<int>(this->entityList.size()) && index1 >= 0 && index1 < static_cast<int>(this->renderList.size())) {

            this->entityList.erase(this->entityList.begin() + index0);
            this->renderList.erase(this->renderList.begin() + index1);
            re.layer = NULL;
	    this->sortStatus = true;

        }

    }

    void Layer::setRenderOrder(std::function<bool(const Entity *, const Entity *)> newRO) {

        this->renderOrder = newRO;
        this->sortStatus = true;

    }

    void Layer::sortEntityList(std::function<bool(const Entity *, const Entity *)> cmp) {

        std::sort(this->entityList.begin(), this->entityList.end(), cmp);

    }

    void Layer::sortRenderList(std::function<bool(const Entity *, const Entity *)> cmp) {

        std::sort(this->renderList.begin(), this->renderList.end(), cmp);

    }

}
