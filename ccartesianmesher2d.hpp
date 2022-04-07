#ifndef CCARTESIANMESHER2D_HPP
#define CCARTESIANMESHER2D_HPP

#include <cstddef>
#include "definesHeader.hpp"

void cMesh(List<Rectangle>& mesh, Polygon& poly, double minArea);
void cMeshFHObject(FHObject& obj, List<Rectangle>& rects, double minArea);
void cMeshMore(List<Rectangle>& mesh, PolyStructure& poly, double minArea);

#endif /* CCARTESIANMESHER2D_HPP */