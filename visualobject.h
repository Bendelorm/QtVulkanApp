#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H
#include "Vertex.h"
#include <qmatrix4x4.h>
#include <vector>
#include <vulkan/vulkan_core.h>

class VisualObject
{
public:
    std::vector<Vertex> mVertices;
    std::vector<Vertex> getVertices() { return mVertices; }
    VisualObject();
    //
    VkDeviceMemory mBufferMemory{ VK_NULL_HANDLE };
    VkBuffer mBuffer{ VK_NULL_HANDLE };
    VkPrimitiveTopology mTopology { VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST };
    //
    QMatrix4x4 mMatrix;
};

#endif // VISUALOBJECT_H
