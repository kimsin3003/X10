#include "Target.h"

class Mirror :
	public Target
{
public:
	virtual bool init();

	virtual void SetEffect(Bullet& bullet) override;
	CREATE_FUNC(Mirror);


};
