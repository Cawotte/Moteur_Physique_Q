#include "ParticleFactory.h"

std::shared_ptr<IParticle> ParticleFactory::getCurrentProjectile() {

	switch (currentProjectileIndex_) {
	case 0:
		return getBasicBall();
		break;
	case 1:
		return getCannonBall();
		break;
	case 2:
		return getLaser();
		break;
	case 3:
		return getSnowflake();
		break;
	case 4:
		return getYoyo();
		break;
	case 5:
		return getBlob1();
		break;
	case 6:
		return getBlob2();
		break;
	case 7:
		return getBlob3();
		break;
	}
	return getBasicBall();
}

std::shared_ptr<IParticle> ParticleFactory::getBasicBall() {
	std::shared_ptr<Particle> pa = std::make_shared<Particle>(Particle(new Vector3D(0, 0, 5), 500.0));
	pa->setShape(new Sphere(pa->getPos(), Color::green, 2)); //Vert
	return pa;
}

std::shared_ptr<IParticle> ParticleFactory::getCannonBall() {
	std::shared_ptr<Particle> pa = std::make_shared<Particle>(Particle(new Vector3D(0, 0, 5), 5000.0));
	pa->setShape(new Sphere(pa->getPos(), Color::black, 3)); //Noir
	return pa;
}

std::shared_ptr<IParticle> ParticleFactory::getLaser() {
	std::shared_ptr<Particle> pa = std::make_shared<Particle>(Particle(new Vector3D(0, 0, 5), -1.f));
	pa->setShape(new Sphere(pa->getPos(), Color::red, 1)); //Rouge
	return pa;
}

std::shared_ptr<IParticle> ParticleFactory::getSnowflake() {
	std::shared_ptr<Particle> pa = std::make_shared<Particle>(Particle(new Vector3D(0, 0, 5), 55.0));
	pa->setShape(new Sphere(pa->getPos(), Color::blue, 1.2f)); //Bleu
	return pa;
}

std::shared_ptr<IParticle> ParticleFactory::getTestWater() {
	std::shared_ptr<Particle> pa = std::make_shared<Particle>(Particle(new Vector3D(0, 125, -30), 400.0));
	pa->setShape(new Sphere(pa->getPos(), Color::yellow, 2)); //Jaune
	return pa;
}

std::shared_ptr<IParticle> ParticleFactory::getYoyo() {

	std::vector<std::shared_ptr<Particle>> pas;

	std::shared_ptr<Particle> a = std::dynamic_pointer_cast<Particle>(getBasicBall());


	a->getShape()->setColor(50, 0, 120);

	pas.push_back(a);

	//Forces
	ParticleForceRegister* fg = new ParticleForceRegister();

	fg->add(a.get(), new AnchoredSpringFG(Vector3D(0, 0, 0), 50, 5));

	std::shared_ptr<ParticleGroup> pg = std::make_shared<ParticleGroup>(ParticleGroup(pas, fg));

	return pg;
}

std::shared_ptr<IParticle> ParticleFactory::getBlob1() {
	//Square linked blob

	//Particles
	std::vector<std::shared_ptr<Particle>> pas;

	std::shared_ptr<Particle> a = std::dynamic_pointer_cast<Particle>(getBasicBall());
	std::shared_ptr<Particle> b = std::dynamic_pointer_cast<Particle>(getBasicBall());
	std::shared_ptr<Particle> c = std::dynamic_pointer_cast<Particle>(getBasicBall());
	std::shared_ptr<Particle> d = std::dynamic_pointer_cast<Particle>(getBasicBall());

	float r = 100;
	float v = 100;
	float bl = 30;
	a->getShape()->setColor(r, v, bl);
	b->getShape()->setColor(r, v, bl);
	c->getShape()->setColor(r, v, bl);
	d->getShape()->setColor(r, v, bl);

	pas.push_back(a);
	pas.push_back(b);
	pas.push_back(c);
	pas.push_back(d);

	//Forces
	ParticleForceRegister* fg = new ParticleForceRegister();

	
	fg->add(a.get(), new BungeeSpringFG(b.get(), 50, 1));
	fg->add(b.get(), new BungeeSpringFG(b.get(), 50, 1));
	fg->add(c.get(), new BungeeSpringFG(b.get(), 50, 1));
	fg->add(d.get(), new BungeeSpringFG(b.get(), 50, 1));
	

	std::shared_ptr<ParticleGroup> pg = std::make_shared<ParticleGroup>(ParticleGroup(pas, fg));

	return pg;
}

std::shared_ptr<IParticle> ParticleFactory::getBlob2() {

	//Square linked blob

	//Particles
	std::vector<std::shared_ptr<Particle>> pas;

	std::shared_ptr<Particle> a = std::dynamic_pointer_cast<Particle>(getBasicBall());
	std::shared_ptr<Particle> b = std::dynamic_pointer_cast<Particle>(getBasicBall());
	std::shared_ptr<Particle> c = std::dynamic_pointer_cast<Particle>(getBasicBall());
	std::shared_ptr<Particle> d = std::dynamic_pointer_cast<Particle>(getBasicBall());


	//Colors
	float r = 140;
	float v = 100;
	float bl = 0;
	a->getShape()->setColor(r, v, bl);
	b->getShape()->setColor(r, v, bl);
	c->getShape()->setColor(r, v, bl);
	d->getShape()->setColor(r, v, bl);

	pas.push_back(a);
	pas.push_back(b);
	pas.push_back(c);
	pas.push_back(d);

	//Forces
	ParticleForceRegister* fg = new ParticleForceRegister();

	fg->add(a.get(), new SpringFG(b.get(), 50, 1));
	fg->add(b.get(), new SpringFG(c.get(), 50, 1));
	fg->add(c.get(), new SpringFG(d.get(), 50, 1));
	fg->add(d.get(), new SpringFG(a.get(), 50, 1));


	std::shared_ptr<ParticleGroup> pg = std::make_shared<ParticleGroup>(ParticleGroup(pas, fg));

	return pg;
}

std::shared_ptr<IParticle> ParticleFactory::getTestBlop() {
	std::shared_ptr<Particle> pa = std::make_shared<Particle>(new Vector3D(0, 0, 5), 400.0);
	pa->setShape(new Sphere(pa->getPos(), Color::purple, 0.7f));
	return pa;
}

std::shared_ptr<IParticle> ParticleFactory::getBlob3() {


	//Particles
	std::vector<std::shared_ptr<Particle>> pas;

	//Forces
	ParticleForceRegister* fg = new ParticleForceRegister();

	//Centre

	std::shared_ptr<Particle> a = std::dynamic_pointer_cast<Particle>(getTestBlop());

	pas.push_back(a);

	//Corps
	Particle* b = NULL;
	for (int i = 0; i < 50; i++) {

		std::shared_ptr<Particle> b = std::dynamic_pointer_cast<Particle>(getTestBlop());

		pas.push_back(b);

		fg->add(b.get(), new SpringFG(a.get(), 100, 1));
		fg->add(a.get(), new SpringFG(b.get(), 100, 1));

	}

	std::shared_ptr<ParticleGroup> pg = std::make_shared<ParticleGroup>(ParticleGroup(pas, fg));

	return pg;
}
