#ifndef PAGES_H
#define PAGES_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCalendarWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QTableView>
#include <QModelIndex>
#include <QCheckBox>
#include <QList>
#include "Zones.h"
#include <QLabel>
#include <QDateEdit>
#include <QCheckBox>
#include <QValidator>
#include <QGridLayout>
#include <QProgressDialog>
#include "DeviceTypes.h"
#include "DeviceConfiguration.h"

class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;

class ConfigurationPage : public QWidget
{
    public:
        ~ConfigurationPage();
        ConfigurationPage();
        QComboBox *unitCombo;
        QComboBox *crankLengthCombo;
        QCheckBox *allRidesAscending;
	QLineEdit *BSdaysEdit;
	QComboBox *bsModeCombo;
        

    private:
	QGroupBox *configGroup;
	QLabel *unitLabel;
	QLabel *warningLabel;
	QHBoxLayout *unitLayout;
	QHBoxLayout *warningLayout;
	QVBoxLayout *configLayout;
	QVBoxLayout *mainLayout;
	QGridLayout *bsDaysLayout;
	QHBoxLayout *bsModeLayout;
};

class CyclistPage : public QWidget
{
    public:
        ~CyclistPage();
        CyclistPage(const Zones *_zones);
        int thresholdPower;
        QString getText();
        int getCP();
	void setCP(int cp);
	void setSelectedDate(QDate date);
        void setCurrentRange(int range = -1);
        QPushButton *btnBack;
        QPushButton *btnForward;
        QPushButton *btnDelete;
        QCheckBox *checkboxNew;
        QCalendarWidget *calendar;
        QLabel *lblCurRange;
        QLabel *txtStartDate;
        QLabel *txtEndDate;
        QLabel *lblStartDate;
        QLabel *lblEndDate;
	QLabel *perfManLabel;
	QLabel *perfManStartLabel;
	QLabel *perfManSTSLabel;
	QLabel *perfManLTSLabel;
	QLineEdit *perfManStart;
	QLineEdit *perfManSTSavg;
	QLineEdit *perfManLTSavg;

        int getCurrentRange();
	bool isNewMode();

	inline void setCPFocus() {
	    txtThreshold->setFocus();
	}

	inline QDate selectedDate() {
	    return calendar->selectedDate();
	}

    private:
	QGroupBox *cyclistGroup;
        const Zones *zones;
        int currentRange;
	QLabel *lblThreshold;
        QLineEdit *txtThreshold;
	QIntValidator *txtThresholdValidator;
	QVBoxLayout *perfManLayout;
	QHBoxLayout *perfManStartValLayout;
	QHBoxLayout *perfManSTSavgLayout;
	QHBoxLayout *perfManLTSavgLayout;
	QHBoxLayout *powerLayout;
	QHBoxLayout *rangeLayout;
	QHBoxLayout *dateRangeLayout;
	QHBoxLayout *zoneLayout;
	QHBoxLayout *calendarLayout;
	QVBoxLayout *cyclistLayout;
	QVBoxLayout *mainLayout;
	QIntValidator *perfManStartValidator;
	QIntValidator *perfManSTSavgValidator;
	QIntValidator *perfManLTSavgValidator;
};

class deviceModel : public QAbstractTableModel
{

 public:
     deviceModel(QObject *parent=0);
     QObject *parent;

     // sets up the headers
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;

     // how much data do we have?
     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;

     // manipulate the data - data() gets and setData() sets (set/get might be better?)
     QVariant data(const QModelIndex &index, int role) const;
     bool setData(const QModelIndex &index, const QVariant &value, int role);

     // insert/remove and update
     void add(DeviceConfiguration &);   // add a new DeviceConfiguration
     void del();                        // add a new DeviceConfiguration
     bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
     bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());


     QList<DeviceConfiguration> Configuration;  // the actual data
 };

class DevicePage : public QWidget
{
    public:
        ~DevicePage();
        DevicePage(QWidget *parent = 0);
        void setConfigPane();
        void pairClicked(DeviceConfiguration *, QProgressDialog *);

    QList<DeviceType> devices;

    // GUI Elements
	QGroupBox *deviceGroup;
    QLabel *nameLabel;
    QLineEdit *deviceName;

    QLabel *typeLabel;
    QComboBox *typeSelector;

    QLabel *specLabel;
    QLabel *specHint;   // hints at the format for a port spec
    QLabel *profHint;   // hints at the format for profile info
    QLineEdit *deviceSpecifier;

    QLabel *profLabel;
    QLineEdit *deviceProfile;

    QCheckBox *isDefaultDownload;
    QCheckBox *isDefaultRealtime;

    QTableView *deviceList;

    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *pairButton;

    QGridLayout *leftLayout;
    QVBoxLayout *rightLayout;

    QGridLayout *inLayout;
    QVBoxLayout *mainLayout;

    deviceModel *deviceListModel;
};


#endif
