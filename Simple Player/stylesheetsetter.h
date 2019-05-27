#ifndef STYLESHEETSETTER_H
#define STYLESHEETSETTER_H

#include<QWidget>
#include<QTableView>
#include<QSlider>

class StyleSheetSetter
{   
public:
    static void setMainWidgetStylesheet(QWidget*);
    static void setPlayListViewStyleSheet(QTableView*);
    static void setHorizontalSliderStyleSheet(QSlider*);
};

#endif // STYLESHEETSETTER_H
