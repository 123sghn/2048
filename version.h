#ifndef VERSION_H
#define VERSION_H

#include <QWidget>
#include "implementation.h"

namespace Ui { class version; }

class version : public QWidget
{
    Q_OBJECT

public:
    version(QWidget* parent = nullptr);
    ~version();

private:
    Ui::version* ui;
};

#endif // VERSION_H
