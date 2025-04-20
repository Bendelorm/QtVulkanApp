#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "VisualObject.h"

class HeightMap : public VisualObject
{
public:
    HeightMap(const std::string& filename);

    void makeTerrain(unsigned char* textureData, int width, int height);
    float barycentricHeight(const QVector2D& p, const QVector3D& a, const QVector3D& b, const QVector3D& c);
    float getHeightAtPosition(float worldX, float worldZ);
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width;
    int height;
};

#endif // HEIGHTMAP_H
