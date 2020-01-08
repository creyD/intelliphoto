#ifndef INTELLITOOLSETTINGS_H
#define INTELLITOOLSETTINGS_H

class IntelliToolsettings {
public:
    /*!
     * \brief The LineStyle enum classifing all ways of drawing a line.
     */
    enum class LineStyle {
            SOLID_LINE,
            DOTTED_LINE
    };
    IntelliToolsettings();
    virtual ~IntelliToolsettings();
    int getLineWidth();
    int getInnerAlpha();
    LineStyle getLinestyle();

private:
    int lineWidth;
    int innerAlpha;
    LineStyle Linestyle;
};

#endif // INTELLITOOLSETTINGS_H
