#include "editchar.h"
#include "ui_editchar.h"

editchar::editchar(int toDisplay, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editchar)
{
    ui->setupUi(this);

    generator = toDisplay;

    ui->Name->setText(QString::fromStdString(availableGens.at(toDisplay).getsetName()));
    ui->LevelSpin->setValue(availableGens.at(toDisplay).getsetLevel());
    ui->HPSpin->setValue(availableGens.at(toDisplay).getsetHP());

    // set up combo boxes
    map<int, Race>::iterator raceIt;
    for( raceIt=availableRaces.begin(); raceIt!=availableRaces.end(); raceIt++ )
    {
        //racePos.push_back(raceIt->first);
        ui->RaceBox->addItem(QString::fromStdString(raceIt->second.getsetName()));
    }
    map<int, Class>::iterator classIt;
    for( classIt=availableClasses.begin(); classIt != availableClasses.end(); classIt++ )
    {
        //classPos.push_back(classIt->first);
        ui->ClassBox->addItem(QString::fromStdString(classIt->second.getsetName()));
    }
    for( int i=0; i < (int)alignStrs.size(); i++ )
    {
        ui->AlignBox->addItem(QString::fromStdString(alignStrs.at(i)));
    }

    // set combo box values
    ui->ClassBox->setCurrentIndex(availableGens.at(toDisplay).getsetClass());
    ui->RaceBox->setCurrentIndex(availableGens.at(toDisplay).getsetRace());

    // Convert from ALIGN in trinary to 0-8
    // This can be done by converting the align values to decimal. Multiply the 3s place by 3 and divide by 10 and add to the 1s place. Thus 12 = 3 + 2 = 5, and 22 = 6 + 2 = 8
    int morality = availableGens[toDisplay].getsetAlign().at(0) * 3;
    int charAlign = morality + availableGens[toDisplay].getsetAlign().at(1);
    ui->AlignBox->setCurrentIndex(charAlign);

    // set stats
    ui->StrSpin->setValue(availableGens.at(toDisplay).getsetStats().at(STRENGTH));
    ui->DexSpin->setValue(availableGens.at(toDisplay).getsetStats().at(DEXTERITY));
    ui->ConSpin->setValue(availableGens.at(toDisplay).getsetStats().at(CONSTITUTION));
    ui->IntSpin->setValue(availableGens.at(toDisplay).getsetStats().at(INTELLIGENCE));
    ui->WisSpin->setValue(availableGens.at(toDisplay).getsetStats().at(WISDOM));
    ui->ChaSpin->setValue(availableGens.at(toDisplay).getsetStats().at(CHARISMA));

    // set up personality boxes
    ui->PosPerson->setText(availableGens.at(toDisplay).getPersonTrait(0));
    ui->NeuPerson->setText(availableGens.at(toDisplay).getPersonTrait(1));
    ui->NegPerson->setText(availableGens.at(toDisplay).getPersonTrait(2));

    // connect buttons
    connect(ui->ApplyButton, &QPushButton::clicked, this, &editchar::onOk);
    connect(ui->DelButton, &QPushButton::clicked, this, &editchar::onDelete);
    connect(ui->NewName, &QPushButton::clicked, this, &editchar::onNewName);

    // connect changeable elements to onEdit
    connect(ui->Name, &QLineEdit::textEdited, this, &editchar::onEdit);
    connect(ui->LevelSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->HPSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->RaceBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEdit()));
    connect(ui->ClassBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEdit()));
    connect(ui->AlignBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEdit()));
    connect(ui->StrSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->DexSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->ConSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->IntSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->WisSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->ChaSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &editchar::onEdit);
    connect(ui->PosPerson, &QLineEdit::textEdited, this, &editchar::onEdit);
    connect(ui->NeuPerson, &QLineEdit::textEdited, this, &editchar::onEdit);
    connect(ui->NegPerson, &QLineEdit::textEdited, this, &editchar::onEdit);
}

editchar::~editchar()
{
    delete ui;
}

void editchar::onEdit()
{
    if(!hasBeenEdited)
    {
        disconnect(ui->ApplyButton, &QPushButton::clicked, this, &QWidget::close);
        // connect Apply button to a different function, the apply button function. Also change button text
        ui->ApplyButton->setText("Save");
        connect(ui->ApplyButton, &QPushButton::clicked, this, &editchar::onSave);
        hasBeenEdited = true;
    }
}

void editchar::onDelete()
{
    QTextStream out(stdout);

    map<int, Generator>::iterator it;
    it = availableGens.find(generator);
    try {
        // remove NPC object from SQL
        removeFromSQL(availableGens.at(generator));
        availableGens.erase(it);
    }  catch (...) {
        QString error = "Could not remove NPC: ";
        error.append(QString::number(generator));
        logError(removeError, error);
        emit errorCaught(removeError);
    }
    QDialog::reject();
}

void editchar::onNewName()
{
    int race = ui->RaceBox->currentIndex();
    int type = availableRaces.at(race).getsetNameType();
    string name = createName(type);
    if( name.compare("Error") == 0)
    {
        // emit error
        //
        // set Default: "Jeff"
        name = "Jeff";
    }
    ui->Name->setText(QString::fromStdString(name));
}

void editchar::onSave()
{
    // get values from each element, and edit Generator with them
    availableGens.at(generator).getsetName(SET, ui->Name->text().toStdString());
    availableGens.at(generator).getsetLevel(SET, ui->LevelSpin->value());
    availableGens.at(generator).getsetHP(SET, ui->HPSpin->value());
    //availableGens.at(generator).getsetClass(SET, classPos.at(ui->ClassBox->currentIndex()));
    //availableGens.at(generator).getsetRace(SET, racePos.at(ui->RaceBox->currentIndex()));

    // turn alignment into trinary. Add values into an array<int, 2> and set that as the NPC's alignment
    int morality = ui->AlignBox->currentIndex();
    int belief = morality % 3;
    array<int, 2> align = {(morality-belief)/3, belief};
    availableGens.at(generator).getsetAlign(SET, &align);

    // Make array<int, 6> of stat values from STR to CHA
    array<int, 6> stats = {ui->StrSpin->value(), ui->DexSpin->value(), ui->ConSpin->value(), ui->IntSpin->value(), ui->WisSpin->value(), ui->ChaSpin->value()};
    availableGens.at(generator).getsetStats(SET, &stats);

    // save personality changes
    QString personalityTratis;
    personalityTratis.append(ui->PosPerson->text());
    personalityTratis.append(", ");
    personalityTratis.append(ui->NeuPerson->text());
    personalityTratis.append(", ");
    personalityTratis.append(ui->NegPerson->text());
    personalityTratis.append(", ");
    availableGens.at(generator).getsetPerson(SET, personalityTratis);

    // save NPC in SQL, overwrite current SQL object
    //saveGenerator(availableGens.at(generator));

    // close window and refresh char list
    QDialog::accept();
}

void editchar::onOk()
{
    QDialog::accept();
}
