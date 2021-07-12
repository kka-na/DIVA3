#ifndef INFORMDILG_H
#define INFORMDILG_H

#include "global_header.hpp"
#include "qt_header.hpp"

#include "ui_informdialog.h"

namespace Ui{ class InformDialog; }

class InformDialog : public QDialog
{
	Q_OBJECT
public :
	explicit InformDialog(QWidget *parent = nullptr);
	~InformDialog();

private :
	Ui::InformDialog *ui;
};

#endif

