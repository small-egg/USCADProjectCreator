#include "saveprojectpage.h"
#include "ui_saveprojectpage.h"

#include "projectcreator.h"

#include <QFileDialog>

#include <QJsonDocument>

SaveProjectPage::SaveProjectPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SaveProjectPage)
{
    ui->setupUi(this);

    ui->errorLabel->hide();
}

SaveProjectPage::~SaveProjectPage()
{
    delete ui;
}

bool SaveProjectPage::validatePage()
{
    if(path.isEmpty())
    {
        ui->errorLabel->setText("Выберите файл для сохранения!");
        ui->errorLabel->show();
        return false;
    }

    QFile file(path);

    if(!file.open(QIODevice::WriteOnly))
    {
        ui->errorLabel->setText("Ошибка при сохранении файла: " + file.errorString());
        ui->errorLabel->show();
        return false;
    }

    ProjectCreator* pc = qobject_cast<ProjectCreator*>(wizard());

    QJsonDocument doc(pc->serialize());
    file.write(doc.toJson());
    file.close();

    ui->errorLabel->hide();
    return true;
}

void SaveProjectPage::selectProjectPath()
{
    QString res = QFileDialog::getSaveFileName(this, "Выберите путь для сохранения проекта",
                                               QDir::homePath());

    if(res.isEmpty())
        return;

    path = res;
    ui->pathEdit->setText(path);
}
