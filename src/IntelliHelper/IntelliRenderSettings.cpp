#include "IntelliRenderSettings.h"

IntelliRenderSettings::IntelliRenderSettings()
{

}

void IntelliRenderSettings::setFastRendering(bool Updatedsetting){
		this->fastRenderering = Updatedsetting;
}

bool IntelliRenderSettings::isFastRenderering() const {
		return fastRenderering;
}
