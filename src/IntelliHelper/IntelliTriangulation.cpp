#include "IntelliTriangulation.h"
#include <algorithm>
#include <queue>
#include <cmath>
#define pi 3.1415926535897932384626433832795

std::vector<Triangle> IntelliTriangulation::calculateTriangles(std::vector<QPoint> polyPoints){
		// helper for managing the triangle vertices and their state
		struct TriangleHelper {
				QPoint vertex;
				float interiorAngle;
				int idx;
				bool isTip;
		};

		// calculates the inner angle of 'point'
		auto calculateInner = [](QPoint& point, QPoint& prev, QPoint& post){
									  QPoint AP(point.x()-prev.x(), point.y()-prev.y());
									  QPoint BP(point.x()-post.x(), point.y()-post.y());

									  float topSclar = AP.x()*BP.x()+AP.y()*BP.y();
									  float absolute = static_cast<float>(sqrt(pow(AP.x(),2.)+pow(AP.y(),2.))*sqrt(pow(BP.x(),2.)+pow(BP.y(),2.)));
									  return acos(topSclar/absolute);
							  };

		// gets the first element of vec for which element.isTip == true holds
		auto getTip= [](const std::vector<TriangleHelper>& vec){
							 size_t min = 0;
							 for(size_t i=0; i<vec.size(); i++) {
									 if(vec[i].interiorAngle<vec[min].interiorAngle) {
											 min = i;
									 }
							 }
							 return vec[min];
					 };

		// get the vertex idx bevor idx in relation to the container length
		auto getPrev = [](int idx, int length){
							   return (idx-1)>=0 ? (idx-1) : (length-1);
					   };

		// get the vertex idx after idx in relation to the container lenght
		auto getPost = [](int idx, int length){
							   return (idx+1)%length;
					   };

		// return if the vertex is a tip
		auto isTip = [](float angle){
							 return static_cast<double>(angle)<(pi/2.);
					 };

		std::vector<TriangleHelper>  Vertices;
		std::vector<Triangle> Triangles;

		// set up all vertices and calculate intirior angle
		for(int i=0; i<static_cast<int>(polyPoints.size()); i++) {
				TriangleHelper helper;
				int prev = getPrev(i, static_cast<int>(polyPoints.size()));
				int post = getPost(i, static_cast<int>(polyPoints.size()));

				helper.vertex = polyPoints[static_cast<size_t>(i)];
				helper.idx = i;

				helper.interiorAngle = calculateInner(polyPoints[static_cast<size_t>(i)],
				                                      polyPoints[static_cast<size_t>(prev)],
				                                      polyPoints[static_cast<size_t>(post)]);
				helper.isTip = isTip(helper.interiorAngle);
				Vertices.push_back(helper);
		}

		// search triangles based on the intirior angles of each vertey
		while(Triangles.size() != polyPoints.size()-2) {
				Triangle tri;
				TriangleHelper smallest = getTip(Vertices);
				int prev = getPrev(smallest.idx, static_cast<int>(Vertices.size()));
				int post = getPost(smallest.idx, static_cast<int>(Vertices.size()));

				// set triangle and push it
				tri.A = Vertices[static_cast<size_t>(prev)].vertex;
				tri.B = Vertices[static_cast<size_t>(smallest.idx)].vertex;
				tri.C = Vertices[static_cast<size_t>(post)].vertex;
				Triangles.push_back(tri);

				// update Vertice array
				Vertices.erase(Vertices.begin()+smallest.idx);
				for(size_t i=static_cast<size_t>(smallest.idx); i<Vertices.size(); i++) {
						Vertices[i].idx-=1;
				}

				// update post und prev idx
				post = getPrev(post, Vertices.size());
				prev = prev<smallest.idx ? prev : (prev-1);

				// calcultae neighboors of prev and post to calculate new interior angles
				int prevOfPrev = getPrev(prev, static_cast<int>(Vertices.size()));
				int postOfPrev = getPost(prev, static_cast<int>(Vertices.size()));

				int prevOfPost = getPrev(post, static_cast<int>(Vertices.size()));
				int postOfPost = getPost(post, static_cast<int>(Vertices.size()));

				// update vertices with interior angles
				// updtae prev
				Vertices[static_cast<size_t>(prev)].interiorAngle = calculateInner(Vertices[static_cast<size_t>(prev)].vertex,
				                                                                   Vertices[static_cast<size_t>(prevOfPrev)].vertex,
				                                                                   Vertices[static_cast<size_t>(postOfPrev)].vertex);
				Vertices[static_cast<size_t>(prev)].isTip = isTip(Vertices[static_cast<size_t>(prev)].interiorAngle);
				// update post
				Vertices[static_cast<size_t>(post)].interiorAngle = calculateInner(Vertices[static_cast<size_t>(post)].vertex,
				                                                                   Vertices[static_cast<size_t>(prevOfPost)].vertex,
				                                                                   Vertices[static_cast<size_t>(postOfPost)].vertex);
				Vertices[static_cast<size_t>(post)].isTip = isTip(Vertices[static_cast<size_t>(post)].interiorAngle);
		}
		return Triangles;
}

bool IntelliTriangulation::isInPolygon(std::vector<Triangle> &triangles, QPoint &point){
		for(auto triangle : triangles) {
				if(IntelliTriangulation::isInTriangle(triangle, point)) {
						return true;
				}
		}
		return false;
}
