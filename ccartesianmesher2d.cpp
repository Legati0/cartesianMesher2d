#include "ccartesianmesher2d.hpp"
#include "cpolyutils2d.hpp"

#include<algorithm> // for copy.
#include<iterator> // for back_inserter

void cMesh(std::vector<Rectangle>* mesh, Polygon* poly, double minArea) {
	double minX, maxX, minY, maxY;
	cGetMinMax(poly, &minX, &maxX, &minY, &maxY);

	Rectangle startRect;
	startRect.points[0] = Point(minX, minY);
	startRect.points[1] = Point(maxX, minY);
	startRect.points[2] = Point(maxX, maxY);
	startRect.points[3] = Point(minX, maxY);

	std::vector<Rectangle> currentRects;
	cSplitRectInNxM(&startRect, &currentRects, minArea);

	while (currentRects.size() > 0) {
		std::vector<int> indicesToDelete;

		for (unsigned int i = 0; i < currentRects.size(); i++) {

			switch(cIsPolyInCutOutPoly(&currentRects.at(i), poly)) {
				// if rect is outside remove
				case -1: 	
					indicesToDelete.push_back(i);
				break;
				// if rect is inside, add to result and remove
				case 1: 
					mesh->push_back(currentRects.at(i));
					indicesToDelete.push_back(i);
				break;
			}
		}

		// remove tagged elems
		for (unsigned int i = indicesToDelete.size(); i-- > 0; )
			currentRects.erase(currentRects.begin() + indicesToDelete.at(i));



  		indicesToDelete.clear();
		std::vector<Rectangle> newRects;

		// split every rectangle in currentRects into smaller rectangles
		for (unsigned int i = 0; i < currentRects.size(); i++) {
			// cSplitRect.. appends to the newRects vector
			cSplitRectInNxM(&currentRects.at(i), &newRects, minArea);
		}
		currentRects = newRects;
	}

}
void cMeshFHObject(FHObject* obj, std::vector<Rectangle>* mesh, double minArea) {
	double minX, maxX, minY, maxY;
	cGetMinMax(&obj->face, &minX, &maxX, &minY, &maxY);

	Rectangle startRect;
	startRect.points[0] = Point(minX, minY);
	startRect.points[1] = Point(maxX, minY);
	startRect.points[2] = Point(maxX, maxY);
	startRect.points[3] = Point(minX, maxY);

	std::vector<Rectangle> currentRects;
	cSplitRectInNxM(&startRect, &currentRects, minArea);

	while (currentRects.size() > 0) {
		std::vector<int> indicesToDelete;

		for (unsigned int i = 0; i < currentRects.size(); i++) {

			int retF = cIsPolyInCutOutPoly(&currentRects.at(i), &obj->face);
			// if rect is outside remove
			if (retF == -1) { 	
				indicesToDelete.push_back(i);

			// rect is inside face
			} else if (retF == 1) {

				// no holes exist -> cant be in a hole
				if (obj->holes.empty()) {
					mesh->push_back(currentRects.at(i));
					indicesToDelete.push_back(i);
					continue;
				}

				// check holes
				int holesMaxRet = -1;
				for (Polygon p : obj->holes) {
					int ret = cIsPolyInCutOutPoly(&currentRects.at(i), &p);
					holesMaxRet = std::max(ret, holesMaxRet);

				}
				// if rect is outside add to result and remove 
				if (holesMaxRet == -1) {
					mesh->push_back(currentRects.at(i));
					indicesToDelete.push_back(i);
				// if inside any hole, remove
				} else if (holesMaxRet == 1) {
					indicesToDelete.push_back(i);
				}
			}
		}
		// remove tagged elems
		for (unsigned int i = indicesToDelete.size(); i-- > 0; )
			currentRects.erase(currentRects.begin() + indicesToDelete.at(i));

	  	indicesToDelete.clear();
		std::vector<Rectangle> newRects;

		// split every rectangle in currentRects into smaller rectangles
		for (unsigned int i = 0; i < currentRects.size(); i++) {
			// cSplitRect.. appends to the newRects vector
			cSplitRectInNxM(&currentRects.at(i), &newRects, minArea);
		}
		currentRects = newRects;
	}
}

void cMeshMore(std::vector<Rectangle>* mesh, PolyStructure* polys, double minArea) {
	for (FHObject fhO : *polys) {
		cMeshFHObject(&fhO, mesh, minArea);
	}
}