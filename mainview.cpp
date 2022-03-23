#include "mainview.h"

MainView::MainView(QWidget *parent) : QWidget(parent)
{
    Recents = new QGridLayout(this);
    setLayout(Recents);
    createWindows();
}

void MainView::createWindows()
{
    createChCards();
    createClCards();
    createRCards();
}

void MainView::createChCards()
{
    map<int, Generator>::iterator it;
    //if(availableGens.empty())
    //{
    //    QLabel empty = QLabel(emptyChar, this);
    //    Recents->addWidget(&empty);
    //}
    int position = 3;
    for( it=availableGens.begin(); it!=availableGens.end(); it++ )
    {
        try {
            CharCard* newCard = new CharCard(it->first, this);
            Recents->addWidget(newCard, (position/3)-1, position%3);
            chCards.insert(pair<int, CharCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditChar()));
            connect(newCard, &CharCard::errorCaught, this, &MainView::onError);
        }  catch (...) {
            QString error = "Card cannot be created for NPC: ";
            error.append(QString::number(it->first));
            logError(CardErr, error);
            onError(CardErr);
        }
    }
}

void MainView::createClCards()
{
    map<int, Class>::iterator it;
    int position = 3;
    for( it=availableClasses.begin(); it!=availableClasses.end(); it++ )
    {
        try {
            ClassCard* newCard = new ClassCard(it->first, this);
            Recents->addWidget(newCard, (position/3)-1, position%3);
            clCards.insert(pair<int, ClassCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditClass()));
            connect(newCard, &ClassCard::errorCaught, this, &MainView::onError);
            newCard->hide();
        } catch (...) {
            QString error = "Card cannot be created for Class: ";
            error.append(QString::number(it->first));
            logError(CardErr, error);
            onError(CardErr);
        }
    }
}

void MainView::createRCards()
{
    map<int, Race>::iterator it;
    int position = 3;
    for( it=availableRaces.begin(); it!=availableRaces.end(); it++ )
    {
        try {
            RaceCard* newCard = new RaceCard(it->first, this);
            Recents->addWidget(newCard, (position/3)-1, position%3);
            rCards.insert(pair<int, RaceCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditRace()));
            connect(newCard, &RaceCard::errorCaught, this, &MainView::onError);
            newCard->hide();
        }  catch (...) {
            QString error = "Card cannot be created for Race: ";
            error.append(QString::number(it->first));
            logError(CardErr, error);
            onError(CardErr);
        }
    }
}

void MainView::refreshChars()
{
    show_chars();

    // delete all cards
    map<int, CharCard*>::iterator card;
    for( card = chCards.begin(); card != chCards.end(); card++ )
    {
        Recents->removeWidget(card->second);
        delete card->second;
    }
    chCards.clear();

    // recreate all cards
    map<int, Generator>::iterator it;
    int position = 3;
    for( it = availableGens.begin(); it != availableGens.end(); it++ )
    {
        CharCard* newCard = new CharCard(it->first, this);
        try {
            Recents->addWidget(newCard, (position/3)-1, position%3);
            chCards.insert(pair<int, CharCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditChar()));
            connect(newCard, &CharCard::errorCaught, this, &MainView::onError);
        }  catch (...) {
            QString error = "Card cannot be created for NPC: ";
            error.append(QString::number(it->first));
            logError(CardErr, error);
            onError(CardErr);
        }
    }
}

void MainView::refreshClass()
{
    show_class();

    // delete all cards
    map<int, ClassCard*>::iterator card;
    for( card = clCards.begin(); card != clCards.end(); card++ )
    {
        Recents->removeWidget(card->second);
        delete card->second;
    }
    clCards.clear();

    // recreate all cards
    map<int, Class>::iterator it;
    int position = 3;
    for( it = availableClasses.begin(); it != availableClasses.end(); it++ )
    {
        ClassCard* newCard = new ClassCard(it->first, this);
        try {
            Recents->addWidget(newCard, (position/3)-1, position%3);
            clCards.insert(pair<int, ClassCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditClass()));
            connect(newCard, &ClassCard::errorCaught, this, &MainView::onError);
        }  catch (...) {
            QString error = "Card cannot be created for Class: ";
            error.append(QString::number(it->first));
            logError(CardErr, error);
            onError(CardErr);
        }
    }
}

void MainView::refreshRace()
{
    show_race();

    // delete all cards
    map<int, RaceCard*>::iterator card;
    for( card = rCards.begin(); card != rCards.end(); card++ )
    {
        Recents->removeWidget(card->second);
        delete card->second;
    }
    clCards.clear();

    // recreate all cards
    map<int, Race>::iterator it;
    int position = 3;
    for( it = availableRaces.begin(); it != availableRaces.end(); it++ )
    {
        RaceCard* newCard = new RaceCard(it->first, this);
        try {
            Recents->addWidget(newCard, (position/3)-1, position%3);
            rCards.insert(pair<int, RaceCard*>(it->first, newCard));
            position++;
            connect(newCard, SIGNAL(widgetClicked()), this, SLOT(on_EditClass()));
            connect(newCard, &RaceCard::errorCaught, this, &MainView::onError);
        }  catch (...) {
            QString error = "Card cannot be created for Class: ";
            error.append(QString::number(it->first));
            logError(CardErr, error);
            onError(CardErr);
        }
    }
}

