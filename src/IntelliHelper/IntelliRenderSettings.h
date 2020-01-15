#ifndef INTELLIRENDERSETTINGS_H
#define INTELLIRENDERSETTINGS_H


class IntelliRenderSettings
{
public:
IntelliRenderSettings();

/*!
 * \brief setFastRendering sets fastRendering to Updatedsetting.
 * \param Updatedsetting - Represents the new value for the Fast Rendering Flag.
 */
void setFastRendering(bool Updatedsetting);
/*!
 * \brief The getfastRenderer gets the value of the flag for the fastRenderer setting.
 * \return Returns true if fastRenderer is active else false
 */
bool isFastRenderering();

private:
bool fastRenderering = true;
};

#endif
