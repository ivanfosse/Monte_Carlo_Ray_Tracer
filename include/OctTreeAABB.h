#ifndef OCT_TREE_AABB
#define OCT_TREE_AABB

#include <vector>

#include <glm/glm.hpp>
#include "utils.h"

class Mesh;

// Axis aligned bounding box.
// The AABB also has a transform matrix, hence it is not necessarily
// axis aligned in world coordinates.
struct AABB
{
	glm::vec3 min;
	glm::vec3 max;
	glm::mat4 transform;

	bool intersect(Ray r) const;
	bool intersectTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) const;
};

// A node of an octree. Has eight child nodes
class OctNodeAABB
{
public:
	OctNodeAABB(
		int depth,
		Mesh* mesh,
		glm::vec3 aabb_min,
		glm::vec3 aabb_max);
	~OctNodeAABB();

	bool intersect(IntersectionData* id, Ray r) const;

protected:
	Mesh* mesh_;
	AABB aabb_;
	std::vector<unsigned short> triangle_indices_;

	OctNodeAABB* left_bottom_far_;
	OctNodeAABB* right_bottom_far_;
	OctNodeAABB* left_top_far_;
	OctNodeAABB* right_top_far_;
	OctNodeAABB* left_bottom_near_;
	OctNodeAABB* right_bottom_near_;
	OctNodeAABB* left_top_near_;
	OctNodeAABB* right_top_near_;
};

// An octree containing axis aligned bounding boxes
class OctTreeAABB : public OctNodeAABB
{
public:
	OctTreeAABB(
	int depth,
	Mesh* mesh);

	~OctTreeAABB();
private:
};

#endif