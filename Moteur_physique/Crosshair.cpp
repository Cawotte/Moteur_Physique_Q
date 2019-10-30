#include "Crosshair.h"

//Interpolation linéaire entre entre A et B avec t dans [0,1]
float Crosshair::lerp01(float a, float b, float t)
{
	return a + t * (b - a);
}

void Crosshair::changeParticle(std::shared_ptr<IParticle> pa)
{
	if (selectedParticle_ == NULL) {
		//If no particle yet, init it
		selectedParticle_ = pa;
		pa->setVit(Vector3D());
		pa->setPos(pos_);
		
	}
	else {
		pa->setVit(selectedParticle_->getVit());
		pa->setPos(*selectedParticle_->getPos());

		//delete(selectedParticle_);
		selectedParticle_ = pa;
	}

}

void Crosshair::selectNextParticle()
{
	changeParticle(factory_.nextProjectile());
}

void Crosshair::loadShot(float elapsedTime)
{

	//Puissance actuelle en fonction du temps de charge
	currentShotPower_ = lerp01(minShotPower_, maxShotPower_, currentLoadTime_ / timeLoadMaxShot_);

	currentLoadTime_ += elapsedTime;

	//Si puissance max atteinte, retour à 0.
	if (currentLoadTime_ >= timeLoadMaxShot_) {
		currentLoadTime_ = 0.f;
	}
}

std::shared_ptr<IParticle> Crosshair::fireParticle()
{
	std::shared_ptr<IParticle> toShoot = factory_.getCurrentProjectile();

	//Prepare new particle
	toShoot->setVit(selectedParticle_->getVit());
	toShoot->setPos(*selectedParticle_->getPos());

	//Prepare speed and aim of the particle to shoot

	//If particle is Laser, constant value.
	if (factory_.getCurrentProjectileIndex() == 2) {
		toShoot->setVit(aimDirection_ * baseVelocity_ * maxShotPower_);
	}
	else {
		toShoot->setVit(aimDirection_ * baseVelocity_ * currentShotPower_);
	}

	//reset charge values
	currentShotPower_ = minShotPower_;
	currentLoadTime_ = 0.f;

	return toShoot;
}

void Crosshair::draw()
{
	//draw particle
	selectedParticle_->draw();

	//draw a line from the crosshair origine to the particle (better aim)
	GlutUtils::drawLine(pos_, *selectedParticle_->getPos(), Color::red); 
	//draw a line from origin to crosshair (better perspective)
	GlutUtils::drawLine(pos_, Vector3D(), Color::red);

	//Draw the aim line with size depending on shot strenght
	float lineLenght = lerp01(4.f, 15.f, currentShotPower_ / maxShotPower_);
	Vector3D directionAim = (*selectedParticle_->getPos() - pos_).normalized() * lineLenght;
	GlutUtils::drawLine(*selectedParticle_->getPos(), (*selectedParticle_->getPos()) + directionAim, Color::red);
}
