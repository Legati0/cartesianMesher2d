#ifndef CCARTESIANMESHER2D_HPP
#define CCARTESIANMESHER2D_HPP

#include "definesHeader.hpp"

void cMesh(std::vector<Rectangle>* mesh, Polygon* poly, double minArea);
void cMeshFHObject(FHObject* obj, std::vector<Rectangle> rects, double minArea);
void cMeshMore(std::vector<Rectangle>* mesh, PolyStructure* poly, double minArea);

#endif /* CCARTESIANMESHER2D_HPP */