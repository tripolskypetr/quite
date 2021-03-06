#include "nodestruct.h"

namespace Quite {
namespace Objects {

/*****************************************************************************/

NodeStruct::NodeStruct() {
    parent = nullptr;
    node = nullptr;
    newTree = false;
    type = -1;
    key = -1;
}

/*---------------------------------------------------------------------------*/

void NodeStruct::printInfo(const NodeStruct& that) {
    qDebug() << getInfo(that);
}

/*---------------------------------------------------------------------------*/

QString NodeStruct::getInfo(const NodeStruct &that) {
    QStringList tmp;
    QString nodePointer;

    {
        const void * address = static_cast<const void*>(that.node);
        std::stringstream ss;
        ss << address;
        std::string name = ss.str();
        nodePointer=QString::fromStdString(name);
    }

    tmp << "NodeStruct"
    << "node:" << nodePointer
    << "newTree:" << QVariant(that.newTree).toString()
    << "type" << QVariant(that.type).toString()
    << "key" << QVariant(that.key).toString();
    return tmp.join(' ');
}

/*---------------------------------------------------------------------------*/

bool NodeStruct::equals(
    const NodeStruct* a,
    const NodeStruct* b,
    bool recursive
) {
    if (a->key!=b->key) {
        return false;
    } else if (a->type!=b->type) {
        return false;
    } else if (recursive) {
        const NodeStruct* parent1 = a;
        const NodeStruct* parent2 = b;
        while(true) {
            parent1 = parent1->parent;
            parent2 = parent2->parent;
            if (parent1==nullptr&&parent2==nullptr) {
                return true;
            } else if (parent1==nullptr&&parent2!=nullptr) {
                return false;
            } else if (parent1!=nullptr&&parent2==nullptr) {
                return false;
            } else if (!equals(parent1, parent2, false)) {
                return false;
            } else {
                continue;
            }
        }
    } else {
        return true;
    }
}

/*****************************************************************************/

} // namespace Objects
} // namespace Quite
