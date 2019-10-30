#include "Shape.h"

//Dessine les 6 faces du parall�l�pip�de rectangle, centr� sur la position de la particule
void Rect3D::draw() {
	GlutUtils::drawRectangle(*position_, width_, height_, depth_, color_);
}

Contact Rect3D::collideWith(Shape& shape)
{
	return shape.collideWithInternal(*this);
}

Contact Rect3D::collideWithInternal(Sphere& sphere)
{
	//DRY!!!

	float restit = 0.75f;

	//sphere and rect
	Vector3D minRect = getMinPos();
	Vector3D maxRect = getMaxPos();

	Vector3D nearestPoint(
		std::fmaxf(minRect.x, std::fminf(position_->x, maxRect.x)),
		std::fmaxf(minRect.y, std::fminf(position_->y, maxRect.y)),
		std::fmaxf(minRect.z, std::fminf(position_->z, maxRect.z))
	);

	Vector3D delta(
		position_->x - nearestPoint.x,
		position_->y - nearestPoint.y,
		position_->z - nearestPoint.z
	);

	float cornerDistanceSq = std::powf(delta.x, 2.f) + std::powf(delta.y, 2.f) + std::powf(delta.z, 2.f);


	if (cornerDistanceSq < std::powf(sphere.getRadius(), 2.f))
	{
		float dPene = std::sqrt(cornerDistanceSq);
		Vector3D n = nearestPoint - *position_;

		//restite?
		return Contact(dPene, n);
	}
	else {
		return Contact{};
	}
}

Contact Rect3D::collideWithInternal(Rect3D& rect)
{
	return Contact{};
}

//dessine la sph�re centr�e sur la position de la particule
void Sphere::draw() {
	GlutUtils::drawSphere(*position_, radius_, color_);
}

Contact Sphere::collideWith(Shape& shape)
{
	return shape.collideWithInternal(*this);
}

Contact Sphere::collideWithInternal(Sphere& sphere)
{
	float restit = 0.95f;

	float distAB = position_->distanceWith(sphere.getPos());
	float cumulatedRadius = radius_ + sphere.getRadius();

	if (distAB < cumulatedRadius) {

		//PARAMETERS, TO MOVE

		float dPene = cumulatedRadius - distAB;
		Vector3D n = *position_ - sphere.getPos();

		return Contact(dPene, n); //use restit?

	}
	else {
		return Contact{};
	}
}

Contact Sphere::collideWithInternal(Rect3D& rect)
{
	float restit = 0.75f;

	//sphere and rect
	Vector3D minRect = rect.getMinPos();
	Vector3D maxRect = rect.getMaxPos();

	Vector3D nearestPoint(
		std::fmaxf(minRect.x, std::fminf(position_->x, maxRect.x)),
		std::fmaxf(minRect.y, std::fminf(position_->y, maxRect.y)),
		std::fmaxf(minRect.z, std::fminf(position_->z, maxRect.z))
	);

	Vector3D delta(
		position_->x - nearestPoint.x,
		position_->y - nearestPoint.y,
		position_->z - nearestPoint.z
	);

	float cornerDistanceSq = std::powf(delta.x, 2.f) + std::powf(delta.y, 2.f) + std::powf(delta.z, 2.f);


	if (cornerDistanceSq < std::powf(radius_, 2.f))
	{
		float dPene = std::sqrt(cornerDistanceSq);
		Vector3D n = nearestPoint - *position_;

		//restite?
		return Contact(dPene, n);
	}
	else {
		return Contact{};
	}
}


float Sphere::getRadius() {
	return radius_;
}
