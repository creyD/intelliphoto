#ifndef INTELLITOOLSETTINGS_H
#define INTELLITOOLSETTINGS_H

//for unit testing
class UnitTest;

class IntelliToolsettings {
friend UnitTest;
public:
IntelliToolsettings();
virtual ~IntelliToolsettings();

int getLineWidth();
void setLineWidth(int LineWidth);

int getInnerAlpha();
void setInnerAlpha(int innerAlpha);

private:
int lineWidth;
int innerAlpha;
};

#endif
