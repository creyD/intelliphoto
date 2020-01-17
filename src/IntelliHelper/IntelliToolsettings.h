#ifndef INTELLITOOLSETTINGS_H
#define INTELLITOOLSETTINGS_H

//for unit testing
class UnitTest;

class IntelliToolsettings {
friend UnitTest;
public:
IntelliToolsettings();
virtual ~IntelliToolsettings();

int getLineWidth() const;
void setLineWidth(int LineWidth);

int getInnerAlpha() const;
void setInnerAlpha(int innerAlpha);

private:
int lineWidth;
int innerAlpha;
};

#endif
