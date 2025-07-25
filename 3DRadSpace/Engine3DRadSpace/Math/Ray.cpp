#include "Ray.hpp"
#include "Math.hpp"

using namespace Engine3DRadSpace::Math;

std::optional<float> Ray::Intersects(const BoundingSphere &sph) const
{
    Vector3 difference = sph.Center - Origin;

    float differenceLengthSquared = difference.LengthSquared();
    float sphereRadiusSquared = sph.Radius * sph.Radius;

    // If the distance between the ray start and the sphere's centre is less than
    // the radius of the sphere, it means we've intersected. N.B. checking the LengthSquared is faster.
    if(differenceLengthSquared < sphereRadiusSquared) return 0.0f;

    float distanceAlongRay = Vector3::Dot(Direction, difference);
    // If the ray is pointing away from the sphere then we don't ever intersect
    if(distanceAlongRay < 0) return std::nullopt;

    // Next we kinda use Pythagoras to check if we are within the bounds of the sphere
    // if x = radius of sphere
    // if y = distance between ray position and sphere centre
    // if z = the distance we've travelled along the ray
    // if x^2 + z^2 - y^2 < 0, we do not intersect
    return sphereRadiusSquared + distanceAlongRay * distanceAlongRay - differenceLengthSquared;


 //   //https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 //   float a = Direction.Dot(Origin - sph.Center);
 //   float nabla = powf(a, 2) - (powf((Origin - sph.Center).Length(),2) - powf(sph.Radius, 2));

 //   if(nabla < 0) return std::nullopt;
	//if(Math::WithinEpsilon(nabla, 0)) return -a;
 //   if(nabla > 0) return std::min(-a - sqrtf(nabla), -a + sqrt(nabla));
}

std::optional<float> Ray::Intersects(const Triangle &tri) const
{
    //https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    Vector3 vertex0 = tri.PointA;
    Vector3 vertex1 = tri.PointB;
    Vector3 vertex2 = tri.PointC;
    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = Vector3::Cross(Direction, edge2);
    a = edge1.Dot(h);

    if(a > -epsilon && a < epsilon)
        return std::nullopt;    // This ray is parallel to this triangle.

    f = 1.0f / a;
    s = Origin - vertex0;
    u = f * s.Dot(h);

    if(u < 0.0f || u > 1.0f)
        return std::nullopt;

    q = Vector3::Cross(s, edge1);
    v = f * Direction.Dot(q);

    if(v < 0.0f || u + v > 1.0f)
        return std::nullopt;

    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.Dot(q);

    if(t > epsilon) // ray intersection
        return t;
    else // This means that there is a line intersection but not a ray intersection.
        return std::nullopt;
}

std::optional<float> Ray::Intersects(const BoundingBox &box) const
{
    //Branchless ray-bounding box intersection algorithm: https://tavianator.com/2022/ray_box_boundary.html

    Vector3 invD = 1.0f / Direction;

    float tmin = 0.0;
    float tmax = std::numeric_limits<float>::infinity();

    //x coord
    float tx1 = box.Position.X - Origin.X * invD.X;
    float tx2 = (box.Position.X + box.Scale.X) - Origin.X * invD.X;

    tmin = std::max(tmin, std::min(std::min(tx1, tx2), tmax));
    tmax = std::min(tmax, std::max(std::max(tx1, tx2), tmin));

    //y coord
    float ty1 = box.Position.Y - Origin.Y * invD.Y;
    float ty2 = (box.Position.Y + box.Scale.Y) - Origin.Y * invD.Y;

    tmin = std::max(tmin, std::min(std::min(ty1, ty2), tmax));
    tmax = std::min(tmax, std::max(std::max(ty1, ty2), tmin));

    //z coord
    float tz1 = box.Position.Z - Origin.Z * invD.Z;
    float tz2 = (box.Position.Z + box.Scale.Z) - Origin.Z * invD.Z;

    tmin = std::max(tmin, std::min(std::min(tz1, tz2), tmax));
    tmax = std::min(tmax, std::max(std::max(tz1, tz2), tmin));

    if(tmin <= tmax)
        return tmin;
    else return std::nullopt;

}

std::optional<float> Ray::Intersects(const BoundingPlane& plane) const
{
    //https://stackoverflow.com/questions/23975555/how-to-do-ray-plane-intersection
    const float denom = Vector3::Dot(plane.Normal, Direction);

    // Prevent divide by zero:
    if (abs(denom) <= std::numeric_limits<float>::epsilon())
        return std::nullopt;

    float t = -(Vector3::Dot(plane.Normal, Origin) + plane.D) / denom;

    if (t <= 1e-4)
        return std::nullopt;

    return t;
}
