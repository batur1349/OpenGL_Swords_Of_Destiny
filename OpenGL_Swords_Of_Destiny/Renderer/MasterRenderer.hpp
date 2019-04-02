#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Model/Model.hpp"
class Model;

class MasterRenderer
{
public:
	// Constructor and ~Destructor
	MasterRenderer();
	virtual ~MasterRenderer();

	// Functions
	void Prepare();
	const void Render(BaseModel& model) const;
	const void Render(Model& model) const;
};

#endif // !MASTERRENDERER_HPP