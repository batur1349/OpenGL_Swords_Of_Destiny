#ifndef MASTERRENDERER_HPP
#define MASTERRENDERER_HPP

#include "../Model/BaseModel.hpp"

class MasterRenderer
{
public:
	// Constructor and ~Destructor
	MasterRenderer();
	virtual ~MasterRenderer();

	// Functions
	void Prepare();
	const void Render(BaseModel& model) const;
};

#endif // !MASTERRENDERER_HPP