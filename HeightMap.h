#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "VisualObject.h"

class HeightMap : public VisualObject
{
public:
    HeightMap(const std::string& filename);

    void makeTerrain(unsigned char* textureData, int width, int height);
};

#endif // HEIGHTMAP_H
