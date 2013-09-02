#ifndef _LOCATION_HPP_
#define _LOCATION_HPP_

class Location
{
public:
	Location(): posX_(0.0f), posY_(0.0f)
	{
	};

	inline void setPosition(float posX, float posY)
	{
		posX_ = posX;
		posY_ = posY;
	}

	inline void translate(float amountX, float amountY)
	{
		posX_ += amountX;
		posY_ += amountY;
	}

	inline float getPosX() const
	{
		return posX_;
	}

	inline float getPosY() const
	{
		return posY_;
	}

private:
	float posX_;
	float posY_;
};

#endif
