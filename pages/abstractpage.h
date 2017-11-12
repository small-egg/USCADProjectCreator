#ifndef ABSTACTPAGE_H
#define ABSTACTPAGE_H

#include "auxiliary_classes/datainputwidget.h"

#include <QWizardPage>

class AbstractPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit AbstractPage(const int columnCount, const QStringList& labels,
                         QWidget *parent = Q_NULLPTR);

protected slots:
    bool    validatePage() override;

protected: // Methods
    void    initUi(const QString& title, const QString& subtitle, const QString& description);

    bool    isDataValid() const;

protected:
    DataInputWidget*    dataWgt;

private:
    const int           columnCount;
    const QStringList   labels;
};

#endif // ABSTACTPAGE_H
