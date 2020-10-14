#pragma once

class IObject {
public:

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;

private:

};