void MainView::show_chars()
{
    if(!chCards.empty() && chCards.begin()->second->isHidden())
    {
        if( !clCards.empty())
        {
            map<int, ClassCard*>::iterator cIt;
            for( cIt = clCards.begin(); cIt != clCards.end(); cIt++ )
            {
                cIt->second->hide();
            }
        }

        if( !rCards.empty() )
        {
            map<int, RaceCard*>::iterator rIt;
            for( rIt = rCards.begin(); rIt != rCards.end(); rIt++ )
            {
                rIt->second->hide();
            }
        }

        map<int, CharCard*>::iterator it;
        for( it = chCards.begin(); it != chCards.end(); it++ )
        {
            it->second->show();
            it->second->refreshCard();
        }
    }
    else if( chCards.empty() )
    {
        // Add "No characters here message
        if( !clCards.empty())
        {
            map<int, ClassCard*>::iterator cIt;
            for( cIt = clCards.begin(); cIt != clCards.end(); cIt++ )
            {
                cIt->second->hide();
            }
        }

        if( !rCards.empty() )
        {
            map<int, RaceCard*>::iterator rIt;
            for( rIt = rCards.begin(); rIt != rCards.end(); rIt++ )
            {
                rIt->second->hide();
            }
        }
    }
}

void MainView::show_class()
{
    if(!clCards.empty() && clCards.begin()->second->isHidden())
    {
        if( !chCards.empty() )
        {
            map<int, CharCard*>::iterator it;
            for( it = chCards.begin(); it != chCards.end(); it++ )
            {
                it->second->hide();
            }
        }

        if( !rCards.empty() )
        {
            map<int, RaceCard*>::iterator rIt;
            for( rIt = rCards.begin(); rIt != rCards.end(); rIt++ )
            {
                rIt->second->hide();
            }
        }

        map<int, ClassCard*>::iterator cIt;
        for( cIt = clCards.begin(); cIt != clCards.end(); cIt++ )
        {
            cIt->second->show();
            cIt->second->refreshCard();
        }
    }
    else if( clCards.empty() )
    {
        // Add "No classes here message
        if( !chCards.empty() )
        {
            map<int, CharCard*>::iterator it;
            for( it = chCards.begin(); it != chCards.end(); it++ )
            {
                it->second->hide();
            }
        }

        if( !rCards.empty() )
        {
            map<int, RaceCard*>::iterator rIt;
            for( rIt = rCards.begin(); rIt != rCards.end(); rIt++ )
            {
                rIt->second->hide();
            }
        }
    }
}

void MainView::show_race()
{
    if(!rCards.empty() && rCards.begin()->second->isHidden())
    {
        if( !chCards.empty() )
        {
            map<int, CharCard*>::iterator it;
            for( it = chCards.begin(); it != chCards.end(); it++ )
            {
                it->second->hide();
            }
        }

        if( !clCards.empty())
        {
            map<int, ClassCard*>::iterator cIt;
            for( cIt = clCards.begin(); cIt != clCards.end(); cIt++ )
            {
                cIt->second->hide();
            }
        }

        map<int, RaceCard*>::iterator rIt;
        for( rIt = rCards.begin(); rIt != rCards.end(); rIt++ )
        {
            rIt->second->show();
            rIt->second->refreshCard();
        }
    }
    else if( rCards.empty() )
    {
        // Add "No races here message
        if( !chCards.empty() )
        {
            map<int, CharCard*>::iterator it;
            for( it = chCards.begin(); it != chCards.end(); it++ )
            {
                it->second->hide();
            }
        }

        if( !clCards.empty())
        {
            map<int, ClassCard*>::iterator cIt;
            for( cIt = clCards.begin(); cIt != clCards.end(); cIt++ )
            {
                cIt->second->hide();
            }
        }
    }
}

void MainView::display_char(int toDisp)
{
    cEdit = new editchar(toDisp, this);
    connect(cEdit, &editchar::errorCaught, this, &MainView::onError);
    connect(cEdit, &QDialog::accepted, this, &MainView::refreshChars);
    connect(cEdit, &QDialog::rejected, this, &MainView::refreshChars);
    cEdit->show();
}

void MainView::display_class(int toDisp)
{
    if( toDisp == -1 )
    {
        clEdit = new NewClass(this);
    }
    else
    {
        clEdit = new NewClass(toDisp, this);
        //connect(clEdit, &QDialog::rejected, this, &MainView::on_DelClass);
    }
    connect(clEdit, &NewClass::errorCaught, this, &MainView::onError);
    connect(clEdit, &QDialog::accepted, this, &MainView::refreshClass);
    clEdit->show();
}

void MainView::display_race(int toDisp)
{
    if( toDisp == -1 )
    {
        rEdit = new NewRace(this);
    }
    else
    {
        rEdit = new NewRace(toDisp, this);
        // connect delete
    }
    //connect(rEdit, &NewRace::errorCaught, this, &MainView::onError);
    connect(rEdit, &QDialog::accepted, this, &MainView::refreshRace);
    rEdit->show();
}

void MainView::on_EditChar()
{
    CharCard* card = qobject_cast<CharCard*>(sender());
    if( card != NULL )
    {
        display_char(card->getId());
    }
}

void MainView::on_EditClass()
{
    ClassCard* card = qobject_cast<ClassCard*>(sender());
    if( card != NULL )
    {
        display_class(card->getId());
    }
}

void MainView::on_EditRace()
{
    RaceCard* card = qobject_cast<RaceCard*>(sender());
    if( card != NULL )
    {
        display_race(card->getId());
    }
}

void MainView::on_Refresh()
{
    map<int, CharCard*>::iterator it;
    for( it = chCards.begin(); it != chCards.end(); it++ )
    {
        it->second->refreshCard();
    }

    map<int, ClassCard*>::iterator cIt;
    for( cIt = clCards.begin(); cIt != clCards.end(); cIt++ )
    {
        cIt->second->refreshCard();
    }

    map<int, RaceCard*>::iterator rIt;
    for( rIt = rCards.begin(); rIt != rCards.end(); rIt++ )
    {
        rIt->second->refreshCard();
    }
}

void MainView::onError(int code)
{
    emit errorCaught(code);
}
