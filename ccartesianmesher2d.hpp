#ifndef CCARTESIANMESHER2D_HPP
#define CCARTESIANMESHER2D_HPP

#include <cstddef>
#include "definesHeader.hpp"


/**
 * creates a mesh from a polygon
 * @param mesh the return Mesh
 * @param poly the Polygon to mesh
 * @param minArea all rectangles are bigger than this size
 */
void cMesh(List<Rectangle>& mesh, const Polygon& poly, double minArea);
/**
 * creates a mesh from a polygon
 * @param poly the return mesh
 * @param obj face-hole object to mesh
 * @param minArea all rectangles are bigger than this size
 */
void cMeshFHObject(List<Rectangle>& mesh, const FHObject& obj, double minArea);
/**
 * creates a mesh from a polygon
 * @param mesh the return mesh
 * @param poly PolyStructure to mesh
 * @param minArea all rectangles are bigger than this size
 */
void cMeshMore(List<Rectangle>& mesh, const PolyStructure& poly, double minArea);


#endif /* CCARTESIANMESHER2D_HPP */
