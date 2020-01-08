#ifndef INTELLIRENDERSETTINGS_H
#define INTELLIRENDERSETTINGS_H


class IntelliRenderSettings
{
public:
    IntelliRenderSettings();

    /*!
     * \brief The getfastRenderer gets the value of the flag for the fastRenderer setting.
     * \return Returns true if fastRenderer is active else false
     */
    bool getFastRenderer();

private:
    bool fastRenderer = true;
};

#endif // INTELLIRENDERSETTINGS_H
