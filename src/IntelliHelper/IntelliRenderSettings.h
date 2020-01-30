#ifndef INTELLIRENDERSETTINGS_H
#define INTELLIRENDERSETTINGS_H

//for unit testing
class UnitTest;

/*!
 * \brief The IntelliRenderSettings class which manages the render Settings.
 */
class IntelliRenderSettings
{
friend UnitTest;
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
bool isFastRenderering() const;

private:
/*!
 * \brief fastRenderering the state of the project, in relation the the render setting.
 */
bool fastRenderering = true;
};

#endif
