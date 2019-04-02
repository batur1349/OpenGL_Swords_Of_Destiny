#ifndef MODEL_HPP
#define MODEL_HPP

#include "BaseModel.hpp"
#include "../Texture/Texture.hpp"

class Model
{
public:
	// Constructor and ~Destructor
	Model(const BaseModel& model, const Texture& texture);
	virtual ~Model();
	// Getters
	const BaseModel& GetBaseModel() const;
	const Texture& GetTexture() const;
private:
	BaseModel _baseModel;
	Texture _texture;
};
#endif // !MODEL_HPP