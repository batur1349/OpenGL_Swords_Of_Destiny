#include "../pch.h"
#include "Model.hpp"


Model::Model(const BaseModel & model, const Texture & texture)
	: _baseModel(model), _texture(texture)
{

}

Model::~Model()
{
}

const BaseModel & Model::GetBaseModel() const
{
	return _baseModel;
}

const Texture & Model::GetTexture() const
{
	return _texture;
}
