#ifndef INTELLITOOLSETTINGS_H
#define INTELLITOOLSETTINGS_H

class IntelliToolsettings {
public:
IntelliToolsettings();
virtual ~IntelliToolsettings();
int getLineWidth();
void setLineWidth();
void setLineWidth(int LineWidth);
int getInnerAlpha();
void setInnerAlpha();
void setInnerAlpha(int innerAlpha);

private:
int lineWidth;
int innerAlpha;
};

#endif
