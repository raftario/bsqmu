#include "agreementdialog.h"
#include "ui_agreementdialog.h"

AgreementDialog::AgreementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgreementDialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
}

AgreementDialog::~AgreementDialog()
{
    delete ui;
}
