#ifndef INTELLITOOLSETTINGS_H
#define INTELLITOOLSETTINGS_H

//for unit testing
class UnitTest;
/*!
 * \brief The IntelliToolsettings class managing the settings of the tools, independent of an existing tool.
 */
class IntelliToolsettings {
friend UnitTest;
public:
/*!
 * \brief IntelliToolsettings - basic constructor of the IntelliToolsettings, initializing the basics.
 */
IntelliToolsettings();

/*!
 * \brief ~IntelliToolsettings - basic destructor.
 */
virtual ~IntelliToolsettings();

/*!
 * \brief getLineWidth returns the width attribute of the line.
 * \return returns the width attribute as integer.
 */
int getLineWidth() const;

/*!
 * \brief setLineWidth sets the width attribute of the line.
 * \param LineWidth - the future width of the line
 */
void setLineWidth(int LineWidth);

/*!
 * \brief getInnerAlpha returns the inner alpha value.
 * \return returns the inner alpha attribute as integer.
 */
int getInnerAlpha() const;

/*!
 * \brief setInnerAlpha sets the inner alpha attribute of the Tool.
 * \param innerAlpha - the future inner alpha of the Tool.
 */
void setInnerAlpha(int innerAlpha);

private:

/*!
 * \brief lineWidth attribute of a Tool.
 */
int lineWidth;

/*!
 * \brief innerAlpha aattribute of a Tool.
 */
int innerAlpha;
};

#endif
