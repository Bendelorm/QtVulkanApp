#include "HeightMap.h"
#include "Vertex.h"
#include "stb_image.h"

HeightMap::HeightMap(const std::string& filename)
{
    width = 256;
    height = 256;
    int channels = 4;

    unsigned char* textureData = stbi_load(filename.c_str(), &width, &height, &channels, 4);

    if (!textureData)
    {
        throw std::runtime_error("Failed to load heightmap image: " + filename);
    }

    // Now pass the data to the terrain creation function
    makeTerrain(textureData, width, height);

    // Free image memory when done
    stbi_image_free(textureData);
}

//Function that makes a terrain grid from a heightmap, using the values in the heightmap as height.
//This function will crash if the width and height of the heightmap is not set correct!
//The size of the textureData array is widthIn * heightIn.
// The function is not tested in this codebase, and is provided as an example.
void HeightMap::makeTerrain(unsigned char* textureData, int widthIn, int heightIn)
{

    //Default normal pointing straight up - should be calculated correctly for lights to work!!!
    float normal[3]{0.f, 1.f, 0.f};

    //How many meters between each vertex in both x and z direction
    //This should be sent in as a parameter!
    float horisontalSpacing{.5f};

    //Scaling the height read from the heightmap. 0 -> 255 meters if this is set to 1
    //This should be sent in as a parameter!
    float heightSpacing{.02f};

    //Offset the whole terrain in y (height) axis
    //Moves the terrain mesh up or down
    //Because of Barycentric calculations, we want the terrain to be in World coordinates!
	//So we don't want to move the terrain up or down in the Y axis after it is made
    float heightPlacement{-5.f};

    //Getting the scale of the heightmap
    //Using depth as the name of texture height, to not confuse with terrain height
    unsigned short width = widthIn;       //Width == x-axis
    unsigned short depth = heightIn;      //Depth == z-axis

    //Temp variables for creating the mesh
    //Adding offset so the middle of the terrain will be in World origo
    float vertexXStart{0.f};            // if world origo should be at center use: {0.f - width * horisontalSpacing / 2};
    float vertexZStart{0.f};            // if world origo should be at center use: {0.f + depth * horisontalSpacing / 2};

    //Loop to make the mesh from the values read from the heightmap (textureData)
	//Double for-loop to make the depth and the width of the terrain in one go
    for(int d{0}; d < depth; ++d)       //depth loop
    {
        for(int w{0}; w < width; ++w)   //width loop
        {
            //Heightmap image is actually stored as an one dimentional array - so calculating the correct index for column and row
            //and scale it according to variables
            // Calculate the correct index for the R value of each pixel
            int index = (w + d * width) * 4; // Each pixel has 4 bytes (RGBA)
            float heightFromBitmap = static_cast<float>(textureData[index]);         // * heightSpacing + heightPlacement;
            float normalizedHeight = heightFromBitmap / 255.f;
            float r, g, b;
            if (normalizedHeight < 0.4f)
            {
                // Low elevations: green
                r = 0.1f;
                g = 0.6f + normalizedHeight * 0.4f; // gets lighter green
                b = 0.1f;
            }
            else if (normalizedHeight < 0.8f)
            {
                // Mid elevations: brown
                float t = (normalizedHeight - 0.4f) / 0.4f;
                r = 0.5f + t * 0.3f;
                g = 0.3f + t * 0.2f;
                b = 0.1f;
            }
            else
            {
                // High elevations: snow (white)
                float t = (normalizedHeight - 0.8f) / 0.2f;
                r = 0.8f + t * 0.2f;
                g = 0.8f + t * 0.2f;
                b = 0.8f + t * 0.2f;
            }
			//                                          x - value                      y-value               z-value
            mVertices.emplace_back(Vertex{vertexXStart + (w * horisontalSpacing), heightFromBitmap, vertexZStart - (d * horisontalSpacing),
                //  dummy normal=0,1,0                  Texture coordinates
                normal[0],normal[1],normal[2],           w / (width - 1.f), d / (depth - 1.f)});
        }
    }

    // The mesh(grid) is drawn in quads with diagonals from lower left to upper right
    //          _ _
    //         |/|/|
    //          - -
    //         |/|/|
    //          - -
    //Making the indices for this mesh:
    for(int d{0}; d < depth-1; ++d)        //depth - 1 because we draw the last quad from depth - 1 and in negative z direction
    {
        for(int w{0}; w < width-1; ++w)    //width - 1 because we draw the last quad from width - 1 and in positive x direction
        {
			//Indices for one quad:
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
            mIndices.emplace_back(w + d * width + width);       // 0 + 0 * mWidth + mWidth      = mWidth
            mIndices.emplace_back(w + d * width);               // 0 + 0 * mWidth               = 0
            mIndices.emplace_back(w + d * width + 1);           // 0 + 0 * mWidth + 1           = 1
            mIndices.emplace_back(w + d * width + width + 1);   // 0 + 0 * mWidth + mWidth + 1  = mWidth + 1
        }
    }

 
	//Calculating the normals for the mesh
    //Function not made yet:
    //calculateHeighMapNormals();

}
float HeightMap::barycentricHeight(const QVector2D& p, const QVector3D& a, const QVector3D& b, const QVector3D& c)
{
    // Get the 2D coordinates (x, z) of each triangle vertex
    QVector2D a2D(a.x(), a.z());
    QVector2D b2D(b.x(), b.z());
    QVector2D c2D(c.x(), c.z());

    // Vectors from A to B and A to C
    QVector2D v0 = b2D - a2D;
    QVector2D v1 = c2D - a2D;
    QVector2D v2 = p   - a2D;

    // Dot products for barycentric calculation
    float d00 = QVector2D::dotProduct(v0, v0);
    float d01 = QVector2D::dotProduct(v0, v1);
    float d11 = QVector2D::dotProduct(v1, v1);
    float d20 = QVector2D::dotProduct(v2, v0);
    float d21 = QVector2D::dotProduct(v2, v1);

    // Calculate denominator
    float denom = d00 * d11 - d01 * d01;
    if (denom == 0.0f)
        return a.y(); // Degenerate triangle — just return a.y as fallback

    // Barycentric coordinates
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;

    // Interpolate height (y) using barycentric weights
    return u * a.y() + v * b.y() + w * c.y();
}
float HeightMap::getHeightAtPosition(float worldX, float worldZ)
{
    float horisontalSpacing = 0.5f;  // match your terrain generation
    int gridX = static_cast<int>(worldX / horisontalSpacing);
    int gridZ = static_cast<int>(-worldZ / horisontalSpacing);  // assuming Z goes negative in your loop

    if (gridX < 0 || gridZ < 0 || gridX >= width - 1 || gridZ >= height - 1)
        return 0.0f;  // out of bounds

    // Find which triangle of the quad we are in
    float xCoord = fmod(worldX, horisontalSpacing) / horisontalSpacing;
    float zCoord = fmod(-worldZ, horisontalSpacing) / horisontalSpacing;

    // Get triangle vertices from mVertices
    QVector3D a, b, c;
    int topLeftIndex = gridX + gridZ * width;
    if (xCoord + zCoord <= 1.0f)
    {
        // Top-left triangle
        a = QVector3D(mVertices[topLeftIndex].x, mVertices[topLeftIndex].y, mVertices[topLeftIndex].z);
        b = QVector3D(mVertices[topLeftIndex + 1].x, mVertices[topLeftIndex + 1].y, mVertices[topLeftIndex + 1].z);
        c = QVector3D(mVertices[topLeftIndex + width].x, mVertices[topLeftIndex + width].y, mVertices[topLeftIndex + width].z);
    }
    else
    {
        // Bottom-right triangle
        a = QVector3D(mVertices[topLeftIndex + 1 + width].x, mVertices[topLeftIndex + 1 + width].y, mVertices[topLeftIndex + 1 + width].z);
        b = QVector3D(mVertices[topLeftIndex + width].x, mVertices[topLeftIndex + width].y, mVertices[topLeftIndex + width].z);
        c = QVector3D(mVertices[topLeftIndex + 1].x, mVertices[topLeftIndex + 1].y, mVertices[topLeftIndex + 1].z);
    }

    QVector2D p(worldX, worldZ);
    return barycentricHeight(QVector2D(p.x(), p.y()), a, b, c);
}
